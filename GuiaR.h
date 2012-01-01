// GuiaR.h: interface for the GuiaR class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUIAR_H__4D5D7F3E_1E7B_4E3F_A58D_193FD0E272BE__INCLUDED_)
#define AFX_GUIAR_H__4D5D7F3E_1E7B_4E3F_A58D_193FD0E272BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ondas.h"

class GuiaR  : public Ondas
{
public:
	GuiaR();
	virtual ~GuiaR();

	double z_inicia_desenho_grafE;
	double z_inicia_desenho_grafH;



	int Set(double /*a_*/, double /*b_*/, double /*freq_*/, double /*Er_*/, double /*Ur_*/);
	
	double a;//largura do guia
	double b;//altura do guia
	int m;//modo m
	int n;//modo n

	int nLinhasA;//numero de linhas de força a desenhar no eixo x - largura
	int nLinhasB;//numero de linhas de força a desenhar no eixo y - altura




//FUNÇÕES
public:


	double Getfc();//devolve a frequencia de corte
	Complexo alfaB();//constante de propagação do meio
	//alfaB.i = Bmn [Rad/m] constante de fase
	//alfaB.r = alfa_mn [Np/m] constante de atenuação
	double M();
	double N();
	double GetLmn();//devolve o comprimento de onda do modo mn



	//funções a serem overidden (sobrepostas) pelas classes derivadas
	virtual void DrawE( double ){};
	
	virtual void DrawE_2Da(double /*t*/, double /*a*/){};
	virtual void DrawE_2Db(double /*t*/, double /*b*/){};
	virtual void DrawE_2Dz(double /*t*/, double /*z*/){};

	virtual void DrawE_Draw(double){};
	virtual void DrawE_Draw_2Dz( double /*t*/){};

	virtual void DrawH( double ){};
	virtual void DrawH_alternativo( double ){};

	virtual void DrawH_Draw( double ){};


	
};

#endif // !defined(AFX_GUIAR_H__4D5D7F3E_1E7B_4E3F_A58D_193FD0E272BE__INCLUDED_)
