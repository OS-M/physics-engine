#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QPaintEvent>
#include "Engine/engine.h"
#include "Painter/painter.h"

class View : public QWidget {
  Q_OBJECT

 public:
  View(QWidget* parent, int64_t tickrate, std::shared_ptr<Engine> engine);

  void paintEvent(QPaintEvent* event) override;

 private:
  std::shared_ptr<Engine> engine_;
};

#endif //VIEW_H
