#include "AbstractDialogWindow.h"

#include <QRegExp>
#include <QRegExpValidator>

AbstractDialogWindow::AbstractDialogWindow(const AbstractFigure* pf, QWidget* parent) : QDialog(parent)
{
  widgetCenterX = pf->getCenter().x();
  widgetCenterY = pf->getCenter().y();
  
  figure_ang = pf->getAng();
  maxW = pf->getParentW();
  maxH = pf->getParentH();

  playout = new QVBoxLayout;
  
  auto ps = pf->getPS();
  QLabel* plbl_p = new QLabel("Perimeter: " + QString::number(ps.first));
  QLabel* plbl_s = new QLabel(" Square: " + QString::number(ps.second));
  QHBoxLayout* phbl_ps = new QHBoxLayout;
  phbl_ps->addWidget(plbl_p);
  phbl_ps->addWidget(plbl_s);
  playout->addLayout(phbl_ps);

  ptxt_w  = new QLineEdit(QString::number(pf->getW()));
  ptxt_h  = new QLineEdit(QString::number(pf->getH()));
  
  ptxt_w->setValidator(pvalidator);
  ptxt_h->setValidator(pvalidator);
  
  QLabel* plbl_w = new QLabel("&W:");
  QLabel* plbl_h = new QLabel("&H:");

  plbl_w->setBuddy(ptxt_w);
  plbl_h->setBuddy(ptxt_h);
  
  QHBoxLayout* phbl_WH = new QHBoxLayout;
  phbl_WH->addWidget(plbl_w);
  phbl_WH->addStretch(5);
  phbl_WH->addWidget(ptxt_w);
  phbl_WH->addSpacing(5); 
  phbl_WH->addWidget(plbl_h);
  phbl_WH->addStretch(5);
  phbl_WH->addWidget(ptxt_h); 
  playout->addLayout(phbl_WH);

  QLabel*       plbl_rotation = new QLabel("Rotation:");
                prb_left      = new QRadioButton("&Left");
                prb_right     = new QRadioButton("&Right");
                ptxt_ang      = new QLineEdit("0");
  
  ptxt_ang->setValidator(new QRegExpValidator(QRegExp("^[0-9]+(\\.[0-9]+)?$"), this));
  prb_left->setChecked(true);
  
  phbl_Rotation = new QHBoxLayout;
  phbl_Rotation->addWidget(plbl_rotation);
  phbl_Rotation->addWidget(prb_left);
  phbl_Rotation->addWidget(prb_right);
  phbl_Rotation->addWidget(ptxt_ang);


  QPushButton* pcmdOk     = new QPushButton("&Ok");
  QPushButton* pcmdCancel = new QPushButton("&Cancel");
  
  connect(pcmdOk, SIGNAL(clicked()), SLOT(CheckValuesSlot()));
  connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));
  
  phbl_buttons = new QHBoxLayout;
  phbl_buttons->addWidget(pcmdOk);
  phbl_buttons->addWidget(pcmdCancel);
  
  playout->setSizeConstraint(QLayout::SetFixedSize); 
  setLayout(playout);
}

AbstractDialogWindow::~AbstractDialogWindow() {}

int AbstractDialogWindow::getW() const
{
  return ptxt_w->text().toInt();
}

int AbstractDialogWindow::getH() const
{
  return ptxt_h->text().toInt();
}

double AbstractDialogWindow::getAng() const
{
  return ptxt_ang->text().toDouble();
}
