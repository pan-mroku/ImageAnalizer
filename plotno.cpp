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
      {
        nowe[i*szerokosc+j]=maska.Splot(*this,j,i);
      }

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
  return *this; //@FIXME: przerobić na maski
  /*  ILbyte test[4][9]={
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

  Plotno nowe(*this);

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
  cerr<<"tu"<<endl;
	
  return nowe;*/
}

Plotno Plotno::Hough(Plotno* ak)
{
  ILuint R=floor(sqrt((double)(szerokosc*szerokosc+wysokosc*wysokosc)));
  ILuint* akumulator=new ILuint[270*R];

  for(ILuint i=0;i<270*R;i++)
    akumulator[i]=0;

  for(ILuint j=0;j<wysokosc;j++)
    for(ILuint i=0;i<szerokosc;i++)
      {
        if(obraz[i+j*szerokosc].BW()>0)continue;
        for(ILint fi=-90;fi<180;fi++)
          {
            double fi_f=fi;
            double r=i*cos(fi_f*PI/180)+j*sin(fi_f*PI/180);
            if(r<0)
              {
                if(fi<45)
                  fi_f+=180;
                else
                  fi_f-=180;
                r=i*cos(fi_f*PI/180)+j*sin(fi_f*PI/180);
              }
            akumulator[fi+90+270*(ILuint)r]+=1;
          }
      }
  ILuint fi=0,r=0;
  for(ILuint i=0; i<270;i++)
    for(ILuint j=0;j<R;j++)
      if(akumulator[fi+270*r]<akumulator[i+270*j])
        {
          fi=i;
          r=j;
        }
  Plotno nowe=*this;
  for(ILuint i=0;i<szerokosc*wysokosc;i++)
    {
      nowe[i]=255;
    }

  for(ILuint j=0;j<wysokosc;j++)
    for(ILuint i=0;i<szerokosc;i++)
      {
        double fi_f=fi-90;
        ILint r_=i*cos(fi_f*PI/180)+j*sin(fi_f*PI/180);
        if(r_<0)
          {
            if(fi_f<45)
              fi_f+=180;
            else
              fi_f-=180;
            r_=i*cos(fi_f*PI/180)+j*sin(fi_f*PI/180);
          }
        if(floor((float)r_)==r)
          {

            nowe[i+j*szerokosc]=0;
          }
      }
  
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
  MaskaX mx;
  MaskaY my;

  MaskaXY mxy;
  MaskaXX mxx;
  MaskaYY myy;

  MaskaXXX mxxx;
  MaskaXXY mxxy;
  MaskaXYY mxyy;
  MaskaYYY myyy;

  Plotno rozmycie=BW().Rozmyj(1);

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
