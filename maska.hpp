#ifndef _MASKA
#define _MASKA

#include <IL/il.h>
#include <iostream>
#include <vector>
#include "plotno.hpp"

class Maska
{
private:
  std::vector<std::vector<ILbyte> > maska;
  ILuint szerokosc;
  ILuint wysokosc;
  ILbyte dzielnik;
public:
  Maska(ILuint _szerokosc=0, ILuint _wysokosc=0);
  Maska(const ILbyte _maska[], ILbyte dzielnik=1, ILuint _szerokosc=0, ILuint _wysokosc=0);

  Maska& operator=(const ILbyte _maska[]);
  ILuint Szerokosc();
  ILuint Wysokosc();
  ILbyte Dzielnik();
  void Szerokosc(ILuint _szerokosc);
  void Wysokosc(ILuint _wysokosc);
  void Dzielnik(ILbyte _dzielnik);

  Pixel Maskuj(const Plotno& p, ILuint x, ILuint y);

  friend std::ostream& operator<<(std::ostream& out, const Maska& m);
};

#endif
