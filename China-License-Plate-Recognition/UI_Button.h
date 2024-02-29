#pragma once

// CUI_Button

#include "UI_BaseWnd.h"
#define KBS_NONE	0x0
#define KBS_ADD		0x1
#define KBS_UPDATE	0x2
#define KBS_REMOVE	0x3
#define KBS_EXCEL	0x4
#define KBS_SEARCH	0x5
#define KBS_AGREE	0x6
#define KBS_DEAGREE	0x7
#define KBS_USER	0x8
#define KBS_DROP	0x9

class CUI_Button : public CUI_BaseWnd
{
	DECLARE_DYNAMIC(CUI_Button)

public:

	CUI_Button();
	virtual ~CUI_Button();
	
	void		CreateButton(CWnd* pWnd, CString strText, int nStyle = KBS_NONE);
	int			GetButtonStyle() { return m_nStyle; }

protected:

	int			m_nStyle;
	BOOL		m_bPressed;
	int			m_nState;
	CxImage		m_imageButton;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


