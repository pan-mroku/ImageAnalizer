#include <IL/il.h>
#include <iostream>
#include <cmath>
#include "maska.hpp"

using namespace std;

int main(int argc,char** argv)
{
  ILbyte maska_tab[9]={-1,0,-1,0,6,0,-1,0,-1};
  Maska maska(maska_tab,2,3,3);
  string plik="lena.bmp";

  if(argc>1)
  {
    plik=argv[1];
  }

  ilInit();
  ilEnable(IL_FILE_OVERWRITE);

  Plotno obrazek(plik.c_str());
  
  obrazek.Maskuj(maska);
  //obrazek.Filtruj();

  if(argc==3)
	  plik=argv[2];
  else
    plik.insert(0,"maskuj_");

  obrazek.Zapisz(plik.c_str());
  ilShutDown();
  return 1;
}
