#ifndef _MASKA
#define _MASKA

#include <IL/il.h>
#include <iostream>
#include <vector>
#include "pixel.hpp"

class Plotno;

class Maska
{
private:
  std::vector<std::vector<ILbyte> > maska;
  ILuint szerokosc;
  ILuint wysokosc;
  ILubyte dzielnik;
public:
  Maska();
  /*  ~Maska();
      Maska(const Maska& kopia);*/
  Maska(const ILbyte* _maska, ILubyte dzielnik=1, ILuint _szerokosc=0, ILuint _wysokosc=0);

  Pixel& Maskuj(const Plotno& p, ILuint x, ILuint y);

  friend std::ostream& operator<<(std::ostream& out, const Maska& m);
};

#endif
