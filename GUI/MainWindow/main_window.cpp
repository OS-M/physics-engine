#include "main_window.h"

#include "Painter/painter.h"

MainWindow::MainWindow() {
  this->resize(500, 500);
}

void MainWindow::paintEvent(QPaintEvent* event) {
  Painter painter(this, QSizeF(130, 130));
  Polygon rectangle_object
      ({Point(50, 50), Point(90, 50), Point(95, 60), Point(90, 90), Point(60, 120),
        Point(50, 90)});
  static double angle = 0.f;
  rectangle_object = rectangle_object.Rotated(Point(70, 70), angle);
  angle += 0.01;
  painter.drawPolygon(rectangle_object.ToQPolygonF());
  painter.setBrush(Qt::red);
  for (int i = 0; i < 130; i++) {
    for (int j = 0; j < 130; j++) {
      if (rectangle_object.Contains(Point(i, j))) {
        painter.drawEllipse(Point(i, j).ToQPointF(), 0.1, 0.1);
      }
    }
  }
  polygon_ = rectangle_object;
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
  Point point(event->pos());
  point.MutableX() *= 100. / this->width();
  point.MutableY() *= 100. / this->height();
  qWarning() << polygon_.Contains(point);
}
