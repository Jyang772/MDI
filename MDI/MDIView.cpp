
// MDIView.cpp : implementation of the CMDIView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MDI.h"
#endif

#include "MDIDoc.h"
#include "MDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDIView

IMPLEMENT_DYNCREATE(CMDIView, CView)

BEGIN_MESSAGE_MAP(CMDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMDIView construction/destruction

CMDIView::CMDIView()
{
	// TODO: add construction code here

}

CMDIView::~CMDIView()
{
}

BOOL CMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMDIView drawing

void CMDIView::OnDraw(CDC* pDC)
{
	CMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->MoveTo(50, 50);
	pDC->LineTo(50, 200);
	pDC->LineTo(150, 200);
	pDC->LineTo(150, 50);
	pDC->LineTo(50, 50);


	// TODO: add draw code for native data here
}


// CMDIView printing

BOOL CMDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMDIView diagnostics

#ifdef _DEBUG
void CMDIView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDIDoc* CMDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIDoc)));
	return (CMDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CMDIView message handlers
