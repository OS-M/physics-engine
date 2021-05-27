#include "main_window.h"

#include "Painter/painter.h"

#include "PhysicsObject/RectangleObject/rectangle_object.h"

MainWindow::MainWindow() {
  this->resize(500, 500);
}

void MainWindow::paintEvent(QPaintEvent* event) {
  Painter painter(this, QSizeF(100, 100));
  RectangleObject rectangle_object(Point(50, 50), 20, 20);
  rectangle_object.Draw(&painter);
  auto circle = rectangle_object.GetBoundingCircle();
  painter.drawEllipse(QPointF(circle.center().x(),
                              circle.center().y()),
                      std::sqrt(circle.squared_radius()),
                      std::sqrt(circle.squared_radius()));
}
