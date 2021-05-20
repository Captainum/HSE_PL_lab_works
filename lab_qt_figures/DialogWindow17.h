#ifndef DIALOGWINDOW17_H
#define DIALOGWINDOW17_H

#include "AbstractDialogWindow.h"

#include "Figure17.h"

struct newValues17
{
  int w, h;
  double ang;
  int x, y;
  int realW, realH;
  Parameters17 params17;
};

class DialogWindow17 : public AbstractDialogWindow
{
Q_OBJECT

private:
  
  QLineEdit* ptxt_AX;
  QLineEdit* ptxt_BR;
  QLineEdit* ptxt_CR;
  QLineEdit* ptxt_DR;
  QLineEdit* ptxt_EQ;
  QLineEdit* ptxt_FP;

  newValues17 vals;

public:
  DialogWindow17(const Figure17* pf, QWidget* parent = 0);
  ~DialogWindow17() = default;

public:
  Parameters17 getParams17() const;
  newValues17 getNewValues17() const;

private slots:
  void CheckValuesSlot() override;
};

#endif //DIALOGWINDOW17_H
