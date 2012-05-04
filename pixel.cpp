#include "pixel.hpp"

Pixel::Pixel(const Pixel& kopia)
{
  b=kopia.b;
  g=kopia.g;
  r=kopia.r;
}

Pixel::Pixel(const ILubyte& trojka)
{
  b=trojka;
  g=*(&trojka+1);
  r=*(&trojka+2);
}

ILubyte Pixel::R()
{
  if(r>255)
    return 255;
  if(r<0)
    return 0;
  return r;
}

ILubyte Pixel::G()
{
  if(g>255)
    return 255;
  if(g<0)
    return 0;
  return g;
}

ILubyte Pixel::B()
{
  if(b>255)
    return 255;
  if(b<0)
    return 0;
  return b;
}

ILint Pixel::Jasnosc()
{
  return (3*r+5*g+2*b)/10;
}

Pixel Pixel::BW()
{
  return Pixel(Jasnosc());
}

Pixel Pixel::operator*(const ILbyte& p)
{
  return Pixel(r*p,g*p,b*p);
}

Pixel Pixel::operator/(const ILbyte& p)
{
  return Pixel(r/p,g/p,b/p);
}

Pixel Pixel::operator+(const ILbyte& p)
{
  return Pixel(r+p,g+p,b+p);
}

Pixel Pixel::operator-(const ILbyte& p)
{
  return Pixel(r-p,g-p,b-p);
}

Pixel Pixel::operator*(const Pixel& p)
{
  return Pixel(r*p.r,g*p.g,b*p.b);
}

Pixel Pixel::operator/(const Pixel& p)
{
  return Pixel(r/p.r,g/p.g,b/p.b);
}

Pixel Pixel::operator+(const Pixel& p)
{
  return Pixel(r+p.r,g+p.g,b+p.b);
}

Pixel Pixel::operator-(const Pixel& p)
{
  return Pixel(r-p.r,g-p.g,b-p.b);
}

bool Pixel::operator>(const Pixel& p)
{
  if(std::abs(3*r+5*g+2*b)>std::abs(3*p.r+5*p.g+2*p.b))
  return true;
return false;
}

bool Pixel::operator<(const Pixel& p)
{
 if(std::abs(3*r+5*g+2*b)<std::abs(3*p.r+5*p.g+2*p.b))
  return true;
return false;
}

std::ostream& operator<<(std::ostream& out,const Pixel& p)
{
  return out<<(int)p.r<<":"<<(int)p.g<<":"<<(int)p.b;
}

Pixel& Pixel::operator>>=(const int i)
{
  r>>=i;
  g>>=i;
  b>>=i;
  return *this;
}

Pixel& Pixel::operator+=(const Pixel& p)
{
  r+=p.r;
  g+=p.g;
  b+=p.b;
  return *this;
}


Pixel& Pixel::operator+=(const float f)
{
  r+=int(f);
  g+=int(f);
  b+=int(f);
  return *this;
}
