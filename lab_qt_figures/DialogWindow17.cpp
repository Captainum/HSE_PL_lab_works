#include "DialogWindow17.h"

#include <QMessageBox>

#include <cmath>

DialogWindow17::DialogWindow17(const Figure17* pf, QWidget* parent) : AbstractDialogWindow(pf, parent)
{
  setWindowTitle("Choose parameters for figure17");
   
  auto params17 = pf->getParams17();
  
  ptxt_AX = new QLineEdit(QString::number(params17.AX));
  ptxt_BR = new QLineEdit(QString::number(params17.BR));
  ptxt_CR = new QLineEdit(QString::number(params17.CR));
  ptxt_DR = new QLineEdit(QString::number(params17.DR));
  ptxt_EQ = new QLineEdit(QString::number(params17.EQ));
  ptxt_FP = new QLineEdit(QString::number(params17.FP));
  
  ptxt_AX->setValidator(pvalidator);
  ptxt_BR->setValidator(pvalidator);
  ptxt_CR->setValidator(pvalidator);
  ptxt_DR->setValidator(pvalidator);
  ptxt_EQ->setValidator(pvalidator);
  ptxt_FP->setValidator(pvalidator);

  QLabel* plbl_AX = new QLabel("&AX: ");
  QLabel* plbl_BR = new QLabel("&BR:");
  QLabel* plbl_CR = new QLabel("&CR: ");
  QLabel* plbl_DR = new QLabel("&DR:");
  QLabel* plbl_EQ = new QLabel("&EQ:");
  QLabel* plbl_FP = new QLabel("&FP:");

  plbl_AX->setBuddy(ptxt_AX);
  plbl_BR->setBuddy(ptxt_BR);
  plbl_CR->setBuddy(ptxt_CR);
  plbl_DR->setBuddy(ptxt_DR);
  plbl_EQ->setBuddy(ptxt_EQ);
  plbl_FP->setBuddy(ptxt_FP);
  
  QHBoxLayout* phbl_AXBR = new QHBoxLayout;
  phbl_AXBR->addWidget(plbl_AX);
  phbl_AXBR->addStretch(5);
  phbl_AXBR->addWidget(ptxt_AX); 
  phbl_AXBR->addSpacing(5);
  phbl_AXBR->addWidget(plbl_BR);
  phbl_AXBR->addStretch(5);
  phbl_AXBR->addWidget(ptxt_BR);
  playout->addLayout(phbl_AXBR);
  
  QHBoxLayout* phbl_CRDR = new QHBoxLayout;
  phbl_CRDR->addWidget(plbl_CR);
  phbl_CRDR->addStretch(5);
  phbl_CRDR->addWidget(ptxt_CR); 
  phbl_CRDR->addSpacing(5);
  phbl_CRDR->addWidget(plbl_DR);
  phbl_CRDR->addStretch(5);
  phbl_CRDR->addWidget(ptxt_DR); 
  playout->addLayout(phbl_CRDR);
 
  QHBoxLayout* phbl_EQFP = new QHBoxLayout;
  phbl_EQFP->addWidget(plbl_EQ);
  phbl_EQFP->addStretch(5);
  phbl_EQFP->addWidget(ptxt_EQ); 
  phbl_EQFP->addSpacing(5);
  phbl_EQFP->addWidget(plbl_FP);
  phbl_EQFP->addStretch(5);
  phbl_EQFP->addWidget(ptxt_FP); 
  playout->addLayout(phbl_EQFP);

  playout->addLayout(phbl_Rotation); 
  playout->addLayout(phbl_buttons);

}

Parameters17 DialogWindow17::getParams17() const
{
  return Parameters17(ptxt_AX->text().toInt(),
                      ptxt_BR->text().toInt(),
                      ptxt_CR->text().toInt(),
                      ptxt_DR->text().toInt(),
                      ptxt_EQ->text().toInt(),
                      ptxt_FP->text().toInt());
}

newValues17 DialogWindow17::getNewValues17() const
{
  return vals;
}

void DialogWindow17::CheckValuesSlot()
{
  auto w = getW();
  auto h = getH();
  auto delta_ang = getAng();
  if (prb_left->isChecked())
  {
    delta_ang = -delta_ang;
  }
  auto ang = delta_ang + figure_ang;
  auto params17 = getParams17();

  QPoint p1(-w/2, -h/2);
  QPoint p2(w/2, -h/2);
  QPoint p3(w/2, h/2);
  QPoint p4(-w/2, h/2);
    
  double rad = ang * 3.141592 / 180.0;
  std::array<double, 4> rotMat = {cos(rad), -sin(rad),
                                  sin(rad), cos(rad)};

  QPoint p1t(p1.x() * rotMat[0] + p1.y() * rotMat[1], p1.x() * rotMat[2] + p1.y() * rotMat[3]);
  QPoint p2t(p2.x() * rotMat[0] + p2.y() * rotMat[1], p2.x() * rotMat[2] + p2.y() * rotMat[3]);
  QPoint p3t(p3.x() * rotMat[0] + p3.y() * rotMat[1], p3.x() * rotMat[2] + p3.y() * rotMat[3]);
  QPoint p4t(p4.x() * rotMat[0] + p4.y() * rotMat[1], p4.x() * rotMat[2] + p4.y() * rotMat[3]);
      
  int minX = std::min(p1t.x(), std::min(p2t.x(), std::min(p3t.x(), p4t.x())));
  int minY = std::min(p1t.y(), std::min(p2t.y(), std::min(p3t.y(), p4t.y())));
  int maxX = std::max(p1t.x(), std::max(p2t.x(), std::max(p3t.x(), p4t.x())));
  int maxY = std::max(p1t.y(), std::max(p2t.y(), std::max(p3t.y(), p4t.y())));

  //perehodim v sistemu coordinat PaintArea 
  int X_otn_parent = minX + widgetCenterX;
  int Y_otn_parent = minY + widgetCenterY;
    
  if (!((h > 0) && (w > 0) && (params17.AX > 0) && (params17.BR > 0) && 
        (params17.CR > 0) && (params17.DR > 0) && (params17.EQ > 0) &&
        (params17.FP > 0) && (h < w) && (params17.AX < h / 3) && 
        (params17.BR < h / 3) && (params17.CR < h / 3) && 
        (params17.DR < h / 3) && (params17.EQ < w / 4) && 
        (params17.FP < w / 4)))
  {
    QMessageBox msg(this);
    msg.setWindowTitle("ERROR");
    msg.setModal(true);
    msg.setText("Invalid parameters");
    msg.exec();
  }
  else if ((X_otn_parent <= 0) || (Y_otn_parent <= 0) || 
           (X_otn_parent + maxX - minX >= maxW) || (Y_otn_parent + maxY - minY >= maxH))
  {
    QMessageBox msg(this);
    msg.setWindowTitle("ERROR");
    msg.setModal(true);
    msg.setText("Not enough space");
    msg.exec();
  }
  else
  {
    vals.w = getW();
    vals.h = getH();
    vals.ang = ang;
    vals.x = X_otn_parent;
    vals.y = Y_otn_parent;
    vals.realW = maxX - minX;
    vals.realH = maxY - minY;
    vals.params17 = params17;
    accept();
  }
}
