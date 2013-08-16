// iFormaterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iFormater.h"
#include "iFormaterDlg.h"
#include "iFormaterConvertDlg.h"

CiFormaterDlg::CiFormaterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CiFormaterDlg::IDD, pParent)
{
}

void CiFormaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_LOGINING, m_LoggingIn);
}

BEGIN_MESSAGE_MAP(CiFormaterDlg, CDialog)
	ON_WM_PAINT()
	//ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_BUTTON1, &CiFormaterDlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CiFormaterDlg message handlers

BOOL CiFormaterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	m_BackBmp.LoadBitmapW(IDB_BITMAP3);
	BITMAP bm;
	m_BackBmp.GetBitmap(&bm);
	m_BmpSiz = CSize(bm.bmWidth, bm.bmHeight);
	SetWindowPos(NULL, 0, 0, bm.bmWidth, bm.bmHeight, SWP_NOMOVE);

	SetWindowText(_T("iLFormater - Login"));
	ModifyStyle(0, WS_SYSMENU | WS_MINIMIZEBOX);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CiFormaterDlg::OnPaint()
{
	CPaintDC dc(this);
	
	m_Font.CreateFont(14,				 // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,									 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily
		_T("Serif"));

	dc.SelectObject(&m_Font);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	
	dc.DrawText(_T("USERNAME"), 8, CRect(30, 152, 90, 172), DT_LEFT);
	dc.DrawText(_T("PASSWORD"), 8, CRect(30, 220, 90, 240), DT_LEFT);

	m_Font.DeleteObject();

	m_Font.CreateFont(18,				 // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,									 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily
		_T("Serif"));

	dc.SelectObject(&m_Font);
	dc.DrawText(_T("Login"), 5, CRect(114, 345, 155, 375), DT_LEFT);

	m_Font.DeleteObject();

	CDialog::OnPaint();
}

void CiFormaterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CString cstr;
	//cstr.Format(_T("X: %d, Y: %d"), point.x, point.y);
	//AfxMessageBox(cstr);

	//Login button area
	if((point.x >= 37 && point.x <= 240) && (point.y >= 340 && point.y <= 368))
		ProcessLogin();

	//Min area
	if((point.x >= 240 && point.x <= 259) && (point.y >= 2 && point.y <= 13))
	{
		ShowWindow(SW_MINIMIZE);
	}

	//Close area
	if((point.x >= 260 && point.x <= 279) && (point.y >= 2 && point.y <= 13))
	{
		DestroyWindow();
		PostQuitMessage(0);
		return;
	}

	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CiFormaterDlg::PreTranslateMessage(MSG *pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		ProcessLogin();
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CiFormaterDlg::ProcessLogin()
{
	//CString cstr;
	//cstr.Format(L"X: %d, Y: %d", point.x, point.y);
	//AfxMessageBox(cstr);

	CString cstrUsr;
	CString cstrPass;
	
	m_Edit.GetWindowText(cstrUsr);
	m_Edit2.GetWindowText(cstrPass);
	if(cstrUsr.IsEmpty() || cstrPass.IsEmpty())
	{
		AfxMessageBox(_T("Username/Password field can't be left blank !"));
		return;
	}

	//Utsav - Replace this check with your DB one
	//if(cstrUsr == _T("usa") && cstrPass == _T("usa"))
	if(m_LoggingIn.Load(_T("loader.gif")))
		m_LoggingIn.Draw();
	MySqlConn db = MySqlConn();
	CT2CA szuser(cstrUsr);
	CT2CA szpass(cstrPass);
	std::string user(szuser);
	std::string pass(szpass);

	int iRet = db.auth(user, pass);

	if(iRet == 1)
	{
		std::vector<std::string> country;
		MySqlConn db = MySqlConn();
		db.fill_country(country);
		for(std::vector<std::string>::iterator itr = country.begin(); itr != country.end(); itr++)
		{
			CString cstr((*itr).c_str());
			//m_ComboFormat.AddString((LPCTSTR)(*itr).c_str());
			AfxMessageBox(cstr);
		}
	/*	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOACTIVATE);
		SetWindowText(_T("iLFormater"));

		CiFormaterConvertDlg dlg;
		int iID = dlg.DoModal();
		if(iID == IDCANCEL)
	*/	{
			DestroyWindow();
			PostQuitMessage(0);
		}
	}
	else if(iRet == -1)
	{
		AfxMessageBox(_T("Invalid Username/Password !"));
	}
	else if(iRet == -2)
	{
		AfxMessageBox(_T("Connectivity Problem !"));
	}
}

BOOL CiFormaterDlg::OnEraseBkgnd(CDC* pDC)
{
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);

	CBitmap* pOldbitmap = dcMemory.SelectObject(&m_BackBmp);
	CRect rcClient;
	GetClientRect(&rcClient);

	//const CSize& sbitmap = m_BmpSiz;
	pDC->BitBlt(0, 0, m_BmpSiz.cx, m_BmpSiz.cy, &dcMemory, 0, 0, SRCCOPY);
	dcMemory.SelectObject(pOldbitmap);

	return TRUE;
}

void CiFormaterDlg::OnDestroy()
{
	CDialog::OnDestroy();
	m_BackBmp.DeleteObject();
}
