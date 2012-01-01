// Complexo.h: interface for the Complexo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLEXO_H__CEAD7CC9_9727_4AAA_A210_896245274B81__INCLUDED_)
#define AFX_COMPLEXO_H__CEAD7CC9_9727_4AAA_A210_896245274B81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Complexo  
{

	public:
	Complexo(double,double);
	Complexo();
	virtual ~Complexo();

	double r, i;

	friend Complexo operator+( Complexo a, Complexo b );
	friend Complexo operator+( double a, Complexo b );
	friend Complexo operator+( Complexo a, double b );
	friend Complexo operator-( Complexo a, Complexo b );
	friend Complexo operator-( double a, Complexo b );
	friend Complexo operator-( Complexo a, double b );
	friend Complexo operator-( Complexo a);
	friend Complexo operator*( Complexo a, Complexo b );
	friend Complexo operator*( double a, Complexo b );
	friend Complexo operator*( Complexo a, double b );
	friend Complexo operator/( Complexo a, Complexo b );
	friend Complexo operator/( Complexo a, double b );
	friend Complexo operator/( double a, Complexo b );
	friend Complexo operator^( Complexo x, Complexo y);
	friend Complexo operator^( double x, Complexo y);
	friend Complexo operator^( Complexo x, double y);

	//friend Complexo operator=( Complexo a);
	Complexo &operator=( Complexo & );  // Right side is the argument.
	Complexo &operator=( const double & );  // Right side is the argument.


};

double cabs(Complexo);
double arg(Complexo );
Complexo conj(Complexo);
Complexo sqrt(Complexo);	

Complexo exp(Complexo);

Complexo cos(Complexo);
Complexo sen(Complexo);
Complexo tg(Complexo);
Complexo cotg(Complexo);

Complexo cosh(Complexo);
Complexo senh(Complexo);
Complexo tgh(Complexo);
Complexo cotgh(Complexo);

Complexo arccos(Complexo);
Complexo arcsen(Complexo);
Complexo arctg(Complexo);
Complexo acotg(Complexo);

Complexo asinh(Complexo);
Complexo acosh(Complexo);
Complexo atanh(Complexo);
Complexo acotgh(Complexo);

Complexo ln(Complexo);
Complexo log(Complexo);


#endif // !defined(AFX_COMPLEXO_H__CEAD7CC9_9727_4AAA_A210_896245274B81__INCLUDED_)
