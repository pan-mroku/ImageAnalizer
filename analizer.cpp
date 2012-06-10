#include <IL/il.h>
#include <iostream>
#include <cmath>
#include "maski_rozne.hpp"

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
  
  string prewitt=plik;
  string kierunkowy=plik;
  string lindeberg=plik;
  
  prewitt.insert(plik.find_last_of("."),"_prewitt");
  kierunkowy.insert(plik.find_last_of("."),"_filtrkierunkowy");
  lindeberg.insert(plik.find_last_of("."),"_lindeberg");

  cout<<"Prewitt"<<endl;
  obrazek.Rozmyj(1).Prewitt().Zapisz(prewitt.c_str());

  cout<<"Filtr kierunkowy"<<endl;
  obrazek.Filtruj().Zapisz(kierunkowy.c_str());

  cout<<"Lindeberg"<<endl;
  obrazek.Lindeberg().Zapisz(lindeberg.c_str());

  ilShutDown();
  return 0;
}
