#pragma once
#include "PictureEx.h"
#include "MySqlConn.h"
// CiFormaterConvertDlg dialog

class CiFormaterConvertDlg : public CDialog
{
	DECLARE_DYNAMIC(CiFormaterConvertDlg)

public:
	CiFormaterConvertDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CiFormaterConvertDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_PathBox;
	CComboBox m_ComboFormat;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	CPictureEx m_cLogo;
	CBitmap m_BackBmp;
	CSize m_BmpSiz;
	CFont m_Font;
};
