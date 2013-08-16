// iFormaterDlg.h : header file
//

#pragma once
#include "PictureEx.h"
#include "MySqlConn.h"

// CiFormaterDlg dialog
class CiFormaterDlg : public CDialog
{
public:
	CiFormaterDlg(CWnd* pParent = NULL);	// standard constructor

	enum { IDD = IDD_IFORMATER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


protected:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	//afx_msg void OnPaint();
	//afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit;
	CEdit m_Edit2;
	//afx_msg void OnBnClickedButton1();
	//CButtonST m_BtnLogin;
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void ProcessLogin();
	CPictureEx m_LoggingIn;
	CBitmap m_BackBmp;
	CSize m_BmpSiz;
	CFont m_Font;
};
