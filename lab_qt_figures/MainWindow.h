#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ToolBar.h"
#include "PaintArea.h"

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
  ToolBar*   ptb;
  PaintArea* ppa;

public:
  MainWindow(QWidget* parent = 0);
};

#endif //MAINWINDOW_H
