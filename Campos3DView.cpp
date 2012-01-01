// Campos3DView.cpp : implementation of the CCampos3DView class
//

#include "stdafx.h"
#include "Campos3D.h"

#include "Campos3DDoc.h"
#include "Campos3DView.h"
#include "OndasDlg.h"
#include "Complexo.h"
#include "GuiasRectDlg.h"
#include "GuiasRectDlg2.h"
#include "GuiasCilDlg.h"
#include "resource.h"
#include "GuiasNCampos.h"
#include "GuiasNCamposZDlg.h"
#include "Formula_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define GRAF_3D			0
#define GRAF_2D			1
#define GRAF_2D_a		2
#define GRAF_2D_b		3
#define GRAF_2D_z		4



#define ONDAS			0
#define GUIAS_RECT		1
#define GUIAS_CIL		2


#define MAX_STRING	1024



GLuint	SmallFont,		/* Small raster font */
		SymbolFont,    /*symbol font*/
		MediumFont,		/* Medium raster font */
		LargeFont;		/* Large raster font */



GLuint	FontCreateBitmaps(HDC hdc, char *typeface, int height,
		                  int weight, DWORD italic);
GLuint	FontCreateOutlines(HDC hdc, char *typeface, int height,
		                   int weight, DWORD italic);
void	FontDelete(GLuint font);

void	FontPrintf(GLuint font, char *format, ...);
void	FontPuts(GLuint font, char *s);



/////////////////////////////////////////////////////////////////////////////
// CCampos3DView

IMPLEMENT_DYNCREATE(CCampos3DView, CView)

BEGIN_MESSAGE_MAP(CCampos3DView, CView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CCampos3DView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_BOTAO_ONDAS, OnBotaoOndas)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BTN_GUIAS, OnBtnGuias)
	ON_COMMAND(ID_START_STOP_TIME, OnStartStopTime)
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_BTN_t_MENOS, OnBTNtMENOS)
	ON_COMMAND(ID_BTN_t_MAIS, OnBTNtMAIS)
	ON_COMMAND(ID_BTN_GUIA_CILINDRICO, OnBtnGuiaCilindrico)
	ON_COMMAND(ID_POPUP_CAMPOMAGNETICO, OnPopupCampomagnetico)
	ON_COMMAND(ID_BTN_Z_menos, OnBTNZmenos)
	ON_COMMAND(ID_BTN_Z_mais, OnBTNZmais)
	ON_COMMAND(ID_POPUP_CAMPOELECTRICO, OnPopupCampoelectrico)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_POPUP_CALCULAR, OnPopupCalcular)
	ON_COMMAND(ID_BTN_FORMULAS, OnBtnFormulas)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCampos3DView construction/destruction

CCampos3DView::CCampos3DView()
{
	// TODO: add construction code here

	MouseDownPoint.x=0;
	MouseDownPoint.y=0;
//	X_Angle=40;
//	Y_Angle=40;
	Ondas_movimento=false;
	Mouse_Move=false;
	RightBtnEmBaixo=false;

	slider_Ez=100;

	t=0;
}

CCampos3DView::~CCampos3DView()
{
}

BOOL CCampos3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// these styles are requested by OpenGL
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// these styles are meant for a use of this class in a MDI application
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW );


	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCampos3DView drawing

void CCampos3DView::OnDraw(CDC* pDC)
{
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	double s = pDoc->m_scale;

	wglMakeCurrent(m_hDC,m_hRC);// Make the rendering context current
	glClearColor(0,0,0,0);//set background clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the window and the depth buffer
	// the couple glPush - glPop is necessary because the entire
	// scene is rotated of the given angle (which is absolute) at every redraw
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);

	
	glPushMatrix();	
	glRotated(pDoc->onda.xRot,1.0,0.0,0.0);
	glRotated(pDoc->onda.yRot,0.0,1.0,0.0);
	glRotated(pDoc->onda.zRot,0.0,0.0,1.0);

	
	/*
#define GRAF_3D			0
#define GRAF_2D			1
#define GRAF_2D_a		2
#define GRAF_2D_b		3
#define GRAF_2D_z		4

	*/

	switch(pDoc->selectscene[0])
	{
		
	// ondas
	case ONDAS:
		

		glPushMatrix();
		glScaled(0.001,0.001,0.001);
		
		GLOndasEixo();
		GLOndas3D();
		//if (Ondas_movimento)
		//	GLOndas3Dmovimento();

		glPopMatrix();
		
		break;
	//	Guias de Ondas Rectangulares
	case GUIAS_RECT:
		

		GLEixo3D();

		glPushMatrix();
		glScaled(s,s,s);
	
		//Guia de Ondas Rectangular
		GLGuiasRectEixo();
	

		
		

		if (pDoc->TM_TE && (pDoc->XD_x==GRAF_3D || pDoc->XD_x==GRAF_2D_a 
											|| pDoc->XD_x==GRAF_2D_b /*|| pDoc->XD_x==GRAF_2D_z*/))
		{
			if (!Ondas_movimento)
			{
				if (pDoc->Graf_Em)
					pDoc->guiaR->DrawE_Draw(t);

				if (pDoc->Graf_Hm)
					pDoc->guiaR->DrawH_Draw(t);
			}
			else
			{
				if (pDoc->Graf_Em)
					pDoc->guiaR->DrawE_Draw(t);

				if (pDoc->Graf_Hm)
					pDoc->guiaR->DrawH_Draw(t);
				
				t=t+1E-12;			
				Invalidate(false);
			}

		}
	

		if (pDoc->TM_TE && (pDoc->XD_x == GRAF_2D_z))
		{
			pDoc->guiaR->DrawE_Draw_2Dz(t);
		}





		//modo TE campo Magnetico 3D
		if (!pDoc->TM_TE && pDoc->Graf_Hm && pDoc->XD_x==GRAF_3D)
			pDoc->guiaR->DrawH_Draw(t);
			//GLGuiasRectTE_H_3D_Draw();

				
		glPopMatrix();

		break;



	case GUIAS_CIL:

		GLEixo3D();
		GLGuiasCilEixo();
		///GlGuiasCilEixo();



		break;




	
	};




	glPopMatrix();

	glPopMatrix();
	glFinish();
	// Swap our scene to the front
	SwapBuffers(m_hDC);
	// Allow other rendering contexts to co-exist
	wglMakeCurrent(m_hDC,NULL);	
}

/////////////////////////////////////////////////////////////////////////////
// CCampos3DView printing

BOOL CCampos3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCampos3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCampos3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCampos3DView diagnostics

#ifdef _DEBUG
void CCampos3DView::AssertValid() const
{
	CView::AssertValid();
}

void CCampos3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCampos3DDoc* CCampos3DView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCampos3DDoc)));
	return (CCampos3DDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCampos3DView message handlers

int CCampos3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	

	int nPixelFormat;					// Pixel format index
	m_hDC = ::GetDC(m_hWnd);			// Get the Device context

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
		1,								// Version of this structure	
		PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |			// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,				// Double buffered mode
		PFD_TYPE_RGBA,					// RGBA Color mode
		24,								// Want 24bit color 
		0,0,0,0,0,0,					// Not used to select mode
		0,0,							// Not used to select mode
		0,0,0,0,0,						// Not used to select mode
		32,								// Size of depth buffer
		0,								// Not used to select mode
		0,								// Not used to select mode
		PFD_MAIN_PLANE,					// Draw in main plane
		0,								// Not used to select mode
		0,0,0 };						// Not used to select mode

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);

	// Set the pixel format for the device context
	VERIFY(SetPixelFormat(m_hDC, nPixelFormat, &pfd));

	// Create the rendering context
	m_hRC = wglCreateContext(m_hDC);

	// Make the rendering context current, perform initialization, then
	// deselect it
	VERIFY(wglMakeCurrent(m_hDC,m_hRC));
//	GLSetupRC(m_hDC);
	wglMakeCurrent(NULL,NULL);

	// Create the palette if needed
//	InitializePalette();

	return 0;

}

void CCampos3DView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	VERIFY(wglMakeCurrent(m_hDC,m_hRC));


//------------------------------------------------------------------------
	// set correspondence between window and OGL viewport
	/*	glViewport(0,0,cx,cy);

		//double nRange=50;

		m_dAspectRatio=double(cx)/double(cy);

		// update the camera
 		glPushMatrix();
			glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(40.0,m_dAspectRatio,5, 20.0f);
				glTranslatef(0.0f,0.0f,-10.f);
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();*/

//------------------------------------------------------------------------


	int w=cx;
	int h=cy;

	double nRange=0.050;
//	double nRange=50;

//	if (pDoc->selectscene[0] == 1)
//		nRange=0.050;
		
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)//altura
		h = 1;

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
	
		
	//Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	// Reset the coordinate system before modifying
	glLoadIdentity();


	if (w <= h)
		glOrtho(-(nRange),nRange,-nRange*h/w,nRange*h/w,-(nRange*2),nRange*2);
	else
		glOrtho(-(nRange*w/h),nRange*w/h,-nRange,nRange,-(nRange*2),nRange*2);



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	

//-----------------------------------------------------------------



	VERIFY(wglMakeCurrent(NULL,NULL));

	// force redraw
	Invalidate(TRUE);




}








/*
 * 'FontCreateBitmaps()' - Load Windows font bitmaps into OpenGL display
 *                         lists.
 *
 * Only glyphs 32-127 are loaded at present.
 */

GLuint
FontCreateBitmaps(HDC   hdc,		/* I - Device Context */
                  char  *typeface,	/* I - Font specification */
                  int   height,		/* I - Font height/size in pixels */
	          int   weight,		/* I - Weight of font (bold, etc) */
	          DWORD italic)		/* I - Text is italic */
{
  GLuint	base;			/* Base display list for font */
  HFONT		font;			/* Windows font ID */

  
  //if ((base = glGenLists(96)) == 0)
  if ((base = glGenLists(224)) == 0)
	  return (0);

  if (stricmp(typeface, "symbol") == 0)
    font = CreateFont(height, 0, 0, 0, weight, italic, FALSE, FALSE,
                      SYMBOL_CHARSET, OUT_TT_PRECIS,
                      CLIP_DEFAULT_PRECIS, DRAFT_QUALITY,
                      DEFAULT_PITCH, typeface);
  else
    font = CreateFont(height, 0, 0, 0, weight, italic, FALSE, FALSE,
                      ANSI_CHARSET, OUT_TT_PRECIS,
                      CLIP_DEFAULT_PRECIS, DRAFT_QUALITY,
                      DEFAULT_PITCH, typeface);
  
  
  SelectObject(hdc, font);
  
  //wglUseFontBitmaps(hdc, 32, 96, base);
  wglUseFontBitmaps(hdc, 32, 224, base);

  return (base);
}


/*
 * 'FontDelete()' - Delete the OpenGL display lists used for a font.
 */

void
FontDelete(GLuint font)	/* I - Font to delete */
{
  if (font == 0)
    return;

 // glDeleteLists(font, 96);
  glDeleteLists(font, 224);
}


/*
 * 'FontPuts()' - Display a string using the specified font.
 */

void
FontPuts(GLuint font,	/* I - Font to use */
         char   *s)	/* I - String to display */
{
  if (font == 0)
    return;

  if (s == NULL)
    return;

  glPushAttrib(GL_LIST_BIT);
    glListBase(font - 32);
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, s);
  glPopAttrib();
}



/*
 * 'FontPrintf()' - Display a formatted string using the specified font.
 */

void
FontPrintf(GLuint font,		/* I - Font to use */
           char   *format,	/* I - printf() style format string */
           ...)			/* I - Other arguments as necessary */
{
  va_list	ap;			/* Argument pointer */
  char		s[MAX_STRING + 1];	/* Output string */


  if (format == NULL)
    return;

  va_start(ap, format);
  vsprintf(s, format, ap);
  va_end(ap);

  FontPuts(font, s);
}









void CCampos3DView::OnBotaoOndas() 
{
	// TODO: Add your command handler code here
	

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	OndasDlg dlg;
	Complexo j(0,1);
	double z;
	double t=0;
	
	Ondas_movimento=false;
	Invalidate(false);


	dlg.m_campo_elect_x=pDoc->onda.Em;
	dlg.m_campo_elect_y=pDoc->onda.Emy;
	dlg.m_Er=pDoc->onda.Er;
	dlg.m_Ur=pDoc->onda.Ur;
	dlg.m_frequencia=pDoc->onda.f/1000000;//gigahertz
	dlg.m_condutividade=pDoc->onda.GetG();
	dlg.m_impedancia_amplitude=cabs(pDoc->onda.Getn());
	dlg.m_impedancia_angulo=arg(pDoc->onda.Getn())*180/PI;

	dlg.m_angulo_polarizacao=pDoc->onda.O;
	dlg.m_desfasagem_inicial=pDoc->onda.teta;

	
	if (dlg.DoModal()==IDOK)
	{
			
		

		pDoc->selectscene[0]=0;
		pDoc->onda.Em=dlg.m_campo_elect_x;
		pDoc->onda.Emy=dlg.m_campo_elect_y;
		pDoc->onda.Er=dlg.m_Er;
		pDoc->onda.Ur=dlg.m_Ur;
		pDoc->onda.f=dlg.m_frequencia*1000000;//gigahertz

		if (dlg.flag_condutividade)
			pDoc->onda.SetG(dlg.m_condutividade);
		else
		{
			double r,i;
			r=dlg.m_impedancia_amplitude*cos(dlg.m_impedancia_angulo*PI/180);
			i=dlg.m_impedancia_amplitude*sin(dlg.m_impedancia_angulo*PI/180);
			Complexo n1(r,i);
			pDoc->onda.Setn(n1);
		}

		pDoc->onda.O=dlg.m_angulo_polarizacao;
		pDoc->onda.teta=dlg.m_desfasagem_inicial;
		
		Complexo E;//=pDoc->O.Em;
		Complexo Ey;//=pDoc->O.Emy;
		Complexo H;
		Complexo Hx;
		double a=pDoc->onda.GetAB().r;//atenuacao da onda
		double B=pDoc->onda.GetAB().i;//
		double o=pDoc->onda.teta;//fase inicial
		double O=pDoc->onda.O;//angulo polarizacao
		double n=cabs(pDoc->onda.Getn());
		double on=arg(pDoc->onda.Getn());

		pDoc->step_onda=2*PI/(B*pDoc->Q);
	

		pDoc->onda.Em_array.RemoveAll();
		pDoc->onda.Emy_array.RemoveAll();
		pDoc->onda.Hm_array.RemoveAll();
		pDoc->onda.Hmx_array.RemoveAll();

		

		for(z=0;z<=pDoc->Q*5;z=z+pDoc->step_onda)//5 periodos da onda
		{
			E=pDoc->onda.Em*exp(-a*z+j*(-B*z+o) );//ex
			Ey=pDoc->onda.Emy*exp(-a*z+j*(-B*z+o+O));//ey

			H=pDoc->onda.Em/n*exp(-a*z+j*(-B*z+o-on) );//ey
			Hx=-pDoc->onda.Emy/n*exp(-a*z+j*(-B*z+o-on+O));//ex

			pDoc->onda.Em_array.Add(E);
			pDoc->onda.Emy_array.Add(Ey);

			pDoc->onda.Hm_array.Add(H);
			pDoc->onda.Hmx_array.Add(Hx);


		}

		Invalidate(false);
	}


}



void CCampos3DView::GLEixo3D()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	double Range=pDoc->Guias_Eixo_range;


	// red x axis
	glColor3f(1.f,0.f,0.f);
	//eixo xx
	glBegin(GL_LINES);
	glVertex3d(-Range,0,0);
	glVertex3d(Range,0,0);
	glEnd();

	// green y axis
	glColor3f(0.f,1.f,0.f);
	//eixo yy
	glBegin(GL_LINES);
	glVertex3d(0,-Range,0);
	glVertex3d(0,Range,0);
	glEnd();

	// yellow z axis
	glColor3f(1.f,1.f,0.f);
	//eixo zz
	glBegin(GL_LINES);
	glVertex3d(0,0,-Range);
	glVertex3d(0,0,Range);
	glEnd();



	//--Letras-------------------------------------------------------------

	SmallFont  = FontCreateBitmaps(m_hDC, "Courier", 16,  FW_BOLD, 0);

	glRasterPos3d(-Range-Range/20,0,0);//-xx
	FontPuts(SmallFont, "-x");

	glRasterPos3d(Range+Range/20,0,0);//+xx
	FontPuts(SmallFont, "+x");
	
	glRasterPos3d(0,-Range-Range/20,0);//-yy
	FontPuts(SmallFont, "-y");
	glRasterPos3d(0,Range+Range/20,0);//+yy
	FontPuts(SmallFont, "+y");

	glRasterPos3d(0,0,-Range-Range/10);//-zz
	FontPuts(SmallFont, "-z");
	glRasterPos3d(0,0,Range+Range/10);//+zz
	FontPuts(SmallFont, "+z");

	FontDelete(SmallFont);

//---------------------------------------------------------------------

	//for(GLdouble w=-Range;w<=Range;w=w+5)
	for(GLdouble w=-Range;w<=Range;w=w+Range/10)
	{
		GLdouble unit=Range/100;

		// red x axis
		glColor3f(1.f,0.f,0.f);
		glBegin(GL_LINES);//eixo xx
		glVertex3d(w,unit,0);
		glVertex3d(w,-unit,0);
		glEnd();
		
		// green y axis
		glColor3f(0.f,1.f,0.f);
		glBegin(GL_LINES);//eixo yy
		glVertex3d(unit,w,0);
		glVertex3d(-unit,w,0);
		glEnd();


		// yellow z axis
		glColor3f(1.f,1.f,0.f);
		glBegin(GL_LINES);//eixo zz
		glVertex3d(0,unit,w);
		glVertex3d(0,-unit,w);
		glEnd();

	}

}


void CCampos3DView::GLGuiasRectEixo()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	
//	CString sz;

	//guia rectangular

	double a;
	double b;
	double z;
	double Fs=1;//factor de escala para o eixo z

	double Range=pDoc->Guias_Eixo_range;


	if (pDoc->TM_TE)//modo TM - Transversal Magnetico
		pDoc->guiaR=&pDoc->TM;
	else			//modo TE - Transversal Electrico
		pDoc->guiaR=&pDoc->TE;


	a=pDoc->guiaR->a;
	b=pDoc->guiaR->b;
	z=pDoc->guiaR->GetLmn()*Fs;
	//z=pDoc->TM.GetLmn();



//	sz.Format("%lf",z);

//	AfxMessageBox(sz);
	
	
	glColor3d(0.7,1,1);

//	glPushMatrix();
	//amplia 1000 vezes o eixo z
	//glScaled(1,1,1000);

	//inicio do guia rectangular
	glBegin(GL_LINE_STRIP);
		glVertex3d(0,0,0);
		glVertex3d(a,0,0);
		glVertex3d(a,b,0);
		glVertex3d(0,b,0);
		glVertex3d(0,0,0);
	glEnd();


	//fim do guia rectangular
	glBegin(GL_LINE_STRIP);
		glVertex3d(0,0,z);
		glVertex3d(a,0,z);
		glVertex3d(a,b,z);
		glVertex3d(0,b,z);
		glVertex3d(0,0,z);
	glEnd();

	//paredes laterais do guia 
	glBegin(GL_LINES);
		glVertex3d(0,0,0);
		glVertex3d(0,0,z);
		glVertex3d(a,0,0);
		glVertex3d(a,0,z);	
		glVertex3d(0,b,0);
		glVertex3d(0,b,z);
		glVertex3d(a,b,0);
		glVertex3d(a,b,z);
	glEnd();

//	glPopMatrix();

}

void CCampos3DView::GLGuiasCilEixo()
{

	double t;
	double R=0.01;
	double L=0.03;
//	double a,b,z;
	int nLinhas=10;
	
	glColor3d(0.7,1,1);

//	glColor3d(1,0,0);
	auxWireCylinder(0.02,0.02);
	auxSolidCylinder(0.01,0.01);
//	auxWireSphere(0.01);


	glBegin(GL_LINE_STRIP);
	for (t=0;t<=2*PI;t=t+2*PI/100)
	{
		glVertex3d(R*cos(t),R*sin(t),0);
	}
	glEnd();


	glBegin(GL_LINE_STRIP);
	for (t=0;t<=2*PI;t=t+2*PI/100)
	{
		glVertex3d(R*cos(t),R*sin(t),L);
	}
	glEnd();


	glBegin(GL_LINES);
	for (t=0;t<=2*PI;t=t+2*PI/nLinhas)
	{
		glVertex3d(R*cos(t),R*sin(t),0);
		glVertex3d(R*cos(t),R*sin(t),L);
	}
	glEnd();





	/*
	a=b=z=0.01;

	glBegin(GL_LINES);
		glVertex3d(0,0,0);
		glVertex3d(0,0,z);
		glVertex3d(a,0,0);
		glVertex3d(a,0,z);	
		glVertex3d(0,b,0);
		glVertex3d(0,b,z);
		glVertex3d(a,b,0);
		glVertex3d(a,b,z);
	glEnd();*/

}

void CCampos3DView::GLGuiasRectTM_E_2Da()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


//	CString str;
	double z;
	double a=pDoc->a2D;
	double b;
	//double Vx;
	double Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point
//	double NormaV;		//Norma vectorial

	//t=0.0000000000135;

//	double distA;
	double distB;
	
//	double nLinhasA;
	double nLinhasB;
	
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	double scaleVector;
//	double i;
	double j;

	int k=0;	//contador das linhas de força
//	double s =1;
	double l=pDoc->TM.GetLmn();
	

	//RedF,GreenF,BlueF;
	//CArray <double,double> RedT,GreenT,BlueT;

	pDoc->R.RemoveAll();
	pDoc->G.RemoveAll();
	pDoc->B.RemoveAll();
	
	
//	a=pDoc->TM.a;
	b=pDoc->TM.b;
	

//	nLinhasA=10;
	nLinhasB=10;

//	distA=a/nLinhasA;
	distB=b/nLinhasB;


	//pDoc->Campo_Electrico_TM.SetSize(3*int(nLinhasA*nLinhasB));
	pDoc->Campo_Electrico_TM.SetSize(3*int(nLinhasB));
	z=p_z=l/Q;
	
	k=0;
//	i=distA/2;
	j=distB/2;

	
	
	// 1º parte do guia
	
	for(j = distB/2 ; j < b ; j += distB)
	{
		p_x=a;
		p_y=j;	
		p_z=l/4-l/(Q*4);
		
		//reinicia os arrais
		pDoc->Campo_Electrico_TM[k].Ex_arrai.RemoveAll();
		pDoc->Campo_Electrico_TM[k].Ey_arrai.RemoveAll();
		pDoc->Campo_Electrico_TM[k].Ez_arrai.RemoveAll();

		//guarda os pontos de uma linha num arrai
		pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
		pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
		pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);


		Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;
		
		if (Vz >0 )//frente
		{
			pDoc->R.Add(pDoc->RedF);
			pDoc->G.Add(pDoc->GreenF);
			pDoc->B.Add(pDoc->BlueF);
		}
		else //tras
		{
			pDoc->R.Add(pDoc->RedT);
			pDoc->G.Add(pDoc->GreenT);
			pDoc->B.Add(pDoc->BlueT);
		}

		//for(z=l/Q;z<l;z=z+l/Q)
		for(z=0;z<Q;z++)
		{
		//	Vx=pDoc->TM.Ex(p_x,p_y,p_z,t).r;
			Vy=pDoc->TM.Ey(p_x,p_y,p_z,t).r;
			Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;
			
			if (Vz >0 )//frente
			{
			//	Vx=-Vx;
				Vy=-Vy;
				Vz=-Vz;
			}
			
			
			Vmax=VectorMax(0,Vy,Vz);

			if ( Vmax > l/Q)
			{
				scaleVector=l/(Q*Vmax);
				/* Vx*=scaleVector;*/ 
				Vy*=scaleVector; Vz*=scaleVector;
			}
				
			//p_x=p_x+Vx;	
			p_y=p_y+Vy;	p_z=p_z+Vz;

			//	if (p_x<0 || p_x>pDoc->TM.a)break;
			if (p_y<0 || p_y>pDoc->TM.b)break;
			if (p_z<0 || p_z>l/4)break;

			pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
			pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
			pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
			
		}
		

		k++;
	
	}




	// 2º parte do guia
			
	for(j = distB/2 ; j < b ; j += distB)
	{
//		p_x=i;
		p_y=j;	
		p_z=l/4+l/(Q*4);
			
		//reinicia os arrais
		pDoc->Campo_Electrico_TM[k].Ex_arrai.RemoveAll();
		pDoc->Campo_Electrico_TM[k].Ey_arrai.RemoveAll();
		pDoc->Campo_Electrico_TM[k].Ez_arrai.RemoveAll();

		//guarda os pontos de uma linha num arrai
		pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
		pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
		pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);


		Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;
			
		if (Vz <0 )//tras
		{			
			pDoc->R.Add(pDoc->RedT);
			pDoc->G.Add(pDoc->GreenT);
			pDoc->B.Add(pDoc->BlueT);
		}
		else //frente
		{
			pDoc->R.Add(pDoc->RedF);
			pDoc->G.Add(pDoc->GreenF);
			pDoc->B.Add(pDoc->BlueF);
		}


		//for(z=l/Q;z<l;z=z+l/Q)
		for(z=0;z<Q;z=z++)
		{
		//	Vx=pDoc->TM.Ex(p_x,p_y,p_z,t).r;
			Vy=pDoc->TM.Ey(p_x,p_y,p_z,t).r;
			Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;

			if (Vz <0 )//tras
			{
			//	Vx=-Vx;
				Vy=-Vy;
				Vz=-Vz;					
			}
								
					
			Vmax=VectorMax(0,Vy,Vz);

			if ( Vmax > l/Q)
			{
				scaleVector=l/(Q*Vmax);
				//Vx*=scaleVector; 
				Vy*=scaleVector; Vz*=scaleVector;
			}
				
			//p_x=p_x+Vx;	
			p_y=p_y+Vy;	p_z=p_z+Vz;

		//	if (p_x<0 || p_x>pDoc->TM.a)break;
			if (p_y<0 || p_y>pDoc->TM.b)break;
			if (p_z<l/4 || p_z>l*3/4)break;

			pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
			pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
			pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
			
		}

		k++;
	}



	// 3º parte do guia
	
	for(j = distB/2 ; j < b ; j += distB)
	{
		//p_x=i;
		p_y=j;	
		p_z=l*3/4+l/(Q*4);
			
		//reinicia os arrais
		pDoc->Campo_Electrico_TM[k].Ex_arrai.RemoveAll();
		pDoc->Campo_Electrico_TM[k].Ey_arrai.RemoveAll();
		pDoc->Campo_Electrico_TM[k].Ez_arrai.RemoveAll();

		//guarda os pontos de uma linha num arrai
		pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
		pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
		pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);


		Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;
			
		if (Vz < 0 )//tras
		{				
			pDoc->R.Add(pDoc->RedT);
			pDoc->G.Add(pDoc->GreenT);
			pDoc->B.Add(pDoc->BlueT);
		}
		else //frente
		{
			pDoc->R.Add(pDoc->RedF);
			pDoc->G.Add(pDoc->GreenF);
			pDoc->B.Add(pDoc->BlueF);			
		}


		//for(z=l/Q;z<l;z=z+l/Q)
		for(z=0;z<Q;z=z++)
		{
		//	Vx=pDoc->TM.Ex(p_x,p_y,p_z,t).r;
			Vy=pDoc->TM.Ey(p_x,p_y,p_z,t).r;
			Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;

			if (Vz < 0 )//tras
			{
			//	Vx=-Vx;
				Vy=-Vy;
				Vz=-Vz;								
			}
				
					
			Vmax=VectorMax(0,Vy,Vz);

			if ( Vmax > l/Q)
			{
				scaleVector=l/(Q*Vmax);
				//Vx*=scaleVector; 
				Vy*=scaleVector; Vz*=scaleVector;
			}
				
			//p_x=p_x+Vx;	
			p_y=p_y+Vy;	p_z=p_z+Vz;

		//	if (p_x<0 || p_x>pDoc->TM.a)break;
			if (p_y<0 || p_y>pDoc->TM.b)break;
			if (p_z< l*3/4 || p_z>l)break;

			pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
			pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
			pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
		}
		

		k++;
	}
	

}


void CCampos3DView::GLGuiasRectTM_H_3D()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point
	
	double z;
	double a;
	double b;
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	int l;
	double scaleVector;

	double L=pDoc->TM.GetLmn();
	
	double NCampos=6;
	double LSpace=L/NCampos;

	double distA;
	double distB;
	double nLinhasA;
	double nLinhasB;
	double largura;
	double i, j;
//	double t=0;
	int k;

	a=pDoc->TM.a;
	b=pDoc->TM.b;


	nLinhasA=4;
	nLinhasB=4;

	distA=a/nLinhasA;
	distB=b/nLinhasB;

	if (a < b)
		largura=a;
	else
		largura=b;
	

	pDoc->Campo_Magnetico_TM.SetSize(int((5+2)*nLinhasA*nLinhasB));


	k=0;
	i=distA/2;
	j=distB/2;


	for(z=LSpace; z <= L; z = z+LSpace)
	{
		for (i = distA/2; i < a ; i += distA)
		{
			for(j = distB/2 ; j < b ; j += distB)
			{
				p_x=i;p_y=j;	
				p_z=z;



				if (pDoc->Campo_Magnetico_TM[k].Hx_arrai.GetSize() < 1)
					pDoc->Campo_Magnetico_TM[k].Hx_arrai.Add(p_x);
				else
					pDoc->Campo_Magnetico_TM[k].Hx_arrai[0]=p_x;
						
				if (pDoc->Campo_Magnetico_TM[k].Hy_arrai.GetSize() < 1)
					pDoc->Campo_Magnetico_TM[k].Hy_arrai.Add(p_y);
				else
					pDoc->Campo_Magnetico_TM[k].Hy_arrai[0]=p_y;

				if (pDoc->Campo_Magnetico_TM[k].Hz_arrai.GetSize() < 1)
					pDoc->Campo_Magnetico_TM[k].Hz_arrai.Add(p_z);
				else
					pDoc->Campo_Magnetico_TM[k].Hz_arrai[0]=p_z;

				l=0;

				if (pDoc->RH.GetSize() < l-1)
				{
					pDoc->RH[l]=pDoc->RedF;
					pDoc->GH[l]=pDoc->GreenF;
					pDoc->BH[l]=pDoc->BlueF;
				}
				else
				{					
					pDoc->RH.Add(pDoc->RedT);
					pDoc->GH.Add(pDoc->GreenT);
					pDoc->BH.Add(pDoc->BlueT);					
				}
				

				for(l=0;l<Q;l++)
				{
								
					Vx=pDoc->TM.Hx(p_x,p_y,p_z,t).r;
					Vy=pDoc->TM.Hy(p_x,p_y,p_z,t).r;
					Vz=pDoc->TM.Hz(p_x,p_y,p_z,t).r;

					Vmax=VectorMax(Vx,Vy,Vz);

					
					if ( Vmax > largura/Q)
					{
						scaleVector=largura/(Q*Vmax);
						Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
					}
						
					p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;


					if (p_x<0 || p_x>pDoc->TM.a || p_y<0 || p_y>pDoc->TM.b || p_z<0 || p_z>L)
					{
						pDoc->Campo_Magnetico_TM[k].Hx_arrai.SetSize(l+1);
						pDoc->Campo_Magnetico_TM[k].Hy_arrai.SetSize(l+1);
						pDoc->Campo_Magnetico_TM[k].Hz_arrai.SetSize(l+1);
						break;
					}
					

					int jj=pDoc->RH.GetSize();
					if (pDoc->RH.GetSize() < l-1)
					{
						pDoc->RH[l+1]=pDoc->RedF;
						pDoc->GH[l+1]=pDoc->GreenF;
						pDoc->BH[l+1]=pDoc->BlueF;
					}
					else
					{					
						pDoc->RH.Add(pDoc->RedT);
						pDoc->GH.Add(pDoc->GreenT);
						pDoc->BH.Add(pDoc->BlueT);					
					}
					

					if (pDoc->Campo_Magnetico_TM[k].Hx_arrai.GetSize() < l+2)
						pDoc->Campo_Magnetico_TM[k].Hx_arrai.Add(p_x);
					else
						pDoc->Campo_Magnetico_TM[k].Hx_arrai[l+1]=p_x;

					if (pDoc->Campo_Magnetico_TM[k].Hy_arrai.GetSize() < l+2)
						pDoc->Campo_Magnetico_TM[k].Hy_arrai.Add(p_y);
					else
						pDoc->Campo_Magnetico_TM[k].Hy_arrai[l+1]=p_y;


					if (pDoc->Campo_Magnetico_TM[k].Hz_arrai.GetSize() < l+2)
						pDoc->Campo_Magnetico_TM[k].Hz_arrai.Add(p_z);
					else
						pDoc->Campo_Magnetico_TM[k].Hz_arrai[l+1]=p_z;
					
				}

				k++;
			}			
		}	
	}



}

void CCampos3DView::GLGuiasRectTM_H_3D_Draw()
{
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int k;
	int i;
	int nLinhas;

	
	glColor3d(1,0,0);//vermelho

	glPushMatrix();
	glScaled(1,1,1);

	nLinhas=pDoc->Campo_Magnetico_TM.GetSize();

/////////////-------------------------------

	for(k=0;k<nLinhas;k++)
	{
		glColor3d(pDoc->RH[k],pDoc->GH[k],pDoc->BH[k]);

		glColor3d(1,0,0);//vermelho

		glBegin(GL_LINE_STRIP);

		for(i=0;i<pDoc->Campo_Magnetico_TM[k].Hx_arrai.GetSize();i++)
		{
						
			glVertex3d(	pDoc->Campo_Magnetico_TM[k].Hx_arrai[i],
						pDoc->Campo_Magnetico_TM[k].Hy_arrai[i],
						//0);
						pDoc->Campo_Magnetico_TM[k].Hz_arrai[i]);
		}

		glEnd();
	}


	glPopMatrix();

}

void CCampos3DView::GLGuiasRectTE_H_3D_Draw()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int k;
	int i;
	int nLinhas;

	
	glPushMatrix();
	glScaled(1,1,1);

	nLinhas=pDoc->Campo_Magnetico_TE.GetSize();

	for(k=0;k<nLinhas;k++)
	{
		glColor3d(pDoc->R[k],pDoc->G[k],pDoc->B[k]);

		glBegin(GL_LINE_STRIP);

		for(i=0;i<pDoc->Campo_Magnetico_TE[k].Hx_arrai.GetSize();i++)
		{
						
			glVertex3d(	pDoc->Campo_Magnetico_TE[k].Hx_arrai[i],
						pDoc->Campo_Magnetico_TE[k].Hy_arrai[i],
						pDoc->Campo_Magnetico_TE[k].Hz_arrai[i]);
		}

		glEnd();
	}


	glPopMatrix();



}



void CCampos3DView::GLGuiasRectTE_H_3D()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	double z;
	double a;
	double b;
	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point

//	double t=0; //tempo inicial
//	double t=0.0000000000135;
	double distA;
	double distB;
	double nLinhasA;
	double nLinhasB;
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	double scaleVector;
	double i;
	double j;
	int k=0;	//contador das linhas de força
	double l=pDoc->TE.GetLmn();
	
	
	//RedF,GreenF,BlueF;
/*	pDoc->R.RemoveAll();
	pDoc->G.RemoveAll();
	pDoc->B.RemoveAll();*/
	
	
	a=pDoc->TE.a;
	b=pDoc->TE.b;
	

	nLinhasA=10;
	nLinhasB=10;

	distA=a/nLinhasA;
	distB=b/nLinhasB;


	pDoc->Campo_Magnetico_TE.SetSize(3*int(nLinhasA*nLinhasB));
	z=p_z=l/Q;
	
	k=0;
	i=distA/2;
	j=distB/2;

	
	// 1ª parte do guia
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;p_y=j;
			//p_z=l/(Q*4);
			p_z=0;
			//p_z=l/4-l/(Q*4);
			
			//reinicia os arrais
			pDoc->Campo_Magnetico_TE[k].Hx_arrai.RemoveAll();
			pDoc->Campo_Magnetico_TE[k].Hy_arrai.RemoveAll();
			pDoc->Campo_Magnetico_TE[k].Hz_arrai.RemoveAll();

			//guarda os pontos de uma linha num arrai
			pDoc->Campo_Magnetico_TE[k].Hx_arrai.Add(p_x);
			pDoc->Campo_Magnetico_TE[k].Hy_arrai.Add(p_y);
			pDoc->Campo_Magnetico_TE[k].Hz_arrai.Add(p_z);


			Vz=pDoc->TE.Hz(p_x,p_y,p_z,t).r;
			
			if (Vz >0 )//frente
			{
				pDoc->R.Add(pDoc->RedF);
				pDoc->G.Add(pDoc->GreenF);
				pDoc->B.Add(pDoc->BlueF);
			}
			else //tras
			{
				pDoc->R.Add(pDoc->RedT);
				pDoc->G.Add(pDoc->GreenT);
				pDoc->B.Add(pDoc->BlueT);
			}


			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=pDoc->TE.Hx(p_x,p_y,p_z,t).r;
				Vy=pDoc->TE.Hy(p_x,p_y,p_z,t).r;
				Vz=pDoc->TE.Hz(p_x,p_y,p_z,t).r;


			/*	if (Vz <0 )//trás
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
				}*/
		
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > l/Q)
				{
					scaleVector=l/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
				
				//y_arrai.Add(p_y);
			//	pDoc->Campo_Electrico_TM[k].Ez_ar;
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				if (p_x<0 || p_x>pDoc->TE.a)break;
				if (p_y<0 || p_y>pDoc->TE.b)break;
				if (p_z<0 || p_z>l/4)break;

				pDoc->Campo_Magnetico_TE[k].Hx_arrai.Add(p_x);
				pDoc->Campo_Magnetico_TE[k].Hy_arrai.Add(p_y);
				pDoc->Campo_Magnetico_TE[k].Hz_arrai.Add(p_z);
			}
		

			k++;
		}
	}
	







	// 2ª parte do guia
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;p_y=j;
			p_z=l/2;
			
			//reinicia os arrais
			pDoc->Campo_Magnetico_TE[k].Hx_arrai.RemoveAll();
			pDoc->Campo_Magnetico_TE[k].Hy_arrai.RemoveAll();
			pDoc->Campo_Magnetico_TE[k].Hz_arrai.RemoveAll();

			//guarda os pontos de uma linha num arrai
			pDoc->Campo_Magnetico_TE[k].Hx_arrai.Add(p_x);
			pDoc->Campo_Magnetico_TE[k].Hy_arrai.Add(p_y);
			pDoc->Campo_Magnetico_TE[k].Hz_arrai.Add(p_z);


			Vz=pDoc->TE.Hz(p_x,p_y,p_z,t).r;
			
			if (Vz >0 )//frente
			{
				pDoc->R.Add(pDoc->RedF);
				pDoc->G.Add(pDoc->GreenF);
				pDoc->B.Add(pDoc->BlueF);
			}
			else //tras
			{
				pDoc->R.Add(pDoc->RedT);
				pDoc->G.Add(pDoc->GreenT);
				pDoc->B.Add(pDoc->BlueT);
			}


			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=pDoc->TE.Hx(p_x,p_y,p_z,t).r;
				Vy=pDoc->TE.Hy(p_x,p_y,p_z,t).r;
				Vz=pDoc->TE.Hz(p_x,p_y,p_z,t).r;

						
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > l/Q)
				{
					scaleVector=l/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
				
				//y_arrai.Add(p_y);
			//	pDoc->Campo_Electrico_TM[k].Ez_ar;
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				if (p_x<0 || p_x>pDoc->TE.a)break;
				if (p_y<0 || p_y>pDoc->TE.b)break;
				if (p_z<l/4 || p_z>l*3/4)break;

				pDoc->Campo_Magnetico_TE[k].Hx_arrai.Add(p_x);
				pDoc->Campo_Magnetico_TE[k].Hy_arrai.Add(p_y);
				pDoc->Campo_Magnetico_TE[k].Hz_arrai.Add(p_z);
			}
		

			k++;
		}
	}




	// 3ª parte do guia
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;p_y=j;
			p_z=l/2;
			
			
			//reinicia os arrais
			pDoc->Campo_Magnetico_TE[k].Hx_arrai.RemoveAll();
			pDoc->Campo_Magnetico_TE[k].Hy_arrai.RemoveAll();
			pDoc->Campo_Magnetico_TE[k].Hz_arrai.RemoveAll();

			//guarda os pontos de uma linha num arrai
			pDoc->Campo_Magnetico_TE[k].Hx_arrai.Add(p_x);
			pDoc->Campo_Magnetico_TE[k].Hy_arrai.Add(p_y);
			pDoc->Campo_Magnetico_TE[k].Hz_arrai.Add(p_z);


			Vz=pDoc->TE.Hz(p_x,p_y,p_z,t).r;
			
			if (Vz >0 )//frente
			{
				pDoc->R.Add(pDoc->RedF);
				pDoc->G.Add(pDoc->GreenF);
				pDoc->B.Add(pDoc->BlueF);
			}
			else //tras
			{
				pDoc->R.Add(pDoc->RedT);
				pDoc->G.Add(pDoc->GreenT);
				pDoc->B.Add(pDoc->BlueT);
			}


			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=pDoc->TE.Hx(p_x,p_y,p_z,t).r;
				Vy=pDoc->TE.Hy(p_x,p_y,p_z,t).r;
				Vz=pDoc->TE.Hz(p_x,p_y,p_z,t).r;

						
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > l/Q)
				{
					scaleVector=l/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
				
				//y_arrai.Add(p_y);
			//	pDoc->Campo_Electrico_TM[k].Ez_ar;
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				if (p_x<0 || p_x>pDoc->TE.a)break;
				if (p_y<0 || p_y>pDoc->TE.b)break;
				if (p_z<l/4 || p_z>l*3/4)break;

				pDoc->Campo_Magnetico_TE[k].Hx_arrai.Add(p_x);
				pDoc->Campo_Magnetico_TE[k].Hy_arrai.Add(p_y);
				pDoc->Campo_Magnetico_TE[k].Hz_arrai.Add(p_z);
			}
		

			k++;
		}
	}


}

double CCampos3DView::GetZeroTM_E()
{
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);



	double z1;
	double k_aux;
	int k;

	k_aux=5.2-2*pDoc->TM.f*t;
	k = int(k_aux);

	if (k < k_aux)
		k--;


	z1=pDoc->TM.GetLmn()*( (pDoc->TM.GetW()*t-PI/2+k*PI)/(2*PI) );

	return z1;

}


/*
void CCampos3DView::GLGuiasRectTM_E_3D_alternativa()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	int z;
	double a;
	double b;
	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point
	
	double distA;
	double distB;
	
	double nLinhasA;
	double nLinhasB;
	
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	double scaleVector;
	double i;
	double j;

	int k=0;	//contador das linhas de força
	double l=pDoc->TM.GetLmn();


	a=pDoc->TM.a;
	b=pDoc->TM.b;
	
	nLinhasA=10;
	nLinhasB=10;

	distA=a/nLinhasA;
	distB=b/nLinhasB;


	pDoc->Campo_Electrico_TM.SetSize(3*int(nLinhasA*nLinhasB));
		
	k=0;
	i=distA/2;
	j=distB/2;



	double z1=GetZeroTM_E();





		// 1º parte do guia
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			p_z=l/4-l/(Q*4);

			
		
			if (pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
			else
				pDoc->Campo_Electrico_TM[k].Ex_arrai[0]=p_x;
					
			if (pDoc->Campo_Electrico_TM[k].Ey_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
			else
				pDoc->Campo_Electrico_TM[k].Ey_arrai[0]=p_y;

			if (pDoc->Campo_Electrico_TM[k].Ez_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
			else
				pDoc->Campo_Electrico_TM[k].Ez_arrai[0]=p_z;


			Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;
			
			if (Vz >0 )//frente
			{
				//int jj=pDoc->RE.GetSize();

				if (pDoc->RE.GetSize() < k-1)
				{
					pDoc->RE[k]=pDoc->RedF;
					pDoc->GE[k]=pDoc->GreenF;
					pDoc->BE[k]=pDoc->BlueF;
				}
				else
				{					
					pDoc->RE.Add(pDoc->RedF);
					pDoc->GE.Add(pDoc->GreenF);
					pDoc->BE.Add(pDoc->BlueF);					
				}
					
				
			}
			else //tras
			{
				if (pDoc->RE.GetSize() < k-1)
				{
					pDoc->RE[k]=pDoc->RedT;
					pDoc->GE[k]=pDoc->GreenT;
					pDoc->BE[k]=pDoc->BlueT;
				}
				else
				{					
					pDoc->RE.Add(pDoc->RedT);
					pDoc->GE.Add(pDoc->GreenT);
					pDoc->BE.Add(pDoc->BlueT);					
				}/*
				pDoc->R.Add(pDoc->RedT);
				pDoc->G.Add(pDoc->GreenT);
				pDoc->B.Add(pDoc->BlueT);*/
	//		}


		//	t=0;
			//for(z=l/Q;z<l;z=z+l/Q)
	/*		for(z=0;z<Q;z++)
			{
				Vx=pDoc->TM.Ex(p_x,p_y,p_z,t).r;
				Vy=pDoc->TM.Ey(p_x,p_y,p_z,t).r;
				Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;

				if (Vz >0 )//frente
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
				}
				
				
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > l/Q)
				{
					scaleVector=l/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				if (p_x<0 || p_x>pDoc->TM.a || p_y<0 || p_y>pDoc->TM.b || p_z<0 || p_z>l/4)
				{
					pDoc->Campo_Electrico_TM[k].Ex_arrai.SetSize(z+1);
					pDoc->Campo_Electrico_TM[k].Ey_arrai.SetSize(z+1);
					pDoc->Campo_Electrico_TM[k].Ez_arrai.SetSize(z+1);
					break;
				}

			
				//int kk=pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize();
				
				if (pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
				else
					pDoc->Campo_Electrico_TM[k].Ex_arrai[z+1]=p_x;

				
				if (pDoc->Campo_Electrico_TM[k].Ey_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
				else
					pDoc->Campo_Electrico_TM[k].Ey_arrai[z+1]=p_y;


				if (pDoc->Campo_Electrico_TM[k].Ez_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
				else
					pDoc->Campo_Electrico_TM[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}


}*/

/*
void CCampos3DView::GLGuiasRectTM_E_3D()
{
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

//	int auxsize;

//	CString str;
	int z;
	double a;
	double b;
	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point
//	double NormaV;		//Norma vectorial
//	double t=0.0000000000135;
//	double t=0.0000000000;
	
	double distA;
	double distB;
	
	double nLinhasA;
	double nLinhasB;
	
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	double scaleVector;
	double i;
	double j;

	int k=0;	//contador das linhas de força
//	double s =1;
	double l=pDoc->TM.GetLmn();
	

	
/*	pDoc->R.RemoveAll();
	pDoc->G.RemoveAll();
	pDoc->B.RemoveAll();*/
	
	
/*	a=pDoc->TM.a;
	b=pDoc->TM.b;
	

	nLinhasA=10;
	nLinhasB=10;

	distA=a/nLinhasA;
	distB=b/nLinhasB;


	pDoc->Campo_Electrico_TM.SetSize(3*int(nLinhasA*nLinhasB));
	//z=p_z=l/Q;
	
	k=0;
	i=distA/2;
	j=distB/2;

	
	

	// 1º parte do guia
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			p_z=l/4-l/(Q*4);

			
		
			if (pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
			else
				pDoc->Campo_Electrico_TM[k].Ex_arrai[0]=p_x;
					
			if (pDoc->Campo_Electrico_TM[k].Ey_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
			else
				pDoc->Campo_Electrico_TM[k].Ey_arrai[0]=p_y;

			if (pDoc->Campo_Electrico_TM[k].Ez_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
			else
				pDoc->Campo_Electrico_TM[k].Ez_arrai[0]=p_z;


			Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;
			
			if (Vz >0 )//frente
			{
				//int jj=pDoc->RE.GetSize();

				if (pDoc->RE.GetSize() < k-1)
				{
					pDoc->RE[k]=pDoc->RedF;
					pDoc->GE[k]=pDoc->GreenF;
					pDoc->BE[k]=pDoc->BlueF;
				}
				else
				{					
					pDoc->RE.Add(pDoc->RedF);
					pDoc->GE.Add(pDoc->GreenF);
					pDoc->BE.Add(pDoc->BlueF);					
				}
					
				
			}
			else //tras
			{
				if (pDoc->RE.GetSize() < k-1)
				{
					pDoc->RE[k]=pDoc->RedT;
					pDoc->GE[k]=pDoc->GreenT;
					pDoc->BE[k]=pDoc->BlueT;
				}
				else
				{					
					pDoc->RE.Add(pDoc->RedT);
					pDoc->GE.Add(pDoc->GreenT);
					pDoc->BE.Add(pDoc->BlueT);					
				}/*
				pDoc->R.Add(pDoc->RedT);
				pDoc->G.Add(pDoc->GreenT);
				pDoc->B.Add(pDoc->BlueT);*/
		//	}


		//	t=0;
			//for(z=l/Q;z<l;z=z+l/Q)
/*			for(z=0;z<Q;z++)
			{
				Vx=pDoc->TM.Ex(p_x,p_y,p_z,t).r;
				Vy=pDoc->TM.Ey(p_x,p_y,p_z,t).r;
				Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;

				if (Vz >0 )//frente
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
				}
				
				
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > l/Q)
				{
					scaleVector=l/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				if (p_x<0 || p_x>pDoc->TM.a || p_y<0 || p_y>pDoc->TM.b || p_z<0 || p_z>l/4)
				{
					pDoc->Campo_Electrico_TM[k].Ex_arrai.SetSize(z+1);
					pDoc->Campo_Electrico_TM[k].Ey_arrai.SetSize(z+1);
					pDoc->Campo_Electrico_TM[k].Ez_arrai.SetSize(z+1);
					break;
				}

			
				//int kk=pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize();
				
				if (pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
				else
					pDoc->Campo_Electrico_TM[k].Ex_arrai[z+1]=p_x;

				
				if (pDoc->Campo_Electrico_TM[k].Ey_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
				else
					pDoc->Campo_Electrico_TM[k].Ey_arrai[z+1]=p_y;


				if (pDoc->Campo_Electrico_TM[k].Ez_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
				else
					pDoc->Campo_Electrico_TM[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}




	// 2º parte do guia
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			p_z=l/4+l/(Q*4);
			
			
			if (pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
			else
				pDoc->Campo_Electrico_TM[k].Ex_arrai[0]=p_x;
					
			if (pDoc->Campo_Electrico_TM[k].Ey_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
			else
				pDoc->Campo_Electrico_TM[k].Ey_arrai[0]=p_y;

			if (pDoc->Campo_Electrico_TM[k].Ez_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
			else
				pDoc->Campo_Electrico_TM[k].Ez_arrai[0]=p_z;


			Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;
			
			if (Vz <0 )//tras
			{
				if (pDoc->RE.GetSize() < k-1)
				{
					pDoc->RE[k]=pDoc->RedT;
					pDoc->GE[k]=pDoc->GreenT;
					pDoc->BE[k]=pDoc->BlueT;
				}
				else
				{					
					pDoc->RE.Add(pDoc->RedT);
					pDoc->GE.Add(pDoc->GreenT);
					pDoc->BE.Add(pDoc->BlueT);					
				}
			}
			else //frente
			{				
				if (pDoc->RE.GetSize() < k-1)
				{
					pDoc->RE[k]=pDoc->RedF;
					pDoc->GE[k]=pDoc->GreenF;
					pDoc->BE[k]=pDoc->BlueF;
				}
				else
				{					
					pDoc->RE.Add(pDoc->RedF);
					pDoc->GE.Add(pDoc->GreenF);
					pDoc->BE.Add(pDoc->BlueF);					
				}				
			}


			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z=z++)
			{
				Vx=pDoc->TM.Ex(p_x,p_y,p_z,t).r;
				Vy=pDoc->TM.Ey(p_x,p_y,p_z,t).r;
				Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;

				if (Vz <0 )//tras
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;					
				}
								
					
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > l/Q)
				{
					scaleVector=l/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;



				if (p_x<0 || p_x>pDoc->TM.a || p_y<0 || p_y>pDoc->TM.b || p_z<l/4 || p_z>l*3/4)
				{
					pDoc->Campo_Electrico_TM[k].Ex_arrai.SetSize(z+1);
					pDoc->Campo_Electrico_TM[k].Ey_arrai.SetSize(z+1);
					pDoc->Campo_Electrico_TM[k].Ez_arrai.SetSize(z+1);
					break;
				}


				if (pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
				else
					pDoc->Campo_Electrico_TM[k].Ex_arrai[z+1]=p_x;

				
				if (pDoc->Campo_Electrico_TM[k].Ey_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
				else
					pDoc->Campo_Electrico_TM[k].Ey_arrai[z+1]=p_y;


				if (pDoc->Campo_Electrico_TM[k].Ez_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
				else
					pDoc->Campo_Electrico_TM[k].Ez_arrai[z+1]=p_z;
			}
			
			k++;
		}
	}



	// 3º parte do guia
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;p_y=j;	
			p_z=l*3/4+l/(Q*4);
			
			
			
			if (pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
			else
				pDoc->Campo_Electrico_TM[k].Ex_arrai[0]=p_x;
					
			if (pDoc->Campo_Electrico_TM[k].Ey_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
			else
				pDoc->Campo_Electrico_TM[k].Ey_arrai[0]=p_y;

			if (pDoc->Campo_Electrico_TM[k].Ez_arrai.GetSize() < 1)
				pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
			else
				pDoc->Campo_Electrico_TM[k].Ez_arrai[0]=p_z;



			Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;
			
			if (Vz < 0 )//tras
			{			
				if (pDoc->RE.GetSize() < k-1)
				{
					pDoc->RE[k]=pDoc->RedT;
					pDoc->GE[k]=pDoc->GreenT;
					pDoc->BE[k]=pDoc->BlueT;
				}
				else
				{					
					pDoc->RE.Add(pDoc->RedT);
					pDoc->GE.Add(pDoc->GreenT);
					pDoc->BE.Add(pDoc->BlueT);					
				}
				
			}
			else //frente
			{				
				if (pDoc->RE.GetSize() < k-1)
				{
					pDoc->RE[k]=pDoc->RedF;
					pDoc->GE[k]=pDoc->GreenF;
					pDoc->BE[k]=pDoc->BlueF;
				}
				else
				{					
					pDoc->RE.Add(pDoc->RedF);
					pDoc->GE.Add(pDoc->GreenF);
					pDoc->BE.Add(pDoc->BlueF);					
				}						
			}


			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z=z++)
			{
				Vx=pDoc->TM.Ex(p_x,p_y,p_z,t).r;
				Vy=pDoc->TM.Ey(p_x,p_y,p_z,t).r;
				Vz=pDoc->TM.Ez(p_x,p_y,p_z,t).r;

				if (Vz < 0 )//tras
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;								
				}
				
					
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > l/Q)
				{
					scaleVector=l/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

			
				if (p_x<0 || p_x>pDoc->TM.a || p_y<0 || p_y>pDoc->TM.b || p_z<l*3/4 || p_z>l)
				{
					pDoc->Campo_Electrico_TM[k].Ex_arrai.SetSize(z+1);
					pDoc->Campo_Electrico_TM[k].Ey_arrai.SetSize(z+1);
					pDoc->Campo_Electrico_TM[k].Ez_arrai.SetSize(z+1);
					break;
				}
					
				
				if (pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ex_arrai.Add(p_x);
				else
					pDoc->Campo_Electrico_TM[k].Ex_arrai[z+1]=p_x;

				
				if (pDoc->Campo_Electrico_TM[k].Ey_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ey_arrai.Add(p_y);
				else
					pDoc->Campo_Electrico_TM[k].Ey_arrai[z+1]=p_y;


				if (pDoc->Campo_Electrico_TM[k].Ez_arrai.GetSize() < z+2)
					pDoc->Campo_Electrico_TM[k].Ez_arrai.Add(p_z);
				else
					pDoc->Campo_Electrico_TM[k].Ez_arrai[z+1]=p_z;
			}
		

			k++;
		}
	}


}*/

void CCampos3DView::GLGuiasRectTM_E_3D_Draw()
{
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int k;
	int i;
	int nLinhas;

	
	glPushMatrix();
	glScaled(1,1,1);

	nLinhas=pDoc->Campo_Electrico_TM.GetSize();

	for(k=0;k<nLinhas;k++)
	{

	
		glColor3d(pDoc->RE[k],pDoc->GE[k],pDoc->BE[k]);

		glBegin(GL_LINE_STRIP);

		for(i=0;i<pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize();i++)
		{
						
			glVertex3d(	pDoc->Campo_Electrico_TM[k].Ex_arrai[i],
						pDoc->Campo_Electrico_TM[k].Ey_arrai[i],
						pDoc->Campo_Electrico_TM[k].Ez_arrai[i]);
		}

		glEnd();
	}


	glPopMatrix();


}

void CCampos3DView::GLGuiasRectTM_E_2Da_Draw()
{
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int k;
	int i;
	int nLinhas;

	
	glPushMatrix();
	glScaled(1,1,1);

	nLinhas=pDoc->Campo_Electrico_TM.GetSize();

	for(k=0;k<nLinhas;k++)
	{
		glColor3d(pDoc->R[k],pDoc->G[k],pDoc->B[k]);

		glBegin(GL_LINE_STRIP);

		for(i=0;i<pDoc->Campo_Electrico_TM[k].Ex_arrai.GetSize();i++)
		{
						
			glVertex3d(	pDoc->Campo_Electrico_TM[k].Ex_arrai[i],
						pDoc->Campo_Electrico_TM[k].Ey_arrai[i],
						pDoc->Campo_Electrico_TM[k].Ez_arrai[i]);
		}

		glEnd();
	}


	glPopMatrix();
}


void CCampos3DView::GLOndasEixo()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	double Range=pDoc->Ondas_Eixo_range;



	// red x axis
	glColor3f(1.f,0.f,0.f);
	//eixo xx
	glBegin(GL_LINES);
	glVertex3d(-Range,0,0);
	glVertex3d(Range,0,0);
	glEnd();

	// green y axis
	glColor3f(0.f,1.f,0.f);
	//eixo yy
	glBegin(GL_LINES);
	glVertex3d(0,-Range,0);
	glVertex3d(0,Range,0);
	glEnd();

	// yellow z axis
	glColor3f(1.f,1.f,0.f);
	//eixo zz
	glBegin(GL_LINES);
	glVertex3d(0,0,-Range);
	glVertex3d(0,0,Range);
	glEnd();
	


//-----------------------------------------------------------------

	
	SmallFont  = FontCreateBitmaps(m_hDC, "Courier", 16,  FW_BOLD, 0);

	glRasterPos3d(-Range-Range/20,0,0);//-xx
	FontPuts(SmallFont, "-Em");

	glRasterPos3d(Range+Range/20,0,0);//+xx
	FontPuts(SmallFont, "+Em");
	
	glRasterPos3d(0,-Range-Range/20,0);//-yy
	FontPuts(SmallFont, "-Hm");
	glRasterPos3d(0,Range+Range/20,0);//+yy
	FontPuts(SmallFont, "+Hm");

	glRasterPos3d(0,0,-Range-Range/20);//-zz
	FontPuts(SmallFont, "-z");
	glRasterPos3d(0,0,Range+Range/20);//+zz
	FontPuts(SmallFont, "+z");

	FontDelete(SmallFont);



	for(GLdouble w=-Range;w<=Range;w=w+5)
	{
		GLdouble unit=.5;

		// red x axis
		glColor3f(1.f,0.f,0.f);
		glBegin(GL_LINES);//eixo xx
		glVertex3d(w,unit,0);
		glVertex3d(w,-unit,0);
		glEnd();
		
		// green y axis
		glColor3f(0.f,1.f,0.f);
		glBegin(GL_LINES);//eixo yy
		glVertex3d(unit,w,0);
		glVertex3d(-unit,w,0);
		glEnd();


		// yellow z axis
		glColor3f(1.f,1.f,0.f);
		glBegin(GL_LINES);//eixo zz
		glVertex3d(0,unit,w);
		glVertex3d(0,-unit,w);
		glEnd();

	}


}


void CCampos3DView::GLOndas3D()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//double Range=pDoc->Ondas_Eixo_range;
	int i=0;
	Complexo j(0,1);
	double n=cabs(pDoc->onda.Getn());
//	double on=arg(pDoc->onda.Getn());
//	Complexo n_=pDoc->onda.Getn();
	double O=pDoc->onda.O;



	double ux;
	double uy;
	double uz;
	double Oz;


	glPushMatrix();
	//glScaled(0.1,0.1,0.1);

		//campo eléctrico	
		glColor3d(1,0,0);//vermelho
		
		double z=0;
		for(z=0;z<=pDoc->Q*5;z=z+pDoc->step_onda)//5 periodos da onda
		{
			
			//CAMPO ELECTRICO-------------------------------------------------------------
			glColor3d(1,0,0);//vermelho

			glBegin(GL_LINES);
			glVertex3d(pDoc->onda.Em_array[i].r,pDoc->onda.Emy_array[i].r,z);
			glVertex3d(0,0,z);
			glEnd();

			//cone do vector
			ux=pDoc->onda.Em_array[i].r;
			uy=pDoc->onda.Emy_array[i].r;
			uz=0;

			//angulo em graus
			Oz=180/PI*acos(uz/sqrt(ux*ux + uy*uy + uz*uz));

			glPushMatrix();
			glTranslated(pDoc->onda.Em_array[i].r, 0 ,0);
			glTranslated(0,pDoc->onda.Emy_array[i].r,0);
			glTranslated(0, 0, z);
			glRotated(Oz,-uy, ux, 0);
			glTranslated(0, 0,-1);
			if (fabs(pDoc->onda.Em_array[i].r)>1)
				auxSolidCone(0.3,1);
			glPopMatrix();
			

				
			//CAMPO MAGNETICO------------------------------------------------------------
			glPushMatrix();
			glScaled(300,300,1);
				
			glColor3d(0,0,1);//azul
			glBegin(GL_LINES);
		//	glVertex3d(	(-pDoc->onda.Emy_array[i]/n).r,(pDoc->onda.Em_array[i]/n).r,z);
			glVertex3d(	(pDoc->onda.Hmx_array[i]).r,
						(pDoc->onda.Hm_array[i]).r,z);
			glVertex3d(0,0,z);
			glEnd();

			glPopMatrix();

			//cone do vector
			ux=(pDoc->onda.Hmx_array[i]).r;
			uy=(pDoc->onda.Hm_array[i]).r;
			uz=0;

			//angulo em graus
			Oz=180/PI*acos(uz/sqrt(ux*ux + uy*uy + uz*uz));

			glPushMatrix();
			//glTranslated(300*(-pDoc->onda.Emy_array[i]/n).r, 0 ,0);
			//glTranslated(0,300*(pDoc->onda.Em_array[i]/n).r,0);
			
			glTranslated(300*(pDoc->onda.Hmx_array[i]).r, 0 ,0);
			glTranslated(0,300*(pDoc->onda.Hm_array[i]).r,0);
			
			glTranslated(0, 0, z);
			glRotated(Oz,-uy, ux, 0);
			glTranslated(0, 0,-1);
			if (300*fabs((pDoc->onda.Hm_array[i]).r)>1)
				auxSolidCone(0.3,1);
			glPopMatrix();

			i++;

		}

	glPopMatrix();


}

void CCampos3DView::GLOndas3Dmovimento()
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	Complexo E;//=pDoc->O.Em;
	Complexo Ey;//=pDoc->O.Emy;
	Complexo H;
	Complexo Hx;
	double a=pDoc->onda.GetAB().r;//atenuacao da onda
	double B=pDoc->onda.GetAB().i;////constante B ou velocidade da fase
	double o=pDoc->onda.teta;//fase inicial
	double O=pDoc->onda.O;//angulo polarizacao
	double n=cabs(pDoc->onda.Getn());
	double on=arg(pDoc->onda.Getn());
	double W=pDoc->onda.GetW();
	double L=pDoc->onda.GetL();//comprimento de onda
	double vf=pDoc->onda.Getvf();//velocidade de propagação da onda
	double z=0;
	int i;
	double step_time;
	Complexo j(0,1);
	double t=pDoc->onda.t;

	pDoc->step_onda=2*PI/(B*pDoc->Q);
	
	step_time=1/(W*pDoc->Q);


//------------------------------------------------------


	t=pDoc->onda.t=t+step_time*2;


	i=0;
	for(z=0;z<=pDoc->Q*5;z=z+pDoc->step_onda)//2 periodos da onda
	{


		E=pDoc->onda.Em*exp(-a*z+j*(W*t-B*z+o) );//ex
		Ey=pDoc->onda.Emy*exp(-a*z+j*(W*t-B*z+o+O));//ey
		H=pDoc->onda.Em/n*exp(-a*z+j*(W*t-B*z+o-on) );//ey
		Hx=-pDoc->onda.Emy/n*exp(-a*z+j*(W*t-B*z+o-on+O));//ex

		pDoc->onda.Em_array[i]=E;
		pDoc->onda.Emy_array[i]=Ey;
		pDoc->onda.Hm_array[i]=H;
		pDoc->onda.Hmx_array[i]=Hx;



		i=i+1;
	}

	Invalidate(false);
		
}
	


void CCampos3DView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	// remember where we clicked
	MouseDownPoint=point;
	// capture mouse movements even outside window borders
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}

void CCampos3DView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	// forget where we clicked
	MouseDownPoint=CPoint(0,0);
	// release mouse capture
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}

void CCampos3DView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);




	// check if we have captured the mouse
	if (GetCapture()==this)
	{

		if (pDoc->selectscene[0]==GUIAS_RECT && pDoc->XD_x==GRAF_2D_a && RightBtnEmBaixo)
		{
			pDoc->a2D+=double(point.x-MouseDownPoint.x)/100000;

			if (pDoc->a2D <= 0)
				pDoc->a2D=0;
			
			if (pDoc->a2D >= pDoc->TM.a)
				pDoc->a2D=pDoc->TM.a;
				
			/*CString str;
			str.Format("%lf",point.x);
			//str.Format("%lf",pDoc->a2D);
			AfxMessageBox(str);*/

				
			pDoc->guiaR->DrawE_2Da(0,pDoc->a2D);
			

			Mouse_Move=true;
			Invalidate(TRUE);
			MouseDownPoint=point;

			return;

		}


		
		if (pDoc->selectscene[0]==GUIAS_RECT && pDoc->XD_x==GRAF_2D_b && RightBtnEmBaixo)
		{
			pDoc->b2D-=double(point.y-MouseDownPoint.y)/10000000;

			if (pDoc->b2D <= 0)
				pDoc->b2D=0;
			
			if (pDoc->b2D >= pDoc->TM.b)
				pDoc->b2D=pDoc->TM.b;
				
			/*CString str;
			str.Format("%lf",point.x);
			//str.Format("%lf",pDoc->a2D);
			AfxMessageBox(str);*/

				
			pDoc->guiaR->DrawE_2Db(0,pDoc->b2D);
			

			Mouse_Move=true;
			Invalidate(TRUE);
			MouseDownPoint=point;

			return;
		}




		if (pDoc->selectscene[0]==GUIAS_RECT && pDoc->XD_x==GRAF_2D_z && RightBtnEmBaixo)
		{

			/*
			double l=pDoc->TM.GetLmn();
			double z_move=double(point.x-MouseDownPoint.x);

			if (z_move > 0)
				pDoc->z2D=pDoc->z2D+pDoc->TM.GetLmn()/10;
			
			if (z_move < 0)
				pDoc->z2D=pDoc->z2D-pDoc->TM.GetLmn()/10;*/

			
			pDoc->z2D+=double(point.x-MouseDownPoint.x)*pDoc->TM.GetLmn()/1000;


			if (pDoc->z2D >= pDoc->TM.GetLmn())
				pDoc->z2D=pDoc->TM.GetLmn();
			if (pDoc->z2D <= 0)
				pDoc->z2D=0; 

						

			/*CString str;
			str.Format("x=%ld; y=%ld",point.x, point.y);
			//str.Format("%lf",pDoc->a2D);
			AfxMessageBox(str);*/

				
			pDoc->guiaR->DrawE_2Dz(0,pDoc->z2D);
			

			Mouse_Move=true;
			Invalidate(TRUE);
			MouseDownPoint=point;

			return;
		}





		// increment the object rotation angles
		pDoc->onda.xRot+=double(point.y-MouseDownPoint.y)/3.6;
		pDoc->onda.yRot+=double(point.x-MouseDownPoint.x)/3.6;
		
		pDoc->onda.zRot+=double(point.x-MouseDownPoint.x)/(3.6*3);
		pDoc->onda.zRot+=double(point.y-MouseDownPoint.y)/(3.6*3);
		

		// redraw the view
		Invalidate(TRUE);
		// remember the mouse point
		MouseDownPoint=point;
		
	};




	//CView::OnMouseMove(nFlags, point);
}


void CCampos3DView::OnStartStopTime() 
{
	// TODO: Add your command handler code here

	//CCampos3DDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	
	SetTimer(ID_ONDRAW_TIMER,1000,NULL);
	
	Ondas_movimento=!Ondas_movimento;

	if (Ondas_movimento)
		SetTimer(ID_ONDRAW_TIMER,1,NULL);
	else
		KillTimer(ID_ONDRAW_TIMER);

	
	//Invalidate(false);
}



int CCampos3DView::OnBtnGuias() 
{
	// TODO: Add your command handler code here
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	int modal2;	
	GuiasRectDlg dlg;
	GuiasRectDlg2 dl;
	CString m_n_STR_fc;
	double fc;
	int m;
	int n;
	int ni=1;


	if (pDoc->TM_TE)//modo TM - Transversal Magnetico
		pDoc->guiaR=&pDoc->TM;
	else			//modo TE - Transversal Electrico
		pDoc->guiaR=&pDoc->TE;


	dlg.m_a=pDoc->guiaR->a*1000;
	dlg.m_b=pDoc->guiaR->b*1000;
	dlg.m_frequencia=pDoc->guiaR->f/1e9;//gigahertz;
	dlg.TM_TE=pDoc->TM_TE;
	dlg.m_Er=pDoc->guiaR->Er;
	dlg.m_ur=pDoc->guiaR->Ur;

	
	
	dl.m_list_modos_M_N_fc.RemoveAll();
	dl.m_list_modos_M.RemoveAll();
	dl.m_list_modos_N.RemoveAll();


	if (dlg.DoModal()==IDOK)
	{
		pDoc->TM_TE=dlg.TM_TE;

		if (pDoc->TM_TE)//modo TM - Transversal Magnetico
			pDoc->guiaR=&pDoc->TM;
		else			//modo TE - Transversal Electrico
			pDoc->guiaR=&pDoc->TE;

		
		pDoc->guiaR->Set(dlg.m_a/1000,dlg.m_b/1000,dlg.m_frequencia*1e9,dlg.m_Er,dlg.m_ur);
			
		dl.m_static_a.Format("%.2lf",dlg.m_a);
		dl.m_static_b.Format("%.2lf",dlg.m_b);
		dl.m_static_freq.Format("%.2lf",dlg.m_frequencia);
		
		dl.m_static_Er.Format("%.2lf",dlg.m_Er);
		dl.m_static_ur.Format("%.2lf",dlg.m_ur);
		dl.m_static_L.Format("%lf",pDoc->guiaR->GetLmn());
		
				

		if (pDoc->TM_TE)//modo TM - Transversal Magnetico
			ni=1;
		else			//modo TE - Transversal Electrico
			ni=0;


			for(m=1;m<5;m++)
				for(n=ni;n<5;n++)
				{
					pDoc->guiaR->m=m;
					pDoc->guiaR->n=n;
					fc=pDoc->guiaR->Getfc();
										
					if (pDoc->guiaR->f >= fc)
					{
						m_n_STR_fc.Format("%d,%d - fc:%.2lf",m,n,fc/1000000000);
						dl.m_list_modos_M_N_fc.Add(m_n_STR_fc);
						dl.m_list_modos_M.Add(m);
						dl.m_list_modos_N.Add(n);
					
					}				
				}

			dl.m=1;
			if (pDoc->TM_TE)//modo TM - Transversal Magnetico
				dl.n=1;
			else			//modo TE - Transversal Electrico
				dl.n=0;

					
	}
	else
	{
		return 1;
	}



	dl.m_Em=pDoc->Graf_Em;
	dl.m_Hm=pDoc->Graf_Hm;

	dl.XD_x=pDoc->XD_x;


	dl.m_2Da=pDoc->a2D*1000;
	dl.m_2Db=pDoc->b2D*1000;
	dl.m_2Dz=pDoc->z2D*1000;

	

	modal2=dl.DoModal();

	if (modal2==3)
		return OnBtnGuias();


	if (modal2==IDCANCEL)
		return 1;

	
	if (modal2==IDOK)
	{

		pDoc->guiaR->m=dl.m;
		pDoc->guiaR->n=dl.n;
				
		
		pDoc->Graf_Em=dl.m_Em;
		pDoc->Graf_Hm=dl.m_Hm;

		pDoc->XD_x=dl.XD_x;

		pDoc->a2D=dl.m_2Da/1000;
		pDoc->b2D=dl.m_2Db/1000;
		pDoc->z2D=dl.m_2Dz/1000;
		

		//-Modo TM -------------------------------------------------------------
	
		/*
#define GRAF_3D			0
#define GRAF_2D			1
#define GRAF_2D_a		2
#define GRAF_2D_b		3
#define GRAF_2D_z		4
*/
	
		
		if (pDoc->Graf_Em && pDoc->XD_x==GRAF_3D)
			pDoc->guiaR->DrawE(0);
		
		

		if (pDoc->Graf_Hm && pDoc->XD_x==GRAF_3D)
		//	pDoc->guiaR->DrawH(t);
			pDoc->guiaR->DrawH_alternativo(t);



		if (pDoc->Graf_Em && pDoc->XD_x==GRAF_2D_a )		
			//pDoc->guiaR->DrawE_2Da(t,pDoc->a2D);
			pDoc->guiaR->DrawE_2Da(0,pDoc->a2D);


		if (pDoc->Graf_Em && pDoc->XD_x==GRAF_2D_b )		
			//pDoc->guiaR->DrawE_2Db(t,pDoc->a2D);
			pDoc->guiaR->DrawE_2Db(0,pDoc->b2D);


		if (pDoc->Graf_Em && pDoc->XD_x==GRAF_2D_z )
			//pDoc->guiaR->DrawE_2Db(t,pDoc->a2D);
			pDoc->guiaR->DrawE_2Dz(0,pDoc->z2D);



		// modo TM Campo Electrico 2Da - grafico corte em x 
	//	if (pDoc->TM_TE /*modo TM*/
	//		&& dl.m_Em  /*Campo Electrico*/
	//		&& pDoc->XD_x==GRAF_2D_a) /*2Da*/
			//GLGuiasRectTM_E_2Da();
	


		//------------------------------------------------------------------------
		



		//-Modo TE----------------------------------------------------------------

		// modo TE Campo Magnetico 3D
		if ( (!pDoc->TM_TE) /*modo TE*/
			&& dl.m_Hm		/*Campo Magnetico*/
			&& pDoc->XD_x==GRAF_3D) /*3D*/
			pDoc->guiaR->DrawH(t);
			//GLGuiasRectTE_H_3D();

		//------------------------------------------------------------------------
			
			



		pDoc->selectscene[0]=1;

		Invalidate(false);
	
	
	}

	dl.m_list_modos_M_N_fc.RemoveAll();

	return 1;

}


int CCampos3DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	

	CString str;
	str.Format("%d",nChar);
//	AfxMessageBox(str);

	if(nChar == VK_UP)
		pDoc->onda.xRot-= 5.0f;

	if(nChar == VK_DOWN)
		pDoc->onda.xRot += 5.0f;

	if(nChar == VK_LEFT)
		pDoc->onda.yRot -= 5.0f;

	if(nChar == VK_RIGHT)
		pDoc->onda.yRot += 5.0f;

	if(nChar == VK_NUMPAD7 || nChar == '7' )
		pDoc->onda.zRot -= 5.0f;

	if(nChar == VK_NUMPAD9 || nChar == '9' )
		pDoc->onda.zRot += 5.0f;


	if(nChar == VK_ADD || nChar == 187)
	{
	//	if (pDoc->FLAG_GRAF2D || pDoc->FLAG_GRAF3D || pDoc->FLAG_GRAF2D_COMPLEXO)
		{	
			if (pDoc->m_scale<50)
			{
				pDoc->m_scale*=2;
			}
		}
	}


	if(nChar == 'S' )
	{
		OnStartStopTime();
		return 1;		
	}


	


	if(nChar == VK_SUBTRACT || nChar == 189)
	{
		{	
			if (pDoc->m_scale>0.1)
			{
				pDoc->m_scale/=2;
			}
		}
	}


	
	if (nChar == 'O' )
	{ 
		OnBotaoOndas();
		return 1;
	}


	if (nChar == 'G' )
	{ 
		OnBtnGuias();
		return 1;
	}

	if (nChar == 'C' )
	{ 
		OnBtnGuiaCilindrico();
		return 1;
	}


	// redraw the view	
	Invalidate(false);

	

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	return 1;
}

void CCampos3DView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	
	Ondas_movimento=false;
}

void CCampos3DView::OnBTNtMENOS() 
{
	// TODO: Add your command handler code here
	
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if (t<=0)
		return;

//	t-=0.0000000000005;
	t=t-1E-12;

//	pDoc->guiaR->DrawE(t);	
	//GLGuiasRectTM_E_3D();

	Invalidate(false);
}

void CCampos3DView::OnBTNtMAIS() 
{
	// TODO: Add your command handler code here

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);




	//t+=0.0000000000005;
	//t+=1E-11;
	t=t+1E-12;

	//pDoc->guiaR->DrawE(t);
//	GLGuiasRectTM_E_3D();
	//GLGuiasRectTM_H_3D();

	Invalidate(false);
}


void CCampos3DView::OnBTNZmenos() 
{
	// TODO: Add your command handler code here
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	double z1=pDoc->guiaR->GetLmn()/4;

	if (pDoc->guiaR->z_inicia_desenho_grafE < (-z1))
		return;

	pDoc->guiaR->z_inicia_desenho_grafE = pDoc->guiaR->z_inicia_desenho_grafE - z1 * 0.1;


	pDoc->guiaR->DrawE(t);
	Invalidate(false);

}

void CCampos3DView::OnBTNZmais() 
{
	// TODO: Add your command handler code here
	
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	double z1=pDoc->guiaR->GetLmn()/4;

	if (pDoc->guiaR->z_inicia_desenho_grafE > z1)
		return;

	pDoc->guiaR->z_inicia_desenho_grafE = pDoc->guiaR->z_inicia_desenho_grafE + z1 * 0.1;


	pDoc->guiaR->DrawE(t);
	Invalidate(false);

}



void CCampos3DView::OnBtnGuiaCilindrico() 
{
	// TODO: Add your command handler code here
		
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	GuiasCilDlg dlg;

	if (dlg.DoModal()==IDOK)
	{



		
		pDoc->selectscene[0]=2;

		Invalidate(false);

	}

}

void CCampos3DView::OnContextMenu(CWnd*, CPoint point)
{

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// CG: This block was added by the Pop-up Menu component
	if (pDoc->selectscene[0]==1 && !Mouse_Move)
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_CAMPOS3_DVIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CCampos3DView::OnPopupCampomagnetico() 
{
	// TODO: Add your command handler code here

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	GuiasNCampos dlg;
	

	dlg.m_ncampos_z=pDoc->TM.NCamposZ;
	dlg.m_nlinhas_forca=pDoc->TM.NCamposJ;


//	dlg.m_slider_Ez=slider_Ez;

	if (dlg.DoModal()==IDOK)
	{

		pDoc->TM.NCamposZ=dlg.m_ncampos_z;
		pDoc->TM.NCamposJ=dlg.m_nlinhas_forca;

		if (pDoc->TM.NCamposZ < 0)
			pDoc->TM.NCamposZ=0;

		if (pDoc->TM.NCamposJ < 0)
			pDoc->TM.NCamposJ=0;


	//	z1=pDoc->guiaR->GetLmn()/4;

	//	pDoc->guiaR->z_inicia_desenho_grafE=z1*dlg.m_slider_Ez/101;

	//	slider_Ez=dlg.m_slider_Ez;

	}
	else 
		return;



	pDoc->guiaR->DrawH_alternativo(t);
	

	Invalidate(false);

}


void CCampos3DView::OnPopupCampoelectrico() 
{
	// TODO: Add your command handler code here

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	GuiasNCamposZDlg dlg;
	double z;


	dlg.m_NLinhas_x=pDoc->TM.NCamposx;
	dlg.m_NLinhas_y=pDoc->TM.NCamposy;

	dlg.m_slider_z=slider_Ez;

	if (dlg.DoModal()==IDOK)
	{
		pDoc->TM.NCamposx=dlg.m_NLinhas_x;
		pDoc->TM.NCamposy=dlg.m_NLinhas_y;


		if (pDoc->TM.NCamposx < 0)
			pDoc->TM.NCamposx=0;

		if (pDoc->TM.NCamposy < 0)
			pDoc->TM.NCamposy=0;

		z=pDoc->guiaR->GetLmn()/4;

		pDoc->guiaR->z_inicia_desenho_grafE=z*dlg.m_slider_z/101;

		slider_Ez=dlg.m_slider_z;
	}
	else
		return;


	//pDoc->guiaR->DrawE(t);

//	pDoc->guiaR->DrawE(0);



		if (pDoc->Graf_Em && pDoc->XD_x==GRAF_3D)
			pDoc->guiaR->DrawE(0);
			//pDoc->guiaR->DrawE_alternativo(t);

		if (pDoc->Graf_Em && pDoc->XD_x==GRAF_2D_a )		
			pDoc->guiaR->DrawE_2Da(0,pDoc->a2D);


		if (pDoc->Graf_Em && pDoc->XD_x==GRAF_2D_b )		
			pDoc->guiaR->DrawE_2Db(0,pDoc->b2D);

		if (pDoc->Graf_Em && pDoc->XD_x==GRAF_2D_z )		
			pDoc->guiaR->DrawE_2Dz(0,pDoc->z2D);


	Invalidate(false);

}

void CCampos3DView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
//	AfxMessageBox("Cliquei o direito");

	RightBtnEmBaixo=true;

	MouseDownPoint=point;

	Mouse_Move=false;


	SetCapture();


	CView::OnRButtonDown(nFlags, point);
}

void CCampos3DView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	RightBtnEmBaixo=false;

	MouseDownPoint=CPoint(0,0);

	ReleaseCapture();

	CView::OnRButtonUp(nFlags, point);
}

void CCampos3DView::OnPopupCalcular() 
{
	// TODO: Add your command handler code here
	
	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	Formula_Dlg dlg;
	int i;

	dlg.pDoc=pDoc;

	for (i=0;i<pDoc->TM.Formulas.GetSize();i++)
	{
		dlg.Formulas.Add(pDoc->TM.Formulas[i]);
	}


	if (dlg.DoModal()==IDOK)
	{

	}

}


void CCampos3DView::OnBtnFormulas() 
{
	// TODO: Add your command handler code here

	
	OnPopupCalcular();

}

void CCampos3DView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	CCampos3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if (pDoc->selectscene[0] == ONDAS)
		if (Ondas_movimento)
			GLOndas3Dmovimento();

	


	CView::OnTimer(nIDEvent);
}
