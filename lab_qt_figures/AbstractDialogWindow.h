#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRegExp>
#include <QRegExpValidator>
#include <QRadioButton>


#include "AbstractFigure.h"

class AbstractDialogWindow : public QDialog
{
Q_OBJECT

protected:
 
  int widgetCenterX;
  int widgetCenterY;
  
  double figure_ang;
  
  int maxW, maxH;
   
  QLineEdit* ptxt_w;
  QLineEdit* ptxt_h;
  QLineEdit* ptxt_ang;

  QVBoxLayout* playout;
  
  QHBoxLayout* phbl_Rotation;
  QRadioButton* prb_left;
  QRadioButton* prb_right;

  QHBoxLayout* phbl_buttons;
  
  QRegExpValidator* pvalidator = new QRegExpValidator(QRegExp("^[1-9][0-9]+$"), this);

public:
  AbstractDialogWindow(const AbstractFigure* pf, QWidget* parent = 0);
  virtual ~AbstractDialogWindow() = 0;

public:
  int getW() const;
  int getH() const;
  double getAng() const;

protected slots:
  virtual void CheckValuesSlot() = 0;
};

#endif //DIALOGWINDOW_H
