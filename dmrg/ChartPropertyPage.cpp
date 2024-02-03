// ChartPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "dmrg.h"
#include "ChartPropertyPage.h"
#include "afxdialogex.h"

#include "Options.h"

#include "dmrgDoc.h"
#include "MainFrm.h"
#include "dmrgView.h"


// CChartPropertyPage dialog

IMPLEMENT_DYNAMIC(CChartPropertyPage, CMFCPropertyPage)

CChartPropertyPage::CChartPropertyPage()
	: CMFCPropertyPage(IDD_PROPPAGE_CHART)
{
	bigTicksX = theApp.options.bigTicksX;
	bigTicksY = theApp.options.bigTicksY;
	smallTicksX = theApp.options.smallTicksX;
	smallTicksY = theApp.options.smallTicksY;

	minEnergy = theApp.options.minEnergy;
	maxEnergy = theApp.options.maxEnergy;
}

void CChartPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, minEnergyEdit);
	DDX_Control(pDX, IDC_EDIT2, maxEnergyEdit);

	DDX_Text(pDX, IDC_EDIT1, minEnergy);
	DDX_Text(pDX, IDC_EDIT2, maxEnergy);
	DDX_Text(pDX, IDC_EDIT3, bigTicksX);
	DDX_Text(pDX, IDC_EDIT4, smallTicksX);
	DDX_Text(pDX, IDC_EDIT5, bigTicksY);
	DDX_Text(pDX, IDC_EDIT6, smallTicksY);
}


BEGIN_MESSAGE_MAP(CChartPropertyPage, CMFCPropertyPage)
	ON_EN_CHANGE(IDC_EDIT1, &CChartPropertyPage::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &CChartPropertyPage::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT2, &CChartPropertyPage::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT4, &CChartPropertyPage::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CChartPropertyPage::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CChartPropertyPage::OnEnChangeEdit6)
END_MESSAGE_MAP()


// CChartPropertyPage message handlers


void CChartPropertyPage::ApplyValues()
{
	theApp.options.bigTicksX = bigTicksX;
	theApp.options.bigTicksY = bigTicksY;
	theApp.options.smallTicksX = smallTicksX;
	theApp.options.smallTicksY = smallTicksY;

	theApp.options.minEnergy = minEnergy;
	theApp.options.maxEnergy = maxEnergy;

	theApp.options.Save();

	CMainFrame *frm = (CMainFrame*)theApp.m_pMainWnd;
	if (frm)
	{
		CdmrgDoc* doc = frm->GetDocument();
		doc->SetYAxisRange();
		CdmrgView* view = doc->GetView();
		if (view) view->Invalidate();
	}
}


BOOL CChartPropertyPage::OnApply()
{
	UpdateData();
	ApplyValues();

	return CMFCPropertyPage::OnApply();
}


void CChartPropertyPage::OnEnChangeEdit1()
{
	SetModified();
}


void CChartPropertyPage::OnEnChangeEdit3()
{
	SetModified();
}


void CChartPropertyPage::OnEnChangeEdit2()
{
	SetModified();
}


void CChartPropertyPage::OnEnChangeEdit4()
{
	SetModified();
}


void CChartPropertyPage::OnEnChangeEdit5()
{
	SetModified();
}


void CChartPropertyPage::OnEnChangeEdit6()
{
	SetModified();
}
