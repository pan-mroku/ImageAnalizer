#ifndef __MASKI_ROZNE
#define __MASKI_ROZNE

#include "maska.hpp"

class MaskaGauss: public Maska
{
protected:
  double t;
  void wypelnij();
public:
  MaskaGauss(ILuint _bok=3);

  double T();
  void T(double _t);
};

//-----------------------------------------------------------------

class MaskaX : public Maska
{
public:
  MaskaX();
};

//-----------------------------------------------------------------

class MaskaY : public Maska
{
public:
  MaskaY();
};

//-----------------------------------------------------------------

class MaskaXX : public Maska
{
public:
  MaskaXX();
};

//-----------------------------------------------------------------

class MaskaXY : public Maska
{
public:
  MaskaXY();
};

//-----------------------------------------------------------------

class MaskaYY : public Maska
{
public:
  MaskaYY();
};

//-----------------------------------------------------------------

class MaskaXXX : public Maska
{
public:
  MaskaXXX();
};

//-----------------------------------------------------------------

class MaskaXXY : public Maska
{
public:
  MaskaXXY();
};

//-----------------------------------------------------------------

class MaskaXYY : public Maska
{
public:
  MaskaXYY();
};

//-----------------------------------------------------------------

class MaskaYYY : public Maska
{
public:
  MaskaYYY();
};

//-----------------------------------------------------------------

#endif
