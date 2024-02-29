#pragma once


// CPage_ImageWnd
#include "PAGE_BaseWnd.h"
#include "ImageView.h"
#include "UI_Button.h"
#include "EngineProcessor.h"
class CPage_ImageWnd : public CPAGE_BaseWnd
{
	DECLARE_DYNAMIC(CPage_ImageWnd)

public:
	CPage_ImageWnd();
	virtual ~CPage_ImageWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	CEdit m_ctlImgPath;
	CRect m_rtImgPath;

	CUI_Button m_btnOpen, m_btnStart, m_btnStop;
	CRect m_rtOpen;

	CListCtrl m_ctlImgList;
	CRect m_rtImgList;

	CImageView m_wndImageView;

	CEngineProcessor m_xEngineProc;
public:
	afx_msg void OnItemchangedImgList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawImgList(NMHDR *pNMHDR, LRESULT *pResult);
	void OnClickedOpenButton();
};


