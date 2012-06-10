#ifndef _PLOTNO
#define _PLOTNO

#include <IL/il.h>
#include <iostream>
#include <vector>
#include "pixel.hpp"

class Maska;
class MaskaGauss;

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
  Plotno(ILuint _szerokosc, ILuint _wysokosc);
  Pixel& operator[](int index);
  const Pixel& operator[](int index) const;
  void Zapisz(const char* plik);

  ILuint Wysokosc() const;
  ILuint Szerokosc() const;

  Plotno Splot(const Maska& maska);
  Plotno BW();
  Plotno Prewitt();
  Plotno Rozmyj(ILuint _ile_razy=1);
  Plotno Filtruj();
  Plotno Hough(Plotno* ak=0);
  Plotno Lindeberg();
  
  Plotno operator+(const Plotno& p);
  Plotno operator-(const Plotno& p);

  friend std::ostream& operator<<(std::ostream& out, const Plotno& p);
  friend class Maska;
};
#endif
