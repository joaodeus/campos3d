// Campos3DDoc.cpp : implementation of the CCampos3DDoc class
//

#include "stdafx.h"
#include "Campos3D.h"

#include "Campos3DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCampos3DDoc

IMPLEMENT_DYNCREATE(CCampos3DDoc, CDocument)

BEGIN_MESSAGE_MAP(CCampos3DDoc, CDocument)
	//{{AFX_MSG_MAP(CCampos3DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCampos3DDoc construction/destruction

CCampos3DDoc::CCampos3DDoc()
{
	// TODO: add one-time construction code here

	selectscene.RemoveAll();
	selectscene.Add(-1);
	Ondas_Eixo_range=50;
	Guias_Eixo_range=0.050;//50mm
	Q=20;//numero da amostras por periodo na onda

	TM_TE=true;

	Graf_Em=true;
	Graf_Hm=true;

	

	//Guias de Ondas Rectangulares--------------

	//escala do guia de ondas
	m_scale=1;

	//tipo de grafico 3D, 2D, ...
	XD_x=0;

	//cores para frente
	RedF=0;
	GreenF=0;
	BlueF=1;

	//cores para trás
	RedT=0;
	GreenT=1;
	BlueT=1;


	a2D=0;
	b2D=0;
	z2D=0;

//	guiaR = new GuiaR;

	
	//------------------------------------------

}

CCampos3DDoc::~CCampos3DDoc()
{

}

BOOL CCampos3DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

//	CDocument::SetTitle("Ola");





	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCampos3DDoc serialization

void CCampos3DDoc::Serialize(CArchive& ar)
{
	int g;
	
	if (ar.IsStoring())
	{
		// TODO: add storing code here

		//define o grafico: ondas 3D, guias, etc...
		selectscene.Serialize(ar);
	
		ar<<onda.xRot;
		ar<<onda.yRot;
		ar<<onda.zRot;
		ar<<step_onda;

		
		ar<<onda.Em;
		ar<<onda.Emy;
		ar<<onda.Er;
		ar<<onda.Ur;
		ar<<onda.f;
		ar<<onda.GetG();
		ar<<onda.O;
		ar<<onda.teta;

		
			/*	dlg.m_campo_elect_x=pDoc->onda.Em;
	dlg.m_campo_elect_y=pDoc->onda.Emy;
	dlg.m_Er=pDoc->onda.Er;
	dlg.m_Ur=pDoc->onda.Ur;
	dlg.m_frequencia=pDoc->onda.f/1000000;//gigahertz
	dlg.m_condutividade=pDoc->onda.GetG();
	dlg.m_impedancia_amplitude=cabs(pDoc->onda.Getn());
	dlg.m_impedancia_angulo=arg(pDoc->onda.Getn())*180/PI;

	dlg.m_angulo_polarizacao=pDoc->onda.O;
	dlg.m_desfasagem_inicial=pDoc->onda.teta;*/
	

		Arrai_Em_size=onda.Em_array.GetSize();
		Arrai_Emy_size=onda.Emy_array.GetSize();
		Arrai_Hm_size=onda.Hm_array.GetSize();
		Arrai_Hmx_size=onda.Hmx_array.GetSize();


		ar<<Arrai_Em_size;
		ar<<Arrai_Emy_size;
		ar<<Arrai_Hm_size;
		ar<<Arrai_Hmx_size;

		onda.Em_array.Serialize(ar);
		onda.Emy_array.Serialize(ar);
		onda.Hm_array.Serialize(ar);
		onda.Hmx_array.Serialize(ar);


		
	}
	else
	{
		// TODO: add loading code here
		
		//define o grafico: ondas 3D, guias, etc...
		selectscene.Serialize(ar);

		ar>>onda.xRot;
		ar>>onda.yRot;
		ar>>onda.zRot;
		ar>>step_onda;


		ar>>onda.Em;
		ar>>onda.Emy;
		ar>>onda.Er;
		ar>>onda.Ur;
		ar>>onda.f;
		ar>>g;
		onda.SetG(g);
		ar>>onda.O;
		ar>>onda.teta;
		
		
		ar>>Arrai_Em_size;
		ar>>Arrai_Emy_size;
		ar>>Arrai_Hm_size;
		ar>>Arrai_Hmx_size;
		
		onda.Em_array.SetSize(Arrai_Em_size);	
		onda.Emy_array.SetSize(Arrai_Emy_size);	
		onda.Hm_array.SetSize(Arrai_Hm_size);	
		onda.Hmx_array.SetSize(Arrai_Hmx_size);	
		
		

		onda.Em_array.Serialize(ar);
		onda.Emy_array.Serialize(ar);
		onda.Hm_array.Serialize(ar);
		onda.Hmx_array.Serialize(ar);

		
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCampos3DDoc diagnostics

#ifdef _DEBUG
void CCampos3DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCampos3DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCampos3DDoc commands
