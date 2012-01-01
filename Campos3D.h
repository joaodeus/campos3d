// Campos3D.h : main header file for the CAMPOS3D application
//

#if !defined(AFX_CAMPOS3D_H__8DF168F2_E9B5_4764_95D4_3079B830D946__INCLUDED_)
#define AFX_CAMPOS3D_H__8DF168F2_E9B5_4764_95D4_3079B830D946__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCampos3DApp:
// See Campos3D.cpp for the implementation of this class
//

class CCampos3DApp : public CWinApp
{
public:
	CCampos3DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCampos3DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCampos3DApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMPOS3D_H__8DF168F2_E9B5_4764_95D4_3079B830D946__INCLUDED_)
