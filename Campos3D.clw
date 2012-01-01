; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=GuiasCilDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "campos3d.h"
LastPage=0

ClassCount=13
Class1=CCampos3DApp
Class2=CAboutDlg
Class3=CCampos3DDoc
Class4=CCampos3DView
Class5=CChildFrame
Class6=GuiasRectDlg
Class7=GuiasRectDlg2
Class8=CMainFrame
Class9=OndasDlg

ResourceCount=13
Resource1=IDD_GUIAS_REC
Resource2=IDD_GUIAS_REC2
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_GUIAR_NCAMPOS
Resource5=IDR_MAINFRAME (English (U.S.))
Resource6=IDR_CAMPOS3D
Resource7=CG_IDR_POPUP_CAMPOS3_DVIEW
Class10=GuiasCilDlg
Resource8=CG_IDR_POPUP_FORMULA__DLG
Resource9=IDR_CAMPOSTYPE (English (U.S.))
Class11=GuiasNCampos
Resource10=IDD_GUIAR_NCAMP_Z
Class12=GuiasNCamposZDlg
Resource11=IDD_ONDAS3D
Class13=Formula_Dlg
Resource12=IDD_GUIAS_CIL
Resource13=IDD_FORMULAS

[CLS:CCampos3DApp]
Type=0
BaseClass=CWinApp
HeaderFile=Campos3D.h
ImplementationFile=Campos3D.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Campos3D.cpp
ImplementationFile=Campos3D.cpp
LastObject=ID_BTN_GUIAS

[CLS:CCampos3DDoc]
Type=0
BaseClass=CDocument
HeaderFile=Campos3DDoc.h
ImplementationFile=Campos3DDoc.cpp

[CLS:CCampos3DView]
Type=0
BaseClass=CView
HeaderFile=Campos3DView.h
ImplementationFile=Campos3DView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CCampos3DView

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=ID_START_STOP_TIME

[CLS:GuiasRectDlg]
Type=0
BaseClass=CDialog
HeaderFile=GuiasRectDlg.h
ImplementationFile=GuiasRectDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_ur

[CLS:GuiasRectDlg2]
Type=0
BaseClass=CDialog
HeaderFile=GuiasRectDlg2.h
ImplementationFile=GuiasRectDlg2.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK_Em

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:OndasDlg]
Type=0
BaseClass=CDialog
HeaderFile=OndasDlg.h
ImplementationFile=OndasDlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_GUIAS_REC]
Type=1
Class=GuiasRectDlg
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177294
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_a,edit,1350631552
Control7=IDC_EDIT_b,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_ur,edit,1350631552
Control17=IDC_EDIT_Er,edit,1350631552
Control18=IDC_FREQUENCIA,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_CHECK_TM,button,1342242819
Control21=IDC_CHECK_TE,button,1342242819
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,button,1342177287
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,button,1342177287

[DLG:IDD_GUIAS_REC2]
Type=1
Class=GuiasRectDlg2
ControlCount=41
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CMBO_FREQ_CORTE,combobox,1344340226
Control6=IDC_CHECK_Em,button,1342242819
Control7=IDC_CHECK_Hm,button,1342242819
Control8=IDC_STATIC,button,1342177287
Control9=IDC_CHECK3D,button,1342242819
Control10=IDC_STATIC,static,1342308352
Control11=IDC_CHECK2D_A,button,1342242819
Control12=IDC_STATIC,static,1342177294
Control13=IDC_STATIC,static,1342177294
Control14=IDC_STATIC,static,1342177294
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_A_,edit,1350631552
Control17=IDC_STATIC,static,1342177294
Control18=IDC_CHECK2D_B,button,1342242819
Control19=IDC_CHECK2D_Z,button,1342242819
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EDIT_B_,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EDIT_Z_,edit,1350631552
Control26=IDC_STATIC,button,1342177287
Control27=IDC_BTN_VOLTAR,button,1342242816
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC_a,static,1342308352
Control31=IDC_STATIC_b,static,1342308352
Control32=IDC_STATIC_FREQ,static,1342308352
Control33=IDC_STATIC_Er,static,1342308352
Control34=IDC_STATIC_ur,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC_L,static,1342308352
Control40=IDC_STATIC,button,1342177287
Control41=IDC_STATIC,static,1342308352

[DLG:IDD_ONDAS3D]
Type=1
Class=OndasDlg
ControlCount=37
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ONDAS_Em_x,edit,1350631552
Control7=IDC_ONDAS_Em_y,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_ANGULO_POL,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_ONDAS_FREQ,edit,1350631552
Control18=IDC_ONDAS_FASE_INI,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_G_condutividade,edit,1350631552
Control29=IDC_n_IMP_AMPLITUDE,edit,1484849280
Control30=IDC_n_IMP_ANGULO,edit,1484849280
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_ONDAS_ur,edit,1350631552
Control34=IDC_ONDAS_Er,edit,1350631552
Control35=IDC_CONDUTIVIDADE,button,1342177289
Control36=IDC_IMPEDANCIA,button,1342177289
Control37=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_CAMPOS3D]
Type=1
Class=?
Command1=ID_BOTAO_ONDAS
Command2=ID_BTN_GUIAS
Command3=ID_BTN_GUIA_CILINDRICO
Command4=ID_START_STOP_TIME
Command5=ID_BOTAO_ONDAS
Command6=ID_BTN_t_MENOS
Command7=ID_BTN_t_MAIS
Command8=ID_BTN_Z_menos
Command9=ID_BTN_Z_mais
Command10=ID_BUTTON32794
Command11=ID_BTN_FORMULAS
Command12=ID_BUTTON32792
CommandCount=12

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_CAMPOSTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_TILE_VERT
Command21=ID_WINDOW_ARRANGE
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_GUIAS_CIL]
Type=1
Class=GuiasCilDlg
ControlCount=23
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177294
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_a,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_ur,edit,1350631552
Control14=IDC_EDIT_Er,edit,1350631552
Control15=IDC_FREQUENCIA,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_CHECK_TM,button,1342242819
Control18=IDC_CHECK_TE,button,1342242819
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,button,1342177287

[CLS:GuiasCilDlg]
Type=0
HeaderFile=GuiasCilDlg.h
ImplementationFile=GuiasCilDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK_TM
VirtualFilter=dWC

[MNU:CG_IDR_POPUP_CAMPOS3_DVIEW]
Type=1
Class=?
Command1=ID_POPUP_CAMPOMAGNETICO
Command2=ID_POPUP_CAMPOELECTRICO
Command3=ID_POPUP_CALCULAR
CommandCount=3

[DLG:IDD_GUIAR_NCAMPOS]
Type=1
Class=GuiasNCampos
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ED_NCAMPOS_Z,edit,1350631552
Control6=IDC_ED_NLINHAS_FORCA,edit,1350631552

[CLS:GuiasNCampos]
Type=0
HeaderFile=GuiasNCampos.h
ImplementationFile=GuiasNCampos.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SLIDER_POS_Z

[DLG:IDD_GUIAR_NCAMP_Z]
Type=1
Class=GuiasNCamposZDlg
ControlCount=11
Control1=IDC_ED_NLINHAS_x,edit,1350631552
Control2=IDC_ED_NLINHAS_y,edit,1350631552
Control3=IDC_SLIDER_POS_Z,msctls_trackbar32,1342242840
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352

[CLS:GuiasNCamposZDlg]
Type=0
HeaderFile=GuiasNCamposZDlg.h
ImplementationFile=GuiasNCamposZDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=GuiasNCamposZDlg

[DLG:IDD_FORMULAS]
Type=1
Class=Formula_Dlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FLEXG_FORMULAS,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control4=IDC_ED_F1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ED_F2,edit,1350631552
Control7=IDC_FLEXG_VARIAVEIS,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control8=IDC_BTN_VALIDAR,button,1342242816
Control9=IDC_BTN_CALCULAR,button,1342242816
Control10=IDC_COMBO_RESULTADO_FORMULA,combobox,1344343105
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352

[CLS:Formula_Dlg]
Type=0
HeaderFile=Formula_Dlg.h
ImplementationFile=Formula_Dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=Formula_Dlg
VirtualFilter=dWC

[MNU:CG_IDR_POPUP_FORMULA__DLG]
Type=1
Class=?
Command1=ID_POP_ADD_FORMULA
Command2=ID_POP_ELIMINAR_FORMULA
CommandCount=2

