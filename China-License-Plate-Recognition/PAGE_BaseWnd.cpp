// PAGE_BaseWnd.cpp : implementation file
//

#include "pch.h"
#include "PAGE_BaseWnd.h"


// CPAGE_BaseWnd

IMPLEMENT_DYNAMIC(CPAGE_BaseWnd, CWnd)

CPAGE_BaseWnd::CPAGE_BaseWnd()
{
	m_nParam = 0;
	
}

CPAGE_BaseWnd::~CPAGE_BaseWnd()
{
}


BEGIN_MESSAGE_MAP(CPAGE_BaseWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CPAGE_BaseWnd message handlers



void CPAGE_BaseWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

BOOL CPAGE_BaseWnd::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN )
	{
		if( GetKeyState(VK_TAB) < 0 && GetKeyState(VK_SHIFT) < 0 )
		{
			CWnd* pWnd = CWnd::FromHandle(pMsg->hwnd);
			CWnd* pNextWnd = pWnd->GetWindow(GW_HWNDPREV);
			while( pNextWnd )
			{
				DWORD dwStyle = pNextWnd->GetStyle();
				if( dwStyle & WS_TABSTOP )
				{
					pNextWnd->SetFocus();
					return TRUE;
				}
				pNextWnd = pNextWnd->GetWindow(GW_HWNDPREV);
			}
			pNextWnd = pWnd->GetParent()->GetWindow(GW_CHILD);
			while( pNextWnd )
			{
				if( !pNextWnd->GetWindow(GW_HWNDNEXT))
					break;
				pNextWnd = pNextWnd->GetWindow(GW_HWNDNEXT);
			}
			
			while( pNextWnd != pWnd )
			{
				DWORD dwStyle = pNextWnd->GetStyle();
				if( dwStyle & WS_TABSTOP )
				{
					pNextWnd->SetFocus();
					Invalidate(FALSE);
					return TRUE;
				}
				pNextWnd = pNextWnd->GetWindow(GW_HWNDPREV);
			}
			return TRUE;
		}
		else if( GetKeyState(VK_TAB) < 0 )
		{
			CWnd* pWnd = CWnd::FromHandle(pMsg->hwnd);
			CWnd* pNextWnd = pWnd->GetWindow(GW_HWNDNEXT);
			while( pNextWnd )
			{
				DWORD dwStyle = pNextWnd->GetStyle();
				if( dwStyle & WS_TABSTOP )
				{
					pNextWnd->SetFocus();
					Invalidate(FALSE);
					return TRUE;
				}
				pNextWnd = pNextWnd->GetWindow(GW_HWNDNEXT);
			}
			pNextWnd = pWnd->GetParent()->GetWindow(GW_CHILD);
			while( pNextWnd != pWnd )
			{
				DWORD dwStyle = pNextWnd->GetStyle();
				if( dwStyle & WS_TABSTOP )
				{
					pNextWnd->SetFocus();
					Invalidate(FALSE);
					return TRUE;
				}
				pNextWnd = pNextWnd->GetWindow(GW_HWNDNEXT);
			}
			return TRUE;
		}

	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CPAGE_BaseWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( GetFocus() != this )
		SetFocus();

	CWnd::OnLButtonDown(nFlags, point);
}