#include <QCoreApplication>


#include "Handler.h"

int main(int argc, char** argv)
{
  int current_code = 0;

  do {
    QCoreApplication app(argc, argv);
    Handler h;
    current_code = app.exec();
  } while (current_code == Handler::CODE_TO_RESTART);
  
  return current_code;
}
