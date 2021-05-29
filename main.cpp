#include <QApplication>
#include "GUI/MainWindow/main_window.h"
#include <QTimer>
#include "Engine/engine.h"
#include "GUI/MainWindow/main_window.h"
#include "PhysicsObject/PolygonObject/polygon_object.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  auto engine = std::make_shared<Engine>(64, QSizeF(250, 250));

  engine->AddObject(std::make_shared<PolygonObject>(Point(10, 10), 30, 40));
  auto obj = std::make_shared<PolygonObject>(Point(0, 200), 250, 50);
  obj->SetStatic(true);
  engine->AddObject(obj);

  
  MainWindow main_window(64, engine);
  main_window.show();

  return QApplication::exec();
}