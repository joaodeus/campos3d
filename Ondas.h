// Ondas.h: interface for the Ondas class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONDAS_H__C7CECACA_EB4E_4E33_8615_D12792447961__INCLUDED_)
#define AFX_ONDAS_H__C7CECACA_EB4E_4E33_8615_D12792447961__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Complexo.h"


class Ondas  
{
public:
	Ondas();
	virtual ~Ondas();


	////////////////////////////////////////////////////////////////
//	 Variaveis para o desenho grafico

	double xRot;
	double yRot;
	double zRot;

/////////////////
// variaveis da onda


	double t;

	double f;//[Hz] frequ�ncia
	double Ur;//[H/m] permeabilidade magn�tica relativa
	double Er;//[F/m] permitividade electrica relativa
	double Em;//[V/m] amplitude do campo el�ctrico
	double Emy;//[V/m] componente y para polariza��o vertical
	//double Hm;// amplitude do campo magnetico
	//double Hmx;// componente x para polariza��o vertical


	//double alfa;//[Np/m] constante de atenua��o
	double teta;// �ngulo de desfasagem inicial
	double O;//�ngulo para pol. circular
	double Q;//factor antialising Q>=2
protected:
	Complexo n;//[ohm] imped�ncia intr�nseca do meio
	double G;//[S/m] condutividade do meio
	
public:
	
	double Getvf();//[m/s] velocidade de propaga��o da onda
	double GetL();//[m] comprimento de onda
	//double GetB();//[Rad/m] constante de fase 
	double GetE();//[F/m] permitividade el�ctrica
	double GetU();//[H/m] permeabilidade magn�tica
	double GetW();//[Rad] 2*PI*f frequ�ncia angular
	Complexo GetAB();//const. de propaga��o do meio

	double GetG();//[S/m] condutividade do meio
	void SetG(double);
	Complexo Getn();//[ohm] imped�ncia intr�nseca do meio
	void Setn(Complexo);


	CArray<Complexo,Complexo> Hm_array;//componente y do campo magnetico
	CArray<Complexo,Complexo> Hmx_array;//componente x do campo magnetico (s� para polariza��o vertical)


	//Arrays que guardam valores, para o desenho do gr�fico
	CArray<Complexo,Complexo> Em_array;//componente x do campo electrico
	CArray<Complexo,Complexo> Emy_array;//componente y do campo electrico (s� para polariza��o vertical)



};



/////////////////////////////////////////////////
/////////////////////////////////////////////////
/// classe Grafico



#ifndef GRAFICO
#define GRAFICO


class Grafico : public CObject
{

    DECLARE_SERIAL(Grafico);
public:
	Grafico();

	virtual ~Grafico();

	

	CArray<double,double> Ex_arrai;
	CArray<double,double> Ey_arrai;
	CArray<double,double> Ez_arrai;

	CArray<double,double> Hx_arrai;
	CArray<double,double> Hy_arrai;
	CArray<double,double> Hz_arrai;

	double RedE;
	double GreenE;
	double BlueE;

	double RedH;
	double GreenH;
	double BlueH;

	
};


#endif GRAFICO



#endif // !defined(AFX_ONDAS_H__C7CECACA_EB4E_4E33_8615_D12792447961__INCLUDED_)
