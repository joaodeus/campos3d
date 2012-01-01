// GuiasNCamposZDlg.cpp : implementation file
//

#include "stdafx.h"
#include "campos3d.h"
#include "GuiasNCamposZDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GuiasNCamposZDlg dialog


GuiasNCamposZDlg::GuiasNCamposZDlg(CWnd* pParent /*=NULL*/)
	: CDialog(GuiasNCamposZDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(GuiasNCamposZDlg)
	m_NLinhas_x = 0;
	m_NLinhas_y = 0;
	m_slider_z = 0;
	//}}AFX_DATA_INIT
}


void GuiasNCamposZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GuiasNCamposZDlg)
	DDX_Control(pDX, IDC_SLIDER_POS_Z, m_slider_pos_z);
	DDX_Text(pDX, IDC_ED_NLINHAS_x, m_NLinhas_x);
	DDX_Text(pDX, IDC_ED_NLINHAS_y, m_NLinhas_y);
	DDX_Slider(pDX, IDC_SLIDER_POS_Z, m_slider_z);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GuiasNCamposZDlg, CDialog)
	//{{AFX_MSG_MAP(GuiasNCamposZDlg)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GuiasNCamposZDlg message handlers

void GuiasNCamposZDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	

	m_slider_z=nPos;


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL GuiasNCamposZDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	

	m_slider_pos_z.SetRange(1,100);
	m_slider_pos_z.SetPos(m_slider_z);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
