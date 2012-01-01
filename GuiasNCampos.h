#if !defined(AFX_GUIASNCAMPOS_H__D472EAE1_9ADA_11DA_B956_C42DF3588558__INCLUDED_)
#define AFX_GUIASNCAMPOS_H__D472EAE1_9ADA_11DA_B956_C42DF3588558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiasNCampos.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GuiasNCampos dialog

class GuiasNCampos : public CDialog
{
// Construction
public:
//	CString st;
	GuiasNCampos(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GuiasNCampos)
	enum { IDD = IDD_GUIAR_NCAMPOS };
	int		m_ncampos_z;
	int		m_nlinhas_forca;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GuiasNCampos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GuiasNCampos)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIASNCAMPOS_H__D472EAE1_9ADA_11DA_B956_C42DF3588558__INCLUDED_)
