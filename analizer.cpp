#include <IL/il.h>
#include <iostream>
#include <cmath>
#include "plotno.hpp"

using namespace std;

int main(int argc,char** argv)
{
  ILbyte maska[9]={-1,0,-1,0,6,0,-1,0,-1};
  string plik="lena.bmp";

  if(argc>1)
  {
    plik=argv[1];
  }

  ilInit();
  ilEnable(IL_FILE_OVERWRITE);

  Plotno obrazek(plik.c_str());
  
  //obrazek.Maskuj(maska,3);
  //obrazek.Filtruj();
   Plotno aku;
   obrazek.Hough(&aku);

  if(argc==3)
	  plik=argv[2];
  else
	  plik="asd.png";
  aku.Zapisz(("aku_"+plik).c_str());
  obrazek.Zapisz(plik.c_str());
  ilShutDown();
  return 1;
}
