// GuiasCilDlg.cpp : implementation file
//

#include "stdafx.h"
#include "campos3d.h"
#include "GuiasCilDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GuiasCilDlg dialog


GuiasCilDlg::GuiasCilDlg(CWnd* pParent /*=NULL*/)
	: CDialog(GuiasCilDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(GuiasCilDlg)
	m_Er = 1.0;
	m_Ur = 1.0;
	m_frequencia = 25.0;
	m_a = 5.0;
	//}}AFX_DATA_INIT
}


void GuiasCilDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GuiasCilDlg)
	DDX_Control(pDX, IDC_CHECK_TM, m_TM);
	DDX_Control(pDX, IDC_CHECK_TE, m_TE);
	DDX_Text(pDX, IDC_EDIT_Er, m_Er);
	DDX_Text(pDX, IDC_EDIT_ur, m_Ur);
	DDX_Text(pDX, IDC_FREQUENCIA, m_frequencia);
	DDX_Text(pDX, IDC_EDIT_a, m_a);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GuiasCilDlg, CDialog)
	//{{AFX_MSG_MAP(GuiasCilDlg)
	ON_BN_CLICKED(IDC_CHECK_TE, OnCheckTe)
	ON_BN_CLICKED(IDC_CHECK_TM, OnCheckTm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GuiasCilDlg message handlers

BOOL GuiasCilDlg::OnInitDialog() 
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

void GuiasCilDlg::OnCheckTe() 
{
	// TODO: Add your control notification handler code here

	m_TE.SetCheck(1);
	m_TM.SetCheck(0);
	TM_TE=false;
}

void GuiasCilDlg::OnCheckTm() 
{
	// TODO: Add your control notification handler code here
	m_TE.SetCheck(0);
	m_TM.SetCheck(1);
	TM_TE=true;
}
