#include <IL/il.h>
#include <iostream>
#include <cmath>
#include "maska.hpp"

using namespace std;

int main(int argc,char** argv)
{
  string plik="lena.bmp";

  if(argc>1)
  {
    plik=argv[1];
  }

  ilInit();
  ilEnable(IL_ORIGIN_SET);
  ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
  ilEnable(IL_FILE_OVERWRITE);

  Plotno obrazek(plik.c_str());
  
  obrazek.Lindeberg();

  if(argc==3)
	  plik=argv[2];
  else
    plik.insert(plik.find_last_of("."),"_");

  obrazek.Zapisz(plik.c_str());
  ilShutDown();
  return 1;
}
