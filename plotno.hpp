#ifndef _PLOTNO
#define _PLOTNO

#include <IL/il.h>
#include <iostream>
#include <vector>
#include "pixel.hpp"

class Maska;

class Plotno
{
private:
  Pixel* obraz;
  ILuint wysokosc;
  ILuint szerokosc;
public:
  Plotno(const char* plik);
  ~Plotno();
  Plotno(const Plotno& kopia);
  Pixel& operator[](int index);
  const Pixel& operator[](int index) const;
  void Zapisz(const char* plik);
  Plotno& Maskuj(const ILbyte* _maska=0, const ILuint _bok=3);
  Plotno& Filtruj();
  friend std::ostream& operator<<(std::ostream& out, const Plotno& p);
  friend class Maska;
};
#endif
