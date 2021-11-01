#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <memory>
#include <qstatusbar.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Set plot properties
  ui->x_plot->addGraph();
  ui->y_plot->addGraph();
  ui->z_plot->addGraph();

  ui->x_plot->graph(0)->setPen(QPen(QColor(255, 255, 255)));
  ui->y_plot->graph(0)->setPen(QPen(QColor(255, 255, 255)));
  ui->z_plot->graph(0)->setPen(QPen(QColor(255, 255, 255)));

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

  //   ui->x_plot->xAxis->setLabel("time");
  //   ui->y_plot->xAxis->setLabel("time");
  //   ui->z_plot->xAxis->setLabel("time");

  ui->x_plot->yAxis->setLabelColor(QColor(255, 255, 255));
  ui->y_plot->yAxis->setLabelColor(QColor(255, 255, 255));
  ui->z_plot->yAxis->setLabelColor(QColor(255, 255, 255));

  // Some settings to make plots nicer
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));

  QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(30, 30, 30));

  // Set properties
  ui->x_plot->xAxis->setBasePen(QPen(Qt::white, 1));
  ui->x_plot->yAxis->setBasePen(QPen(Qt::white, 1));
  ui->x_plot->xAxis->setTickPen(QPen(Qt::white, 1));
  ui->x_plot->yAxis->setTickPen(QPen(Qt::white, 1));
  ui->x_plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
  ui->x_plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
  ui->x_plot->xAxis->setTickLabelColor(Qt::white);
  ui->x_plot->yAxis->setTickLabelColor(Qt::white);
  ui->x_plot->xAxis->grid()->setPen(
      QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  ui->x_plot->yAxis->grid()->setPen(
      QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  ui->x_plot->xAxis->grid()->setSubGridPen(
      QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  ui->x_plot->yAxis->grid()->setSubGridPen(
      QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  ui->x_plot->xAxis->grid()->setSubGridVisible(true);
  ui->x_plot->yAxis->grid()->setSubGridVisible(true);
  ui->x_plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
  ui->x_plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
  ui->x_plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->x_plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->x_plot->setBackground(plotGradient);
  ui->x_plot->axisRect()->setBackground(axisRectGradient);

  ui->y_plot->xAxis->setBasePen(QPen(Qt::white, 1));
  ui->y_plot->yAxis->setBasePen(QPen(Qt::white, 1));
  ui->y_plot->xAxis->setTickPen(QPen(Qt::white, 1));
  ui->y_plot->yAxis->setTickPen(QPen(Qt::white, 1));
  ui->y_plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
  ui->y_plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
  ui->y_plot->xAxis->setTickLabelColor(Qt::white);
  ui->y_plot->yAxis->setTickLabelColor(Qt::white);
  ui->y_plot->xAxis->grid()->setPen(
      QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  ui->y_plot->yAxis->grid()->setPen(
      QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  ui->y_plot->xAxis->grid()->setSubGridPen(
      QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  ui->y_plot->yAxis->grid()->setSubGridPen(
      QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  ui->y_plot->xAxis->grid()->setSubGridVisible(true);
  ui->y_plot->yAxis->grid()->setSubGridVisible(true);
  ui->y_plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
  ui->y_plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
  ui->y_plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->y_plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->y_plot->setBackground(plotGradient);
  ui->y_plot->axisRect()->setBackground(axisRectGradient);

  ui->z_plot->xAxis->setBasePen(QPen(Qt::white, 1));
  ui->z_plot->yAxis->setBasePen(QPen(Qt::white, 1));
  ui->z_plot->xAxis->setTickPen(QPen(Qt::white, 1));
  ui->z_plot->yAxis->setTickPen(QPen(Qt::white, 1));
  ui->z_plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
  ui->z_plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
  ui->z_plot->xAxis->setTickLabelColor(Qt::white);
  ui->z_plot->yAxis->setTickLabelColor(Qt::white);
  ui->z_plot->xAxis->grid()->setPen(
      QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  ui->z_plot->yAxis->grid()->setPen(
      QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  ui->z_plot->xAxis->grid()->setSubGridPen(
      QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  ui->z_plot->yAxis->grid()->setSubGridPen(
      QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  ui->z_plot->xAxis->grid()->setSubGridVisible(true);
  ui->z_plot->yAxis->grid()->setSubGridVisible(true);
  ui->z_plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
  ui->z_plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
  ui->z_plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->z_plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->z_plot->setBackground(plotGradient);
  ui->z_plot->axisRect()->setBackground(axisRectGradient);

  //   // Set titlebar text
  //   ui->statusbar->showMessage(QString("selva"));

  obj = std::make_unique<fastdds_thread>(ui->x_plot, ui->y_plot, ui->z_plot,
                                         ui->statusbar);
  obj->start();
}

MainWindow::~MainWindow() {
  obj->quit();
  obj->requestInterruption();

  obj->wait();
  delete ui;
}

// Clear all plots
void MainWindow::on_clear_btn_clicked() {
  ui->x_plot->graph(0)->data()->clear();
  ui->y_plot->graph(0)->data()->clear();
  ui->z_plot->graph(0)->data()->clear();
}
