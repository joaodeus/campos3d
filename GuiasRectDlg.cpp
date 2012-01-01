// GuiasRectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "campos3d.h"
#include "GuiasRectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GuiasRectDlg dialog


GuiasRectDlg::GuiasRectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(GuiasRectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(GuiasRectDlg)
	m_a = 0.0;
	m_b = 0.0;
	m_Er = 0.0;
	m_ur = 0.0;
	m_frequencia = 0.0;
	//}}AFX_DATA_INIT

//	TM_TE=true;
}


void GuiasRectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GuiasRectDlg)
	DDX_Control(pDX, IDC_CHECK_TM, m_TM);
	DDX_Control(pDX, IDC_CHECK_TE, m_TE);
	DDX_Text(pDX, IDC_EDIT_a, m_a);
	DDX_Text(pDX, IDC_EDIT_b, m_b);
	DDX_Text(pDX, IDC_EDIT_Er, m_Er);
	DDX_Text(pDX, IDC_EDIT_ur, m_ur);
	DDX_Text(pDX, IDC_FREQUENCIA, m_frequencia);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GuiasRectDlg, CDialog)
	//{{AFX_MSG_MAP(GuiasRectDlg)
	ON_BN_CLICKED(IDC_CHECK_TE, OnCheckTe)
	ON_BN_CLICKED(IDC_CHECK_TM, OnCheckTm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GuiasRectDlg message handlers

void GuiasRectDlg::OnCheckTe() 
{
	// TODO: Add your control notification handler code here
	m_TE.SetCheck(1);
	m_TM.SetCheck(0);
	TM_TE=false;
}

void GuiasRectDlg::OnCheckTm() 
{
	// TODO: Add your control notification handler code here
	m_TE.SetCheck(0);
	m_TM.SetCheck(1);
	TM_TE=true;
}

BOOL GuiasRectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if (TM_TE)
		m_TM.SetCheck(1);
	else
		m_TE.SetCheck(1);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
