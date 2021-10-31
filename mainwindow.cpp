#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Set plot properties

  ui->plot->addGraph();
  ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
  ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  ui->plot->xAxis->setTicker(timeTicker);
  ui->plot->axisRect()->setupFullAxesBox();
  ui->plot->yAxis->setRange(-5, 5);

  ui->plot->xAxis->setLabel("time");
  ui->plot->yAxis->setLabel("position");

  //   // make left and bottom axes transfer their ranges to right and top axes:
  //   connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)),
  //   ui->plot->xAxis2,
  //           SLOT(setRange(QCPRange)));
  //   connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)),
  //   ui->plot->yAxis2,
  //           SLOT(setRange(QCPRange)));

  //   // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  //   connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimePlot()));
  //   dataTimer.start(0); // Interval 0 means to refresh as fast as possible

  //   ui->plot->xAxis->setRange(0, 100);
  //   ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
  //                             QCP::iSelectPlottables);

  obj = new fastdds_thread(ui->plot);
  obj->start();
}

MainWindow::~MainWindow() {
  delete ui;
  delete obj;
  //   delete mocap_sub;
}

void MainWindow::addpoint(double x, double y) {
  qv_x.append(x);
  qv_y.append(y);
}

void MainWindow::cleardata() {
  qv_x.clear();
  qv_y.clear();
}

void MainWindow::plot() {
  ui->plot->graph(0)->setData(qv_x, qv_y);
  //   ui->plot->rescaleAxes();
  ui->plot->replot();
  ui->plot->update();
}

void MainWindow::on_add_btn_clicked() {
  addpoint(sub::mocap_msg.pose.position.x, 5);
  plot();
}

void MainWindow::on_clear_btn_clicked() {
  cleardata();
  plot();
}
