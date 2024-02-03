#pragma once

#include "NumberEdit.h"

// CHeisenbergPropertyPage

class CHeisenbergPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CHeisenbergPropertyPage)

public:
	CHeisenbergPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_HEISENBERG };
#endif

private:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	void ApplyValues();
	void DoDataExchange(CDataExchange* pDX) override;
	BOOL OnApply() override;

	CNumberEdit jzEdit;
	CNumberEdit jxyEdit;

	double Jz;
	double Jxy;
};


