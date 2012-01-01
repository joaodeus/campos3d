// Complexo.cpp: implementation of the Complexo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "campos3d.h"
#include "Complexo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


Complexo::Complexo(double a,double b)
{
	r=a;
	i=b;
}

Complexo::Complexo()
{
	i=0;
	r=0;
}

Complexo::~Complexo()
{
	i=0;
	r=0;
}

//Grafico &Grafico::operator=( Grafico &a )

Complexo &Complexo::operator =(Complexo &a)
{
	r=a.r;
	i=a.i;
	return *this;
}

Complexo &Complexo::operator =(const double &a)
{
	r=a;
	i=0;
	return *this;
}

// Operator overloaded using a friend function
Complexo operator+( Complexo a , Complexo b)
{
	Complexo z;
	z.r=a.r+b.r;
	z.i=a.i+b.i;
return z;
}

Complexo operator+( double a , Complexo b )
{
	Complexo z;
	z.r=a+b.r;
	z.i=b.i;
return z;
}

Complexo operator+( Complexo a , double b )
{
	Complexo z;
	z.r=a.r+b;
	z.i=a.i;
	return z;
}

Complexo operator-( Complexo a , Complexo b )
{
	Complexo z;
	z.r=a.r-b.r;
	z.i=a.i-b.i;
	return z;
}

Complexo operator-( double a , Complexo b )
{
	Complexo z;
	z.r=a-b.r;
	z.i=-b.i;
	return z;
}

Complexo operator-( Complexo a , double b )
{
	Complexo z;
	z.r=a.r-b;
	z.i=a.i;
	return z;
}

Complexo operator-( Complexo a )
{
	Complexo z;
	z.r=-a.r;
	z.i=-a.i;
	return z;
}


Complexo operator*( Complexo a , Complexo b )
{
	Complexo z;
	z.r=a.r*b.r-a.i*b.i;
	z.i=a.r*b.i+a.i*b.r;
	return z;
}


Complexo operator*( double a , Complexo b )
{
	Complexo z;
	z.r=a*b.r;
	z.i=a*b.i;
	return z;
}


Complexo operator*( Complexo a , double b )
{
	Complexo z;
	z.r=a.r*b;
	z.i=a.i*b;
	return z;
}

Complexo operator/( Complexo a , Complexo b )
{
	/*
	Complexo z;
	z.r=(a.r*b.r + a.i*b.i) / (b.r*b.r + b.i*b.i);
	z.i=(a.i*b.r - a.r*b.i)/ (b.r*b.r + b.i*b.i);
	return z;*/
	Complexo c;
	double r,den;
	
	if (fabs(b.r) >= fabs(b.i))
	{
		r=b.i/b.r;
		den=b.r+r*b.i;
		c.r=(a.r+r*a.i)/den;
		c.i=(a.i-r*a.r)/den;
	}
	else
	{
		r=b.r/b.i;
		den=b.i+r*b.r;
		c.r=(a.r*r+a.i)/den;
		c.i=(a.i*r-a.r)/den;
	}

	return c;
}

Complexo operator/( double a , Complexo b )
{
	
	Complexo c;
	Complexo aa(a,0);
	double r,den;
	
	if (fabs(b.r) >= fabs(b.i))
	{
		r=b.i/b.r;
		den=b.r+r*b.i;
		c.r=(aa.r+r*aa.i)/den;
		c.i=(aa.i-r*aa.r)/den;
	}
	else
	{
		r=b.r/b.i;
		den=b.i+r*b.r;
		c.r=(aa.r*r+aa.i)/den;
		c.i=(aa.i*r-aa.r)/den;
	}

	return c;
}


Complexo operator/( Complexo a , double b )
{
	a.r=a.r/b;
	a.i=a.i/b;
	return a;
}

Complexo operator^( Complexo x , Complexo y )
{
	if (x.r==0 && x.i==0)
		return x;
	return exp(y*ln(x));
}


Complexo operator^( double x , Complexo y )
{
	Complexo z(x,0);
	if (x==0)
		return z;
	return exp(y*ln(z));
}

Complexo operator^( Complexo x , double y )
{
	if (x.r==0 && x.i==0)
		return x;
	return exp(y*ln(x));
}


double cabs(Complexo z)
{
	double x,y,temp;

	x=fabs(z.r);
	y=fabs(z.i);

	if (x==0)
		return y;
	if (y==0)
		return x;
	if (x<=y)
	{
		temp=y/x;
		return x*sqrt(1+temp*temp);
	}
	else
	{
		temp=x/y;
		return y*sqrt(1+temp*temp);

	}
	//return sqrt(z.r*z.r+z.i*z.i);
}


double arg(Complexo x)
{
	return atan2(x.i,x.r);
}

Complexo conj(Complexo x)
{
	Complexo z;
	z.r=x.r;
	z.i=-x.i;
	return z;
}

Complexo sqrt(Complexo x)
{
	double P=cabs(x);
	double O=arg(x);

	x.r=sqrt(P)*cos(O/2);
	x.i=sqrt(P)*sin(O/2);

	return x;
}

Complexo exp(Complexo x)
{
	Complexo y;
	y.r=exp(x.r)*cos(x.i);
	y.i=exp(x.r)*sin(x.i);
	return y;
	/*Complexo z;
	z.r=exp(x.r)*cos(x.i);
	z.i=exp(x.r)*sin(x.i);
	
	return z;*/
}


Complexo ln(Complexo x)
{
	Complexo z;
		
	z.r=log(cabs(x));
	z.i=atan2(x.i,x.r);

	//log(z) = log(abs(z)) + i*atan2(y,x)

	return z;
}


Complexo log(Complexo x)
{
//	Complexo a(10,0);

	//return ln(x)/ln(a);
	return ln(x)/log(10);
}







Complexo cos(Complexo x)
{
	Complexo j(0,1);
	//return ( e^j*x + e^-j*x )/2;
	return ((exp(j*x) + exp(-j*x))/2);
}

Complexo sen(Complexo x)
{
	Complexo j(0,1);
	return ((exp(j*x) - exp(-j*x))/(j*2));
}

Complexo tg(Complexo x)
{
	return sen(x)/cos(x);
}

Complexo cotg(Complexo x)
{
	return cos(x)/sen(x);
}







Complexo cosh(Complexo x)
{
	return ((exp(x) + exp(-x))/2);
}

Complexo senh(Complexo x)
{
	return ((exp(x) - exp(-x))/2);
}

Complexo tgh(Complexo x)
{

	return (	(exp(x)-exp(-x)) / (exp(x)+exp(-x) ) 	);
	//return senh(x)/cosh(x);
}

Complexo cotgh(Complexo x)
{
	return (	(exp(x)+exp(-x)) / (exp(x)-exp(-x) ) 	);
	//return cosh(x)/senh(x);
}







Complexo arccos(Complexo z)
{
	Complexo j(0,1);
	//return -j*ln(z+sqrt(z^2+1));
	return -j*ln(z+j*sqrt(1-z^2));
}

Complexo arcsen(Complexo z)
{
	Complexo j(0,-1),v(0,1);
	return j*ln(v*z+sqrt(1-z^2));
//	Complexo j(0,1);
	//return -j*ln(j*z+sqrt(1-z^2));
//	return -j*ln(j*z+sqrt(1-z^2));
}

Complexo arctg(Complexo z)
{
	/*Complexo j(0,1);
	return -0.5*j*ln((1+j*x)/(1-j*x));*/
	return 0.5*ln((1+z)/(1-z));
}

Complexo acotg(Complexo x)
{
	/*Complexo j(0,1);
	return -0.5*j*ln((x+j)/(x-j));//?????????*/
	return 0.5*ln((x+1)/(x-1));
}





Complexo asinh(Complexo z)
{
	//return ln(z+sqrt(z^2+1));
	return ln(z+(z*z+1)^0.5);

}

Complexo acosh(Complexo z)
{
	return ln(z+sqrt(z^2-1));
}

Complexo atanh(Complexo z)
{
	return 0.5*ln((1+z)/(1-z));
}

Complexo acotgh(Complexo z)
{
	return 0.5*ln((z+1)/(z-1));
}

