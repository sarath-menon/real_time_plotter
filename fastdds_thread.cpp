#include "fastdds_thread.h"

fastdds_thread::fastdds_thread(QCustomPlot *plot, QObject *parent)
    : QThread(parent) { // Fastdds
  // Create domain participant
  dp = std::make_shared<DefaultParticipant>(0, "godot_visualizer_qos");

  // Create  subscriber
  mocap_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &sub::mocap_msg,
                                "mocap_pose", dp->participant());

  // initialize  subscriberDefaultParticipant
  mocap_sub->init();

  plot_ = plot;

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(plot_->xAxis, SIGNAL(rangeChanged(QCPRange)), plot_->xAxis2,
          SLOT(setRange(QCPRange)));
  connect(plot_->yAxis, SIGNAL(rangeChanged(QCPRange)), plot_->yAxis2,
          SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimePlot()));
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void fastdds_thread::run() { // Blocks until new data is available

  for (;;) {
    mocap_sub->listener->wait_for_data();
    qInfo() << " Received data";

    // qv_y.append(sub::mocap_msg.pose.position.x);
    // qv_x.append(counter);

    // plot_->graph(0)->setData(qv_x, qv_y);

    // // plot_->rescaleAxes();
    // plot_->replot();
    // plot_->update();

    counter++;
  }

  //   emit valueChanged();
};

fastdds_thread::~fastdds_thread() { // Fastdds
  delete mocap_sub;
}

void fastdds_thread::realtimePlot() {
  static QTime time(QTime::currentTime());
  static double lastPointKey = 0;

  // calculate time elapsed since start of demo, in seconds
  double key = time.elapsed() / 1000.0;

  if (key - lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    plot_->graph(0)->addData(key, sub::mocap_msg.pose.position.x);

    // rescale value (vertical) axis to fit the current data:
    plot_->graph(0)->rescaleValueAxis();
    // plot_->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }

  // make key axis range scroll with the data (at a constant range size of 8):
  plot_->xAxis->setRange(key, 10, Qt::AlignRight);
  plot_->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;

  //   if (key - lastFpsKey > 2) // average fps over 2 seconds
  //   {
  //     ui->statusBar->showMessage(
  //         QString("%1 FPS, Total Data points: %2")
  //             .arg(frameCount / (key - lastFpsKey), 0, 'f', 0)
  //             .arg(plot_->graph(0)->data()->size() +
  //                  plot_->graph(1)->data()->size()),
  //         0);
  //     lastFpsKey = key;
  //     frameCount = 0;
  //   }
}