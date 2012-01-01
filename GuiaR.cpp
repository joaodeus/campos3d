// GuiaR.cpp: implementation of the GuiaR class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "campos3d.h"
#include "GuiaR.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GuiaR::GuiaR()
{

	a=0.012;
	b=0.010;
	m=1;
	n=1;
	f=25000000000;
	Ur=1;
	Er=1;

	z_inicia_desenho_grafE=0;
	z_inicia_desenho_grafE=0;
}

GuiaR::~GuiaR()
{

}

int GuiaR::Set(double a_, double b_, double freq_, double Er_, double Ur_)
{
	a=a_;
	b=b_;
	f=freq_;
	Er=Er_;
	Ur=Ur_;

	return 1;
}

double GuiaR::Getfc()
{
	//return 0.5*sqrt(pow(m/(a*0.001),2)+pow(n/(b*0.001),2))
	return 0.5*sqrt(pow(m/(a),2)+pow(n/(b),2))
		/sqrt(Uo*Ur*Eo*Er);
}

Complexo GuiaR::alfaB()
{
	Complexo z;
	double M_,N_,W,E,U;
	double x;

	M_=m*PI/(a);
	N_=n*PI/(b);
	W=2*PI*f;
	E=Er*Eo;
	U=Ur*Uo;

	x=M_*M_+N_*N_-W*W*E*U;
	
	if (x>=0)
	{
		z.r=sqrt(x);
		z.i=0;
	}
	else
	{
		z.r=0;
		z.i=sqrt(-x);
	}
	return z;
}

double GuiaR::M()
{
	return m*PI/a;
}

double GuiaR::N()
{
	return n*PI/b;
}

double GuiaR::GetLmn()
{
	return C/(f*sqrt(Ur*Er))
		///sqrt(1-(pow(m/(a*0.001),2)+pow(n/(b*0.001),2))
		/sqrt(1-(pow(m/(a),2)+pow(n/(b),2))
		/(f*f*4*Uo*Ur*Eo*Er));
}