#ifndef FIGURE27_H
#define FIGURE27_H

#include "AbstractFigure.h"

class Figure27 : public AbstractFigure
{
Q_OBJECT

private:
  Parameters27 params27;

protected:
  virtual void paintEvent(QPaintEvent*);

public:
  Figure27(size_t id, int w, int h, double ang, Parameters27 params27, QWidget* parent = 0) : AbstractFigure(27, id, w, h, ang, parent), params27(params27) {}
  ~Figure27() = default;

public:
  std::pair<int, int> getPS() const override;
  Parameters27 getParams27() const;
  void setParams27(Parameters27 params27);
};

#endif //FIGURE27_H
