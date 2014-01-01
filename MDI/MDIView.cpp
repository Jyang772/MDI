
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
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMDIView construction/destruction

CMDIView::CMDIView(): m_FirstPoint(0)
, m_SecondPoint(0)
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
	//CMDIDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//pDC->MoveTo(50, 50);
	//pDC->LineTo(50, 150);
	//pDC->LineTo(150, 150);
	//pDC->LineTo(150, 50);
	//pDC->LineTo(50, 50);


	//CPen aPen;                                                    //Create a CPen object
	//aPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));                   //Initialize Pen 
	// 
	//CPen* pOldPen = pDC->SelectObject(&aPen);
	//pDC->Ellipse(50, 50, 150, 150);

	//CRect rect(250, 50, 300, 100);
	//CPoint start(275, 100);
	//CPoint end(250, 75);	
	//pDC->SelectObject(pOldPen); 
	//pDC->Arc(&rect, start, end);

	//


	//CBrush aBrush;
	//aBrush.CreateHatchBrush(HS_DIAGCROSS, (255, 0, 0));

	////CBrush* pOldBrush = pDC->SelectObject(&aBrush);

	//CBrush* pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));     //Return type for SelectStockObject is CDGIObject*

	//
	//pDC->SelectObject(pOldBrush);



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


void CMDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonUp(nFlags, point);
}


void CMDIView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_FirstPoint = point;

	CView::OnLButtonDown(nFlags, point);
}


void CMDIView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Define a Device Context object for the view
	CClientDC aDC(this);                                                 // DC is for this view

	// Verify the left button is down and mouse messages captured
	if ((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		m_SecondPoint = point;                                             // Save the current cursor position
		if (m_pTempElement)
		{
			// An element was created previously
			if (ElementType::CURVE == GetDocument()->GetElementType())        // A curve?
			{  // We are drawing a curve so add a segment to the existing curve
				std::static_pointer_cast<CCurve>(m_pTempElement)->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC);                                   // Now draw it
				return;                                                       // We are done
			}
			else
			{
				// If we get to here it's not a curve so
				// redraw the old element so it disappears from the view
				aDC.SetROP2(R2_NOTXORPEN);                                     // Set the drawing mode
				m_pTempElement->Draw(&aDC);                                    // Redraw the old element to erase it
			}
		}

		// Create a temporary element of the type and color that
		// is recorded in the document object, and draw it
		m_pTempElement.reset(CreateElement());                             // Create a new element
		m_pTempElement->Draw(&aDC);                                        // Draw the element
	}
}
