// Ondas.cpp: implementation of the Ondas class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "campos3d.h"
#include "Ondas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ondas::Ondas()
{

	t=0;


	Q=10;
	f=10000000;
	Ur=1;
	Er=1;
	O=0;
	G=0.0002;
	Em=50;
	Emy=0;
	n.r=376.73430918211;
	n.i=0;
	teta=0;

	xRot=40;
	yRot=40;
	zRot=0;
}

Ondas::~Ondas()
{

}


double Ondas::Getvf()
{
	return C/sqrt(Er*Ur);
}

double Ondas::GetL()
{
	return C/(f*sqrt(Ur*Er));
}

Complexo Ondas::GetAB()
{
	Complexo j(0,1);
	double w=GetW();
	double u=GetU();
	double e=GetE();

	//const. de propagação do meio
	return sqrt(j*w*u*(G+j*w*e));
	//return sqrt(j*2*PI*f*Uo*Ur*(G+j*2*PI*f*Eo*Er));

}

double Ondas::GetE()
{
	return Eo*Er;
}

double Ondas::GetU()
{
	return Uo*Ur;
}

double Ondas::GetW()
{
	return 2*PI*f;
}

void Ondas::SetG(double g)
{
	Complexo j(0,1);
	double W=GetW();
	G=g;

	n=sqrt(j*W*Ur*Uo/(G+j*W*Er*Eo));
}

double Ondas::GetG()
{
	return G;
}

void Ondas::Setn(Complexo x)
{
	Complexo j(0,1),g;
	double W=GetW(),E=GetE(),U=GetU();
	n=x;
	g=j*W*U/(n^2)-j*W*E;
	G=g.r;
}

Complexo Ondas::Getn()
{
	return n;
}




///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//   classe Grafico - funções



IMPLEMENT_SERIAL( Grafico, CObject, 1 );



Grafico::Grafico()
{


	
}


Grafico::~Grafico()
{
	
	Ex_arrai.RemoveAll();
	Ey_arrai.RemoveAll();
	Ez_arrai.RemoveAll();

	Hx_arrai.RemoveAll();
	Hy_arrai.RemoveAll();
	Hz_arrai.RemoveAll();

}