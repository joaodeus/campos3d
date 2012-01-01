// Campos3DDoc.h : interface of the CCampos3DDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMPOS3DDOC_H__0D3AD7AC_2A9C_4C43_A314_EA877742263A__INCLUDED_)
#define AFX_CAMPOS3DDOC_H__0D3AD7AC_2A9C_4C43_A314_EA877742263A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#include "Ondas.h"
#include "TM_Rectangular.h"
#include "TEr.h"

#include "TEc.h"
#include "TMc.h"

class CCampos3DDoc : public CDocument
{
protected: // create from serialization only
	CCampos3DDoc();
	DECLARE_DYNCREATE(CCampos3DDoc)

// Attributes
public:

//Onda Electromagnetica
	Ondas onda;

	double Ondas_Eixo_range;
	double Guias_Eixo_range;
	int Arrai_Em_size;
	int Arrai_Emy_size;
	int Arrai_Hm_size;
	int Arrai_Hmx_size;

	

	//cores para as linhas de força dos guias
	double RedF,GreenF,BlueF;
	double RedT,GreenT,BlueT;

	CArray <double,double> R;
	CArray <double,double> G;
	CArray <double,double> B;


	CArray <double,double> RE;
	CArray <double,double> GE;
	CArray <double,double> BE;

	CArray <double,double> RH;
	CArray <double,double> GH;
	CArray <double,double> BH;



	double step_onda;
	double Q;//numero da amostras por periodo na onda
	
	CArray<int,int> selectscene;

//Guia de Ondas Rectangular

	GuiaR *guiaR;
	TEr TE;
	TMr TM;
	
	CArray<Grafico,Grafico> Campo_Electrico_TM;
	CArray<Grafico,Grafico> Campo_Magnetico_TM;
	
	CArray<Grafico,Grafico> Campo_Electrico_TE;
	CArray<Grafico,Grafico> Campo_Magnetico_TE;

	bool TM_TE;// True->TM ; False->TE
	BOOL Graf_Em;
	BOOL Graf_Hm;
	int XD_x;
	double a2D;
	double b2D;
	double z2D;

	
	double m_scale;

//Guia de Ondas Cilindrico
	GuiaC *guiaC;
	TEc TE_cil;
	TMc TM_cil;





// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCampos3DDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCampos3DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCampos3DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMPOS3DDOC_H__0D3AD7AC_2A9C_4C43_A314_EA877742263A__INCLUDED_)
