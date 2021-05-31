#include "main_window.h"

#include <utility>

#include "Painter/painter.h"
#include "PhysicsObject/PolygonObject/polygon_object.h"

MainWindow::MainWindow(int64_t tickrate, const std::shared_ptr<Engine>& engine)
    :
    view_(this, tickrate, engine), engine_(engine) {
  this->resize(engine->GetWorldSize().expandedTo(QSizeF(1000, 1000)).toSize());
  ticker_.start(1000 / tickrate);
  connect(&ticker_, &QTimer::timeout,
          [this]() {
            this->repaint();
          });
  delta_time_measurer_.start();
}

void MainWindow::paintEvent(QPaintEvent* event) {
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
  Point point(world_transform_.map(event->pos()));
  auto obj = std::make_shared<PolygonObject>(point, 30, 40);
  engine_->AddObject(obj);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  view_.resize(event->size());
  world_transform_ = QTransform();
  world_transform_.scale(engine_->GetWorldSize().width() / this->width(),
                         engine_->GetWorldSize().height() / this->height());
}
