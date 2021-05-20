#include "PaintArea.h"
#include "DialogWindow17.h"
#include "DialogWindow27.h"

#include <QPainter>

#include <array>

void PaintArea::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
  //BACKGROUND//
    auto w = width()  -1;
    auto h = height() -1;
    painter.fillRect(0,0,w,h,Qt::white);
      
    painter.drawLine(0,0,w,0);	// top
    painter.drawLine(w,0,w,h);	// right
    painter.drawLine(w,h,0,h); 	// botton
    painter.drawLine(0,h,0,0);	// left
  //////////////
}

void PaintArea::mousePressEvent(QMouseEvent*)
{
  if (selected)
  {
    figures[selectedId]->setClicked(false);
    repaint();
  }
  selected = false;
  selectedId = -1;
  
  emit DisableDeleteButtonSignal();
}

void PaintArea::resizeEvent(QResizeEvent* event)
{
  for (const auto& figure : figures)
  {
    figure.second->setParentValues(event->size().width(), event->size().height());
  }
}

PaintArea::PaintArea(QWidget* parent) : QWidget(parent)
{
  setMinimumWidth(705);
  setMinimumHeight(505);
}

void PaintArea::EnableDeleteButtonSlot(size_t id)
{
  if (selected)
  {
    figures[selectedId]->setClicked(false);
  }
  
  selected = true; 
  selectedId = id;
  
  figures[selectedId]->setClicked(true);
  
  repaint();
  
  emit EnableDeleteButtonSignal();
}

void PaintArea::AddFigureSlot(int type)
{
  if (type == 17)
  {
    Parameters17 p17(60, 60, 60, 60, 70, 70);
    figures.emplace(counter, new Figure17(counter, 300, 200, 0, std::move(p17), this));
  }
  else
  {
    Parameters27 p27(60, 60, 60, 60, 70);
    figures.emplace(counter, new Figure27(counter, 300, 200, 0, std::move(p27), this));
  }
  
  figures[counter]->setParentValues(width(), height());
  figures[counter]->show();
  
  connect(figures[counter], SIGNAL(SelectedSignal(size_t)), this, SLOT(EnableDeleteButtonSlot(size_t)));
  connect(figures[counter], SIGNAL(OpenDialogWindowSignal(AbstractFigure*)), this, SLOT(OpenDialogWindowSlot(AbstractFigure*)));
  connect(figures[counter], SIGNAL(ChangeParentMinWidthHeightSignal()), this, SLOT(ChangeMinWidthHeightSlot()));
  counter++;

  ChangeMinWidthHeightSlot();
}

void PaintArea::DeleteFigureSlot()
{
  delete figures[selectedId];
  figures.erase(selectedId);
  
  selected = false;
  selectedId = -1;

  ChangeMinWidthHeightSlot();
}

void PaintArea::OpenDialogWindowSlot(AbstractFigure* figure)
{
  if (figure->getType() == 17)
  {
    Figure17* pf = static_cast<Figure17*>(figure);
    DialogWindow17 pdw(pf, this);
    if (pdw.exec() == QDialog::Accepted)
    {
      newValues17 vals = pdw.getNewValues17();
      pf->move(vals.x, vals.y);
      pf->resize(vals.realW, vals.realH);
      pf->setParams17(vals.params17);
      pf->setValues(vals.w, vals.h, vals.ang);
    }
  }
  if (figure->getType() == 27)
  {
    Figure27* pf = static_cast<Figure27*>(figure);
    DialogWindow27 pdw(pf, this);
    if (pdw.exec() == QDialog::Accepted)
    {
      newValues27 vals = pdw.getNewValues27();
      pf->move(vals.x, vals.y);
      pf->resize(vals.realW, vals.realH);
      pf->setParams27(vals.params27);
      pf->setValues(vals.w, vals.h, vals.ang);
    }
  }
  figure->setClicked(false);
  selected = false;
  selectedId = -1;
  figure->repaint();
  
  ChangeMinWidthHeightSlot();
}

void PaintArea::ChangeMinWidthHeightSlot()
{
  auto minW = 705;
  auto minH = 505;
  
  for (const auto& figure : figures)
  {
    if (figure.second->x() + figure.second->width() > minW)
    {
      minW = figure.second->x() + figure.second->width();
    }
    if (figure.second->y() + figure.second->height() > minH)
    {
      minH = figure.second->y() + figure.second->height();
    }
  }
  
  setMinimumWidth(minW);
  setMinimumHeight(minH);
}
