#include "plotno.hpp"
#include "maska.hpp"
#include "maski_rozne.hpp"

using std::cerr;
using std::endl;

Plotno::Plotno()
{
  ilGenImages(1,&id);
  szerokosc=0;
  wysokosc=0;
  obraz=0;
}

Plotno::Plotno(const char* plik)
{
  ilGenImages(1,&id);
  ilLoadImage(plik);
  ILubyte* tmp=ilGetData();
  szerokosc=ilGetInteger(IL_IMAGE_WIDTH);
  wysokosc=ilGetInteger(IL_IMAGE_HEIGHT);

  obraz=new Pixel[wysokosc*szerokosc];
  for(ILuint i=0;i<wysokosc;i++)
    for(ILuint j=0;j<szerokosc;j++)
      {
        ILuint w=i*szerokosc+j;
        obraz[w]=tmp[3*w];
      }
}

Plotno::Plotno(ILuint _szerokosc, ILuint _wysokosc)
{
  ilGenImages(1,&id);
  szerokosc=_szerokosc;
  wysokosc=_wysokosc;
  obraz=new Pixel[wysokosc*szerokosc];
  for(ILuint i=0;i<wysokosc;i++)
    for(ILuint j=0;j<szerokosc;j++)
      obraz[i*szerokosc+j]=0;
}

Plotno::~Plotno()
{
  delete[] obraz;
  ilDeleteImages(1,&id);
}

Plotno::Plotno(const Plotno& kopia)
{
  *this=kopia;
}

Plotno& Plotno::operator=(const Plotno& kopia)
{
  ilGenImages(1,&id);

  szerokosc=kopia.szerokosc;
  wysokosc=kopia.wysokosc;

  obraz=new Pixel[kopia.wysokosc*kopia.szerokosc];

  for(ILuint i=0;i<kopia.wysokosc;i++)
    for(ILuint j=0;j<kopia.szerokosc;j++)
      obraz[i*szerokosc+j]=kopia[i*szerokosc+j];

  return *this;
}

Plotno::Plotno(const Pixel _obraz[],ILuint _szerokosc, ILuint _wysokosc)
{
  ilGenImages(1,&id);
  szerokosc=_szerokosc;
  wysokosc=_wysokosc;
  obraz=new Pixel[szerokosc*wysokosc];
  for(ILuint j=0;j<wysokosc;j++)
    for(ILuint i=0;i<szerokosc;i++)
      obraz[i+j*szerokosc]=_obraz[i+j*szerokosc];
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
  ilBindImage(id);

  ILubyte* nowy=new ILubyte[3*szerokosc*wysokosc];

  for(ILuint x=0;x<szerokosc;x++)
    for(ILuint y=0;y<wysokosc;y++)
      {
        ILuint index_nowy=3*(y*szerokosc+x);
        ILuint index_obraz=y*szerokosc+x;
        nowy[index_nowy]=obraz[index_obraz].R();
        nowy[index_nowy+1]=obraz[index_obraz].G();
        nowy[index_nowy+2]=obraz[index_obraz].B();
      }
  ilTexImage(szerokosc,wysokosc,1,3,IL_RGB,IL_UNSIGNED_BYTE,nowy);
  ilSaveImage(plik);
  delete[] nowy;
}

ILuint Plotno::Wysokosc() const
{
  return wysokosc;
}

ILuint Plotno::Szerokosc() const
{
  return szerokosc;
}

Plotno Plotno::Splot(const Maska& maska)
{
  Plotno nowe=*this;
  
  for(ILuint i=0;i<wysokosc;i++)
    for(ILuint j=0;j<szerokosc;j++)
      nowe[i*szerokosc+j]=maska.Splot(*this,j,i);

  return nowe;
}

Plotno Plotno::BW()
{
  Plotno wynik(*this);
  for(ILuint i=0;i<szerokosc*wysokosc;i++)
    wynik.obraz[i]=wynik.obraz[i].BW();
  return wynik;
}

Plotno Plotno::Prewitt()
{
  double maska_tab[9]={-1,-1,-1,-1,8,-1,-1,-1,-1};
  Maska maska(maska_tab,3,3,1);
  return BW().Splot(maska);
}

Plotno Plotno::Rozmyj(ILuint _ile_razy)
{
  double cl_znow_nie_ogarnia[]={1,1,1,1,1,1,1,1,1};
  Maska maska(cl_znow_nie_ogarnia,3,3,9);
  Plotno wynik=*this;
  for(ILuint i=0;i<_ile_razy;i++)
    wynik=wynik.Splot(maska);
  return wynik;
}

Plotno Plotno::Filtruj()
{
  Maska t[4];
  t[0]= MaskaKrawedz0();
  t[1]=MaskaKrawedz45();
  t[2]=MaskaKrawedz90();
  t[3]=MaskaKrawedz135();

  Maska m[4]={Maska0(), Maska45(), Maska90(), Maska135()};

  Pixel wynik[4]={0,0,0,0};

  Plotno bw=Rozmyj(1).BW();
  Plotno nowe(szerokosc,wysokosc);

  for(ILuint x=0;x<szerokosc;x++)
    for(ILuint y=0;y<wysokosc;y++)
      {
        for(ILuint i=0;i<4;i++)
          wynik[i]=t[i].Splot(bw,x,y);

        ILuint kierunek=0;
        for(ILuint i=1;i<4;i++)
          if(wynik[i]>wynik[kierunek])
            kierunek=i;

        nowe[y*szerokosc+x]=m[kierunek].Splot(bw,x,y);
      }
	
  return nowe;
}

Plotno Plotno::Hough(Plotno* ak)
{
  //Maksymalny r to przekątna obrazu
  ILuint R=floor(sqrt((double)(szerokosc*szerokosc+wysokosc*wysokosc)));

  ILuint* akumulator=new ILuint[270*R];
  //czyścimy akumulator
  for(ILuint i=0;i<270*R;i++)
    akumulator[i]=0;

  //liczymy akumulator dla każdego piksla
  for(ILuint x=0;x<szerokosc;x++)
    for(ILuint y=0;y<wysokosc;y++)
      {
        //pod uwagę bierzemy tylko czarne piksle
        if(obraz[x+y*szerokosc].BW()>0)continue;

        //zapisywanie akumulatora
        for(ILint fi=-90;fi<180;fi++)
          {
            double fi_f=fi;
            double r=x*cos(fi_f*PI/180)+y*sin(fi_f*PI/180);

            //jeśli r wychodzi ujemne, to prostą będzie musiał złapać inny kąt
            if(r<0)
              continue;

            akumulator[fi+90+270*ILuint(r)]+=1;
          }
      }

  Plotno nowe(szerokosc,wysokosc);
  for(ILuint i=0;i<szerokosc*wysokosc;i++)
    nowe[i]=255;

  //szukamy maksimum
  ILuint fi=0,r=0;
  for(ILuint i=0; i<270;i++)
    for(ILuint j=0;j<R;j++)
      if(akumulator[fi+270*r]<akumulator[i+270*j])
        {
          fi=i;
          r=j;
        }
  cerr<<akumulator[fi+270*r]<<endl;
  //rysujemy prostą
  for(ILuint y=0;y<wysokosc;y++)
    for(ILuint x=0;x<szerokosc;x++)
      {
        double fi_f=fi;
        fi_f-=90; //nie możemy od razu odjąć od fi, bo się unsigned chachmęci
        double r_=x*cos(fi_f*PI/180)+y*sin(fi_f*PI/180);


        if(r_<0)        //jak wyżej
          continue;

        //jeśli r się zgadza to zaznaczamy prostą
        if(floor(r_)==r)
            nowe[x+y*szerokosc]=0;
      }
  
  //Jeśli chcemy zapisać gdzieś ak (podano parametr) to trzeba przerobić akumulator na piksle
  if(ak)
    {
      delete [] ak->obraz;
      ak->obraz=new Pixel[270*R];
      for(ILuint i=0;i<R*270;i++)
        ak->obraz[i]=akumulator[i];
      ak->wysokosc=R;
      ak->szerokosc=270;
    }

  delete [] akumulator;
  return nowe;
}

Plotno Plotno::Lindeberg()
{
  MaskaGauss gauss(5);
  //gauss.T(64);

  MaskaX mx;
  MaskaY my;

  MaskaXY mxy;
  MaskaXX mxx;
  MaskaYY myy;

  MaskaXXX mxxx;
  MaskaXXY mxxy;
  MaskaXYY mxyy;
  MaskaYYY myyy;

  Plotno rozmycie=BW().Splot(gauss);
  //      return rozmycie;
  Plotno wynik(szerokosc,wysokosc);
  
  for(ILuint x=0;x<szerokosc;x++)
    for(ILuint y=0;y<wysokosc;y++)
      {
        
        ILint Lx=mx.Splot(rozmycie,x,y);
        ILint Ly=my.Splot(rozmycie,x,y);

        ILint Lxx=mxx.Splot(rozmycie,x,y);
        ILint Lxy=mxy.Splot(rozmycie,x,y);
        ILint Lyy=myy.Splot(rozmycie,x,y);
        
        ILint Lxxx=mxxx.Splot(rozmycie,x,y);
        ILint Lxxy=mxxy.Splot(rozmycie,x,y);
        ILint Lxyy=mxyy.Splot(rozmycie,x,y);
        ILint Lyyy=myyy.Splot(rozmycie,x,y);

        ILint I=Lx*Lx*Lxx+2*Lx*Ly*Lxy+Ly*Ly*Lyy;

        if(I==0)
          if((Lx*Lx*Lx*Lxxx+3*Lx*Lx*Ly*Lxxy+3*Lx*Ly*Ly*Lxyy+Ly*Ly*Ly*Lyyy)<0)
            wynik.obraz[y*szerokosc+x]=255;
      }
  return wynik;
}

Plotno Plotno::operator+(const Plotno& p)
{
  Plotno wynik(*this);
  for(ILuint x=0;x<szerokosc;x++)
    for(ILuint y=0;y<wysokosc;y++)
      //wynik[y*szerokosc+x]=(wynik[y*szerokosc+x]+p[y*szerokosc+x])/double(2);
      wynik[y*szerokosc+x]+=p[y*szerokosc+x];
  return wynik;
}

Plotno Plotno::operator-(const Plotno& p)
{
  Plotno wynik(*this);
  for(ILuint x=0;x<szerokosc;x++)
    for(ILuint y=0;y<wysokosc;y++)
      //wynik[y*szerokosc+x]=(wynik[y*szerokosc+x]-p[y*szerokosc+x])/double(2);
      wynik[y*szerokosc+x]-=p[y*szerokosc+x];
  return wynik;
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
