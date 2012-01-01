// TM_Rectangular.h: interface for the TM_Rectangular class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TM_RECTANGULAR_H__42549780_ADDF_4ED7_B920_28C4E096CC32__INCLUDED_)
#define AFX_TM_RECTANGULAR_H__42549780_ADDF_4ED7_B920_28C4E096CC32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "GuiaR.h"

class TMr : public GuiaR
{
public:
	TMr();
//	TMr(double /*a_*/, double /*b_*/, double /*freq_*/, double /*Er_*/, double /*Ur_*/);

	virtual ~TMr();

	//atributos
public:
	
	double Potencia;


	CArray<Grafico,Grafico> graf_E;

	CArray<Grafico,Grafico> graf_H;


	double color_i;
	double color_j;
	double color_z;
	double color_t;


	//cores para as linhas de força dos guias
	double RedF,GreenF,BlueF;
	double RedT,GreenT,BlueT;


	double RedHF,GreenHF,BlueHF;
	double RedHT,GreenHT,BlueHT;


	//campo magnetico
	int NCamposZ;//numero de campos a desenhar ao longo do eixo z
	int NCamposJ;//numero de campos a desenhar transversalmente

	//campo electrico
	int NCamposx;
	int NCamposy;
	

	CArray<CString,CString> Formulas;

//funções
public:

	//campo Eléctrico
	virtual void DrawE( double /*t*/);//funcao que calcula os pontos do campo electrico
	virtual void DrawE_2Da( double /*t*/, double /*a*/);//funcao que calcula os pontos do campo electrico
	virtual void DrawE_2Db( double /*t*/, double /*b*/);//funcao que calcula os pontos do campo electrico
	virtual void DrawE_2Dz( double /*t*/, double /*z*/);//funcao que calcula os pontos do campo electrico

//	virtual void DrawE_alternativo( double /*t*/);//funcao que calcula os pontos do campo electrico

//	void DrawE_alternativo( double /*t*/);//funcao que calcula os pontos do campo electrico

//	void DrawE_Draw();//funcao que desenha os pontos do campo electrico
	virtual void DrawE_Draw(double /*t*/);//funcao que desenha os pontos do campo electrico
	virtual void DrawE_Draw_2Dz( double /*t*/);


	void GetZero_E(double , double &, double &);//funcão auxiliar usada por DrawE() para calculos
	void GetZero_H(double , double &, double &);//funcão auxiliar usada por DrawH_Draw() para calculos
	
	
	//funcao auxiliar para determinar a cor do campo magnetico
	// ou seja se este roda para a direita ou para a esquerda
//	int quadrante(double /*pxy*/, int /*m*/,int /*n*/, double /*a*/, double /*b*/); 
	




//	void DrawH( double );
	virtual void DrawH_alternativo( double );
	virtual void DrawH_Draw(double /*t*/);//funcao que desenha os pontos do campo magnetico

	Complexo Ex(double, double, double, double);
	Complexo Ey(double, double, double, double);
	Complexo Ez(double, double, double, double);

	Complexo Hx(double, double, double, double);
	Complexo Hy(double, double, double, double);
	Complexo Hz(double, double, double, double);

	double Sav_z(double,double,double, double);


//private:

	//double swap_cor(double /*cor1*/, double /*cor2*/, bool /*cor*/);
	///*true devole cor1 - false devolve cor2*/


};

#endif // !defined(AFX_TM_RECTANGULAR_H__42549780_ADDF_4ED7_B920_28C4E096CC32__INCLUDED_)
