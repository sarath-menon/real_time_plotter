#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PositionPubSubTypes.h"
#include "default_participant.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "sub_variables.h"
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
  QVector<double> qv_x, qv_y;

private:
  Ui::MainWindow *ui;

  // Fastdds objects
private:
  // Create doamin participant
  std::shared_ptr<DefaultParticipant> dp;

  // Motion capture data subscriber
  // std::unique_ptr<DDSSubscriber> mocap_sub;
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *mocap_sub;
};
#endif // MAINWINDOW_H
