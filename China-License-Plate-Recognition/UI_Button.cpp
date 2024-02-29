// UI_Button.cpp : implementation file
//

#include "pch.h"
#include "China-License-Plate-Recognition.h"
#include "UI_Button.h"


// CUI_Button

IMPLEMENT_DYNAMIC(CUI_Button, CUI_BaseWnd)

CUI_Button::CUI_Button()
{
	m_nState = 0;
	m_nStyle = KBS_NONE;
	m_bPressed = FALSE;

	HRSRC hSrc = FindResource(0, MAKEINTRESOURCE(IDB_ICON_BUTTON), _T("PNG"));
	m_imageButton.LoadResource(hSrc, CXIMAGE_FORMAT_PNG);
}

CUI_Button::~CUI_Button()
{
}


BEGIN_MESSAGE_MAP(CUI_Button, CUI_BaseWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CUI_Button message handlers




void CUI_Button::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect crcClient;
	GetClientRect(&crcClient);

	if (PtInRect(crcClient, point))
	{
		if (m_nState == 1)
		{
			m_bPressed = TRUE;
			m_nState = 2;
			SetCapture();
			Invalidate(FALSE);
		}
	}

	SetFocus();

	CWnd::OnLButtonDown(nFlags, point);
}


void CUI_Button::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect crcClient;
	GetClientRect(&crcClient);

	if (PtInRect(crcClient, point))
	{
		if (m_bPressed)
		{
			if (m_nState != 2)
			{
				m_nState = 2;
				SetCapture();
				Invalidate(FALSE);
			}
		}
		else
		{
			if (m_nState != 1)
			{
				m_nState = 1;
				SetCapture();
				Invalidate(FALSE);
			}
		}
	}
	else
	{
		if (m_bPressed)
		{
			if (m_nState != 1)
			{
				m_nState = 1;
				SetCapture();
				Invalidate(FALSE);
			}
		}
		else
		{
			if (m_nState != 0)
			{
				m_nState = 0;
				ReleaseCapture();
				Invalidate(FALSE);
			}
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CUI_Button::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect crcClient;
	GetClientRect(&crcClient);

	if( m_bPressed && PtInRect(crcClient, point) )
	{
		GetParent()->PostMessage(WM_COMMAND, (WPARAM) this, 0);
	}

	GetCursorPos(&point);
	ScreenToClient(&point);

	m_bPressed = FALSE;
	OnMouseMove(nFlags, point);
	Invalidate(FALSE);
	
	CWnd::OnLButtonUp(nFlags, point);
}


void CUI_Button::OnPaint()
{
	CPaintDC dc(this); 

	CRect crcClient;
	GetClientRect(&crcClient);

	CxMemDC dcMem(&dc, crcClient.Width(), crcClient.Height());

	COLORREF crcButton;
	CxImage image;

	CString strText;

	switch (m_nStyle)
	{
	case KBS_ADD: 
		{
			COLORREF crText[] = { RGB(53, 170, 71), RGB(93, 210, 111), RGB(13, 130, 31), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			m_imageButton.Crop(0, 0, 18, 18, &image);
			break;
		}
	case KBS_UPDATE: 
		{
			COLORREF crText[] = { RGB(75, 141, 208), RGB(115, 181, 248), RGB(13, 101, 168), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			m_imageButton.Crop(54, 0, 72, 18, &image);
			break;
		}
	case KBS_REMOVE: 
		{
			COLORREF crText[] = { RGB(214, 74, 56), RGB(254, 114, 96), RGB(174, 34, 16), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			m_imageButton.Crop(18, 0, 36, 18, &image);
			break;
		}
	case KBS_EXCEL: 
		{
			COLORREF crText[] = { RGB(215, 184, 72), RGB(255, 224, 112), RGB(175, 144, 32), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			m_imageButton.Crop(108, 0, 126, 18, &image);
			break;
		}
	case KBS_SEARCH:
		{
			COLORREF crText[] = { RGB(53, 170, 71), RGB(93, 210, 111), RGB(13, 130, 31), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			m_imageButton.Crop(126, 0, 144, 18, &image);
			break;
		}
	case KBS_AGREE:
		{
			COLORREF crText[] = { RGB(53, 170, 71), RGB(93, 210, 111), RGB(13, 130, 31), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			m_imageButton.Crop(90, 0, 108, 18, &image);
			break;
		}
	case KBS_DEAGREE:
		{
			COLORREF crText[] = { RGB(214, 74, 56), RGB(254, 114, 96), RGB(174, 34, 16), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			m_imageButton.Crop(36, 0, 54, 18, &image);
			break;

		}
	case KBS_NONE:
		{
			COLORREF crText[] = { RGB(214, 74, 56), RGB(254, 114, 96), RGB(174, 34, 16), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			break;
		}
	case KBS_USER:
		{
			COLORREF crText[] = { RGB(53, 170, 71), RGB(93, 210, 111), RGB(13, 130, 31), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			break;
		}
	case KBS_DROP:
		{
			COLORREF crText[] = { RGB(214, 74, 56), RGB(254, 114, 96), RGB(174, 34, 16), RGB(191, 191, 191) };
			crcButton = crText[m_nState];
			m_imageButton.Crop(144, 0, 162, 18, &image);
			break;
		}
	}


	GetWindowText(strText);

	if( !IsWindowEnabled() )
	{
		crcButton = RGB(200, 200, 200);
	}

	if (m_nStyle == KBS_DROP)
	{
		dcMem.DrawTheRectangle(crcClient, crcButton, RGB(244, 200, 200));
	}
	else
	{
		dcMem.DrawTheRectangle(crcClient, crcButton, crcButton);
	}

	CRect crcText = crcClient;
	if (m_nStyle != KBS_NONE && m_nStyle != KBS_USER )
	{
		crcText.right -= 25;
		crcText.left += 5;
		strText = strText;
	}

	dcMem.DrawTheText(strText, crcText, 
		(m_nStyle == KBS_NONE || m_nStyle == KBS_USER ) ? DT_CENTER | DT_VCENTER | DT_SINGLELINE : DT_LEFT | DT_VCENTER | DT_SINGLELINE,
		&the_font_16NC, RGB(250, 250, 250));
	CRect crcIcon = crcClient;
	crcIcon.left = crcIcon.right - 22;
	crcIcon.top = (crcClient.Height() - 18) / 2 + crcClient.top;
	crcIcon.bottom = crcIcon.top + 18;
	crcIcon.right = crcIcon.left + 18;

	image.Draw(dcMem.GetSafeHdc(), crcIcon);

	CRect crcData = crcClient;
	crcData.DeflateRect(2, 2, 2, 2);

	if( GetFocus() == this && m_nStyle != KBS_DROP)
	{
		dcMem.DrawTheDotRect(crcData, RGB(200, 200, 200));
	}

	dcMem.DrawBlt(&dc, crcClient);
}


void CUI_Button::CreateButton(CWnd* pWnd, CString strText, int nStyle)
{
	CWnd::Create(NULL, strText, WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(0, 0, 0, 0), pWnd, 323);
	m_nStyle = nStyle;
}

void CUI_Button::OnSetFocus(CWnd* pOldWnd)
{
	CUI_BaseWnd::OnSetFocus(pOldWnd);

	Invalidate(FALSE);
}

void CUI_Button::OnKillFocus(CWnd* pNewWnd)
{
	CUI_BaseWnd::OnKillFocus(pNewWnd);

	Invalidate(FALSE);
}

BOOL CUI_Button::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == 0x20 || pMsg->wParam == 0x0d )
		{
			GetParent()->SendMessage(WM_COMMAND, (WPARAM) this, 0);
			return TRUE;
		}
	}

	return CUI_BaseWnd::PreTranslateMessage(pMsg);
}
