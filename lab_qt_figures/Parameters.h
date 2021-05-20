#ifndef PARAMETERS_H
#define PARAMETERS_H

struct Parameters17
{
  int AX, BR, CR, DR, EQ, FP;
  
  Parameters17() {} 
  Parameters17(int AX, int BR, int CR, int DR, int EQ, int FP) : AX(AX), BR(BR), CR(CR), DR(DR), EQ(EQ), FP(FP) {}
};

struct Parameters27
{
  int AR, BX, CX, DX, EQ;
  
  Parameters27() {}
  Parameters27(int AR, int BX, int CX, int DX, int EQ) : AR(AR), BX(BX), CX(CX), DX(DX), EQ(EQ) {}
};

#endif //PARAMETERS_H
