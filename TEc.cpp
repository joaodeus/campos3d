// TEc.cpp: implementation of the TEc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "campos3d.h"
#include "TEc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TEc::TEc()
{

}

TEc::~TEc()
{

}


Complexo TEc::Er(double r, double o, double z, double t)
{

//	Complexo j(0,1);
	Complexo ab=alfaB();
	
	
	double W=GetW();
	double U=GetU();
	double h=d_ha()/a;

	
	// + ou - ?????
	return -W*U*n/ (r*pow(h,2))
		*_jn(n,h*r)*sin(n*o)*exp(W*t-ab*z);
	
}

Complexo TEc::EO(double r, double o, double z, double t)
{
//	Complexo j(0,1);
	Complexo ab;

	double W=GetW();
	double U=GetU();
	double h=d_ha()/a;

	ab=alfaB();


	return W*U/pow(h,2)
		*_djn(h*r)*cos(n*o)*exp(W*t-ab*z);

}

Complexo TEc::Ez(double r, double o, double z, double t)
{

	Complexo E(0,0);
	return E;
}


Complexo TEc::Hr(double r, double o, double z, double t)
{

	//Complexo j(0,1);
	Complexo ab=alfaB();

	double W=GetW();
	double h=d_ha()/a;

	

	return -ab/pow(h,2)
		*_djn(h*r)*cos(n*o)*exp(W*t-ab*z);

}

Complexo TEc::Ho(double r, double o, double z, double t)
{

	Complexo ab=alfaB();

	double W=GetW();
	double h=d_ha()/a;

	return n*ab/r/pow(h,2)
		*_jn(n,h*r)*sin(n*o)*exp(W*t-ab*z);
}

Complexo TEc::Hz(double r, double o, double z, double t)
{
	Complexo ab=alfaB();
	double h=d_ha()/a;
	double W=GetW();

	return cos(n*o)*_jn(n,h*r)*exp(W*t-ab*z);
}



Complexo TEc::alfaB()
{
	Complexo ab;
	double h;
	double h2;
	double W2=pow(GetW(),2);
	double U=GetU();
	double E=GetE();

	h= d_ha()/a;

	h2=pow( h/0.001 ,2);
//	h2=(h/0.001)^2;

	double x=h2-W2*U*E;

	if (x >= 0)
	{
		ab.r=sqrt(x);
		ab.i=0;
	}
	else
	{
		ab.r=0;
		ab.i=sqrt(-x);
	}

	return ab;
}



double TEc::d_ha()
{

	double x;
	double a;
	double b;
	double z;
	double step=0.1;
	
	int l=0;//ordem da raíz

	for(x=2*step;;x+=step)
	{
		a=djn(x-step);
		b=djn(x);

		if (a*b <= 0)
		{
			l++;
			if (l==m)
			{
				z=zeros(x-step,x);
				return z;
			}
		}	
	}

}

double TEc::zeros(double a,double b)
{
	double d,fd,fa,fb,erro=0.000001;
	fa=djn(a);
	fb=djn(b);

	d=(a+b)/2;
	//fd=f(d);

	fd=djn(d);

	if (fa==0)
		return a;
	if (fb==0)
		return b;

	if (fabs(fd) < erro)
		return (d);

	if (fa*fd <=0)
	{
		return zeros(a,d);
	}
	else
	{
		return zeros(d,b);
	}
}



double TEc::_djn(double r)
{
	double h=d_ha()/a;

	return (n/r* _jn(n,h*r) - h*_jn(n+1,h*r));
}

double TEc::djn(double r)
{
	if (n==0)
		return (-_jn(1,r));
	else
		return 0.5*(_jn(n-1,r)-_jn(n+1,r));
}



int TEc::Get_m()
{
	return m;
}

int TEc::Get_n()
{
	return n;
}

void TEc::DrawE(double t)
{

}

void TEc::DrawE_Draw(double t)
{}

void TEc::DrawH(double t)
{}

void TEc::DrawH_Draw(double t)
{

	
}