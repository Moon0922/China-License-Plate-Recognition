// BannerWnd.cpp : implementation file
//

#include "pch.h"
#include "Header_Wnd.h"
#include "China-License-Plate-Recognition.h"
#include "China-License-Plate-RecognitionDlg.h"
// CNormal_BannerWnd

IMPLEMENT_DYNAMIC(CHeader_Wnd, CWnd)

CHeader_Wnd::CHeader_Wnd()
{
	HRSRC hSrc = FindResource(0, MAKEINTRESOURCE(IDB_ICON_MAXI), _T("PNG"));
	m_image_maxi.LoadResource(hSrc, CXIMAGE_FORMAT_PNG);

	hSrc = FindResource(0, MAKEINTRESOURCE(IDB_IMG_LOGO), _T("PNG"));
	m_image_logo.LoadResource(hSrc, CXIMAGE_FORMAT_PNG);
}

CHeader_Wnd::~CHeader_Wnd()
{
}


BEGIN_MESSAGE_MAP(CHeader_Wnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CNormal_BannerWnd message handlers




void CHeader_Wnd::OnPaint()
{
	CPaintDC dc(this);

	CRect crcClient;
	GetClientRect(&crcClient);
	CxMemDC dcMem(&dc, crcClient.Width(), crcClient.Height());
	dcMem.DrawTheRectangle( crcClient, COLOR_BG_BLACK, COLOR_BG_BLACK);

	m_crc_Minimize = CRect(crcClient.Width() - 60, 5, crcClient.Width() - 30, 35);
	m_crc_Close = CRect(crcClient.Width() - 30, 5, crcClient.Width(), 35);
	m_crc_Logo = CRect(10, 5, 40, 30);

	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	if (PtInRect(m_crc_Minimize, point))
	{
		dcMem.FillSolidRect(m_crc_Minimize, RGB(70, 70, 70));
	}
	else if (PtInRect(m_crc_Close, point))
	{
		dcMem.FillSolidRect(m_crc_Close, RGB(255, 30, 30));
	}

	m_image_logo.Draw(dcMem.GetSafeHdc(), m_crc_Logo);

	m_image_maxi.Draw(dcMem.GetSafeHdc(),
			CRect(crcClient.Width() - 60, 5, crcClient.Width(), 35));

	CTime tm = CTime::GetCurrentTime();

	CString strTime;
	strTime.Format(_T("%04d-%02d-%02d   %02d:%02d:%02d"), 
		tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());

	dcMem.SetBkMode(TRANSPARENT);

	CFont font2, font3;
	font2.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	dcMem.SelectObject(&font2);
	dcMem.SetTextColor(COLOR_TIMER);
	dcMem.DrawText(
		strTime,
		CRect(crcClient.Width() - 600, 5, crcClient.Width() - 150, 35),
		DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

	font3.CreateFont(22, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	dcMem.SelectObject(&font3);
	dcMem.SetTextColor(COLOR_FT_WHITE);
	dcMem.DrawText(
		TITLE,
		CRect(50, 0, 400, 40),
		DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(250, 0, 0));
	dcMem.SelectObject(pen);
	dcMem.MoveTo(CPoint(crcClient.left, crcClient.bottom));
	dcMem.LineTo(CPoint(crcClient.right, crcClient.bottom));
	dc.BitBlt(0, 0, crcClient.Width(), crcClient.Height(), &dcMem, 0, 0, SRCCOPY);
}


void CHeader_Wnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(PtInRect(m_crc_Logo, point)){
		((CChinaLicensePlateRecognitionDlg*) GetParent())->EndDialog(IDOK);
	}
	CWnd::OnLButtonDblClk(nFlags, point);
}


void CHeader_Wnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (PtInRect(m_crc_Minimize, point))
	{
		GetParent()->ShowWindow(SW_SHOWMINIMIZED);
	}
	else if (PtInRect(m_crc_Close, point))
	{
		((CChinaLicensePlateRecognitionDlg*) GetParent())->EndDialog(IDOK);
	}
	SetFocus();

	CWnd::OnLButtonDown(nFlags, point);
}


void CHeader_Wnd::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect crcClient;
	GetClientRect(&crcClient);

	if( !PtInRect(crcClient, point) )
	{
		if(GetCapture() == this)
			ReleaseCapture();
	}
	Invalidate(FALSE);

	CWnd::OnMouseMove(nFlags, point);
}


int CHeader_Wnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 1000, 0);
	return 0;
}


void CHeader_Wnd::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 0:
		{
			Invalidate(FALSE);
			break;
		}
	}

	CWnd::OnTimer(nIDEvent);
}

LRESULT CHeader_Wnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if( message == WM_COMMAND )
	{
		return GetParent()->SendMessage(message, wParam, lParam);
	}

	return CWnd::WindowProc(message, wParam, lParam);
}
