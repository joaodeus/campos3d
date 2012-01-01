// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D79F3680_9052_410E_8B07_604B1E7D6E7C__INCLUDED_)
#define AFX_STDAFX_H__D79F3680_9052_410E_8B07_604B1E7D6E7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT



#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

#include <math.h>
#include <stdarg.h>
#include <conio.h>

#include "afxtempl.h"


#define PI 3.1415926535897932



#define C 299795637.7 //  [m/s]  velocidade da luz
#define Uo 4*PI*1e-7 // [H/m]	permeabilidade electrica
#define Eo 8.854*1e-12 // [F/m]	dielectrico do meio






double VectorMax(double,double,double);

void Cone(double /*x*/, double /*y*/, double /*z*/, double /*r*/, double /*h*/ );




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D79F3680_9052_410E_8B07_604B1E7D6E7C__INCLUDED_)
