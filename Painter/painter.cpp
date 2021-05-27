#include "painter.h"

Painter::Painter(QPaintDevice* paint_device, const QSizeF& world_size) :
    QPainter(paint_device), world_size_(world_size) {
  QTransform transform;
  transform.scale(paint_device->width() / world_size.width(),
                  paint_device->height() / world_size.height());
  this->setTransform(transform);
  this->setRenderHints(
      QPainter::Antialiasing |
          QPainter::SmoothPixmapTransform |
          QPainter::TextAntialiasing);
}
