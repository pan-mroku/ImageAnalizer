#include "plotno.hpp"
#include "maska.hpp"

using std::cerr;
using std::endl;

Plotno::Plotno(const char* plik)
{
  ilLoadImage(plik);
  ILubyte* tmp=ilGetData();
  szerokosc=ilGetInteger(IL_IMAGE_WIDTH);
  wysokosc=ilGetInteger(IL_IMAGE_HEIGHT);

  obraz=new Pixel[wysokosc*szerokosc];
  for(ILuint i=0;i<wysokosc;i++)
    for(ILuint j=0;j<szerokosc;j++)
      obraz[i*szerokosc+j]=tmp[3*(i*szerokosc+j)];
}

Plotno::~Plotno()
{
  delete[] obraz;
}

Plotno::Plotno(const Plotno& kopia)
{
  obraz=new Pixel[kopia.wysokosc*kopia.szerokosc];
  for(ILuint i=0;i<kopia.wysokosc;i++)
    for(ILuint j=0;j<kopia.szerokosc;j++)
      obraz[i*szerokosc+j]=kopia[i*szerokosc+j];
}

Pixel& Plotno::operator[](int index)
{
  return obraz[index];
}

const Pixel& Plotno::operator[](int index) const
{
  return obraz[index];
}

void Plotno::Zapisz(const char* plik)
{
  ILubyte* nowy=new ILubyte[3*szerokosc*wysokosc];
  for(ILuint i=0;i<wysokosc;i++)
    for(ILuint j=0;j<szerokosc;j++)
      {
        Pixel p(obraz[i*szerokosc+j]);
        nowy[3*(i*szerokosc+j)]=p.B();
        nowy[3*(i*szerokosc+j)+1]=p.G();
        nowy[3*(i*szerokosc+j)+2]=p.R();
      }
  ilSetData(nowy);
  ilSaveImage(plik);
  delete[] nowy;
}

Plotno& Plotno::Maskuj(const ILbyte* maska, const ILuint bok)
{

  /*  const ILbyte* maska=_maska;
  ILuint bok=_bok;
    if(_maska==0)
    {
    maska={-1,0,-1,0,6,0,-1,0,-1};
    bok=3;
    }
  else
    {
      maska=_maska;
      }*/
  Maska _maska(maska,2,bok,bok);
  
  Pixel* nowe=new Pixel[szerokosc*wysokosc];

  for(ILuint i=0;i<wysokosc*szerokosc;i++)
    nowe[i]=obraz[i];
  
  /*  for(ILuint i=1;i<wysokosc-1;i++)
    for(ILuint j=1;j<szerokosc-1;j++)
      {
        Pixel tmp=0;
        for(ILuint mi=0;mi<bok;mi++)
          for(ILuint mj=0;mj<bok;mj++)
            tmp+=obraz[(i-1+mi)*szerokosc+j-1+mj]*maska[mi*bok+mj]/2;
        nowe[i*szerokosc+j]=tmp;
        }*/
  for(ILuint i=0;i<wysokosc;i++)
    for(ILuint j=0;j<szerokosc;j++)
      {
        nowe[i*szerokosc+j]=_maska.Maskuj(*this,j,i);
        }
  delete[] obraz;
  obraz=nowe;
  return *this;
}

Plotno& Plotno::Filtruj()
{
  ILbyte test[4][9]={
	  {0,0,0,1,2,1,0,0,0}, //0 "-"
	  {0,0,1,0,2,0,1,0,0}, //45 "\"
	  {0,1,0,0,2,0,0,1,0}, //90 "|"
	  {1,0,0,0,2,0,0,0,1} //135 "/"
  };
  Pixel wynik[4]={0,0,0,0};

  ILbyte maska[4][9]={
	  {1,2,1,0,0,0,-1,-2,-1}, //0 "-"
	  {2,1,0,1,0,-1,0,-1,-2}, //45 "\"
	  {-1,0,1,-2,0,-2,-1,0,1}, //90 "|"
	  {0,1,2,-1,0,1,-2,-1,0} //135 "/"
  };

  Pixel* nowe=new Pixel[szerokosc*wysokosc];
  for(ILuint i=0;i<wysokosc*szerokosc;i++)
    nowe[i]=obraz[i].BW();

  for(ILuint i=1;i<wysokosc-1;i++)
    for(ILuint j=1;j<szerokosc-1;j++)
    {
      for(ILuint p=0;p<4;p++)
        wynik[p]=0;

      for(ILuint t=0;t<4;t++)
        for(ILuint mi=0;mi<3;mi++)
          for(ILuint mj=0;mj<3;mj++)
            wynik[t]+=obraz[(i-1+mi)*szerokosc+j-1+mj]*test[t][mi*3+mj]/2;

      ILuint kierunek=0;
      for(ILuint a=0;a<4;a++)
        if(wynik[a]>wynik[kierunek])
          kierunek=a;

      Pixel tmp=0;

      for(ILuint mi=0;mi<3;mi++)
        for(ILuint mj=0;mj<3;mj++)
          tmp+=obraz[(i-1+mi)*szerokosc+j-1+mj]*maska[kierunek][mi*3+mj]/2;

      nowe[i*szerokosc+j]=tmp.BW();
    }
	
  delete[] obraz;
  obraz=nowe;

  return *this;
}

std::ostream& operator<<(std::ostream& out, const Plotno& p)
{
  for(ILuint i=p.wysokosc;i>0;i--)
    {
      for(ILuint j=0;j<p.szerokosc;j++)
        out<<p.obraz[i*p.szerokosc+j]<<" ";
      out<<endl;
    }
  return out;
}
