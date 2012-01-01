// OndasDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Campos3D.h"
#include "OndasDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OndasDlg dialog


OndasDlg::OndasDlg(CWnd* pParent /*=NULL*/)
	: CDialog(OndasDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(OndasDlg)
	m_angulo_polarizacao = 0.0;
	m_condutividade = 0.0;
	m_impedancia_amplitude = 0.0;
	m_impedancia_angulo = 0.0;
	m_campo_elect_x = 10;
	m_campo_elect_y = 0.0;
	m_Er = 1;
	m_desfasagem_inicial = 0.0;
	m_frequencia = 96.1;
	m_Ur = 1;
	//}}AFX_DATA_INIT


	flag_condutividade=true; 
}


void OndasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OndasDlg)
	DDX_Control(pDX, IDC_n_IMP_ANGULO, m_ed_impedancia_angulo);
	DDX_Control(pDX, IDC_n_IMP_AMPLITUDE, m_ed_impedancia_amplitude);
	DDX_Control(pDX, IDC_G_condutividade, m_ed_condutividade);
	DDX_Text(pDX, IDC_ANGULO_POL, m_angulo_polarizacao);
	DDX_Text(pDX, IDC_G_condutividade, m_condutividade);
	DDX_Text(pDX, IDC_n_IMP_AMPLITUDE, m_impedancia_amplitude);
	DDX_Text(pDX, IDC_n_IMP_ANGULO, m_impedancia_angulo);
	DDX_Text(pDX, IDC_ONDAS_Em_x, m_campo_elect_x);
	DDX_Text(pDX, IDC_ONDAS_Em_y, m_campo_elect_y);
	DDX_Text(pDX, IDC_ONDAS_Er, m_Er);
	DDX_Text(pDX, IDC_ONDAS_FASE_INI, m_desfasagem_inicial);
	DDX_Text(pDX, IDC_ONDAS_FREQ, m_frequencia);
	DDX_Text(pDX, IDC_ONDAS_ur, m_Ur);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OndasDlg, CDialog)
	//{{AFX_MSG_MAP(OndasDlg)
	ON_BN_CLICKED(IDC_IMPEDANCIA, OnImpedancia)
	ON_BN_CLICKED(IDC_CONDUTIVIDADE, OnCondutividade)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OndasDlg message handlers

void OndasDlg::OnImpedancia() 
{
	// TODO: Add your control notification handler code here
		
	m_ed_impedancia_angulo.EnableWindow(TRUE);
	m_ed_impedancia_amplitude.EnableWindow(TRUE);
	m_ed_condutividade.EnableWindow(FALSE);
	
	flag_condutividade=false; 
}

void OndasDlg::OnCondutividade() 
{
	// TODO: Add your control notification handler code here

	m_ed_impedancia_angulo.EnableWindow(FALSE);
	m_ed_impedancia_amplitude.EnableWindow(FALSE);
	m_ed_condutividade.EnableWindow(TRUE);

	flag_condutividade=true; 
}

/*
void OndasDlg::OnSetfocusGcondutividade() 
{
	// TODO: Add your control notification handler code here

	m_ed_impedancia_angulo.EnableWindow(FALSE);
	m_ed_impedancia_amplitude.EnableWindow(FALSE);
	m_ed_condutividade.EnableWindow(TRUE);

	flag_condutividade=true;
}

void OndasDlg::OnSetfocusnIMPAMPLITUDE() 
{
	// TODO: Add your control notification handler code here
	
	m_ed_impedancia_angulo.EnableWindow(TRUE);
	m_ed_impedancia_amplitude.EnableWindow(TRUE);
	m_ed_condutividade.EnableWindow(FALSE);

	flag_condutividade=false; 
}

void OndasDlg::OnSetfocusnIMPANGULO() 
{
	// TODO: Add your control notification handler code here
	
	m_ed_impedancia_angulo.EnableWindow(TRUE);
	m_ed_impedancia_amplitude.EnableWindow(TRUE);
	m_ed_condutividade.EnableWindow(FALSE);

	flag_condutividade=false; 
}
*/

