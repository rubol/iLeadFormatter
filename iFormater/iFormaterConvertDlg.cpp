// iFormaterConvertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iFormater.h"
#include "iFormaterConvertDlg.h"
#include <vector>
#include <string>

// CiFormaterConvertDlg dialog

IMPLEMENT_DYNAMIC(CiFormaterConvertDlg, CDialog)

CiFormaterConvertDlg::CiFormaterConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CiFormaterConvertDlg::IDD, pParent)
{
}

CiFormaterConvertDlg::~CiFormaterConvertDlg()
{
}

void CiFormaterConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_PathBox);
	DDX_Control(pDX, IDC_COMBO1, m_ComboFormat);
	//DDX_Control(pDX, IDC_LOGO, m_cLogo);
}


BEGIN_MESSAGE_MAP(CiFormaterConvertDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CiFormaterConvertDlg message handlers

BOOL CiFormaterConvertDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_BackBmp.LoadBitmapW(IDB_BITMAP4);
	BITMAP bm;
	m_BackBmp.GetBitmap(&bm);
	m_BmpSiz = CSize(bm.bmWidth, bm.bmHeight);
	SetWindowPos(NULL, 0, 0, bm.bmWidth, bm.bmHeight, SWP_NOMOVE);

	ModifyStyle(0, WS_SYSMENU | WS_MINIMIZEBOX);
	

	/*m_ComboFormat.AddString(_T("USA"));
	m_ComboFormat.AddString(_T("UK"));*/
	m_ComboFormat.SetCurSel(0);

	Invalidate(1);

	return TRUE;
}

void CiFormaterConvertDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CString cstr;
	//cstr.Format(_T("X: %d, Y: %d"), point.x, point.y);
	//AfxMessageBox(cstr);

	//Min area
	if((point.x >= 409 && point.x <= 427) && (point.y >= 1 && point.y <= 13))
	{
		ShowWindow(SW_MINIMIZE);
	}

	//Close area
	if((point.x >= 429 && point.x <= 448) && (point.y >= 1 && point.y <= 13))
	{
		DestroyWindow();
		PostQuitMessage(0);
		return;
	}

	//Browse area
	if((point.x >= 322 && point.x <= 432) && (point.y >= 127 && point.y <= 151))
	{
		CFileDialog file(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Text.txt (*.txt)|*.txt|All files(*.*)|*.*||"));
		file.DoModal();

		CString cstr = file.GetPathName();
		m_PathBox.SetWindowText(cstr);
	}

	//Convert area
	if((point.x >= 322 && point.x <= 432) && (point.y >= 173 && point.y <= 199))
	{
		//Utsav - Need to put csv convert routine here
		CString cstr;
		//m_PathBox.GetWindowText(cstr);

		//CT2CA pszStr(cstr);

		//char ch[200] = "";
		//strcpy_s(ch, _countof(ch), pszStr);

		m_ComboFormat.GetWindowText(cstr);

		AfxMessageBox(cstr);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CiFormaterConvertDlg::OnPaint()
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
	
	dc.DrawText(_T("Browse.."), 8, CRect(352, 133, 400, 148), DT_LEFT);
	dc.DrawText(_T("Format"), 6, CRect(355, 177, 400, 188), DT_LEFT);
	dc.DrawText(_T("Choose pattern"), 14, CRect(24, 183, 140, 204), DT_LEFT);

	m_Font.DeleteObject();

	CDialog::OnPaint();
}


BOOL CiFormaterConvertDlg::OnEraseBkgnd(CDC* pDC)
{
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);

	CBitmap* pOldbitmap = dcMemory.SelectObject(&m_BackBmp);
	CRect rcClient;
	GetClientRect(&rcClient);

	const CSize& sbitmap = m_BmpSiz;
	pDC->BitBlt(0, 0, sbitmap.cx, sbitmap.cy, &dcMemory, 0, 0, SRCCOPY);
	dcMemory.SelectObject(pOldbitmap);

	return TRUE;
}


void CiFormaterConvertDlg::OnDestroy()
{
	CDialog::OnDestroy();
	m_BackBmp.DeleteObject();
}

BOOL CiFormaterConvertDlg::PreTranslateMessage(MSG *pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CString cstr;
		//m_PathBox.GetWindowText(cstr);

		//CT2CA pszStr(cstr);

		//char ch[200] = "";
		//strcpy_s(ch, _countof(ch), pszStr);

		m_ComboFormat.GetWindowText(cstr);

		AfxMessageBox(cstr);
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}