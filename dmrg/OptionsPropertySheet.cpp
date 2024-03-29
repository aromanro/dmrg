// OptionsPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "dmrg.h"
#include "OptionsPropertySheet.h"


// COptionsPropertySheet

IMPLEMENT_DYNAMIC(COptionsPropertySheet, CMFCPropertySheet)

COptionsPropertySheet::COptionsPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CMFCPropertySheet(nIDCaption, pParentWnd, iSelectPage), hIcon(0)
{
}

COptionsPropertySheet::COptionsPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CMFCPropertySheet(pszCaption, pParentWnd, iSelectPage), hIcon(0)
{
}

COptionsPropertySheet::~COptionsPropertySheet()
{
	if (hIcon) DestroyIcon(hIcon);
}


BEGIN_MESSAGE_MAP(COptionsPropertySheet, CMFCPropertySheet)
END_MESSAGE_MAP()



// COptionsPropertySheet message handlers




BOOL COptionsPropertySheet::OnInitDialog()
{
	BOOL bResult = CMFCPropertySheet::OnInitDialog();

	hIcon = static_cast<HICON>(::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0));

	SetIcon(hIcon, FALSE);

	return bResult;
}
