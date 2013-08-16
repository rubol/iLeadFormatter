// iFormater.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "iFormater.h"
#include "iFormaterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CiFormaterApp

BEGIN_MESSAGE_MAP(CiFormaterApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CiFormaterApp construction

CiFormaterApp::CiFormaterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CiFormaterApp object

CiFormaterApp theApp;


// CiFormaterApp initialization

BOOL CiFormaterApp::InitInstance()
{
	CWinApp::InitInstance();

	CiFormaterDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}
