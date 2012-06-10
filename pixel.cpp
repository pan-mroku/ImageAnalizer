#include "pixel.hpp"

#include<iostream>
using std::cerr;
using std::endl;

Pixel::Pixel(const Pixel& kopia)
{
  b=kopia.b;
  g=kopia.g;
  r=kopia.r;
}

Pixel& Pixel::operator=(const Pixel& p)
{
  b=p.b;
  g=p.g;
  r=p.r;
  return *this;
}

Pixel::Pixel(const ILubyte& trojka)
{
  b=trojka;
  g=*(&trojka+1);
  r=*(&trojka+2);
}

ILubyte Pixel::R() const
{
  if(r>255)
    return 255;
  if(r<0)
    return 0;
  return r;
}

ILubyte Pixel::G() const
{
  if(g>255)
    return 255;
  if(g<0)
    return 0;
  return g;
}

ILubyte Pixel::B() const
{
  if(b>255)
    return 255;
  if(b<0)
    return 0;
  return b;
}

ILint Pixel::Jasnosc() const
{
  return (3*R()+5*G()+2*B())/10;
}

ILint Pixel::BW() const
{
  return (R()+G()+B())/3;
}

Pixel::operator ILint()
{
  return (r+g+b)/3;
}

Pixel Pixel::operator*(const double& p)
{
  return Pixel(r*p,g*p,b*p);
}

Pixel Pixel::operator/(const double& p)
{
  return Pixel(r/p,g/p,b/p);
}

Pixel Pixel::operator+(const double& p)
{
  return Pixel(r+p,g+p,b+p);
}

Pixel Pixel::operator-(const double& p)
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

bool operator>(const Pixel& p1, const Pixel& p2)
{
  if(p1.Jasnosc()>p2.Jasnosc())
    return true;
  return false;
}

bool operator<=(const Pixel& p1, const Pixel& p2)
{
  return !(p1>p2);
}

bool operator<(const Pixel& p1, const Pixel& p2)
{
  return p2>p1;
}

bool operator>=(const Pixel& p1, const Pixel& p2)
{
  return !(p1<p2);
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


Pixel& Pixel::operator+=(const double f)
{
  r+=int(f);
  g+=int(f);
  b+=int(f);
  return *this;
}


Pixel& Pixel::operator-=(const Pixel& p)
{
  r-=p.r;
  g-=p.g;
  b-=p.b;
  return *this;
}

Pixel& Pixel::operator-=(const double f)
{
  r-=int(f);
  g-=int(f);
  b-=int(f);
  return *this;
}
