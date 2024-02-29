#pragma once


class CHeader_Wnd : public CWnd
{
	DECLARE_DYNAMIC(CHeader_Wnd)

public:
	CHeader_Wnd();
	virtual ~CHeader_Wnd();

protected:
	CxImage		m_image_maxi, m_image_logo;
	CRect		m_crc_Minimize, m_crc_Close, m_crc_Logo;
	CRect		m_crc_Item[_MAX_PAGE];

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


