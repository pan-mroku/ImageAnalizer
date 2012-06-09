#ifndef _MASKA
#define _MASKA

#include <IL/il.h>
#include <iostream>
#include <vector>
#include "plotno.hpp"

class Maska
{
protected:
  std::vector<std::vector<double> > maska;
  ILuint szerokosc;
  ILuint wysokosc;
  double dzielnik;
public:
  Maska(ILuint _szerokosc=0, ILuint _wysokosc=0);
  Maska(const double _maska[], ILuint _szerokosc=0, ILuint _wysokosc=0, double _dzielnik=1);

  Maska& operator=(const double _maska[]);
  Maska operator/(const Maska& mianownik) const;
  Maska operator+(const Maska& druga) const;

  ILuint Szerokosc();
  ILuint Wysokosc();
  double Dzielnik();
  void Szerokosc(ILuint _szerokosc);
  void Wysokosc(ILuint _wysokosc);
  void Dzielnik(double _dzielnik);

  Pixel Splot(const Plotno& p, ILuint x, ILuint y) const;

  friend std::ostream& operator<<(std::ostream& out, const Maska& m);
};

#endif
