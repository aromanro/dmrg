#pragma once


// CDmrgPropertyPage dialog

class CDmrgPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CDmrgPropertyPage)

public:
	CDmrgPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_DMRG };
#endif

private:
	int model;
	int sites;
	int states;
	int sweeps;

	int calcEnergyGap;
	int nrStates;

	CEdit nrStatesEdit;

	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	void ApplyValues();
	BOOL OnApply() override;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnEnChangeEdit5();
	BOOL OnInitDialog() override;
};
