#include "AbstractFigure.h"

bool AbstractFigure::clicked()
{
  return m_clicked;
}

void AbstractFigure::mousePressEvent(QMouseEvent* pe)
{
  m_pos = pe->globalPos() - pos();
  if (pe->button() == Qt::LeftButton)
  {
    m_clicked = true;
    emit SelectedSignal(m_id);
  }
  else if (pe->button() == Qt::RightButton)
  {
    m_clicked = true;
    emit SelectedSignal(m_id);
    emit OpenDialogWindowSignal(this);
  }
}

void AbstractFigure::mouseMoveEvent(QMouseEvent* pe)
{
  QPoint tmp(pos().x(), pos().y());

  if (((pe->globalPos() - m_pos).x() + width() < parentW) &&
      ((pe->globalPos() - m_pos).x() > 0))
  {
    tmp.setX((pe->globalPos() - m_pos).x());
  }
  else
  {
    m_pos.setX(pe->globalPos().x() - pos().x());
  }
  if (((pe->globalPos() - m_pos).y() + height() < parentH) &&
      ((pe->globalPos() - m_pos).y() > 0))
  {
    tmp.setY((pe->globalPos() - m_pos).y());
  }
  else
  {
    m_pos.setY(pe->globalPos().y() - pos().y());
  }
  m_center = QPoint(x() + width()/2, y() + height()/2);
  move(tmp);
  emit ChangeParentMinWidthHeightSignal();
}

AbstractFigure::~AbstractFigure() {}

void AbstractFigure::setClicked(bool clicked)
{
  m_clicked = clicked;
}

size_t AbstractFigure::getType() const
{
  return type;
}

size_t AbstractFigure::getId() const
{
  return m_id;
}

int AbstractFigure::getW() const
{
  return w;
}

int AbstractFigure::getH() const
{
  return h;
}

double AbstractFigure::getAng() const
{
  return ang;
}

void AbstractFigure::setValues(int w, int h, double ang)
{
  this->w = w;
  this->h = h;
  this->ang = ang;
}

QPoint AbstractFigure::getCenter() const
{
  return m_center;
}

int AbstractFigure::getParentW() const
{
  return parentW;
}

int AbstractFigure::getParentH() const
{
  return parentH;
}

void AbstractFigure::updateCenter(const QPoint& center)
{
  m_center = center;
}

void AbstractFigure::setParentValues(int w, int h)
{
  parentW = w;
  parentH = h;
}
