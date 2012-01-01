// GuiaC.h: interface for the GuiaC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUIAC_H__8A6D8A80_F332_11DA_B956_B8468DB13B77__INCLUDED_)
#define AFX_GUIAC_H__8A6D8A80_F332_11DA_B956_B8468DB13B77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ondas.h"

class GuiaC : public Ondas  
{
public:
	GuiaC();
	virtual ~GuiaC();

	double a;//raio	
	int m;//modo m, raiz de ordem m 
	int n;//modo n, da função de Bessel de ordem n


	//funções a serem overidden (sobrepostas) pelas classes derivadas
	virtual void DrawE( double ){};
	virtual void DrawE_Draw(double){};

	virtual void DrawH( double ){};
	virtual void DrawH_Draw( double ){};

};

#endif // !defined(AFX_GUIAC_H__8A6D8A80_F332_11DA_B956_B8468DB13B77__INCLUDED_)
