#include "DialogWindow27.h"

#include <QMessageBox>

#include <cmath>

DialogWindow27::DialogWindow27(const Figure27* pf, QWidget* parent) : AbstractDialogWindow(pf, parent)
{
  setWindowTitle("Choose parameters for figure27");
  
  auto params27 = pf->getParams27();

  ptxt_AR = new QLineEdit(QString::number(params27.AR));
  ptxt_BX = new QLineEdit(QString::number(params27.BX));
  ptxt_CX = new QLineEdit(QString::number(params27.CX));
  ptxt_DX = new QLineEdit(QString::number(params27.DX));
  ptxt_EQ = new QLineEdit(QString::number(params27.EQ));
  
  ptxt_AR->setValidator(pvalidator);
  ptxt_BX->setValidator(pvalidator);
  ptxt_CX->setValidator(pvalidator);
  ptxt_DX->setValidator(pvalidator);
  ptxt_EQ->setValidator(pvalidator);

  QLabel* plbl_AR = new QLabel("&AR:");
  QLabel* plbl_BX = new QLabel("&BX:");
  QLabel* plbl_CX = new QLabel("&CX: ");
  QLabel* plbl_DX = new QLabel("&DX:");
  QLabel* plbl_EQ = new QLabel("&EQ:");

  plbl_AR->setBuddy(ptxt_AR);
  plbl_BX->setBuddy(ptxt_BX);
  plbl_CX->setBuddy(ptxt_CX);
  plbl_DX->setBuddy(ptxt_DX);
  plbl_EQ->setBuddy(ptxt_EQ);
  
  QHBoxLayout* phbl_ARBX = new QHBoxLayout;
  phbl_ARBX->addWidget(plbl_AR);
  phbl_ARBX->addStretch(5);
  phbl_ARBX->addWidget(ptxt_AR); 
  phbl_ARBX->addSpacing(5);
  phbl_ARBX->addWidget(plbl_BX);
  phbl_ARBX->addStretch(5);
  phbl_ARBX->addWidget(ptxt_BX);
  playout->addLayout(phbl_ARBX);
  
  QHBoxLayout* phbl_CXDX = new QHBoxLayout;
  phbl_CXDX->addWidget(plbl_CX);
  phbl_CXDX->addStretch(5);
  phbl_CXDX->addWidget(ptxt_CX); 
  phbl_CXDX->addSpacing(5);
  phbl_CXDX->addWidget(plbl_DX);
  phbl_CXDX->addStretch(5);
  phbl_CXDX->addWidget(ptxt_DX); 
  playout->addLayout(phbl_CXDX);
 
  QHBoxLayout* phbl_EQ = new QHBoxLayout;
  phbl_EQ->addSpacing(70);
  phbl_EQ->addWidget(plbl_EQ);
  phbl_EQ->addWidget(ptxt_EQ);
  phbl_EQ->addSpacing(70);
  playout->addLayout(phbl_EQ);

  playout->addLayout(phbl_Rotation);
  playout->addLayout(phbl_buttons);

}

Parameters27 DialogWindow27::getParams27() const
{
  return Parameters27(ptxt_AR->text().toInt(),
                      ptxt_BX->text().toInt(),
                      ptxt_CX->text().toInt(),
                      ptxt_DX->text().toInt(),
                      ptxt_EQ->text().toInt());
}

newValues27 DialogWindow27::getNewValues27() const
{
  return vals;
}
#include <QDebug>
void DialogWindow27::CheckValuesSlot()
{
  auto w = getW();
  auto h = getH();
  auto delta_ang = getAng();
  if (prb_left->isChecked())
  {
    delta_ang = -delta_ang;
  }
  auto ang = delta_ang + figure_ang;
  auto params27 = getParams27();

 //////////////////////////////////////////////
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
    
  if (!((h > 0) && (w > 0) && (params27.AR > 0) && (params27.BX > 0) && 
        (params27.CX > 0) && (params27.DX > 0) && (params27.EQ > 0) &&
        (h < w) && (params27.AR < h / 3) && 
        (params27.BX < h / 3) && (params27.CX < h / 3) && 
        (params27.DX < h / 3) && (params27.EQ < w / 4))) 
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
    vals.params27 = params27;
    accept();
  }
}
