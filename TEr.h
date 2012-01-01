// TEr.h: interface for the TEr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TER_H__565A3E67_AB71_4B6C_B3FA_FC098C7D1EBF__INCLUDED_)
#define AFX_TER_H__565A3E67_AB71_4B6C_B3FA_FC098C7D1EBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "GuiaR.h"

class TEr  : public GuiaR
{
public:
	TEr();
//	TEr(double /*a_*/, double /*b_*/, double /*freq_*/, double /*Er_*/, double /*Ur_*/);
	virtual ~TEr();

	//atributes
public: 
	CArray<Grafico,Grafico> graf_E;

	CArray<Grafico,Grafico> graf_H;


	double Potencia;



	//cores para as linhas de força dos guias
	double RedF,GreenF,BlueF;
	double RedT,GreenT,BlueT;


	double RedHF,GreenHF,BlueHF;
	double RedHT,GreenHT,BlueHT;


	//campo magnetico
	int NCamposx;
	int NCamposy;


	//funções
public: 
	void DrawE( double /*t*/);//funcao que calcula os pontos do campo electrico
	void DrawE_Draw();//funcao que desenha os pontos do campo electrico


	void DrawH( double );//funcao que calcula os pontos do campo electrico
	void DrawH_Draw( double );//funcao que desenha os pontos do campo electrico

	void GetZero_H(double , double &, double &);//funcão auxiliar usada por DrawE() para calculos


	

	Complexo Ex(double,double,double, double);
	Complexo Ey(double,double,double, double);
	Complexo Ez(double,double,double, double);

	Complexo Hx(double,double,double, double);
	Complexo Hy(double,double,double, double);
	Complexo Hz(double,double,double, double);

	//densidade média de potência
	double Sav_z(double,double,double, double);

};

#endif // !defined(AFX_TER_H__565A3E67_AB71_4B6C_B3FA_FC098C7D1EBF__INCLUDED_)
