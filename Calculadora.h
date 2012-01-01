// Calculadora.h: interface for the Calculadora class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCULADORA_H__53B14E79_9F6E_46BD_ADE8_327DD1BE2107__INCLUDED_)
#define AFX_CALCULADORA_H__53B14E79_9F6E_46BD_ADE8_327DD1BE2107__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Complexo.h"


class Calculadora 
{
public:
	Calculadora();
	virtual ~Calculadora();

private:
	typedef struct funcao
	{
		struct funcao *anterior,*proximo;
		long double operando;
		long double j;
		char operador;
		char flag;
		char priori;
		
		//derivadas
		char derivada;
		int nivel;

	}list_d;

	struct
	{
		list_d *inicio,*fim;
	}lista;


public:
	//double r,i;
	char erro;
	bool ERRO;
	int INFINITO;
	int flag_graus_rad_grados;
	
	//valores das variaveis da funcao f_n_variaveis(CString , double, CString);
	//CDWordArray xn;
	CArray<double,double> xn;
	//variaveis da funcao f_n_variaveis(CString , double, CString);
	CStringArray variaveis_n;

	//Interpolacao x, fx
	CArray<double,double> Interpolacao_x;
	CArray<double,double> Interpolacao_fx;


	//guarda os zeros encontrados
	CArray<double,double> zeros;
	//guarda as solucoes encontradas da equacao _resolve()
	CArray<double, double> solucoes_equacao;
	CArray<Complexo, Complexo> solucoes_equacao_Complexas;

	//funções------------------------------------------------------
	double zeros_find(CString,CString,double,double,double,double);
	double zero(CString,CString,double,double,double);

	int equacao_resolve_procura(CString,CString,CString,double,double,double,double);
	int equacao_resolve_procura_Complexo(CString,CString,CString,double,double,double,double);
	
	double equacao_resolve(CString,CString,CString,double,double,double);


	CString Derivada(CString /*f(x)*/, CString /* x */);

	Complexo f(CString,double,CString);
	Complexo fxy(CString,double,CString,double,CString,double,CString);
	Complexo f_n_variaveis(CString , double, CString);
	
	double Integral(CString, CString, double, double, double);
	double IntegralArea(CString, CString, double, double, double);

	double IntegralD(CString, CString, CString, double, double, double,double,double);
	double IntegralDsc(CString, CString, CString, double, double, double,double,double);
	double Integral_Duplo_Funcoes(CString /*fxy*/, CString /*varx*/, CString /*vary*/, 
					double /*Ax*/, double /*Bx*/, 
					CString /*y=fa(x)*/ ,CString /*y=fb(x)*/,double /*m*/);

//	double Calculadora::IntegralD(CString fx, CString x, CString y,double a, double b
//							  , double ay, double by, double m)


	void GetVariaveis(CString);
	int GraficoTemporal(CString);
	double Solve_n_Variaveis(CString ,/*formula*/double /*min*/, 
								double/*max*/, double /*incremento*/,
								double/*precisao*/);

	//função de teste, analiza todas as funções 
	//e todas as constantes que a classe suporta
	//devolve 0 se a string inserida não é função ou constante suportada
//	int funcoes_contantes(CString);


	//numa formula tipo f1(u1,u2,..un)=f2(v1,v2,...,vn) 
	//P*V=n*R*T, procura as variaveis u1,v1,etc..
	//neste caso: P, V, n, R, T
	//devolve o numero de variaveis encontradas
	//e guarda no arrai formula_var, as variaveis encontradas
	//variaveis da funcao find_var()
	int find_var_formula(CString, CString);
	int valida_variaveis(CString);

	CArray<CString,CString> var_formula;
	CArray<CString,CString> var_substitui_aux;
	CArray<int,int> var_substitui_aux_posicao;
	CString Formula;

	CArray<CString,CString> variaveis_formula;
	CArray<CString,CString> variaveis_valor;


	//
	double Interpolacao_Newton(double x);
	double Interpolacao_divid(int, int);
	double Interpolacao_mult(double, int);

	



private:
	int inserir(double, char, char, char, double);
	int inserir_derivada(double, char, char, char, double, char , int);

	Complexo resolve();
	CString resolve_derivada();

	void opera(list_d *);
	void opera2(list_d *);
	void chaveta(list_d *);
	void liberta();
};

#endif // !defined(AFX_CALCULADORA_H__53B14E79_9F6E_46BD_ADE8_327DD1BE2107__INCLUDED_)
