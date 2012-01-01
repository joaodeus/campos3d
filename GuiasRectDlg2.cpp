// GuiasRectDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "campos3d.h"
#include "GuiasRectDlg2.h"

#define GRAF_3D			0
#define GRAF_2D			1
#define GRAF_2D_a		2
#define GRAF_2D_b		3
#define GRAF_2D_z		4




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





/////////////////////////////////////////////////////////////////////////////
// GuiasRectDlg2 dialog


GuiasRectDlg2::GuiasRectDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(GuiasRectDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(GuiasRectDlg2)
	m_static_a = _T("");
	m_static_b = _T("");
	m_static_Er = _T("");
	m_static_freq = _T("");
	m_static_ur = _T("");
	m_Em = TRUE;
	m_Hm = TRUE;
	m_2Da = 1.0;
	m_2Db = 1.0;
	m_2Dz = 1.0;
	m_static_L = _T("");
	//}}AFX_DATA_INIT

	XD_x=0;
	
}


void GuiasRectDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GuiasRectDlg2)
	DDX_Control(pDX, IDC_CHECK2D_A, m_btn_2D_a);
	DDX_Control(pDX, IDC_CHECK2D_B, m_btn_2D_b);
	DDX_Control(pDX, IDC_CHECK2D_Z, m_btn_2D_z);
	DDX_Control(pDX, IDC_CHECK3D, m_btn_3D);
	DDX_Control(pDX, IDC_CHECK_Hm, m_btn_Hm);
	DDX_Control(pDX, IDC_CHECK_Em, m_btn_Em);
	DDX_Control(pDX, IDC_EDIT_Z_, m_ED_z);
	DDX_Control(pDX, IDC_EDIT_B_, m_ED_b);
	DDX_Control(pDX, IDC_EDIT_A_, m_ED_a);
	DDX_Control(pDX, IDC_CMBO_FREQ_CORTE, m_cmbo_freq_corte);
	DDX_Text(pDX, IDC_STATIC_a, m_static_a);
	DDX_Text(pDX, IDC_STATIC_b, m_static_b);
	DDX_Text(pDX, IDC_STATIC_Er, m_static_Er);
	DDX_Text(pDX, IDC_STATIC_FREQ, m_static_freq);
	DDX_Text(pDX, IDC_STATIC_ur, m_static_ur);
	DDX_Check(pDX, IDC_CHECK_Em, m_Em);
	DDX_Check(pDX, IDC_CHECK_Hm, m_Hm);
	DDX_Text(pDX, IDC_EDIT_A_, m_2Da);
	DDX_Text(pDX, IDC_EDIT_B_, m_2Db);
	DDX_Text(pDX, IDC_EDIT_Z_, m_2Dz);
	DDX_Text(pDX, IDC_STATIC_L, m_static_L);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GuiasRectDlg2, CDialog)
	//{{AFX_MSG_MAP(GuiasRectDlg2)
	ON_BN_CLICKED(IDC_BTN_VOLTAR, OnBtnVoltar)
	ON_BN_CLICKED(IDC_CHECK2D_A, OnCheck2dA)
	ON_BN_CLICKED(IDC_CHECK2D_B, OnCheck2dB)
	ON_BN_CLICKED(IDC_CHECK2D_Z, OnCheck2dZ)
	ON_BN_CLICKED(IDC_CHECK3D, OnCheck3d)
	ON_CBN_SELCHANGE(IDC_CMBO_FREQ_CORTE, OnSelchangeCmboFreqCorte)
	ON_BN_CLICKED(IDC_CHECK_Em, OnCHECKEm)
	ON_BN_CLICKED(IDC_CHECK_Hm, OnCHECKHm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GuiasRectDlg2 message handlers

void GuiasRectDlg2::OnBtnVoltar() 
{
	// TODO: Add your control notification handler code here
	
	EndDialog(3);
}

void GuiasRectDlg2::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL GuiasRectDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	int i;

	for(i=0;i<m_list_modos_M_N_fc.GetSize();i++)
	{
		m_cmbo_freq_corte.AddString(m_list_modos_M_N_fc[i]);
	}

 
	if (m_list_modos_M_N_fc.GetSize() != 0)
		m_cmbo_freq_corte.SetCurSel(0);


	
	switch(XD_x)
	{
	case GRAF_3D:
		
		m_ED_a.EnableWindow(false);
		m_ED_b.EnableWindow(false);
		m_ED_z.EnableWindow(false);

		m_btn_2D_a.SetCheck(0);
		m_btn_2D_b.SetCheck(0);
		m_btn_2D_z.SetCheck(0);
		m_btn_3D.SetCheck(1);
		break;

	case GRAF_2D_a:
		
		m_ED_a.EnableWindow(true);
		m_ED_b.EnableWindow(false);
		m_ED_z.EnableWindow(false);

		m_btn_2D_a.SetCheck(1);
		m_btn_2D_b.SetCheck(0);
		m_btn_2D_z.SetCheck(0);
		m_btn_3D.SetCheck(0);
		break;

	case GRAF_2D_b:
		
		m_ED_a.EnableWindow(false);
		m_ED_b.EnableWindow(true);
		m_ED_z.EnableWindow(false);

		m_btn_2D_a.SetCheck(0);
		m_btn_2D_b.SetCheck(1);
		m_btn_2D_z.SetCheck(0);
		m_btn_3D.SetCheck(0);
		break;

	case GRAF_2D_z:
		
		m_ED_a.EnableWindow(false);
		m_ED_b.EnableWindow(false);
		m_ED_z.EnableWindow(true);

		m_btn_2D_a.SetCheck(0);
		m_btn_2D_b.SetCheck(0);
		m_btn_2D_z.SetCheck(1);
		m_btn_3D.SetCheck(0);
	break;

	};



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void GuiasRectDlg2::OnCheck2dA() 
{
	// TODO: Add your control notification handler code here
	m_btn_2D_a.SetCheck(1);
	m_btn_2D_b.SetCheck(0);
	m_btn_2D_z.SetCheck(0);
	m_btn_3D.SetCheck(0);

	
	m_ED_a.EnableWindow(true);
	m_ED_b.EnableWindow(false);
	m_ED_z.EnableWindow(false);

	XD_x=GRAF_2D_a;

}

void GuiasRectDlg2::OnCheck2dB() 
{
	// TODO: Add your control notification handler code here
	m_btn_2D_a.SetCheck(0);
	m_btn_2D_b.SetCheck(1);
	m_btn_2D_z.SetCheck(0);
	m_btn_3D.SetCheck(0);

	m_ED_a.EnableWindow(false);
	m_ED_b.EnableWindow(true);
	m_ED_z.EnableWindow(false);


	XD_x=GRAF_2D_b;

}

void GuiasRectDlg2::OnCheck2dZ() 
{
	// TODO: Add your control notification handler code here
	m_btn_2D_a.SetCheck(0);
	m_btn_2D_b.SetCheck(0);
	m_btn_2D_z.SetCheck(1);
	m_btn_3D.SetCheck(0);


	m_ED_a.EnableWindow(false);
	m_ED_b.EnableWindow(false);
	m_ED_z.EnableWindow(true);

	XD_x= GRAF_2D_z ;
}

void GuiasRectDlg2::OnCheck3d() 
{
	// TODO: Add your control notification handler code here
	m_btn_2D_a.SetCheck(0);
	m_btn_2D_b.SetCheck(0);
	m_btn_2D_z.SetCheck(0);
	m_btn_3D.SetCheck(1);

	m_ED_a.EnableWindow(false);
	m_ED_b.EnableWindow(false);
	m_ED_z.EnableWindow(false);

	XD_x=GRAF_3D;

}

void GuiasRectDlg2::OnSelchangeCmboFreqCorte() 
{
	// TODO: Add your control notification handler code here
	
	int l;
	
	l=m_cmbo_freq_corte.GetCurSel();
	
	if (l>=0)
	{
		m=m_list_modos_M[l];
		n=m_list_modos_N[l];
	}


}

void GuiasRectDlg2::OnCHECKEm() 
{
	// TODO: Add your control notification handler code here


	m_Em=!m_Em;
}

void GuiasRectDlg2::OnCHECKHm() 
{
	// TODO: Add your control notification handler code here
	
	m_Hm=!m_Hm;
}
