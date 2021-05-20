#include "Figure17.h"

#include <QPainter>

void Figure17::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  QPen pen(QBrush(QColor(clicked() ? "blue" : "black")), 3);
  painter.setPen(pen);
  painter.setRenderHint(QPainter::Antialiasing);
  
  painter.translate(width() / 2, height() / 2);
  painter.rotate(ang);
  painter.translate(-w/2, -h/2);
  
  w-=1;
  h-=1;
  
  //A
  painter.drawLine(w - params17.AX, 0, w, params17.AX);
  painter.drawLine(w, params17.AX, w, h - params17.BR);
  //B
  painter.drawArc(w - params17.BR, h - params17.BR, params17.BR * 2, params17.BR * 2, 90 * 16, 90 * 16);
  painter.drawLine(w - params17.BR, h, w / 2 + params17.FP / 2, h);
  //C
  painter.drawArc(0, h - params17.CR * 2, params17.CR * 2, params17.CR * 2, 180 * 16, 90 * 16);
  painter.drawLine(0, h - params17.CR, 0, params17.DR);
  //D
  painter.drawArc(-params17.DR, -params17.DR, params17.DR * 2, params17.DR * 2, 0, -90* 16);
  painter.drawLine(params17.DR, 0, w / 2 - params17.EQ / 2, 0);
  //E
  painter.drawArc(w / 2 - params17.EQ / 2, -params17.EQ / 2, params17.EQ, params17.EQ, 0, -180 * 16);
  painter.drawLine(w / 2 + params17.EQ / 2, 0, w - params17.AX, 0);
  //F
  painter.drawLine(w / 2 + params17.FP / 2, h, w / 2 + params17.FP / 2, h - params17.FP / 2);
  painter.drawLine(w / 2 + params17.FP / 2, h - params17.FP / 2, w / 2 - params17.FP / 2, h - params17.FP / 2);
  painter.drawLine(w / 2 - params17.FP / 2, h - params17.FP / 2, w / 2 - params17.FP / 2, h);
  painter.drawLine(w / 2 - params17.FP / 2, h, params17.CR, h);
 
  w+=1;
  h+=1;
}

std::pair<int, int> Figure17::getPS() const
{
  double pi = 3.141592;
  double perimeter = (w + h) * 2 - params17.AX * 2 - params17.BR * 2 - params17.CR * 2 - 
              params17.DR * 2 - params17.EQ;
  perimeter += sqrt(2) * params17.AX + pi * params17.BR / 2.0 + params17.FP + 
               pi * params17.CR / 2.0 + pi * params17.DR / 2.0 + pi * params17.EQ / 4.0;

  double square = w * h -params17.AX * params17.AX / 2.0 - pi * params17.BR * params17.BR / 4.0 -
                   params17.FP * params17.FP / 2.0 - params17.CR * params17.CR * (1 - pi / 4.0) -
                   pi * params17.DR * params17.DR / 4.0 - pi * params17.EQ * params17.EQ / 8.0;
  return {(int) perimeter, (int) square};
}

Parameters17 Figure17::getParams17() const
{
  return params17;
}

void Figure17::setParams17(Parameters17 params17)
{
  this->params17 = params17;
}
