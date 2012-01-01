#if !defined(AFX_GUIASRECTDLG_H__A4AF12F8_7D09_4633_97A3_51CAD8E1DDFA__INCLUDED_)
#define AFX_GUIASRECTDLG_H__A4AF12F8_7D09_4633_97A3_51CAD8E1DDFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiasRectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GuiasRectDlg dialog

class GuiasRectDlg : public CDialog
{
// Construction
public:
	GuiasRectDlg(CWnd* pParent = NULL);   // standard constructor

	bool TM_TE;

// Dialog Data
	//{{AFX_DATA(GuiasRectDlg)
	enum { IDD = IDD_GUIAS_REC };
	CButton	m_TM;
	CButton	m_TE;
	double	m_a;
	double	m_b;
	double	m_Er;
	double	m_ur;
	double	m_frequencia;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GuiasRectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GuiasRectDlg)
	afx_msg void OnCheckTe();
	afx_msg void OnCheckTm();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIASRECTDLG_H__A4AF12F8_7D09_4633_97A3_51CAD8E1DDFA__INCLUDED_)
