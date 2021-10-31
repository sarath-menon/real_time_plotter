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
}

void fastdds_thread::run() { // Blocks until new data is available

  for (;;) {
    mocap_sub->listener->wait_for_data();
    qInfo() << " Received data";

    qv_y.append(sub::mocap_msg.pose.position.x);
    qv_x.append(counter);

    plot_->graph(0)->setData(qv_x, qv_y);

    plot_->rescaleAxes();
    plot_->replot();
    plot_->update();

    counter++;
  }

  //   emit valueChanged();
};

fastdds_thread::~fastdds_thread() { // Fastdds
  delete mocap_sub;
  delete plot_;
}
