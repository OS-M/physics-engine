#ifndef PAINTER_H_
#define PAINTER_H_

#include <QPainter>

class Painter : public QPainter {
 public:
  Painter(QPaintDevice* paint_device,
          const QSizeF& world_size);

 private:
  QSizeF world_size_;
};

#endif  // PAINTER_H_
