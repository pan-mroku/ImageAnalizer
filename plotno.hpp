#ifndef _PLOTNO
#define _PLOTNO

#include <IL/il.h>
#include <iostream>
#include <vector>
//#include <cmath>
#include "pixel.hpp"

class Maska;

class Plotno
{
private:
  ILuint id;
  Pixel* obraz;
  ILuint wysokosc;
  ILuint szerokosc;
public:
  Plotno();
  Plotno(const char* plik);
  ~Plotno();
  Plotno(const Plotno& kopia);
  Plotno& operator=(const Plotno& kopia);
  Plotno(const Pixel _obraz[],ILuint _szerokosc, ILuint _wysokosc);
  Pixel& operator[](int index);
  const Pixel& operator[](int index) const;
  void Zapisz(const char* plik);
  Plotno& Maskuj(const Maska& maska);
  Plotno& Wyostrz();
  Plotno& Rozmyj();
  Plotno& Filtruj();
  Plotno& Hough(Plotno* ak=0);
  Plotno& Lindeberg();
  friend std::ostream& operator<<(std::ostream& out, const Plotno& p);
  friend class Maska;
};
#endif
