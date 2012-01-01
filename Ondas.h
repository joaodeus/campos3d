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

	double f;//[Hz] frequência
	double Ur;//[H/m] permeabilidade magnética relativa
	double Er;//[F/m] permitividade electrica relativa
	double Em;//[V/m] amplitude do campo eléctrico
	double Emy;//[V/m] componente y para polarização vertical
	//double Hm;// amplitude do campo magnetico
	//double Hmx;// componente x para polarização vertical


	//double alfa;//[Np/m] constante de atenuação
	double teta;// ângulo de desfasagem inicial
	double O;//ângulo para pol. circular
	double Q;//factor antialising Q>=2
protected:
	Complexo n;//[ohm] impedância intrínseca do meio
	double G;//[S/m] condutividade do meio
	
public:
	
	double Getvf();//[m/s] velocidade de propagação da onda
	double GetL();//[m] comprimento de onda
	//double GetB();//[Rad/m] constante de fase 
	double GetE();//[F/m] permitividade eléctrica
	double GetU();//[H/m] permeabilidade magnética
	double GetW();//[Rad] 2*PI*f frequência angular
	Complexo GetAB();//const. de propagação do meio

	double GetG();//[S/m] condutividade do meio
	void SetG(double);
	Complexo Getn();//[ohm] impedância intrínseca do meio
	void Setn(Complexo);


	CArray<Complexo,Complexo> Hm_array;//componente y do campo magnetico
	CArray<Complexo,Complexo> Hmx_array;//componente x do campo magnetico (só para polarização vertical)


	//Arrays que guardam valores, para o desenho do gráfico
	CArray<Complexo,Complexo> Em_array;//componente x do campo electrico
	CArray<Complexo,Complexo> Emy_array;//componente y do campo electrico (só para polarização vertical)



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
