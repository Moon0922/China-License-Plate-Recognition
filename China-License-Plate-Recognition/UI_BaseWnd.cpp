// UI_BaseWnd.cpp : implementation file
//

#include "pch.h"
#include "UI_BaseWnd.h"


// CUI_BaseWnd

IMPLEMENT_DYNAMIC(CUI_BaseWnd, CWnd)

CUI_BaseWnd::CUI_BaseWnd()
{

}

CUI_BaseWnd::~CUI_BaseWnd()
{
}


BEGIN_MESSAGE_MAP(CUI_BaseWnd, CWnd)
END_MESSAGE_MAP()



// CUI_BaseWnd message handlers



BOOL CUI_BaseWnd::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetSafeHwnd() )
	{
		if( GetParent()->PreTranslateMessage(pMsg) )
			return TRUE;
	}

	return CWnd::PreTranslateMessage(pMsg);
}
