#include "utils.hpp"
#include <iostream>
using std::cerr;
using std::endl;

double Gauss(double x, double y, double t)
{
  if(t==0)return x==0&&y==0;
  double licznik=-(x*x+y*y);
  double mianownik=2*t;
  return exp(licznik/mianownik);
}
