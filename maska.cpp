#include "maska.hpp"

using std::vector;
using std::cerr;
using std::endl;

Maska::Maska(ILuint _szerokosc, ILuint _wysokosc)
{
  szerokosc=_szerokosc;
  wysokosc=_wysokosc;
  dzielnik=1;
  for(ILuint i=0;i<szerokosc;i++)
    {
      maska.push_back(vector<ILbyte>());
      for(ILuint j=0;j<wysokosc;j++)
        maska[i].push_back(i==szerokosc/2 && j==wysokosc/2);
    }
}

Maska::Maska(const ILbyte* _maska, ILuint _dzielnik, ILuint _szerokosc, ILuint _wysokosc)
{
  dzielnik=_dzielnik;
  if(_dzielnik==0)
    dzielnik=1;
  szerokosc=_szerokosc;
  wysokosc=_wysokosc;

  for(ILuint i=0;i<szerokosc;i++)
    {
      maska.push_back(vector<ILbyte>());
      for(ILuint j=0;j<wysokosc;j++)
        maska[i].push_back(_maska[i+j*szerokosc]);
    }
}

Maska& Maska::operator=(const ILbyte _maska[])
{
  for(ILuint i=0;i<szerokosc;i++)
    for(ILuint j=0;j<wysokosc;j++)
      maska[i][j]=_maska[i+j*szerokosc];
  return *this;
}

Maska& Maska::Gaussowska()
{
  for(ILint x=0;x<szerokosc;x++)
    for(ILint y=0;y<wysokosc;y++)
      maska[x][y]=10*Gauss(x+szerokosc/2,y+wysokosc/2,1);
  dzielnik=2*PI*10;
  return *this;
}

ILuint Maska::Szerokosc()
{
  return szerokosc;
}

ILuint Maska::Wysokosc()
{
  return wysokosc;
}

ILuint Maska::Dzielnik()
{
  return dzielnik;
}

void Maska::Szerokosc(ILuint _szerokosc)
{
  szerokosc=_szerokosc;
}

void Maska::Wysokosc(ILuint _wysokosc)
{
  wysokosc=_wysokosc;
}

void Maska::Dzielnik(ILuint _dzielnik)
{
  dzielnik=_dzielnik;
}

Pixel Maska::Maskuj(const Plotno& p, ILuint x, ILuint y) const
{
  Pixel tmp=0;
  for(ILuint i=0;i<szerokosc;i++)
    for(ILuint j=0;j<wysokosc;j++)
      {
        ILuint pixel_x=x-szerokosc/2+i;
        ILuint pixel_y=y-wysokosc/2+j;
        if(pixel_x>=p.szerokosc||pixel_y>=p.wysokosc||pixel_x<0||pixel_y<0)
          continue;
        tmp+=p.obraz[pixel_y*p.szerokosc+pixel_x]*maska[i][j]/dzielnik;
      }
  return tmp;
}

std::ostream& operator<<(std::ostream& out, const Maska& m)
{
  out<<(int)m.szerokosc<<"x"<<(int)m.wysokosc;
  for(ILuint j=0;j<m.wysokosc;j++)
    {
      out<<endl;
      for(ILuint i=0;i<m.szerokosc;out<<(int)m.maska[i++][j]<<" ")
        out.width(4);
    }
  out<<(int)m.dzielnik;
  return out;
}
