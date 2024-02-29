// Menu_Wnd.cpp : implementation file
//

#include "pch.h"
#include "China-License-Plate-Recognition.h"
#include "Menu_Wnd.h"


// CMenu_Wnd

IMPLEMENT_DYNAMIC(CMenu_Wnd, CWnd)

CMenu_Wnd::CMenu_Wnd()
{

}

CMenu_Wnd::~CMenu_Wnd()
{
}


BEGIN_MESSAGE_MAP(CMenu_Wnd, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMenu_Wnd message handlers




void CMenu_Wnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	CRect crcClient;
	GetClientRect(&crcClient);

	CxMemDC dcMem(&dc, crcClient.Width(), crcClient.Height());
	dcMem.DrawTheRectangle(crcClient, RGB(30, 30, 30), RGB(30, 30, 30));

	CFont font2, font3;
	font2.CreateFont(30, 0, 0, 0, FW_HEAVY, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	font3.CreateFont(20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	dcMem.SetBkMode(TRANSPARENT);

	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	//dcMem.DrawTheLine(0, 0, crcClient.Width(), 0, RGB(80, 80, 80));
	for(int i = 0; i < theScenario.GetPageCount(); i++){
		//m_rtMenu[i] = CRect(crcClient.Width() - 200 * (i + 1) - 2, 0, crcClient.Width() - 200 * i - 2, crcClient.Height());
		m_rtMenu[i] = CRect(150 * i, 0, 150 * (i + 1), crcClient.Height());
		if( theScenario.GetCurPageIndex() == i ){
			dcMem.DrawTheRectangle(m_rtMenu[i], RGB(50, 50, 50), RGB(50, 50, 50));
			dcMem.DrawTheLine(m_rtMenu[i].left, m_rtMenu[i].bottom - 2, m_rtMenu[i].right, m_rtMenu[i].bottom - 2, RGB(255, 255, 255), 3);
		}

		else if(PtInRect(CRect(m_rtMenu[i].left, m_rtMenu[i].top, m_rtMenu[i].right - 20, m_rtMenu[i].bottom), point)){
			dcMem.DrawTheRectangle(m_rtMenu[i], RGB(100, 100, 100), RGB(100, 100, 100));
			
		}
		
		dcMem.DrawTheText(
			theScenario.GetPageName(i), 
			m_rtMenu[i], 
			DT_CENTER | DT_VCENTER | DT_SINGLELINE, &font3, RGB(255, 255, 255));
	}
	

	dcMem.DrawBlt(&dc, crcClient);
}


int CMenu_Wnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void CMenu_Wnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	for(int i = 0; i < 10; i++){
		if (PtInRect(m_rtMenu[i], point))
		{
			SetCapture();
			Invalidate(FALSE);
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void CMenu_Wnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(FALSE);
	CWnd::OnMouseMove(nFlags, point);
}


void CMenu_Wnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	for(int i = 0; i < 10; i++){
		if (PtInRect(m_rtMenu[i], point) && i != theScenario.GetCurPageIndex())
		{
			theScenario.SelectPage(i);
			break;
		}
	}

	if(GetCapture() == this)
	{
		ReleaseCapture();
	}
	Invalidate(FALSE);
	CWnd::OnLButtonUp(nFlags, point);
}
