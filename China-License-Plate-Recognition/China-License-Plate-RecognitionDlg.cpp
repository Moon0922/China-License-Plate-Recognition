
// China-License-Plate-RecognitionDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "China-License-Plate-Recognition.h"
#include "China-License-Plate-RecognitionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChinaLicensePlateRecognitionDlg dialog


#include "Page_ImageWnd.h"
#include "Page_VideoWnd.h"
CChinaLicensePlateRecognitionDlg::CChinaLicensePlateRecognitionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHINALICENSEPLATERECOGNITION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChinaLicensePlateRecognitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChinaLicensePlateRecognitionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CChinaLicensePlateRecognitionDlg message handlers

BOOL CChinaLicensePlateRecognitionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	ShowWindow(SW_MAXIMIZE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChinaLicensePlateRecognitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChinaLicensePlateRecognitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CChinaLicensePlateRecognitionDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_wndHeader.Create(0, 0, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, WM_USER + 1);
	m_wndMenu.Create(0, 0, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, WM_USER + 2);

	theScenario.InsertPage(_T("Image"), new CPage_ImageWnd);
	theScenario.InsertPage(_T("Video"), new CPage_VideoWnd);

	theScenario.SelectPage(0);
	return 0;
}


void CChinaLicensePlateRecognitionDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_wndHeader.GetSafeHwnd())
		m_wndHeader.MoveWindow(0, 0, cx, HEADER_HEIGHT, FALSE);

	if (m_wndMenu.GetSafeHwnd())
		m_wndMenu.MoveWindow(0, HEADER_HEIGHT, cx, MENU_HEIGHT, FALSE);

	if (theScenario.GetSelectedPage() &&
		theScenario.GetSelectedPage()->GetSafeHwnd())
	{
		theScenario.GetSelectedPage()->MoveWindow(0, HEADER_HEIGHT + MENU_HEIGHT, cx, cy - (HEADER_HEIGHT + MENU_HEIGHT), FALSE);
	}
	Invalidate(TRUE);
}


LRESULT CChinaLicensePlateRecognitionDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_SELECT_PAGE)
	{
		CRect crcClient;
		GetClientRect(&crcClient);

		if (theScenario.GetSelectedPage() &&
			theScenario.GetSelectedPage()->GetSafeHwnd())
		{
			theScenario.GetSelectedPage()->MoveWindow(0, HEADER_HEIGHT + MENU_HEIGHT, crcClient.Width(), crcClient.Height() - (HEADER_HEIGHT + MENU_HEIGHT), FALSE);
		}
		Invalidate(FALSE);
	}
	else if (message == WM_SYSCOMMAND)
	{
		if (wParam == SC_CLOSE)
			exit(0);
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}


BOOL CChinaLicensePlateRecognitionDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return FALSE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
