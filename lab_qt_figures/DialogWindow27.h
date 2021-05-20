#ifndef DIALOGWINDOW27_H
#define DIALOGWINDOW27_H

#include "AbstractDialogWindow.h"

#include "Figure27.h"

struct newValues27
{
  int w, h;
  double ang;
  int x, y;
  int realW, realH;
  Parameters27 params27;
};

class DialogWindow27 : public AbstractDialogWindow
{
Q_OBJECT

private:
  //size_t AX, BR, CR, DR, EQ, FP;
  
  QLineEdit* ptxt_AR;
  QLineEdit* ptxt_BX;
  QLineEdit* ptxt_CX;
  QLineEdit* ptxt_DX;
  QLineEdit* ptxt_EQ;

  newValues27 vals;
  
public:
  DialogWindow27(const Figure27* pf, QWidget* parent = 0);
  ~DialogWindow27() = default;
public:
  Parameters27 getParams27() const;
  newValues27 getNewValues27() const;

private slots:
  void CheckValuesSlot() override;
};

#endif //DIALOGWINDOW17_H
