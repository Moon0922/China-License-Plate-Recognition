#pragma once


// CPage_VideoWnd
#include "PAGE_BaseWnd.h"
#include "ImageView.h"
#include "UI_Button.h"
#include "CVideoProcessor.h"
class CPage_VideoWnd : public CPAGE_BaseWnd
{
	DECLARE_DYNAMIC(CPage_VideoWnd)

public:
	CPage_VideoWnd();
	virtual ~CPage_VideoWnd();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnClickedOpenButton();
private:
	CEdit m_ctlVideoPath;
	CRect m_rtVideoPath;

	CUI_Button m_btnOpen;
	CImageView m_wndImageView;
	CVideoProcessor m_xVideoProc;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};


