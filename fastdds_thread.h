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
  explicit fastdds_thread(QCustomPlot *x_plot, QCustomPlot *y_plot,
                          QCustomPlot *z_plot, QObject *parent = nullptr);
  ~fastdds_thread();

  void run();

public:
  // Create doamin participant
  std::unique_ptr<DefaultParticipant> dp;

  // Motion capture data subscriber
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *mocap_sub;

private:
  // Pointer to plots
  QCustomPlot *x_plot_;
  QCustomPlot *y_plot_;
  QCustomPlot *z_plot_;

  // To keep track of time
  QTimer dataTimer;

  // parameters
  // Scrolling spped [lower is more]
  constexpr static int scroll_speed = 5;

public slots:
  void realtimePlot();
};

#endif // FASTDDS_THREAD_H
