#include "ToolBar.h"

ToolBar::ToolBar(QWidget* parent) : QToolBar(parent), buttonsChecked(0)
{
  setMovable(false);
  setFloatable(false);
  setContextMenuPolicy(Qt::PreventContextMenu);

  pbfigure1 = new QPushButton("FIGURE17");
  pbfigure1->setCheckable(true);

  pbfigure2 = new QPushButton("FIGURE27");
  pbfigure2->setCheckable(true);
  
  pbpaint = new QPushButton("PAINT");
  pbpaint->setEnabled(false);
  
  pbdelete = new QPushButton("DELETE");
  pbdelete->setEnabled(false);
  
  addWidget(pbfigure1);
  addWidget(pbfigure2);
  addSeparator();

  addWidget(pbpaint);
  addSeparator();
  
  addWidget(pbdelete);

  connect(pbfigure1, SIGNAL(toggled(bool)), this, SLOT(ToggledSlot(bool)));
  connect(pbfigure2, SIGNAL(toggled(bool)), this, SLOT(ToggledSlot(bool)));

  connect(pbpaint, SIGNAL(clicked()), this, SLOT(PaintSlot()));
  connect(pbdelete, SIGNAL(clicked()), this, SLOT(DeleteSlot()));
}

void ToolBar::ToggledSlot(bool checked)
{
  if (checked)
  {
    buttonsChecked++;
  }
  else
  {
    buttonsChecked--;
  }
  if (buttonsChecked == 0 || buttonsChecked == 2)
  {
    pbpaint->setEnabled(false);
  }
  else
  {
    pbpaint->setEnabled(true);
  }
}

void ToolBar::PaintSlot()
{
  if (pbfigure1->isChecked())
  {
    emit PaintSignal(17);
  }
  else
  {
    emit PaintSignal(27);
  }

}

void ToolBar::DeleteSlot()
{
  pbdelete->setEnabled(false);
  emit DeleteSignal();
}

void ToolBar::EnableDeleteButtonSlot()
{
  pbdelete->setEnabled(true);
}

void ToolBar::DisableDeleteButtonSlot()
{
  pbdelete->setEnabled(false);
}
