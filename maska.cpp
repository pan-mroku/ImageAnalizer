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
      maska.push_back(vector<double>());
      for(ILuint j=0;j<wysokosc;j++)
        maska[i].push_back(0);
    }
}

Maska::Maska(const double* _maska, ILuint _szerokosc, ILuint _wysokosc, double _dzielnik)
{
  dzielnik=_dzielnik;
  if(_dzielnik==0)
    dzielnik=1;
  szerokosc=_szerokosc;
  wysokosc=_wysokosc;

  for(ILuint i=0;i<szerokosc;i++)
    {
      maska.push_back(vector<double>());
      for(ILuint j=0;j<wysokosc;j++)
        maska[i].push_back(_maska[i+j*szerokosc]);
    }
}

Maska& Maska::operator=(const double _maska[])
{
  for(ILuint i=0;i<szerokosc;i++)
    for(ILuint j=0;j<wysokosc;j++)
      maska[i][j]=_maska[i+j*szerokosc];
  return *this;
}

Maska Maska::operator/(const Maska& mianownik) const
{
  if(szerokosc!=mianownik.szerokosc || wysokosc!=mianownik.wysokosc) return Maska();
  Maska wynik(szerokosc, wysokosc);
  for(ILuint x=0;x<szerokosc;x++)
    for(ILuint y=0;y<wysokosc;y++)
      wynik.maska[x][y]=maska[x][y]/mianownik.maska[x][y];
  return wynik;
}

Maska Maska::operator+(const Maska& druga)const
{
  if(szerokosc!=druga.szerokosc || wysokosc!=druga.wysokosc) return Maska();
  Maska wynik(szerokosc, wysokosc);
  for(ILuint x=0;x<szerokosc;x++)
    for(ILuint y=0;y<wysokosc;y++)
      wynik.maska[x][y]=maska[x][y]+druga.maska[x][y];
  return wynik;
}

ILuint Maska::Szerokosc()
{
  return szerokosc;
}

ILuint Maska::Wysokosc()
{
  return wysokosc;
}

double Maska::Dzielnik()
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

void Maska::Dzielnik(double _dzielnik)
{
  dzielnik=_dzielnik;
}

Pixel Maska::Splot(const Plotno& p, ILuint x, ILuint y) const
{
  Pixel tmp;

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
      for(ILuint i=0;i<m.szerokosc;i++)
        {
          out.width(5);
          out.setf(std::ios::fixed);
          out<<m.maska[i][j]/m.dzielnik;
          out<<" ";
        }
    }
  return out;
}
