#include "Figure27.h"

#include <QPainter>

void Figure27::paintEvent(QPaintEvent*)
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
  painter.drawArc(w - params27.AR, -params27.AR, params27.AR * 2, params27.AR * 2, 180 * 16, 90 * 16);
  painter.drawLine(w, params27.AR, w, h - params27.BX);
  //B
  painter.drawLine(w, h - params27.BX, w - params27.BX, h);
  painter.drawLine(w - params27.BX, h, params27.CX, h);
  //C
  painter.drawLine(params27.CX, h, 0, h - params27.CX);
  painter.drawLine(0, h - params27.CX, 0, params27.DX);
  //D
  painter.drawLine(0, params27.DX, params27.DX, 0);
  painter.drawLine(params27.DX, 0, w / 2 - params27.EQ / 2, 0);
  //E
  painter.drawArc(w / 2 - params27.EQ / 2, -params27.EQ / 2, params27.EQ, params27.EQ, 0, -180 * 16);
  painter.drawLine(w / 2 + params27.EQ / 2, 0, w - params27.AR, 0);
  
  w+=1;
  h+=1;
}

std::pair<int, int> Figure27::getPS() const
{
  double pi = 3.141592;
  double perimeter = (w + h) * 2 - params27.AR * 2 - params27.BX * 2 - params27.CX * 2 - 
              params27.DX * 2 - params27.EQ;
  perimeter += pi * params27.AR / 2 + pi * sqrt(2) * params27.BX +
               sqrt(2) * params27.CX + sqrt(2) * params27.DX + pi * params27.EQ;

  double square = w * h - pi * params27.AR * params27.AR / 4 - params27.BX * params27.BX / 2.0 -
                   params27.CX * params27.CX / 2.0 - params27.DX * params27.DX / 2.0 -
                   pi * params27.EQ * params27.EQ / 8.0;
  return {(int) perimeter, (int) square};
}

Parameters27 Figure27::getParams27() const
{
  return params27;
}

void Figure27::setParams27(Parameters27 params27)
{
  this->params27 = params27;
}
