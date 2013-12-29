
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
	afx_msg void OnAppAbout();          //Message Handler ; afx_msg identifies as message handler
	DECLARE_MESSAGE_MAP()                //Macro indicates that class will contain members that are message handlers and will have a message map
	                                     //in MDI.cpp
};
                                         //CCmdTarget ; The base class for the Microsoft Foundation Class Library message-map architecture.
extern CMDIApp theApp;
