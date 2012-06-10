#ifndef _PIXEL
#define _PIXEL

#include<IL/il.h>
#include<ostream>
#include<cmath>
#include "utils.hpp"

class Pixel
{
private:
  ILint b,g,r;
public:
  Pixel():b(0),g(0),r(0){};
  Pixel(ILint _r, ILint _g, ILint _b):b(_b),g(_g),r(_r){};
  Pixel(ILint c):b(c),g(c),r(c){};
  Pixel(ILuint c):b(c),g(c),r(c){};

  Pixel(const Pixel& kopia);
  Pixel& operator=(const Pixel& p);

  Pixel(const ILubyte& trojka);
  ILubyte R() const;
  ILubyte G() const;
  ILubyte B() const;
  ILint Jasnosc() const;
  ILint BW() const;

  operator ILint();

  Pixel operator*(const double& p);
  Pixel operator/(const double& p);
  Pixel operator+(const double& p);
  Pixel operator-(const double& p);
  Pixel operator*(const Pixel& p);
  Pixel operator/(const Pixel& p);
  Pixel operator+(const Pixel& p);
  Pixel operator-(const Pixel& p);

  friend bool operator>(const Pixel& p1, const Pixel& p2);
  friend bool operator>=(const Pixel& p1, const Pixel& p2);
  friend bool operator<=(const Pixel& p1, const Pixel& p2);
  friend bool operator<(const Pixel& p1, const Pixel& p2);

  friend std::ostream& operator<<(std::ostream& out,const Pixel& p);

  Pixel& operator>>=(const int i);
  Pixel& operator+=(const Pixel& p);
  Pixel& operator+=(const double f);
  Pixel& operator-=(const Pixel& p);
  Pixel& operator-=(const double f);
};

#endif
