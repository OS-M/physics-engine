#include <QApplication>
#include "GUI/MainWindow/main_window.h"
#include <QTimer>
#include "Engine/engine.h"
#include "GUI/MainWindow/main_window.h"
#include "PhysicsObject/PolygonObject/polygon_object.h"
#include "MessageHandler/message_handler.h"

MessageHandler message_handler(true, QtMsgType::QtDebugMsg, "client.log");

void MessageHandlerWrapper(QtMsgType type,
                           const QMessageLogContext& context,
                           const QString& message) {
  message_handler.Handle(type, context, message);
}

template<class T, class... Args>
std::shared_ptr<T> GetStaticObject(Args... args) {
  auto res = std::make_shared<T>(args...);
  res->SetStatic(true);
  return res;
}

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  qInstallMessageHandler(MessageHandlerWrapper);

  double world_width = 500.;
  double world_height = 250.;
  auto engine = std::make_shared<Engine>(64, QSizeF(world_width, world_height));

  engine->AddObject(GetStaticObject<PolygonObject>(
      Point(0, 0), 5, world_height));
  engine->AddObject(GetStaticObject<PolygonObject>(
      Point(0, world_height - 5), world_width, 5));
  engine->AddObject(GetStaticObject<PolygonObject>(
      Point(world_width - 5, 0), 5, world_height));
  engine->AddObject(GetStaticObject<PolygonObject>(
      Point(0, 0), world_width, 5));
  auto obj = GetStaticObject<PolygonObject>(
      Point(0, 150), world_width, 10);
  obj->Rotate(Point(0, 150), -M_PI / 20.);
  engine->AddObject(obj);

  MainWindow main_window(64, engine);
  main_window.show();

  return QApplication::exec();
}