#pragma once


// CPAGE_BaseWnd

class CPAGE_BaseWnd : public CWnd
{
	DECLARE_DYNAMIC(CPAGE_BaseWnd)

public:
	CPAGE_BaseWnd();
	virtual ~CPAGE_BaseWnd();

	virtual void	SetParam(int nParam) { m_nParam = nParam; }
	virtual void	RefreshData() {}
	virtual int		GetCount() { return 0; }

protected:

	int		m_nParam;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


