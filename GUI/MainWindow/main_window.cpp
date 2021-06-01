#include "main_window.h"

#include "Painter/painter.h"
#include "PhysicsObject/PolygonObject/polygon_object.h"
#include "PhysicsObject/CircleObject/circle_object.h"

MainWindow::MainWindow(int64_t tickrate, const std::shared_ptr<Engine>& engine)
    :
    view_(this, tickrate, engine), engine_(engine) {
  this->resize(engine->GetWorldSize().scaled(
      QSizeF(1500, 1000),
      Qt::AspectRatioMode::KeepAspectRatio).toSize());
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
  static int counter = 0;
  Point point(world_transform_.map(event->pos()));
  std::shared_ptr<PhysicsObject> polygon_object;
  if (counter % 3 == 0) {
    polygon_object = std::make_shared<PolygonObject>(
        point, 15, 10);
    polygon_object->SetMass(2);
  } else if (counter % 3 == 1) {
    polygon_object = std::make_shared<PolygonObject>(
        std::vector<Point>{point, point + Point(20, 0),
                           point + Point(30, 15),
                           point + Point(20, 30),
                           point + Point(0, 30)});
    polygon_object->SetMass(5);
  } else {
    polygon_object = std::make_shared<CircleObject>(point, 10);
  }
  polygon_object->Rotate(point, counter);
  counter++;
  if (event->button() == Qt::MouseButton::RightButton) {
    polygon_object->SetAdditionalForce(Point(5, 0));
  }
  engine_->AddObject(polygon_object);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  view_.resize(event->size());
  world_transform_ = QTransform();
  world_transform_.scale(engine_->GetWorldSize().width() / this->width(),
                         engine_->GetWorldSize().height() / this->height());
}
