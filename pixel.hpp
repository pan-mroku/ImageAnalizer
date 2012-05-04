#ifndef _PIXEL
#define _PIXEL

#include<IL/il.h>
#include<ostream>
#include<cmath>

class Pixel
{
private:
  ILint b,g,r;
public:
  Pixel():b(0),g(0),r(0){}
 Pixel(ILint _r, ILint _g, ILint _b):b(_b),g(_g),r(_r){}
 Pixel(ILint c):b(c),g(c),r(c){};
 Pixel(ILuint c):b(c),g(c),r(c){};
  Pixel(const Pixel& kopia);
  Pixel(const ILubyte& trojka);
  ILubyte R();
  ILubyte G();
  ILubyte B();
  ILint Jasnosc();
  ILint BW();

  Pixel operator*(const ILbyte& p);
  Pixel operator/(const ILbyte& p);
  Pixel operator+(const ILbyte& p);
  Pixel operator-(const ILbyte& p);
  Pixel operator*(const Pixel& p);
  Pixel operator/(const Pixel& p);
  Pixel operator+(const Pixel& p);
  Pixel operator-(const Pixel& p);
  bool operator>(const Pixel& p);
  bool operator<(const Pixel& p);
  friend std::ostream& operator<<(std::ostream& out,const Pixel& p);
  Pixel& operator>>=(const int i);
  Pixel& operator+=(const Pixel& p);
  Pixel& operator+=(const float f);
};

#endif
