#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  // Main
  ui->setupUi(this);

  MenuPage *menuPage = new MenuPage(this);
  ui->stackedWidget->addWidget(menuPage);
  connect(menuPage, &MenuPage::setPage, this, &MainWindow::setPage);

  CompressPage *compressPage = new CompressPage(this);
  ui->stackedWidget->addWidget(compressPage);
  connect(compressPage, &CompressPage::setPage, this, &MainWindow::setPage);
  connect(compressPage, &CompressPage::runAsyncFunction, this, &MainWindow::runAsyncFunction);

  SplitPage *splitPage = new SplitPage(this);
  ui->stackedWidget->addWidget(splitPage);
  connect(splitPage, &SplitPage::setPage, this, &MainWindow::setPage);
  connect(splitPage, &SplitPage::runAsyncFunction, this, &MainWindow::runAsyncFunction);

  MergePage *mergePage = new MergePage(this);
  ui->stackedWidget->addWidget(mergePage);
  connect(mergePage, &MergePage::setPage, this, &MainWindow::setPage);
  connect(mergePage, &MergePage::runAsyncFunction, this, &MainWindow::runAsyncFunction);

  RotatePage *rotatePage = new RotatePage(this);
  ui->stackedWidget->addWidget(rotatePage);
  connect(rotatePage, &RotatePage::setPage, this, &MainWindow::setPage);
  connect(rotatePage, &RotatePage::runAsyncFunction, this, &MainWindow::runAsyncFunction);

  connect(this, &MainWindow::showMessageSignal, this, &MainWindow::showMessageSlot);

  // Check if qpdf is installed
  checkQpdfSlot();
}

MainWindow::~MainWindow() { delete ui; }

// Define the checkQpdfSlot function
void MainWindow::checkQpdfSlot() {
  // Check if qpdf is installed
  QString output = qpdf.checkQpdf();
  // Show output in statusbar
  emit showMessageSignal(output, 5000);
  // Change text color in statusbar
  if (output.contains("qpdf version")) {
    ui->statusBar->setStyleSheet("color: green");
  } else {
    ui->statusBar->setStyleSheet("color: red");
  }
}

// Public Slots
void MainWindow::showMessageSlot(const QString &message, int timeout) {
  qDebug() << "Showing message:" << message << "for" << timeout << "milliseconds";
  ui->statusBar->showMessage(message, timeout);
}

void MainWindow::setPage(int newPage) { ui->stackedWidget->setCurrentIndex(newPage); }

void MainWindow::runAsyncFunction(std::function<void()> asyncFunction) {
  ui->statusBar->showMessage(tr("Processing..."));

  QFuture<void> future =
    QtConcurrent::run(asyncFunction)
      .then([this] { emit showMessageSignal(tr("Success!"), 5000); })
      .onFailed(qApp,
        [this](char *error) {
          QMessageBox::warning(this, tr("ERROR"), error);
          emit showMessageSignal(tr("Failed"), 5000);
        })
      .onFailed(qApp, [this]() {
        QMessageBox::warning(this, tr("ERROR"),
          tr("An unknown error has occurred. Read the terminal output for more information"));
        emit showMessageSignal(tr("Failed"), 5000);
      });
}
