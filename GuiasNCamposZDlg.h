#if !defined(AFX_GUIASNCAMPOSZDLG_H__B6132680_BB7F_11DA_B956_BB6CB6FC9429__INCLUDED_)
#define AFX_GUIASNCAMPOSZDLG_H__B6132680_BB7F_11DA_B956_BB6CB6FC9429__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiasNCamposZDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GuiasNCamposZDlg dialog

class GuiasNCamposZDlg : public CDialog
{
// Construction
public:
	GuiasNCamposZDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GuiasNCamposZDlg)
	enum { IDD = IDD_GUIAR_NCAMP_Z };
	CSliderCtrl	m_slider_pos_z;
	int		m_NLinhas_x;
	int		m_NLinhas_y;
	int		m_slider_z;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GuiasNCamposZDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GuiasNCamposZDlg)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIASNCAMPOSZDLG_H__B6132680_BB7F_11DA_B956_BB6CB6FC9429__INCLUDED_)
