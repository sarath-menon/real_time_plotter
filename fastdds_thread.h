#ifndef FASTDDS_THREAD_H
#define FASTDDS_THREAD_H

#include "PositionPubSubTypes.h"
#include "default_participant.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "qcustomplot.h"
#include "sub_variables.h"
#include <QDebug>
#include <QThread>

class fastdds_thread : public QThread {
  Q_OBJECT

public:
  explicit fastdds_thread(QCustomPlot *plot, QObject *parent = nullptr);
  ~fastdds_thread();

  void run();

public:
  // Create doamin participant
  std::unique_ptr<DefaultParticipant> dp;

  // Motion capture data subscriber
  // std::unique_ptr<DDSSubscriber> mocap_sub;
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *mocap_sub;

private:
  QCustomPlot *plot_;

  QTimer dataTimer;

public slots:
  void realtimePlot();
};

#endif // FASTDDS_THREAD_H
