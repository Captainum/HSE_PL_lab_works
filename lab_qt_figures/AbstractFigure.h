#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include <QWidget>
#include <QMouseEvent>

#include <utility>
#include <cmath>

#include "Parameters.h"

class AbstractFigure : public QWidget
{
Q_OBJECT

private:
  size_t type;
  size_t m_id;
  
  int parentW;
  int parentH;
  
  bool m_clicked = false;
  
  QPoint m_pos;
  QPoint m_center;

protected:
  int w, h;
  double ang;

protected:  
  virtual void mousePressEvent(QMouseEvent*);
  virtual void mouseMoveEvent(QMouseEvent*);

public:
  AbstractFigure(size_t type, size_t id, int w, int h, double ang, QWidget* parent = 0) : QWidget(parent), type(type), m_id(id), w(w), h(h), ang(ang)
  {
    move(1, 1);
    resize(w, h);
    m_center = QPoint(x() + w/2, y() + h/2);
  };
  virtual ~AbstractFigure() = 0;

public:
  bool clicked();
  void setClicked(bool);

  virtual std::pair<int, int> getPS() const = 0;
  
  size_t getType() const;
  
  size_t getId() const;

  int getW() const;
  int getH() const;
  double getAng() const;

  void setValues(int w, int h, double ang);

  QPoint getCenter() const;

  int getParentW() const;
  int getParentH() const;

  void updateCenter(const QPoint& center);

  void setParentValues(int w, int h);

signals:
  void SelectedSignal(size_t id);
  void OpenDialogWindowSignal(AbstractFigure* figure);
  void ChangeParentMinWidthHeightSignal();
};

#endif //ABSTRACTFIGURE_H
