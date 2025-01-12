#pragma once

#include <QMessageBox>
#include <QWidget>

#include "api/qpdf.hpp"
#include "interface/utils/fileDialog.hpp"
#include "interface/utils/pdfListItemWidget.hpp"
#include "interface/utils/pdfUtils.hpp"

namespace Ui {
class MergePage;
}

class MergePage : public QWidget {
  Q_OBJECT

public:
  explicit MergePage(QWidget *parent = nullptr);
  ~MergePage();

signals:
  void setPage(int newPage);
  void runAsyncFunction(std::function<void()> asyncFunction);
  void showMessageSignal(const QString &message, int timeout);

private slots:
  void on_tbtn_return_clicked();

  void on_btn_Madd_clicked();

  void on_btn_Mrm_clicked();

  void on_btn_Mup_clicked();

  void on_btn_Mdown_clicked();

  void on_tbtn_pdfMerge_clicked();

private:
  Ui::MergePage *ui;
};
