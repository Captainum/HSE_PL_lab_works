#ifndef FIGURE17_H
#define FIGURE17_H

#include "AbstractFigure.h"

class Figure17 : public AbstractFigure
{
Q_OBJECT

private:
  Parameters17 params17;

protected:
  virtual void paintEvent(QPaintEvent*);

public:
  Figure17(size_t id, int w, int h, double ang, Parameters17 params17, QWidget* parent = 0) : AbstractFigure(17, id, w, h, ang, parent), params17(params17) {}
  ~Figure17() = default;

public:
  std::pair<int, int> getPS() const override;
  Parameters17 getParams17() const;
  void setParams17(Parameters17 params17);
};

#endif //FIGURE17_H
