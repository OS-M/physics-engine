#include <QApplication>
#include "GUI/MainWindow/main_window.h"
#include <QTimer>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  MainWindow main_window;
  main_window.show();
  QTimer timer;
  timer.setInterval(10);
  QObject::connect(&timer, &QTimer::timeout,
                   [&] () {
    main_window.repaint();
  });
  timer.start();

  return QApplication::exec();
}