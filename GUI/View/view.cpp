#include "view.h"
#include <utility>

View::View(QWidget* parent, int64_t tickrate, std::shared_ptr<Engine> engine) :
    QWidget(parent), engine_(std::move(engine)) {}

void View::paintEvent(QPaintEvent* event) {
  Painter painter(this, engine_->GetWorldSize());
  for (const auto& object : *engine_->GetObjects()) {
    object->Draw(&painter);
  }
}
