#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QPushButton>

class ToolBar : public QToolBar
{
Q_OBJECT

private:
  int buttonsChecked;

  QPushButton* pbfigure1;
  QPushButton* pbfigure2;
  QPushButton* pbpaint;
  QPushButton* pbdelete;

public:
  ToolBar(QWidget* parent = 0);

signals:
  void PaintSignal(int type);
  void DeleteSignal();

private slots:
  void ToggledSlot(bool checked);
  void PaintSlot();
  void DeleteSlot();

public slots:
  void EnableDeleteButtonSlot();
  void DisableDeleteButtonSlot();
};

#endif //TOOLBAR_H
