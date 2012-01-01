// Campos3DView.h : interface of the CCampos3DView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMPOS3DVIEW_H__609F44B1_D5D8_470A_8EF7_6BDECE7D22D3__INCLUDED_)
#define AFX_CAMPOS3DVIEW_H__609F44B1_D5D8_470A_8EF7_6BDECE7D22D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCampos3DView : public CView
{
protected: // create from serialization only
	CCampos3DView();
	DECLARE_DYNCREATE(CCampos3DView)

// Attributes
public:
	CCampos3DDoc* GetDocument();
	
	// Atributos para OpenGl
	HGLRC m_hRC;	// Rendering Context
	HDC m_hDC;		// Device Context

	double m_dAspectRatio;    // aspect

	int slider_Ez;


//	double X_Angle;
//	double Y_Angle;

	CPoint MouseDownPoint;

	bool Ondas_movimento;
	bool Mouse_Move;
	bool RightBtnEmBaixo;

	double t;

// Operations
public:

	void GLOndasEixo();
	void GLOndas3D();
	void GLOndas3Dmovimento();


	//Calcula os valores dos campos e guarda-os num arrai
	void GLEixo3D();
	void GLGuiasRectEixo();
	void GLGuiasCilEixo();

	//modo TM - Transversal Magnético
//	void GLGuiasRectTM_E_3D();
//	void GLGuiasRectTM_E_3D_alternativa();
	void GLGuiasRectTM_E_2Da();
	void GLGuiasRectTM_H_3D();	
	//void GLGuiasRectTM_2Db();
	//void GLGuiasRectTM_2Dz();
	double GetZeroTM_E();

	//modo TE - Transversal Eléctrico
	void GLGuiasRectTE_H_3D();


	//Desenha os valores dos campos guardados no arrai
	void GLGuiasRectTM_E_3D_Draw();
	void GLGuiasRectTM_H_3D_Draw();
	void GLGuiasRectTM_E_2Da_Draw();
	void GLGuiasRectTE_H_3D_Draw();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCampos3DView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCampos3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CCampos3DView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBotaoOndas();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnBtnGuias();
	afx_msg void OnStartStopTime();
	afx_msg int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnBTNtMENOS();
	afx_msg void OnBTNtMAIS();
	afx_msg void OnBtnGuiaCilindrico();
	afx_msg void OnPopupCampomagnetico();
	afx_msg void OnBTNZmenos();
	afx_msg void OnBTNZmais();
	afx_msg void OnPopupCampoelectrico();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPopupCalcular();
	afx_msg void OnBtnFormulas();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Campos3DView.cpp
inline CCampos3DDoc* CCampos3DView::GetDocument()
   { return (CCampos3DDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMPOS3DVIEW_H__609F44B1_D5D8_470A_8EF7_6BDECE7D22D3__INCLUDED_)
