#include "maska.hpp"

using std::vector;
using std::cerr;
using std::endl;

Maska::Maska(ILuint _szerokosc, ILuint _wysokosc)
{
  maska=vector<vector<ILbyte> >();
  szerokosc=_szerokosc;
  wysokosc=_wysokosc;
  dzielnik=1;
}

Maska::Maska(const ILbyte* _maska, ILbyte _dzielnik, ILuint _szerokosc, ILuint _wysokosc)
{
  dzielnik=_dzielnik;
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
  maska.clear();
  for(ILuint i=0;i<szerokosc;i++)
    {
      maska.push_back(vector<ILbyte>());
      for(ILuint j=0;j<wysokosc;j++)
        maska[i].push_back(_maska[i+j*szerokosc]);
    }
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

ILbyte Maska::Dzielnik()
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

void Maska::Dzielnik(ILbyte _dzielnik)
{
  dzielnik=_dzielnik;
}

std::ostream& operator<<(std::ostream& out, const Maska& m)
{
  out<<(int)m.szerokosc<<"x"<<(int)m.wysokosc;
  for(ILuint j=0;j<m.wysokosc;j++)
    {
      out<<endl;
      for(ILuint i=0;i<m.szerokosc;out<<(int)m.maska[i++][j]<<" ");
    }
  return out;
}
