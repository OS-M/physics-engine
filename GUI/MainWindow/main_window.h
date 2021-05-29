#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>
#include <QMouseEvent>
#include "GUI/View/view.h"
#include "QTimer"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(int64_t tickrate, std::shared_ptr<Engine> engine);

  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

 private:
  View view_;
  QTimer ticker_;
  QElapsedTimer delta_time_measurer_;
};

#endif  // MAIN_WINDOW_H_
