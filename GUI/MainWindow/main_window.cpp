#include "main_window.h"

#include <utility>

#include "Painter/painter.h"

MainWindow::MainWindow(int64_t tickrate, std::shared_ptr<Engine> engine) :
    view_(this, tickrate, std::move(engine)) {
  this->resize(500, 500);
  ticker_.start(1000 / tickrate);
  connect(&ticker_, &QTimer::timeout,
          [this] () {
    this->repaint();
  });
  delta_time_measurer_.start();
}

void MainWindow::paintEvent(QPaintEvent* event) {
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  view_.resize(event->size());
}
