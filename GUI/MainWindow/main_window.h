#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>
#include <QMouseEvent>
#include "Geometry/Polygon/polygon.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

 private:
  Polygon polygon_;
};

#endif  // MAIN_WINDOW_H_
