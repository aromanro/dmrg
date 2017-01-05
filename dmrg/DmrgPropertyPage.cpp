// DmrgPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "dmrg.h"
#include "DmrgPropertyPage.h"
#include "afxdialogex.h"


// CDmrgPropertyPage dialog

IMPLEMENT_DYNAMIC(CDmrgPropertyPage, CMFCPropertyPage)

CDmrgPropertyPage::CDmrgPropertyPage()
	: CMFCPropertyPage(IDD_PROPPAGE_DMRG),
	model(0), sites(60), states(10), sweeps(4)
{
	model = theApp.options.model;
	sites = theApp.options.sites;
	states = theApp.options.states;
	sweeps = theApp.options.sweeps;

	calcEnergyGap = (theApp.options.calculateEnergyGap ? 1 : 0);
	nrStates = theApp.options.nrStates;
}

CDmrgPropertyPage::~CDmrgPropertyPage()
{
}

void CDmrgPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT5, nrStatesEdit);

	DDX_Radio(pDX, IDC_RADIO1, model);

	DDX_Text(pDX, IDC_EDIT1, sites);
	DDX_Text(pDX, IDC_EDIT2, states);
	DDX_Text(pDX, IDC_EDIT3, sweeps);

	DDX_Check(pDX, IDC_CHECK1, calcEnergyGap);
	DDX_Text(pDX, IDC_EDIT5, nrStates);

	DDV_MinMaxInt(pDX, sites, 4, 400);
	DDV_MinMaxInt(pDX, states, 10, 50);
	DDV_MinMaxInt(pDX, sweeps, 1, 12);
	DDV_MinMaxInt(pDX, nrStates, 1, 9);
}


BEGIN_MESSAGE_MAP(CDmrgPropertyPage, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_RADIO1, &CDmrgPropertyPage::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDmrgPropertyPage::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT1, &CDmrgPropertyPage::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CDmrgPropertyPage::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CDmrgPropertyPage::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_CHECK1, &CDmrgPropertyPage::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT5, &CDmrgPropertyPage::OnEnChangeEdit5)
END_MESSAGE_MAP()


// CDmrgPropertyPage message handlers


void CDmrgPropertyPage::ApplyValues()
{
	theApp.options.model = model;
	theApp.options.sites = sites;
	theApp.options.states = states;
	theApp.options.sweeps = sweeps;

	theApp.options.calculateEnergyGap = (1 == calcEnergyGap ? true : false);
	theApp.options.nrStates = nrStates;

	theApp.options.Save();
}


BOOL CDmrgPropertyPage::OnApply()
{
	UpdateData();
	ApplyValues();

	return CMFCPropertyPage::OnApply();
}


void CDmrgPropertyPage::OnBnClickedRadio1()
{
	SetModified();
}


void CDmrgPropertyPage::OnBnClickedRadio2()
{
	SetModified();
}


void CDmrgPropertyPage::OnEnChangeEdit1()
{
	SetModified();
}


void CDmrgPropertyPage::OnEnChangeEdit2()
{
	SetModified();
}


void CDmrgPropertyPage::OnEnChangeEdit3()
{
	SetModified();
}


void CDmrgPropertyPage::OnBnClickedCheck1()
{
	SetModified();

	UpdateData();

	if (calcEnergyGap) nrStatesEdit.EnableWindow();
	else nrStatesEdit.EnableWindow(false);
}


void CDmrgPropertyPage::OnEnChangeEdit5()
{
	SetModified();
}


BOOL CDmrgPropertyPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	if (calcEnergyGap) nrStatesEdit.EnableWindow();
	else nrStatesEdit.EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
