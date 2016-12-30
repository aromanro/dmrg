#pragma once

#include "NumberEdit.h"

// CHeisenbergPropertyPage

class CHeisenbergPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CHeisenbergPropertyPage)

public:
	CHeisenbergPropertyPage();
	virtual ~CHeisenbergPropertyPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_HEISENBERG };
#endif

protected:
	DECLARE_MESSAGE_MAP()

	CNumberEdit jzEdit;
	CNumberEdit jxyEdit;

public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	void ApplyValues();
	virtual void DoDataExchange(CDataExchange* pDX);
	double Jz;
	double Jxy;
	virtual BOOL OnApply();
};


