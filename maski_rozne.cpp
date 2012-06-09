#include "maski_rozne.hpp"

#include <iostream>
using std::cerr;
using std::endl;

MaskaGauss::MaskaGauss(ILuint _bok):Maska(_bok, _bok)
{
  dzielnik=1;
  t=(double)_bok/6;
  t*=t; //t
  wypelnij();

}

void MaskaGauss::wypelnij()
{
  dzielnik=0;

  for(double x=0;x<szerokosc;x++)
    for(double y=0;y<wysokosc;y++)
      {
        double gauss=Gauss(x-szerokosc/2, y-wysokosc/2,t);
        dzielnik+=gauss;
        maska[x][y]=gauss;
      }
}

double MaskaGauss::T()
{
  return t;
}

void MaskaGauss::T(double _t)
{
  t=_t;
  wypelnij();
}

MaskaX::MaskaX():Maska(3,1)
{
  maska[0][0]=-1;
  maska[1][0]=0;
  maska[2][0]=1;
  dzielnik=2;
}

MaskaY::MaskaY():Maska(1,3)
{
  maska[0][2]=-1;
  maska[0][1]=0;
  maska[0][0]=1;
  dzielnik=2;
}

MaskaXX::MaskaXX():Maska(3,1)
{
  maska[0][0]=1;
  maska[1][0]=-2;
  maska[2][0]=1;
  dzielnik=1;
}

MaskaXY::MaskaXY():Maska(3,3)
{
  dzielnik=4;
  maska[0][0]=maska[2][2]=1;
  maska[0][2]=maska[2][0]=-1;
}

MaskaYY::MaskaYY():Maska(1,3)
{
  maska[0][2]=1;
  maska[0][1]=-2;
  maska[0][0]=1;
  dzielnik=1;
}

MaskaXXX::MaskaXXX():Maska(5,1)
{
  maska[0][0]=-1;
  maska[1][0]=2;
  maska[2][0]=0;
  maska[3][0]=-2;
  maska[4][0]=1;
  dzielnik=2;
}

MaskaXXY::MaskaXXY():Maska(3,3)
{
  dzielnik=2;
  maska[0][2]=maska[2][2]=1;
  maska[0][0]=maska[2][0]=-1;
  maska[1][0]=2;
  maska[1][2]=-2;
}

MaskaXYY::MaskaXYY():Maska(3,5)
{
  dzielnik=8;
  maska[0][0]=maska[0][4]=-1;
  maska[2][0]=maska[2][4]=1;
  maska[0][2]=2;
  maska[2][2]=-2;

}

MaskaYYY::MaskaYYY():Maska(1,5)
{
  maska[0][4]=-1;
  maska[0][3]=2;
  maska[0][2]=0;
  maska[0][1]=-2;
  maska[0][0]=1;
  dzielnik=2;
}

