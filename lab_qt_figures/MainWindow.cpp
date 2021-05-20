#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  resize(600, 500);
  ptb = new ToolBar;
  ppa = new PaintArea;
  
  setCentralWidget(ppa);
  
  addToolBar(Qt::TopToolBarArea, ptb);

  connect(ptb, SIGNAL(PaintSignal(int)), ppa, SLOT(AddFigureSlot(int)));
  connect(ptb, SIGNAL(DeleteSignal()), ppa, SLOT(DeleteFigureSlot()));

  connect(ppa, SIGNAL(EnableDeleteButtonSignal()), ptb, SLOT(EnableDeleteButtonSlot()));
  connect(ppa, SIGNAL(DisableDeleteButtonSignal()), ptb, SLOT(DisableDeleteButtonSlot()));

}
