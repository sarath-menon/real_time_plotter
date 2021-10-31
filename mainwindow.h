#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addpoint(double x, double y);
    void cleardata();
    void plot();

private slots:
    void on_add_btn_clicked();

    void on_clear_btn_clicked();

private:
    QVector<double> qv_x, qv_y;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
