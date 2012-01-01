#if !defined(AFX_ONDASDLG_H__32CAB6B7_7060_4E88_952B_7375FF212234__INCLUDED_)
#define AFX_ONDASDLG_H__32CAB6B7_7060_4E88_952B_7375FF212234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OndasDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OndasDlg dialog

class OndasDlg : public CDialog
{
// Construction
public:
	OndasDlg(CWnd* pParent = NULL);   // standard constructor


	bool flag_condutividade; 

// Dialog Data
	//{{AFX_DATA(OndasDlg)
	enum { IDD = IDD_ONDAS3D };
	CEdit	m_ed_impedancia_angulo;
	CEdit	m_ed_impedancia_amplitude;
	CEdit	m_ed_condutividade;
	double	m_angulo_polarizacao;
	double	m_condutividade;
	double	m_impedancia_amplitude;
	double	m_impedancia_angulo;
	double	m_campo_elect_x;
	double	m_campo_elect_y;
	double	m_Er;
	double	m_desfasagem_inicial;
	double	m_frequencia;
	double	m_Ur;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OndasDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OndasDlg)
	afx_msg void OnImpedancia();
	afx_msg void OnCondutividade();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONDASDLG_H__32CAB6B7_7060_4E88_952B_7375FF212234__INCLUDED_)
