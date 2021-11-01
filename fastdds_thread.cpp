#include "fastdds_thread.h"
#include <qglobal.h>
#include <qthread.h>

fastdds_thread::fastdds_thread(QCustomPlot *x_plot, QCustomPlot *y_plot,
                               QCustomPlot *z_plot, QStatusBar *status_bar,
                               QObject *parent)
    : QThread(parent) {

  // Fastdds ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

  // Create domain participant
  dp = std::make_unique<DefaultParticipant>(0, "godot_visualizer_qos");

  // Create  subscriber
  mocap_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &sub::mocap_msg,
                                "mocap_pose", dp->participant());

  // initialize  subscriberDefaultParticipant
  mocap_sub->init();

  // Qt ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // set pointer to plots
  x_plot_ = x_plot;
  y_plot_ = y_plot;
  z_plot_ = z_plot;

  status_bar_ = status_bar;

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(x_plot_->xAxis, SIGNAL(rangeChanged(QCPRange)), x_plot_->xAxis2,
          SLOT(setRange(QCPRange)));
  connect(x_plot_->yAxis, SIGNAL(rangeChanged(QCPRange)), x_plot_->yAxis2,
          SLOT(setRange(QCPRange)));

  connect(y_plot_->xAxis, SIGNAL(rangeChanged(QCPRange)), y_plot_->xAxis2,
          SLOT(setRange(QCPRange)));
  connect(y_plot_->yAxis, SIGNAL(rangeChanged(QCPRange)), y_plot_->yAxis2,
          SLOT(setRange(QCPRange)));

  connect(z_plot_->xAxis, SIGNAL(rangeChanged(QCPRange)), z_plot_->xAxis2,
          SLOT(setRange(QCPRange)));
  connect(z_plot_->yAxis, SIGNAL(rangeChanged(QCPRange)), z_plot_->yAxis2,
          SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimePlot()));
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

fastdds_thread::~fastdds_thread() { // Fastdds
  delete mocap_sub;
}

void fastdds_thread::run() { // Blocks until new data is available

  forever {

    // Check if program close has been requeated. if so, leave loop
    if (QThread::currentThread()->isInterruptionRequested()) {
      return;
    }

    mocap_sub->listener->wait_for_data_for_ms(100);
  };
}

void fastdds_thread::realtimePlot() {
  static double last_time = 0;

  // calculate time elapsed since start of demo, in seconds

  QTime tm = QTime::currentTime();
  double cur_time = tm.msecsSinceStartOfDay() / 1000.0;
  double diff = cur_time - last_time;

  if (diff > refresh_time) // at most add point every 2 ms
  {
    // add data to lines:
    x_plot_->graph(0)->addData(cur_time, sub::mocap_msg.pose.position.x);
    y_plot_->graph(0)->addData(cur_time, sub::mocap_msg.pose.position.y);
    z_plot_->graph(0)->addData(cur_time, sub::mocap_msg.pose.position.z);

    // rescale value (vertical) axis to fit the current data:
    x_plot_->graph(0)->rescaleValueAxis();
    y_plot_->graph(0)->rescaleValueAxis();
    z_plot_->graph(0)->rescaleValueAxis();

    // x_plot_ ->>graph(1)->rescaleValueAxis(true);
    last_time = cur_time;
  }

  // make key axis range scroll with the data at ocnstant speed
  x_plot_->xAxis->setRange(cur_time, scroll_speed, Qt::AlignRight);
  y_plot_->xAxis->setRange(cur_time, scroll_speed, Qt::AlignRight);
  z_plot_->xAxis->setRange(cur_time, scroll_speed, Qt::AlignRight);

  x_plot_->replot();
  y_plot_->replot();
  z_plot_->replot();

  // calculate frames per second:
  static double lastFpsKey{};
  static int frameCount{};
  ++frameCount;

  if (cur_time - lastFpsKey > 2) // average fps over 2 seconds
  {
    status_bar_->showMessage(
        QString("%1 FPS").arg(frameCount / (cur_time - lastFpsKey), 0, 'f', 0),
        0);

    lastFpsKey = cur_time;
    frameCount = 0;
  }
}