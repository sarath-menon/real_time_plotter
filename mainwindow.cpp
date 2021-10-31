#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Set plot properties

  ui->x_plot->addGraph();
  ui->x_plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  ui->x_plot->xAxis->setTicker(timeTicker);
  ui->x_plot->axisRect()->setupFullAxesBox();

  // Set axes properties
  ui->x_plot->yAxis->setRange(-distance_range, distance_range);
  ui->x_plot->xAxis->setLabel("time");
  ui->x_plot->yAxis->setLabel("x_position");

  obj = std::make_unique<fastdds_thread>(ui->x_plot);
  obj->start();
}

MainWindow::~MainWindow() { delete ui; }

// Clear all plots
void MainWindow::on_clear_btn_clicked() {
  ui->x_plot->graph(0)->data()->clear();
}
