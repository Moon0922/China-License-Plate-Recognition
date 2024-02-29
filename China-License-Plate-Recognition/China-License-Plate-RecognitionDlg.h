
// China-License-Plate-RecognitionDlg.h : header file
//

#pragma once

#include "Header_Wnd.h"
#include "Menu_Wnd.h"
// CChinaLicensePlateRecognitionDlg dialog
class CChinaLicensePlateRecognitionDlg : public CDialogEx
{
// Construction
public:
	CChinaLicensePlateRecognitionDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHINALICENSEPLATERECOGNITION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	CHeader_Wnd m_wndHeader;
	CMenu_Wnd m_wndMenu;
};
