// Page_ImageWnd.cpp : implementation file
//

#include "pch.h"
#include "China-License-Plate-Recognition.h"
#include "Page_ImageWnd.h"


// CPage_ImageWnd

IMPLEMENT_DYNAMIC(CPage_ImageWnd, CPAGE_BaseWnd)

CPage_ImageWnd::CPage_ImageWnd()
{

}

CPage_ImageWnd::~CPage_ImageWnd()
{
}


BEGIN_MESSAGE_MAP(CPage_ImageWnd, CPAGE_BaseWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED,  WM_USER + 1002, &CPage_ImageWnd::OnItemchangedImgList)
	ON_NOTIFY(NM_CUSTOMDRAW, WM_USER + 1002, &CPage_ImageWnd::OnCustomdrawImgList)
END_MESSAGE_MAP()



// CPage_ImageWnd message handlers




void CPage_ImageWnd::OnPaint()
{
	CPaintDC dc(this);
	CRect crcClient;
	GetClientRect(crcClient);

	CxMemDC dcMem(&dc, crcClient.Width(), crcClient.Height());

	//dcMem.DrawTheRectangle(crcClient, RGB(50, 50, 50), RGB(50, 50, 50));
	dcMem.SetTextColor(COLOR_FT_WHITE);
	dcMem.SetBkColor(RGB(0, 0, 0));
	dcMem.SetBkMode(OPAQUE);

	CFont font2, font3;
	dcMem.DrawTheDotRect(CRect( 5, 5, crcClient.Width() / 4, crcClient.Height() ), COLOR_DOT);
	dcMem.DrawBlt(&dc, crcClient);
}


int CPage_ImageWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPAGE_BaseWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_ctlImgPath.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this, WM_USER + 1001);
	m_btnOpen.CreateButton(this, _T("..."), KBS_NONE);
	m_btnStart.CreateButton(this, _T("START"), KBS_NONE);
	m_btnStop.CreateButton(this, _T("STOP"), KBS_NONE);
	m_ctlImgList.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_NOSORTHEADER | WS_BORDER, CRect(0, 0, 0, 0), this, WM_USER + 1002);
	m_wndImageView.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, WM_USER + 1003);

	m_wndImageView.InitView(COLOR_GRAY);

	m_ctlImgList.SetFont(&the_font_14NC);
	m_ctlImgList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_AUTOSIZECOLUMNS);
	CString colStr[] = { _T("No"), _T("FileName"), _T("License"), _T("Time"), _T("Confidence") };
	int	colWidth[] = { 40, 140, 120, 70, 80 };
	for (int i = 0; i < 5; i++) {
		m_ctlImgList.InsertColumn(i, colStr[i], LVCFMT_LEFT, colWidth[i]);
	}

	m_xEngineProc.SetImageView((CWnd*)&m_wndImageView);
	m_xEngineProc.SetListCtrl(&m_ctlImgList);
	return 0;
}


void CPage_ImageWnd::OnSize(UINT nType, int cx, int cy)
{
	CPAGE_BaseWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(m_ctlImgPath.GetSafeHwnd()){
		m_ctlImgPath.MoveWindow( 10, 10, cx / 4 - 150, 30, FALSE);
		m_btnOpen.MoveWindow( cx / 4 - 135, 10, 130, 30, FALSE);
		m_btnStart.MoveWindow( 10, 45, (cx / 4 - 20) / 2, 30, FALSE);
		m_btnStop.MoveWindow( 10 + (cx / 4 - 20) / 2 + 5, 45, (cx / 4 - 20) / 2, 30, FALSE);
		m_ctlImgList.MoveWindow( 10, 80, cx / 4 - 15, cy - 85, FALSE);
		m_wndImageView.MoveWindow(cx / 4 + 5, 5, cx / 4 * 3 - 10, cy - 5, FALSE);
	}
	Invalidate();
}


LRESULT CPage_ImageWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if(message == WM_COMMAND){
		if(wParam == (WPARAM)& m_btnOpen)
			OnClickedOpenButton();
	}
	return CPAGE_BaseWnd::WindowProc(message, wParam, lParam);
}


BOOL CPage_ImageWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CPAGE_BaseWnd::PreTranslateMessage(pMsg);
}

void CPage_ImageWnd::OnItemchangedImgList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMListView->iItem;
	if (index >= 0 && m_xEngineProc.m_curFileIndex != index) {
		m_xEngineProc.StillImage(index);
	}
	*pResult = 0;
}

void CPage_ImageWnd::OnCustomdrawImgList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	*pResult = CDRF_DODEFAULT;

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
	{
		COLORREF clrNewTextColor, clrNewBkColor;
		int	nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		BOOL bSelect = FALSE;
		POSITION pos = m_ctlImgList.GetFirstSelectedItemPosition();
		while (pos)
		{
			int index = m_ctlImgList.GetNextSelectedItem(pos);
			if (index == nItem)
			{
				bSelect = TRUE;
				break;
			}
		}
		if (bSelect)
		{
			clrNewTextColor = RGB(255, 255, 255);
			clrNewBkColor = RGB(0, 120, 215);
		}
		else
		{
			clrNewTextColor = RGB(0, 0, 0);
			clrNewBkColor = RGB(255, 255, 255);
		}
		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;
		*pResult = CDRF_DODEFAULT;
	}
}
#include "DirDialog.h"
void CPage_ImageWnd::OnClickedOpenButton()
{
	CDirDialog dlg;
	dlg.m_strWindowTitle = "Select License Plate Image Location";
	dlg.m_strTitle = "Browse Folder for License Plate Image Files Location";

	CFile file;
	CString strPath;
	TCHAR strSelDir[MAX_PATH] = _T("");
	if (file.Open(theApp.m_strFullPath + _T("\\path.txt"), CFile::modeRead))
	{
		file.Read(strSelDir, MAX_PATH * 2);
		file.Close();
	}
	dlg.m_strSelDir = strSelDir;
	if (!dlg.DoBrowse(AfxGetMainWnd())) return;

	TCHAR path[MAX_PATH];
	lstrcpy(path, dlg.m_strPath.GetBuffer());
	if (file.Open(theApp.m_strFullPath + _T("\\path.txt"), CFile::modeWrite | CFile::modeCreate))
	{
		file.Write(path, MAX_PATH * 2);
		file.Close();
	}
	m_xEngineProc.CollectData(path);
	m_ctlImgPath.SetWindowTextW(path);
}
