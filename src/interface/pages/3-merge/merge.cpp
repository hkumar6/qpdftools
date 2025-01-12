#include "merge.hpp"
#include "ui_merge.h"

MergePage::MergePage(QWidget *parent) : QWidget(parent), ui(new Ui::MergePage) {
  ui->setupUi(this);
}

MergePage::~MergePage() { delete ui; }

void MergePage::on_tbtn_return_clicked() { emit setPage(0); }

void MergePage::on_btn_Madd_clicked() {
  // Get filename and page count
  QString filePath = fileDialog.getOpenFileName(this);
  int pageCount = getPdfPageCount(filePath);
  if (pageCount == 0) {
    emit showMessageSignal(tr("Failed to load PDF"), 5000);
    return;
  }
  QString defaultPageRange = QString("1-%1").arg(pageCount);

  // Add the file to the list as a widget
  auto *item = new QListWidgetItem(ui->list_toMerge);
  auto *widget = new PdfListItemWidget(filePath, defaultPageRange);
  ui->list_toMerge->addItem(item);
  ui->list_toMerge->setItemWidget(item, widget);
  item->setSizeHint(widget->sizeHint());
}

void MergePage::on_btn_Mrm_clicked() {
  if ((ui->list_toMerge->currentRow() >= 0) and (ui->list_toMerge->count() > 0)) {
    delete ui->list_toMerge->takeItem(ui->list_toMerge->row(ui->list_toMerge->currentItem()));
  }
}

void MergePage::on_btn_Mup_clicked() {
  int currentRow = ui->list_toMerge->currentRow();
  qDebug() << currentRow;

  if (currentRow == -1) {
    // Show message in status bar to select an item
    emit showMessageSignal(tr("Select an item to move up"), 5000);
  } else if (currentRow == 0) {
    // Show message in status bar to select an item
    emit showMessageSignal(tr("The selected item is already at the top"), 5000);
  } else if (currentRow > 0) {
    // Get the current item and widget
    QListWidgetItem *currentItem = ui->list_toMerge->item(currentRow);
    auto *currentWidget =
      qobject_cast<PdfListItemWidget *>(ui->list_toMerge->itemWidget(currentItem));
    auto *currentItemClone = currentItem->clone();

    // Insert clone item and widget in the previous row
    ui->list_toMerge->insertItem(currentRow - 1, currentItemClone);
    ui->list_toMerge->setItemWidget(currentItemClone, currentWidget);

    // Remove the current item
    delete ui->list_toMerge->takeItem(currentRow + 1);

    // Reset focus
    ui->list_toMerge->setCurrentRow(currentRow - 1);
  }

  ui->list_toMerge->update();
}

void MergePage::on_btn_Mdown_clicked() {
  int currentRow = ui->list_toMerge->currentRow();
  int listCount = ui->list_toMerge->count();
  qDebug() << currentRow;

  if (currentRow == -1) {
    // Show message in status bar to select an item
    emit showMessageSignal(tr("Select an item to move down"), 5000);
  } else if (listCount == currentRow + 1) {
    // Show message in status bar to select an item
    emit showMessageSignal(tr("The selected item is already at the bottom"), 5000);
  } else if ((currentRow >= 0) and (listCount > 0) and (listCount != (currentRow + 1))) {
    // Get the current item and widget
    QListWidgetItem *currentItem = ui->list_toMerge->item(currentRow);
    auto *currentWidget =
      qobject_cast<PdfListItemWidget *>(ui->list_toMerge->itemWidget(currentItem));
    auto *currentItemClone = currentItem->clone();

    // Insert clone item and widget in the next row
    ui->list_toMerge->insertItem(currentRow + 2, currentItemClone);
    ui->list_toMerge->setItemWidget(currentItemClone, currentWidget);

    // Remove the current item
    delete ui->list_toMerge->takeItem(currentRow);

    // Reset focus
    ui->list_toMerge->setCurrentRow(currentRow + 1);
  }

  ui->list_toMerge->update();
}

void MergePage::on_tbtn_pdfMerge_clicked() {
  // Warning if there is only one file
  if (ui->list_toMerge->count() <= 1) {
    QMessageBox::warning(
      this, tr("Warning"), tr("You need to add two or more files to be able to merge them"));
    return;
  }

  // Set and check the output file
  QString output = fileDialog.getSaveFileName(this);
  if (output.isEmpty()) {
    emit showMessageSignal(tr("No output file selected"), 5000);
    return;
  }

  QStringList inputs;
  // Combine all the files and page ranges
  for (int i = 0; i < ui->list_toMerge->count(); ++i) {
    auto *widget =
      qobject_cast<PdfListItemWidget *>(ui->list_toMerge->itemWidget(ui->list_toMerge->item(i)));
    inputs << widget->getFilename() << widget->getPageRange();
  }

  emit runAsyncFunction([inputs, output] { qpdf.mergePDF(inputs, output); });
}