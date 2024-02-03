
// dmrgView.cpp : implementation of the CdmrgView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "dmrg.h"
#endif

#include "dmrgDoc.h"
#include "dmrgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdmrgView

IMPLEMENT_DYNCREATE(CdmrgView, CView)

BEGIN_MESSAGE_MAP(CdmrgView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CdmrgView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


BOOL CdmrgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CdmrgView drawing

void CdmrgView::OnDraw(CDC* pDC)
{
	CdmrgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CRect rect;
	GetClientRect(rect);

	pDoc->m_Chart.Draw(pDC, rect);
}


// CdmrgView printing


void CdmrgView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CdmrgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CdmrgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CdmrgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CdmrgView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CdmrgView::OnContextMenu(CWnd* /* pWnd */, CPoint /*point*/)
{
#ifndef SHARED_HANDLERS
#endif
}


// CdmrgView diagnostics

#ifdef _DEBUG
void CdmrgView::AssertValid() const
{
	CView::AssertValid();
}

void CdmrgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CdmrgDoc* CdmrgView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdmrgDoc)));
	return dynamic_cast<CdmrgDoc*>(m_pDocument);
}
#endif //_DEBUG


// CdmrgView message handlers


void CdmrgView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CView::OnPrepareDC(pDC, pInfo);

	if (pDC->IsPrinting())
	{
		CRect rect;
		GetClientRect(rect);

		pDC->SetMapMode(MM_ISOTROPIC);

		int cx = pDC->GetDeviceCaps(HORZRES);
		int cy = pDC->GetDeviceCaps(VERTRES);
		
		pDC->SetWindowExt(rect.Width(), rect.Height());
		pDC->SetViewportExt(cx, cy);
		pDC->SetViewportOrg(0, 0);
	}
}


BOOL CdmrgView::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}


BOOL CdmrgView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CdmrgDoc* pDoc = GetDocument();

	if (pDoc && !pDoc->IsFinished())
	{
		RestoreWaitCursor();

		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CdmrgView::OnDestroy()
{
	CView::OnDestroy();

	if (timer) KillTimer(timer);
}


void CdmrgView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);

	CdmrgDoc* pDoc = GetDocument();

	if (pDoc->IsFinished())
	{
		KillTimer(timer);
		timer = 0;

		pDoc->UpdateChartData();

		EndWaitCursor();
		Invalidate();
	}	
}


void CdmrgView::StartTimer()
{
	if (!timer) timer = SetTimer(1, 1000, nullptr);
	BeginWaitCursor();
}
