#pragma once

#include "NumberEdit.h"

// CChartPropertyPage dialog

class CChartPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CChartPropertyPage)

public:
	CChartPropertyPage();
	~CChartPropertyPage() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_CHART };
#endif

private:
	int bigTicksX;
	int bigTicksY;
	int smallTicksX;
	int smallTicksY;

	double minEnergy;
	double maxEnergy;

	CNumberEdit minEnergyEdit;
	CNumberEdit maxEnergyEdit;

	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	void ApplyValues();
	BOOL OnApply() override;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
};
