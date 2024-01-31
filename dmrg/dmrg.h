
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
	BOOL InitInstance() override;
	void PreLoadState() override;
	void LoadCustomState() override;
	void SaveCustomState() override;
// Implementation

	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	Options options;

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	int ExitInstance() override;

private:
	ULONG_PTR gdiplusToken;
};

extern CdmrgApp theApp;
