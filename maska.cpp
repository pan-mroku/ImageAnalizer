#include "maska.hpp"

using std::vector;
using std::cerr;
using std::endl;

Maska::Maska()
{
  maska=vector<vector<ILbyte> >();
  maska.push_back(vector<ILbyte>());
  maska[0].push_back(1);
  szerokosc=wysokosc=1;
  dzielnik=1;
}

/*Maska::~Maska()
{
  //maska.clear;
}

Maska::Maska(const Maska& kopia)
{
  maska=kopia.maska;
  szerokosc=kopia.szerokosc;
  wysokosc=kopia.wysokosc;
  dzielnik=kopia.dzielnik;
}*/

Maska::Maska(const ILbyte* _maska, ILubyte _dzielnik, ILuint _szerokosc, ILuint _wysokosc)
{
  maska=vector<vector<ILbyte> >();  
  for(ILuint i=0;i<_szerokosc;i++)
    {
      maska.push_back(vector<ILbyte>());
      for(ILuint j=0;j<_wysokosc;j++)
        maska[i].push_back(_maska[i+j*_szerokosc]);
    }
}

std::ostream& operator<<(std::ostream& out, const Maska& m)
{
  for(ILuint j=0;j<m.wysokosc;j++,out<<endl)
    for(ILuint i=0;i<m.szerokosc;out<<m.maska[i++][j]<<" ");
  return out;
}
