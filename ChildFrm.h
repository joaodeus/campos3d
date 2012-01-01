// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__8E77411B_D249_44B7_BA6B_0192D478892D__INCLUDED_)
#define AFX_CHILDFRM_H__8E77411B_D249_44B7_BA6B_0192D478892D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:



	
	// This makes the MDI child maximized.
     virtual void ActivateFrame(int nCmdShow) 
	 { 
            // if another window is open, use default
       if(GetMDIFrame()->MDIGetActive())
      CMDIChildWnd::ActivateFrame(nCmdShow); 
       else
      CMDIChildWnd::ActivateFrame(SW_SHOWMAXIMIZED); // else open maximized.
	 }




// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__8E77411B_D249_44B7_BA6B_0192D478892D__INCLUDED_)
