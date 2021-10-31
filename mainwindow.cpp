#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set plot properties
    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot->xAxis->setLabel("time");
    ui->plot->xAxis->setLabel("time");
    ui->plot->yAxis->setLabel("position");
    ui->plot->xAxis->setRange(-5,5);
    ui->plot->yAxis->setRange(0,10);

    ui->plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addpoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void MainWindow::cleardata()
{
    qv_x.clear();
    qv_y.clear();
}

void MainWindow::plot()
{
ui->plot->graph(0)->setData(qv_x, qv_y);
ui->plot->rescaleAxes();
ui->plot->replot();
ui->plot->update();
}


void MainWindow::on_add_btn_clicked()
{
    addpoint(ui->disp_1->value(), ui->disp_2->value());
    plot();
}


void MainWindow::on_clear_btn_clicked()
{
    cleardata();
    plot();
}

