#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fastdds_thread.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
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
  QTimer dataTimer;
  QVector<double> qv_x, qv_y;

public slots:
  void realtimePlot();

private:
  Ui::MainWindow *ui;

  // Fastdds objects
private:
  //   // Create doamin participant
  //   std::shared_ptr<DefaultParticipant> dp;

  //   // Motion capture data subscriber
  //   // std::unique_ptr<DDSSubscriber> mocap_sub;
  //   DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *mocap_sub;

  fastdds_thread *obj;
};
#endif // MAINWINDOW_H
