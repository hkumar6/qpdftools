#pragma once

#include <QMessageBox>
#include <QWidget>

#include "api/qpdf.hpp"
#include "interface/utils/fileDialog.hpp"
#include "interface/utils/pdfUtils.hpp"

namespace Ui {
class SplitPage;
}

class SplitPage : public QWidget {
  Q_OBJECT

public:
  explicit SplitPage(QWidget *parent = nullptr);
  ~SplitPage();

signals:
  void setPage(int newPage);
  void runAsyncFunction(std::function<void()> asyncFunction);
  void showMessageSignal(const QString &message, int timeout);

private slots:
  void on_tbtn_return_clicked();

  void on_btn_selectFile_clicked();

  void on_rbtn_extractAll_clicked();

  void on_rbtn_splitRange_clicked();

  void on_spinBox_fistPage_valueChanged(int arg1);

  void on_tbtn_pdfSplit_clicked();

private:
  Ui::SplitPage *ui;
};
