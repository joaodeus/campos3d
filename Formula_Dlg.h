//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_FORMULA_DLG_H__8BD38C06_3642_11DB_B956_9D615F2D5677__INCLUDED_)
#define AFX_FORMULA_DLG_H__8BD38C06_3642_11DB_B956_9D615F2D5677__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Formula_Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Formula_Dlg dialog

#include "Campos3DDoc.h"
#include "Calculadora.h"



class Formula_Dlg : public CDialog
{
// Construction
public:
	Formula_Dlg(CWnd* pParent = NULL);   // standard constructor


	CArray<CString,CString> Formulas;

	CCampos3DDoc* pDoc;

	CString f;
	CString f1;
	CString f2;

	bool FlagPopUpGridFormulas;

	Calculadora calcFormula;


	CString str_celula;
	long old_coluna_Grid_variaveis;
	long old_linha_Grid_variaveis;
	//long old_coluna_B;
	//long old_linha_B;


// Dialog Data
	//{{AFX_DATA(Formula_Dlg)
	enum { IDD = IDD_FORMULAS };
	CComboBox	m_combo_resultado_formula;
	CEdit	m_ED_f2;
	CEdit	m_ED_f1;
	CMSFlexGrid	m_flexgrid_formulas;
	CMSFlexGrid	m_flexgrid_variaveis;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Formula_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);

	// Generated message map functions
	//{{AFX_MSG(Formula_Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickFlexgFormulas();
	afx_msg void OnDblClickFlexgFormulas();
	afx_msg int OnBtnValidar();
	afx_msg void OnKeyPressFlexgVariaveis(short FAR* KeyAscii);
	afx_msg void OnRowColChangeFlexgVariaveis();
	afx_msg void OnBtnCalcular();
	afx_msg void OnMouseMoveFlexgFormulas(short Button, short Shift, long x, long y);
	afx_msg void OnPopAddFormula();
	afx_msg void OnPopEliminarFormula();
	virtual void OnOK();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMULA_DLG_H__8BD38C06_3642_11DB_B956_9D615F2D5677__INCLUDED_)
