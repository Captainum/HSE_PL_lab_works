#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

#include <unordered_map>

#include "Figure17.h"
#include "Figure27.h"

class PaintArea : public QWidget
{
Q_OBJECT

private:
  std::unordered_map<size_t, AbstractFigure*> figures;
  
  size_t counter = 0;

  bool selected = false;
  size_t selectedId;

protected:
  virtual void paintEvent(QPaintEvent*);
  virtual void mousePressEvent(QMouseEvent*);
  virtual void resizeEvent(QResizeEvent*);

public:
  PaintArea(QWidget* parent = 0);

signals:
  void EnableDeleteButtonSignal();
  void DisableDeleteButtonSignal();

public slots:
  void EnableDeleteButtonSlot(size_t id);
  void AddFigureSlot(int type);
  void DeleteFigureSlot();

  void OpenDialogWindowSlot(AbstractFigure* figure);
  void ChangeMinWidthHeightSlot();
};

#endif //PAINTAREA_H
