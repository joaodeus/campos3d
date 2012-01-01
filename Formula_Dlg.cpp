// Formula_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "campos3d.h"
#include "Formula_Dlg.h"

#include "Calculadora.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Formula_Dlg dialog


Formula_Dlg::Formula_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Formula_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Formula_Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT


	old_coluna_Grid_variaveis=1;
	old_linha_Grid_variaveis=1;

	FlagPopUpGridFormulas=false;
}


void Formula_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Formula_Dlg)
	DDX_Control(pDX, IDC_COMBO_RESULTADO_FORMULA, m_combo_resultado_formula);
	DDX_Control(pDX, IDC_ED_F2, m_ED_f2);
	DDX_Control(pDX, IDC_ED_F1, m_ED_f1);
	DDX_Control(pDX, IDC_FLEXG_FORMULAS, m_flexgrid_formulas);
	DDX_Control(pDX, IDC_FLEXG_VARIAVEIS, m_flexgrid_variaveis);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Formula_Dlg, CDialog)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(Formula_Dlg)
	ON_BN_CLICKED(IDC_BTN_VALIDAR, OnBtnValidar)
	ON_BN_CLICKED(IDC_BTN_CALCULAR, OnBtnCalcular)
	ON_COMMAND(ID_POP_ADD_FORMULA, OnPopAddFormula)
	ON_COMMAND(ID_POP_ELIMINAR_FORMULA, OnPopEliminarFormula)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Formula_Dlg message handlers

BOOL Formula_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	int i;


	m_flexgrid_formulas.SetTextMatrix(0,0,"Formulas:");


 
	m_flexgrid_formulas.SetColWidth(0,7000);

	m_flexgrid_formulas.SetRows(Formulas.GetSize()+1);

	for(i=0;i<Formulas.GetSize();i++)
	{
		m_flexgrid_formulas.SetTextMatrix(i+1,0,Formulas[i]);
	}




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(Formula_Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(Formula_Dlg)
	ON_EVENT(Formula_Dlg, IDC_FLEXG_FORMULAS, -600 /* Click */, OnClickFlexgFormulas, VTS_NONE)
	ON_EVENT(Formula_Dlg, IDC_FLEXG_FORMULAS, -601 /* DblClick */, OnDblClickFlexgFormulas, VTS_NONE)
	ON_EVENT(Formula_Dlg, IDC_FLEXG_VARIAVEIS, -603 /* KeyPress */, OnKeyPressFlexgVariaveis, VTS_PI2)
	ON_EVENT(Formula_Dlg, IDC_FLEXG_VARIAVEIS, 70 /* RowColChange */, OnRowColChangeFlexgVariaveis, VTS_NONE)
	ON_EVENT(Formula_Dlg, IDC_FLEXG_FORMULAS, -606 /* MouseMove */, OnMouseMoveFlexgFormulas, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void Formula_Dlg::OnClickFlexgFormulas() 
{
	// TODO: Add your control notification handler code here
	

}

void Formula_Dlg::OnDblClickFlexgFormulas() 
{
	// TODO: Add your control notification handler code here
	
	
	int n;
	int size;
	

	f=m_flexgrid_formulas.GetText();

	f1=f2=f;

	n=f.Find('=');
	size=f.GetLength();

	f1=f.Left(n);
	f2=f.Right(size-n-1);

//	AfxMessageBox(f1);
//	AfxMessageBox(f2);

	m_ED_f1.SetWindowText(f1);
	m_ED_f2.SetWindowText(f2);

}

int Formula_Dlg::OnBtnValidar() 
{
	// TODO: Add your control notification handler code here
	
	CString str;
	int i;
	int j;
	bool valida;
	CString f1_aux;
	CString f2_aux;


	calcFormula.var_formula.RemoveAll();
	m_ED_f1.GetWindowText(f1);
	m_ED_f2.GetWindowText(f2);

//	AfxMessageBox(f1);
//	AfxMessageBox(f2);

	calcFormula.find_var_formula(f1,f2);

	

	if (calcFormula.var_formula.GetSize()<1)
	{
		AfxMessageBox("A fórmula não contém variáveis !!!");
		return 0;
	}
	else
		m_flexgrid_variaveis.SetRows(calcFormula.var_formula.GetSize()+1);


	
	for(i=0;i<calcFormula.var_formula.GetSize();i++)
	{
		m_flexgrid_variaveis.SetTextMatrix(i+1,0,calcFormula.var_formula[i]);


		//Substitui as variaveis conhecidas----------------------------------------------
		str.Empty();
		m_flexgrid_variaveis.SetTextMatrix(i+1,1,str);

		if (calcFormula.var_formula[i] == "Bmn")
		{		
			str.Format("%lf",pDoc->TM.alfaB().i);
		//	if (m_flexgrid_variaveis.GetTextMatrix(i+1,1)=="")
				m_flexgrid_variaveis.SetTextMatrix(i+1,1, str);
		}

		
		if (calcFormula.var_formula[i] == "a")
		{		
			str.Format("%lf",pDoc->TM.a);
			m_flexgrid_variaveis.SetTextMatrix(i+1,1, str);
		}

		if (calcFormula.var_formula[i] == "b")
		{		
			str.Format("%lf",pDoc->TM.b);
			m_flexgrid_variaveis.SetTextMatrix(i+1,1, str);
		}

		if (calcFormula.var_formula[i] == "m")
		{		
			str.Format("%d",pDoc->TM.m);
			m_flexgrid_variaveis.SetTextMatrix(i+1,1, str);
		}


		if (calcFormula.var_formula[i] == "n")
		{		
			str.Format("%d",pDoc->TM.n);
			m_flexgrid_variaveis.SetTextMatrix(i+1,1, str);
		}

		if (calcFormula.var_formula[i] == "w")
		{		
			str.Format("%G",pDoc->TM.GetW());
			m_flexgrid_variaveis.SetTextMatrix(i+1,1, str);
		}

		if (calcFormula.var_formula[i] == "Lmn")
		{		
			str.Format("%G",pDoc->TM.GetLmn());
			m_flexgrid_variaveis.SetTextMatrix(i+1,1, str);
		}
		//Bmn/h^2*n*PI/b*C*sin(m*PI/a*x)*cos(n*PI/b*y)*sin(w*t-2*PI/Lmn*z)


		//-------------------------------------------------------------------------------

	}


//	AfxMessageBox(f1);
//	AfxMessageBox(f2);


	f.Format("%s=%s",f1,f2);

//------------------------------------------------------------------


	for(i=calcFormula.var_substitui_aux_posicao.GetSize();i>0;i--)
	{

		f.Delete(calcFormula.var_substitui_aux_posicao[i-1]-1,
			calcFormula.var_substitui_aux[i-1].GetLength());

		f.Insert(calcFormula.var_substitui_aux_posicao[i-1]-1,"1");

	}


	i=f.GetLength();
	j=f.Find("=");

	f1.Format("%s",f);
	f2.Format("%s",f);

	f1.Delete(j,i-j);
	f2.Delete(0,j+1);


	
//	AfxMessageBox(f1);
//	AfxMessageBox(f2);


	calcFormula.f(f1,0,"@").r;

	if (calcFormula.ERRO)
	{
		AfxMessageBox("Erro de sintaxe no 1ºmembro da fórmula");
		valida=false;
		return 0;
	}


	calcFormula.f(f2,0,"@").r;

	if (calcFormula.ERRO)
	{
		AfxMessageBox("Erro de sintaxe no 2ºmembro da fórmula");
		valida=false;
		return 0;
	}

	valida=true;
	return 1;


}

void Formula_Dlg::OnKeyPressFlexgVariaveis(short FAR* KeyAscii) 
{
	// TODO: Add your control notification handler code here

	
	int n;
	CString str_dados;

	if (m_flexgrid_variaveis.GetCol()==0)
		return;

	str_dados=m_flexgrid_variaveis.GetText();
	n=str_dados.GetLength();

	if (*KeyAscii==8)
	{
		if (n==0)return;
		str_dados.Delete(n-1,1);
		m_flexgrid_variaveis.SetText(str_dados);
		
		str_celula=str_dados;
		old_coluna_Grid_variaveis=m_flexgrid_variaveis.GetCol();
		old_linha_Grid_variaveis=m_flexgrid_variaveis.GetRow();
		
		return ;
	}
	str_dados.Insert(n,char(*KeyAscii));
	m_flexgrid_variaveis.SetText(str_dados);


	str_celula=str_dados;
	old_coluna_Grid_variaveis=m_flexgrid_variaveis.GetCol();
	old_linha_Grid_variaveis=m_flexgrid_variaveis.GetRow();


}

void Formula_Dlg::OnRowColChangeFlexgVariaveis() 
{
	// TODO: Add your control notification handler code here

/*	Calculadora calc;

	if (str_celula =="")
		str_celula="0";

	calc.f(str_celula,1,"@");
	if (calc.ERRO)
	{
		AfxMessageBox("A célula não contém uma expressão válida.\nPressione a tecla BackSpace.");
		m_flexgrid_variaveis.SetCol(old_coluna_Grid_variaveis);
		m_flexgrid_variaveis.SetRow(old_linha_Grid_variaveis);
	}
*/
	

	CString text;
	Calculadora calc;

	text=m_flexgrid_variaveis.GetTextMatrix(old_linha_Grid_variaveis,old_coluna_Grid_variaveis);
	
	if (text!="" && text!="?" && old_linha_Grid_variaveis!=0 && old_coluna_Grid_variaveis!=0)
	{
		calc.f(text,0,"@");
		if (calc.ERRO)
		{
			AfxMessageBox("A célula não contém uma expressão válida.\nPressione a tecla BackSpace.");
			m_flexgrid_variaveis.SetCol(old_coluna_Grid_variaveis);
			m_flexgrid_variaveis.SetRow(old_linha_Grid_variaveis);
		}
	}

}

void Formula_Dlg::OnBtnCalcular() 
{
	// TODO: Add your control notification handler code here
	


	//	CString f;
//	CString f1;
//	CString f2;
	int i;
	int j;
	CString text;
	CString text2;
	CString text3;


	//if (OnBtnValidar()==0)
	//	return;


	m_combo_resultado_formula.ResetContent( );





//	m_list_resultado_formula.ResetContent();

	m_ED_f1.GetWindowText(f1);
	m_ED_f2.GetWindowText(f2);

	f.Format("%s=%s",f1,f2);


	//calcFormula.Solve_n_Variaveis(f,-1000,1000,0.1,0.00001);

	for(i=calcFormula.var_substitui_aux_posicao.GetSize();i>0;i--)
	{

		f.Delete(calcFormula.var_substitui_aux_posicao[i-1]-1,
			calcFormula.var_substitui_aux[i-1].GetLength());

		for (j=1;j<=calcFormula.var_formula.GetSize();j++)
		{
			text=m_flexgrid_variaveis.GetTextMatrix(j,0);

			text2=m_flexgrid_variaveis.GetTextMatrix(j,1);

			//m_flexgrid_variaveis.SetTextMatrix(j,1,"O porra");

		//	text2=m_flexgrid_variaveis.GetTextMatrix(j,1);
		//	text2.Format("%s",m_flexgrid_variaveis.GetTextMatrix(j,1));

			//AfxMessageBox(text);
			if (calcFormula.var_substitui_aux[i-1]==text)
			{
				text3.Format("(%s)",text2);
				f.Insert(calcFormula.var_substitui_aux_posicao[i-1]-1,text3);
			}
		}
	}

	i=f.GetLength();
	j=f.Find("=");

	f1.Format("%s",f);
	f2.Format("%s",f);

	f1.Delete(j,i-j);
	f2.Delete(0,j+1);


	calcFormula.f(f1,1,"?");
	calcFormula.f(f2,1,"?");

	if (calcFormula.ERRO)
	{
		AfxMessageBox("Erro!!!\nVerifique se todas as variáveis tem valor atribuido.\nA variável a calcular deve ser marcado com '?'");
		return;
	}


//	AfxMessageBox(f1);
//	AfxMessageBox(f2);


	BeginWaitCursor();

	calcFormula.equacao_resolve_procura(f1,f2,"?",-100e31,100e31,0.1,0.00000000001);
//	calcFormula.equacao_resolve_procura(f1,f2,"?",-10000,10000,0.1,0.00000001);
//	calc.equacao_resolve_procura(f1,f2,"?",-100,100,0.1,0.0000001);

	//calc.equacao_resolve_procura(dlg.m_exp1,dlg.m_exp2,dlg.m_variavel,dlg.m_xmin,
	//		dlg.m_xmax,dlg.m_incremento,dlg.m_precisao);


	EndWaitCursor();


	CString aux;

	if (calcFormula.solucoes_equacao.GetSize()!=0)
	{
		aux.Format("%G",calcFormula.solucoes_equacao[0]);
	//	m_ED_resultado.SetWindowText(aux);

		for (i=0;i<calcFormula.solucoes_equacao.GetSize();i++)
		{
			aux.Format("%G",calcFormula.solucoes_equacao[i]);

		//	m_ED_resultado.SetWindowText(aux);
		
			//combo
			m_combo_resultado_formula.AddString(aux);
			m_combo_resultado_formula.SetWindowText(aux);

			//list
		
		//	m_list_resultado_formula.AddString(aux);
		//	m_list_resultado_formula.SetWindowText(aux);
		
		}

	}
	else
	{
	//	m_ED_resultado.SetWindowText("Sem Solução");
		
		m_combo_resultado_formula.SetWindowText("Sem Solução");
	//	m_list_resultado_formula.AddString("Sem Solução");
	//	m_ED_resultados_formula.AddString("Sem Solução");
	//	m_combo_valor_formula.InsertString(0,"Sem Solução");

	}



	//guardar valores calculados



/*	if (FlagNova)
	{
		CString aux;
		i=Formulas.GetSize();
		i_Formula=altera_formulas=i;
		Formulas.SetSize(i+1);

		m_nome_formulas_combo.GetWindowText(aux);
		m_nome_formulas_combo.AddString(aux);
		FlagNova=false;
	}
*/
	
/*	i_Formula=altera_formulas;	
	
	m_nome_formulas_combo.GetWindowText(Formulas[altera_formulas].NomeFormula);
	m_ED_f1.GetWindowText(Formulas[altera_formulas].f1);
	m_ED_f2.GetWindowText(Formulas[altera_formulas].f2);
	
	Formulas[altera_formulas].valores.SetSize(m_grid_formulas.GetRows()-1);
	//m_grid_formulas.GetRows()-1
	for(i=0;i<Formulas[altera_formulas].valores.GetSize();i++)
	{
		Formulas[altera_formulas].valores[i]=m_flexgrid_variaveis.GetTextMatrix(i+1,1);	
	}

*/

			/*//FORMULAS
	CString NomeFormula;
	CString f1;
	CString f2;
	CArray<CString,CString> valores;

*/
}

void Formula_Dlg::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1)
		{
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}


		if (FlagPopUpGridFormulas == true)
		{

			CMenu menu;
			VERIFY(menu.LoadMenu(CG_IDR_POPUP_FORMULA__DLG));

			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			CWnd* pWndPopupOwner = this;

			while (pWndPopupOwner->GetStyle() & WS_CHILD)
				pWndPopupOwner = pWndPopupOwner->GetParent();

			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
				pWndPopupOwner);

		}

		FlagPopUpGridFormulas=false;

	}

	
}

void Formula_Dlg::OnMouseMoveFlexgFormulas(short Button, short Shift, long x, long y) 
{
	// TODO: Add your control notification handler code here
	

//	if (Button ==2 )
//	{
		FlagPopUpGridFormulas=true;
//	}

	


}

void Formula_Dlg::OnPopAddFormula() 
{
	// TODO: Add your command handler code here

	CString str;
	CString str1;
	CString str2;
	long nCount;

	m_ED_f1.GetWindowText(str1);
	m_ED_f2.GetWindowText(str2);

	str.Format("%s=%s",str1,str2);

	nCount=m_flexgrid_formulas.GetRows();
	m_flexgrid_formulas.SetRows(nCount+1);
	m_flexgrid_formulas.SetRow(nCount);

	m_flexgrid_formulas.SetText(str);


}

void Formula_Dlg::OnPopEliminarFormula() 
{
	// TODO: Add your command handler code here
	
	long RowElimina;
	CString str;
	CString aux;

	RowElimina=m_flexgrid_formulas.GetRow();
	aux=m_flexgrid_formulas.GetText();

	str.Format("Pretende eliminar a formula:\n%s",aux);

	 if (AfxMessageBox(str,MB_YESNO) == IDYES)
	 {

		 int n=m_flexgrid_formulas.GetRows();

		 if (m_flexgrid_formulas.GetRows() > 2)
			 m_flexgrid_formulas.RemoveItem(RowElimina);
		 else
			 m_flexgrid_formulas.SetText("");

	 }

}

void Formula_Dlg::OnOK() 
{
	// TODO: Add extra validation here
		
	AfxMessageBox("Vou Morrer!!!");


	CDialog::OnOK();
}

void Formula_Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

}
