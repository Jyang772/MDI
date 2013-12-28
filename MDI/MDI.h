
// MDI.h : main header file for the MDI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMDIApp:
// See MDI.cpp for the implementation of this class
//

class CMDIApp : public CWinApp
{
public:
	CMDIApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMDIApp theApp;
