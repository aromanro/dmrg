#pragma once

#include "NumberEdit.h"

// CChartPropertyPage dialog

class CChartPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CChartPropertyPage)

public:
	CChartPropertyPage();
	virtual ~CChartPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_CHART };
#endif

protected:
	int bigTicksX;
	int bigTicksY;
	int smallTicksX;
	int smallTicksY;

	double minEnergy;
	double maxEnergy;

	CNumberEdit minEnergyEdit;
	CNumberEdit maxEnergyEdit;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void ApplyValues();
	virtual BOOL OnApply();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
};
