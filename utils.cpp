#include "utils.hpp"
#include <iostream>
using std::cerr;
using std::endl;

double Gauss(double x, double y, double t)
{
  if(t==0)return x==0&&y==0;
  double wykladnik=-((x*x)+(y*y))/(2*t);
  double mianownik=sqrt(2*PI*t);
  return exp(wykladnik)/mianownik;
}
