#pragma once


// CMenu_Wnd

class CMenu_Wnd : public CWnd
{
	DECLARE_DYNAMIC(CMenu_Wnd)

public:
	CMenu_Wnd();
	virtual ~CMenu_Wnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
	CRect m_rtMenu[_MAX_PAGE];
};


