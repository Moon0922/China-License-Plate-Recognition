// Page_VideoWnd.cpp : implementation file
//

#include "pch.h"
#include "China-License-Plate-Recognition.h"
#include "Page_VideoWnd.h"


// CPage_VideoWnd

IMPLEMENT_DYNAMIC(CPage_VideoWnd, CPAGE_BaseWnd)

CPage_VideoWnd::CPage_VideoWnd()
{

}

CPage_VideoWnd::~CPage_VideoWnd()
{
}

void CPage_VideoWnd::OnPaint()
{
	CPaintDC dc(this);
	CRect crcClient;
	GetClientRect(crcClient);

	CxMemDC dcMem(&dc, crcClient.Width(), crcClient.Height());
	dcMem.SetTextColor(COLOR_FT_WHITE);
	dcMem.SetBkColor(RGB(0, 0, 0));
	dcMem.SetBkMode(OPAQUE);
	dcMem.DrawBlt(&dc, crcClient);
}

int CPage_VideoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPAGE_BaseWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ctlVideoPath.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this, WM_USER + 2001);
	m_wndImageView.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, WM_USER + 2002);
	m_btnOpen.CreateButton(this, _T("..."), KBS_NONE);
	m_wndImageView.InitView(COLOR_GRAY);
	SetTimer(1, 30, 0);
	return 0;
}

void CPage_VideoWnd::OnSize(UINT nType, int cx, int cy)
{
	if (m_ctlVideoPath.GetSafeHwnd()) {
		m_ctlVideoPath.MoveWindow(10, 10, cx - 150, 30, FALSE);
		m_btnOpen.MoveWindow(cx - 135, 10, 125, 30, FALSE);
		m_wndImageView.MoveWindow(10, 45, cx - 20, cy - 35, FALSE);
	}
	Invalidate();
}

LRESULT CPage_VideoWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_COMMAND) {
		if (wParam == (WPARAM)& m_btnOpen)
			OnClickedOpenButton();
	}
	return CPAGE_BaseWnd::WindowProc(message, wParam, lParam);
}

BOOL CPage_VideoWnd::PreTranslateMessage(MSG * pMsg)
{
	return CPAGE_BaseWnd::PreTranslateMessage(pMsg);
}

void CPage_VideoWnd::OnClickedOpenButton()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Video file| *.avi; *.mp4; *.mpg; *.asf; *.wmv; *.mov||"), this);

	CString strOpenVideoFile = _T("Open Video");
	dlg.m_ofn.lpstrTitle = strOpenVideoFile;

	if (dlg.DoModal() != IDOK)
		return;

	CString strVideoPath = dlg.GetPathName();
	m_xVideoProc.VideoOpen(strVideoPath);
	m_xVideoProc.VideoPlay();
	m_ctlVideoPath.SetWindowTextW(strVideoPath);
}


BEGIN_MESSAGE_MAP(CPage_VideoWnd, CPAGE_BaseWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()




void CPage_VideoWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		EnterCriticalSection(&m_xVideoProc.m_CS);
		if (m_xVideoProc.m_xVideoImage.IsValid())
		{
			CxImage xImage(m_xVideoProc.m_xVideoImage);
			m_wndImageView.SetImage(xImage.MakeBitmap());
		}
		LeaveCriticalSection(&m_xVideoProc.m_CS);
	}

	CPAGE_BaseWnd::OnTimer(nIDEvent);
}


void CPage_VideoWnd::OnDestroy()
{
	CPAGE_BaseWnd::OnDestroy();
	KillTimer(1);
}
