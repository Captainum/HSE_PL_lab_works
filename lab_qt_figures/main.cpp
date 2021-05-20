#include <QApplication>

#include "MainWindow.h"
#include "PaintArea.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  MainWindow w;
  w.show();
  return app.exec();
}
