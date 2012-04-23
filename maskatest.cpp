#include <iostream>
#include "maska.hpp"

using namespace std;

int main()
{
  Maska m(2,2);
  m=(ILbyte[]){1,2,2,1};
  Maska m2((ILbyte[]){1,2},1,2,1);
  cout<<m<<endl<<endl<<m2<<endl;
  return 1;
}
