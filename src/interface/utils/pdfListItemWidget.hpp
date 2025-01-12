#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class PdfListItemWidget : public QWidget {
  Q_OBJECT
public:
  explicit PdfListItemWidget(
    const QString &filename, const QString &pageRange, QWidget *parent = nullptr);

  QString getFilename() const;
  QString getPageRange() const;
  void setPageRange(const QString &range);

private:
  QLabel *filenameLabel;
  QLineEdit *pageRangeEdit;
};