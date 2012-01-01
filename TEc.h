// TEc.h: interface for the TEc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEC_H__88F51B61_F4DF_11DA_B956_8189E525E476__INCLUDED_)
#define AFX_TEC_H__88F51B61_F4DF_11DA_B956_8189E525E476__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiaC.h"

class TEc : public GuiaC  
{
public:
	TEc();
	virtual ~TEc();

	

	//atributes
public: 

//	double h;

	CArray<Grafico,Grafico> graf_E;
	CArray<Grafico,Grafico> graf_H;


//funções
public:
	

	Complexo Er(double, double, double, double);
	Complexo EO(double, double, double, double);
	Complexo Ez(double, double, double, double);
	
	Complexo Hr(double, double, double, double);
	Complexo Ho(double, double, double, double);
	Complexo Hz(double, double, double, double);

	Complexo alfaB();
	double d_ha();
	double zeros(double, double);
	double _djn(double);//derivada de Bessel
	double djn(double);//derivada de Bessel 
						//fórmula alternativa para calcular zeros



	int Get_m();
	int Get_n();

	void DrawE( double /*t*/);//funcao que calcula os pontos do campo electrico
	void DrawE_Draw(double );//funcao que desenha os pontos do campo electrico


	void DrawH( double );//funcao que calcula os pontos do campo electrico
	void DrawH_Draw( double );//funcao que desenha os pontos do campo electrico


};

#endif // !defined(AFX_TEC_H__88F51B61_F4DF_11DA_B956_8189E525E476__INCLUDED_)
