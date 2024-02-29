#pragma once
class CDirDialog
{
public:
	CDirDialog();
	~CDirDialog();

public:
	BOOL DoBrowse(CWnd *pwndParent = NULL);

	CString m_strWindowTitle;
	CString m_strPath;
	CString m_strInitDir;
	CString m_strSelDir;
	CString m_strTitle;
	int  m_iImageIndex;
	BOOL m_bStatus;

private:
	virtual BOOL SelChanged(LPCTSTR lpcsSelection, CString& csStatusText);
	static int __stdcall CDirDialog::BrowseCtrlCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};

