#pragma once


// CUI_BaseWnd

class CUI_BaseWnd : public CWnd
{
	DECLARE_DYNAMIC(CUI_BaseWnd)

public:
	CUI_BaseWnd();
	virtual ~CUI_BaseWnd();

	virtual void CreateUIControl(CWnd* pWnd, CRect crc, UINT nID) {}
	virtual void SetStyle(int nStyle) {}
	virtual void SetUIText(CString strText) {}
	virtual CString GetUIText() { return _T(""); }


protected:

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


