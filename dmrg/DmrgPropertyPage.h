#pragma once


// CDmrgPropertyPage dialog

class CDmrgPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CDmrgPropertyPage)

public:
	CDmrgPropertyPage();
	virtual ~CDmrgPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_DMRG };
#endif

protected:
	int model;
	int sites;
	int states;
	int sweeps;

	int calcEnergyGap;
	int nrStates;

	CEdit nrStatesEdit;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void ApplyValues();
	virtual BOOL OnApply();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnEnChangeEdit5();
	virtual BOOL OnInitDialog();
};
