
// dmrgDoc.h : interface of the CdmrgDoc class
//


#pragma once

#include "Chart.h"

#include "ComputationThread.h"
#include "Options.h"

class CdmrgView;

class CdmrgDoc : public CDocument
{
protected: // create from serialization only
	CdmrgDoc();
	DECLARE_DYNCREATE(CdmrgDoc)

// Attributes
public:
	Chart m_Chart;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CdmrgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	ComputationThread *thread;
	Options options;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	bool IsFinished();
	void UpdateChartData();
	CdmrgView* GetView();
	void StartComputing();
	void SetYAxisRange();
};
