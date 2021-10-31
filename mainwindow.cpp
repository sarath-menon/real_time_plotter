#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Set plot properties

  ui->plot->addGraph();
  ui->plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  ui->plot->xAxis->setTicker(timeTicker);
  ui->plot->axisRect()->setupFullAxesBox();

  // Set axes properties
  ui->plot->yAxis->setRange(-distance_range, distance_range);
  ui->plot->xAxis->setLabel("time");
  ui->plot->yAxis->setLabel("position");

  obj = std::make_unique<fastdds_thread>(ui->plot);
  obj->start();
}

MainWindow::~MainWindow() { delete ui; }

// Clear all plots
void MainWindow::on_clear_btn_clicked() { ui->plot->graph(0)->data()->clear(); }
