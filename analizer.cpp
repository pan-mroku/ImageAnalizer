#include <IL/il.h>
#include <iostream>
#include <cmath>
#include "plotno.h"

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
  
  obrazek.Filtruj();

  if(argc==3)
	  plik=argv[2];
  else
	  plik="asd.png";

  obrazek.Zapisz(plik.c_str());
  ilShutDown();
  return 1;
}
