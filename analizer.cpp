#include <IL/il.h>
#include <iostream>
#include <cmath>
#include "maski_rozne.hpp"

using namespace std;


void info()
{
  cout<<"Analizator obrazów\nPaweł Szymański 2012\n\n\
Użycie: analizer plik [algorytm]\n\n\
Algorytmy:\n\
\t-p, --prewitt\t\t Filtr Prewitta (Laplasjan we wszystkich kierunkach)\n\
\t-l, --lindeberg\t\t Filtr Lindeberga\n\
\t-k, --kierunkowy\t Filtr kierunkowy\n\
\t-h, --hough\t\t Transformacja Hougha dla jednej prostej"<<endl;
}


void init()
{
  ilInit();
  ilEnable(IL_ORIGIN_SET);
  ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
  ilEnable(IL_FILE_OVERWRITE);
}

int main(int argc,char** argv)
{
  if(argc<3)
    {
      info();
      return 1;
    }

  string plik;
  bool p,l,k,h;
  p=l=k=h=false;

  for(int i=1;i<argc;i++)
    {
      string parametr=argv[i];

      if(parametr=="-p" || parametr=="--prewitt")
        {
        p=true;
        continue;
        }
      if(parametr=="-l" || parametr=="--lindeberg")
        {
        l=true;
        continue;
        }

      if(parametr=="-k" || parametr=="--kierunkowy")
        {
        k=true;
        continue;
        }

      if(parametr=="-h" || parametr=="--hough")
        {
        h=true;
        continue;
        }

      if(argv[i][0]!='-')
        {
          plik=parametr;
          continue;
        }
      
      //w przeciwnym wypadku podano błędny parametr
      info();
      return 1;
    }

  if(plik=="")//jeśli nie podano pliku wejściowego, to też błąd
    {
      info();
      return 1;
    }

  //skoro wszystko ok, to zaczynamy.
  init();

  Plotno obrazek(plik.c_str());

  if(p)
    {
      string plik_wyjsciowy=plik;
      plik_wyjsciowy.insert(plik.find_last_of("."),"_prewitt");
      cout<<"Prewitt"<<endl;
      obrazek.Rozmyj(1).Prewitt().Zapisz(plik_wyjsciowy.c_str());
    }

  if(l)
    {
      string plik_wyjsciowy=plik;
      plik_wyjsciowy.insert(plik.find_last_of("."),"_lindeberg");
      cout<<"Lindeberg"<<endl;
      obrazek.Lindeberg().Zapisz(plik_wyjsciowy.c_str());
    }

  if(k)
    {
      string plik_wyjsciowy=plik;
      plik_wyjsciowy.insert(plik.find_last_of("."),"_filtr_kierunkowy");
      cout<<"Filtr kierunkowy"<<endl;
      obrazek.Filtruj().Zapisz(plik_wyjsciowy.c_str());
    }

  if(h)
    {
      string plik_wyjsciowy=plik;
      plik_wyjsciowy.insert(plik.find_last_of("."),"_hough");
      cout<<"Hough"<<endl;
      obrazek.Hough().Zapisz(plik_wyjsciowy.c_str());
    }

  ilShutDown();
  return 0;
}
