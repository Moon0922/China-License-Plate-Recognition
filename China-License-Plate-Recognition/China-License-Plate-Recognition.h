
// China-License-Plate-Recognition.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CChinaLicensePlateRecognitionApp:
// See China-License-Plate-Recognition.cpp for the implementation of this class
//

class CChinaLicensePlateRecognitionApp : public CWinApp
{
public:
	CChinaLicensePlateRecognitionApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

public:
	CString		m_strFullPath;
	void		GetFullPath();
};

extern CChinaLicensePlateRecognitionApp theApp;
