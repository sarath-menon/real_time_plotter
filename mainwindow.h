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

private slots:
  void on_clear_btn_clicked();

private:
  Ui::MainWindow *ui;

  // Fastdds objects
private:
  std::unique_ptr<fastdds_thread> obj;

  // Parameters
  // Distance to cover in plots [meters]
  constexpr static float x_range{5};
  constexpr static float y_range{5};
  constexpr static float z_range{5};
};
#endif // MAINWINDOW_H
