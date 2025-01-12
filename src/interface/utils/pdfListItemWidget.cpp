#include "pdfListItemWidget.hpp"

PdfListItemWidget::PdfListItemWidget(
  const QString &filename, const QString &pageRange, QWidget *parent)
    : QWidget(parent), filenameLabel(new QLabel(filename, this)),
      pageRangeEdit(new QLineEdit(this)) {
  auto layout = new QHBoxLayout(this);

  // Is there a better way to set the size policy?
  // QLabel should expand to take the rest of the space
  filenameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  // QLineEdit should adjust its size based on its content
  pageRangeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  pageRangeEdit->setText(pageRange);

  // Add widgets to the layout
  layout->addWidget(pageRangeEdit);
  layout->addWidget(filenameLabel);

  // Set stretch factors: QLineEdit gets minimal space; QLabel gets the rest
  // layout->setStretch(0, 0); // QLineEdit: no stretch
  // layout->setStretch(1, 1); // QLabel: stretch to fill remaining space

  this->setLayout(layout);
}

QString PdfListItemWidget::getFilename() const { return filenameLabel->text(); }
QString PdfListItemWidget::getPageRange() const { return pageRangeEdit->text(); }

void PdfListItemWidget::setPageRange(const QString &range) { pageRangeEdit->setText(range); }