// GuiasNCampos.cpp : implementation file
//

#include "stdafx.h"
#include "campos3d.h"
#include "GuiasNCampos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GuiasNCampos dialog


GuiasNCampos::GuiasNCampos(CWnd* pParent /*=NULL*/)
	: CDialog(GuiasNCampos::IDD, pParent)
{
	//{{AFX_DATA_INIT(GuiasNCampos)
	m_ncampos_z = 0;
	m_nlinhas_forca = 0;
	//}}AFX_DATA_INIT
}


void GuiasNCampos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GuiasNCampos)
	DDX_Text(pDX, IDC_ED_NCAMPOS_Z, m_ncampos_z);
	DDX_Text(pDX, IDC_ED_NLINHAS_FORCA, m_nlinhas_forca);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GuiasNCampos, CDialog)
	//{{AFX_MSG_MAP(GuiasNCampos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GuiasNCampos message handlers



BOOL GuiasNCampos::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here


//	m_slider_posicao_Ez.SetRange(1,100);
//	m_slider_posicao_Ez.SetPos(100);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
