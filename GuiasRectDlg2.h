#if !defined(AFX_GUIASRECTDLG2_H__04E04DAD_9923_4F74_866D_18FEBCF61CC0__INCLUDED_)
#define AFX_GUIASRECTDLG2_H__04E04DAD_9923_4F74_866D_18FEBCF61CC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiasRectDlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GuiasRectDlg2 dialog

class GuiasRectDlg2 : public CDialog
{
// Construction
public:
	GuiasRectDlg2(CWnd* pParent = NULL);   // standard constructor

	CArray <CString, CString> m_list_modos_M_N_fc; 
	CArray <int, int> m_list_modos_M; 
	CArray <int, int> m_list_modos_N; 
//	CString TipoGrafico;
	
	int m;
	int n;
	int XD_x;
	

// Dialog Data
	//{{AFX_DATA(GuiasRectDlg2)
	enum { IDD = IDD_GUIAS_REC2 };
	CButton	m_btn_2D_a;
	CButton	m_btn_2D_b;
	CButton	m_btn_2D_z;
	CButton	m_btn_3D;
	CButton	m_btn_Hm;
	CButton	m_btn_Em;
	CEdit	m_ED_z;
	CEdit	m_ED_b;
	CEdit	m_ED_a;
	CComboBox	m_cmbo_freq_corte;
	CString	m_static_a;
	CString	m_static_b;
	CString	m_static_Er;
	CString	m_static_freq;
	CString	m_static_ur;
	BOOL	m_Em;
	BOOL	m_Hm;
	double	m_2Da;
	double	m_2Db;
	double	m_2Dz;
	CString	m_static_L;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GuiasRectDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GuiasRectDlg2)
	afx_msg void OnBtnVoltar();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck2dA();
	afx_msg void OnCheck2dB();
	afx_msg void OnCheck2dZ();
	afx_msg void OnCheck3d();
	afx_msg void OnSelchangeCmboFreqCorte();
	afx_msg void OnCHECKEm();
	afx_msg void OnCHECKHm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIASRECTDLG2_H__04E04DAD_9923_4F74_866D_18FEBCF61CC0__INCLUDED_)
