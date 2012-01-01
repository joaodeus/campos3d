#if !defined(AFX_GUIASCILDLG_H__2D443B82_99F3_11DA_B956_0050D4342C93__INCLUDED_)
#define AFX_GUIASCILDLG_H__2D443B82_99F3_11DA_B956_0050D4342C93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiasCilDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GuiasCilDlg dialog

class GuiasCilDlg : public CDialog
{
// Construction
public:
	GuiasCilDlg(CWnd* pParent = NULL);   // standard constructor

	bool TM_TE;

// Dialog Data
	//{{AFX_DATA(GuiasCilDlg)
	enum { IDD = IDD_GUIAS_CIL };
	CButton	m_TM;
	CButton	m_TE;
	double	m_Er;
	double	m_Ur;
	double	m_frequencia;
	double	m_a;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GuiasCilDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GuiasCilDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckTe();
	afx_msg void OnCheckTm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIASCILDLG_H__2D443B82_99F3_11DA_B956_0050D4342C93__INCLUDED_)
