
// dmrg.h : main header file for the dmrg application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


#include <objidl.h>
#include <gdiplus.h>

#pragma comment (lib,"Gdiplus.lib")

#include "Options.h"

// CdmrgApp:
// See dmrg.cpp for the implementation of this class
//

class CdmrgApp : public CWinAppEx
{
public:
	CdmrgApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

private:
	ULONG_PTR gdiplusToken;

public:
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	Options options;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CdmrgApp theApp;
