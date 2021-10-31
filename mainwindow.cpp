#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Set plot properties
  ui->x_plot->addGraph();
  ui->y_plot->addGraph();
  ui->z_plot->addGraph();

  ui->x_plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
  ui->y_plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
  ui->z_plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");

  ui->x_plot->xAxis->setTicker(timeTicker);
  ui->y_plot->xAxis->setTicker(timeTicker);
  ui->z_plot->xAxis->setTicker(timeTicker);

  ui->x_plot->axisRect()->setupFullAxesBox();
  ui->y_plot->axisRect()->setupFullAxesBox();
  ui->z_plot->axisRect()->setupFullAxesBox();

  // Set axes properties
  ui->x_plot->yAxis->setRange(-x_range, x_range);
  ui->x_plot->yAxis->setRange(-y_range, y_range);
  ui->x_plot->yAxis->setRange(-z_range, z_range);

  ui->x_plot->yAxis->setLabel("x_position");
  ui->y_plot->yAxis->setLabel("y_position");
  ui->z_plot->yAxis->setLabel("z_position");

  ui->x_plot->xAxis->setLabel("time");
  ui->y_plot->xAxis->setLabel("time");
  ui->z_plot->xAxis->setLabel("time");

  obj = std::make_unique<fastdds_thread>(ui->x_plot, ui->y_plot, ui->z_plot);
  obj->start();
}

MainWindow::~MainWindow() { delete ui; }

// Clear all plots
void MainWindow::on_clear_btn_clicked() {
  ui->x_plot->graph(0)->data()->clear();
  ui->y_plot->graph(0)->data()->clear();
  ui->z_plot->graph(0)->data()->clear();
}
