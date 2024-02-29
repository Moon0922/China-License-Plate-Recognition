#pragma once

#include "PAGE_BaseWnd.h"

#define _MAX_PAGE		100
#define _MAX_APEX		6

#define PLAYMODE_NONE		0
#define PLAYMODE_VIDEO_NOTRACK	1
#define PLAYMODE_VIDEO_TRACK	2
#define PLAYMODE_IPCAM_NOTRACK	3
#define PLAYMODE_IPCAM_TRACK	4

class CxScenarioManager
{
public:
	CxScenarioManager(void);
	~CxScenarioManager(void);

	int				GetPageCount() { return m_nPageCount; }
	CString			GetPageName(int nIndex) { return m_strPageName[nIndex]; }
	CPAGE_BaseWnd*	GetPage(int nIndex) { return m_pBaseWnd[nIndex]; }

	void			InsertPage(CString strPageName, CPAGE_BaseWnd* pBaseWnd);
	void			SelectPage(int nPage);
	int				GetCurPageIndex() { return m_curPageIndex; }
	CPAGE_BaseWnd*	GetSelectedPage() { return m_pSelectedPage; }

	int				GetApex_No() { return m_nApex; }
	void			SetApex_No(int nNo) { m_nApex = nNo; }
	void			SetApexPoint(CPoint cpoApex);
	CPoint			GetApexPoint(int nNo) { return m_cpoApex[nNo]; }
	CPoint			m_cpoApex[_MAX_APEX];

	int				GetPlayMode() { return m_nPlayMode; }
	void			SetPlayMode(int nMode) { m_nPlayMode = nMode; }

protected:

	int				m_nApex;
	int				m_nPlayMode;
	int				m_nPageCount;
	CPAGE_BaseWnd*	m_pBaseWnd[_MAX_PAGE];
	CPAGE_BaseWnd*	m_pSelectedPage;
	CString			m_strPageName[_MAX_PAGE];
	int				m_curPageIndex;
};

extern CxScenarioManager theScenario;