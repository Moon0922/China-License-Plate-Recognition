#include "pch.h"
#include "xScenarioManager.h"

CxScenarioManager::CxScenarioManager(void)
{
	m_nPageCount = 0;
	m_pSelectedPage = 0;
	m_nPlayMode = PLAYMODE_NONE;

	m_nApex = 0;
}

CxScenarioManager::~CxScenarioManager(void)
{
	for(int i = 0; i < m_nPageCount; i++)
	{
		delete m_pBaseWnd[i];
	}
	m_nPageCount = 0;
}

void CxScenarioManager::InsertPage(CString strPageName, CPAGE_BaseWnd* pBaseWnd)
{
	m_strPageName[m_nPageCount] = strPageName;
	m_pBaseWnd[m_nPageCount] = pBaseWnd;
	pBaseWnd->Create(NULL, NULL, WS_CHILD | WS_TABSTOP, CRect(0, 0, 0, 0), AfxGetMainWnd(), 3230);
	m_nPageCount++;
}

CxScenarioManager theScenario;

void CxScenarioManager::SelectPage(int nPage)
{
	if( m_pSelectedPage == m_pBaseWnd[nPage] )
		return;

	m_curPageIndex = nPage;

	if( m_pSelectedPage )
		m_pSelectedPage->ShowWindow(SW_HIDE);


	m_pSelectedPage = m_pBaseWnd[nPage];

	if( m_pSelectedPage )
		m_pSelectedPage->ShowWindow(SW_SHOW);

	if( AfxGetMainWnd() )
	{
		AfxGetMainWnd()->SendMessage(WM_SELECT_PAGE, (WPARAM) nPage);
	}
}

void CxScenarioManager::SetApexPoint(CPoint cpoApex)
{
	m_cpoApex[m_nApex] = cpoApex;
}