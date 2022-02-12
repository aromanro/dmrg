// HeisenbergPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "dmrg.h"
#include "HeisenbergPropertyPage.h"

#include "Options.h"

// CHeisenbergPropertyPage

IMPLEMENT_DYNAMIC(CHeisenbergPropertyPage, CMFCPropertyPage)

CHeisenbergPropertyPage::CHeisenbergPropertyPage()
: CMFCPropertyPage(IDD_PROPPAGE_HEISENBERG)
, Jz(theApp.options.Jz)
, Jxy(theApp.options.Jxy)
{
}

CHeisenbergPropertyPage::~CHeisenbergPropertyPage()
{
}


BEGIN_MESSAGE_MAP(CHeisenbergPropertyPage, CMFCPropertyPage)
	ON_EN_CHANGE(IDC_EDIT1, &CHeisenbergPropertyPage::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CHeisenbergPropertyPage::OnEnChangeEdit2)
END_MESSAGE_MAP()



// CHeisenbergPropertyPage message handlers




void CHeisenbergPropertyPage::OnEnChangeEdit1()
{
	SetModified();
}


void CHeisenbergPropertyPage::OnEnChangeEdit2()
{
	SetModified();
}


void CHeisenbergPropertyPage::ApplyValues()
{
	theApp.options.Jz = Jz;
	theApp.options.Jxy = Jxy;

	theApp.options.Save();
}


void CHeisenbergPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDIT1, jzEdit);
	DDX_Control(pDX, IDC_EDIT2, jxyEdit);

	DDX_Text(pDX, IDC_EDIT1, Jz);
	DDX_Text(pDX, IDC_EDIT2, Jxy);

	CMFCPropertyPage::DoDataExchange(pDX);
}


BOOL CHeisenbergPropertyPage::OnApply()
{
	ApplyValues();

	return CMFCPropertyPage::OnApply();
}
