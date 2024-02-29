#pragma once

#define PROC_NONE			0
#define PROC_START			1
#define PROC_STOP			2
#define MSG_SHOW_RESULT		WM_USER + 1000

//#include "CRLPREngineExport.h"
class CEngineProcessor
{
public:
	CEngineProcessor();
	~CEngineProcessor();

public:
	CString	m_strImageDir;
	HANDLE	m_hLPRThread;
	int		m_nProcStatus;
	int		m_curFileIndex;
	vector<CString> m_vecImagePath;
	CRITICAL_SECTION m_CS;

	CListCtrl *m_wndListCtrl;
	void SetListCtrl(CListCtrl *pListCtrl) { m_wndListCtrl = pListCtrl; };
	CWnd* m_pImageView;
	void SetImageView(CWnd *pImageView) { m_pImageView = pImageView; };

public:
	void* m_hEngineHandle;
	void CollectData(CString strDir);
	void Start();
	void Stop();
	static void LPRProc(LPARAM lParam);
	void StillImage(int index);
};

