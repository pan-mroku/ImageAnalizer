#ifndef _PLOTNO
#define _PLOTNO

#include "pixel.h"

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
  Plotno& Maskuj(const ILbyte* maska, const ILuint bok);
  Plotno& Filtruj();
  friend std::ostream& operator<<(std::ostream& out, const Plotno& p);
};
#endif
