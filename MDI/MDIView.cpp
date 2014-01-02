
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
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Curve.h"
#include "Ellipse.h"
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
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMDIView construction/destruction

CMDIView::CMDIView()
  : m_FirstPoint(CPoint(0,0)), m_pTempElement(nullptr)
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

  // Draw the sketch
  for(auto iter = pDoc->begin() ; iter != pDoc->end() ; ++iter)
  {
    std::shared_ptr<CElement> pElement(*iter);
    if(pDC->RectVisible(pElement->GetEnclosingRect()))                 // Element visible?
      pElement->Draw(pDC);                                             // Yes, draw it.
  }

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


void CMDIView::OnLButtonDown(UINT nFlags, CPoint point)
{
   m_FirstPoint = point;                                               // Record the cursor position
   SetCapture();                                                       // Capture subsequent mouse messages
}


void CMDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
  if(this == GetCapture())
    ReleaseCapture();                                                  // Stop capturing mouse messages

  // Make sure there is an element
  if(m_pTempElement)
  { // Add the element pointer to the sketch
    
    GetDocument()->AddElement(m_pTempElement); 
    InvalidateRect(&m_pTempElement->GetEnclosingRect());
    m_pTempElement.reset();                                            // Reset the element pointer
   }
}


void CMDIView::OnMouseMove(UINT nFlags, CPoint point)
{
  // Define a Device Context object for the view
  CClientDC aDC(this);                                                 // DC is for this view

  // Verify the left button is down and mouse messages captured
  if((nFlags & MK_LBUTTON) && (this == GetCapture()))                  
  {
    m_SecondPoint = point;                                             // Save the current cursor position
    if(m_pTempElement)
    {
      // An element was created previously
      if(ElementType::CURVE == GetDocument()->GetElementType())        // A curve?
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

// Create an element of the current type
CElement* CMDIView::CreateElement(void) const
{
   // Get a pointer to the document for this view
   CMDIDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);                 // Verify the pointer is good
        
   // Get the current element color
   COLORREF color = static_cast<COLORREF>(pDoc->GetElementColor());

   // Now select the element using the type stored in the document
   switch(pDoc->GetElementType())
   {
      case ElementType::RECTANGLE:
         return new CRectangle(m_FirstPoint, m_SecondPoint, color);
        
      case ElementType::CIRCLE:
         return new CCircle(m_FirstPoint, m_SecondPoint, color);
        
      case ElementType::CURVE:
         return new CCurve(m_FirstPoint, m_SecondPoint, color);
        
      case ElementType::LINE:
         return new CLine(m_FirstPoint, m_SecondPoint, color);

	  case ElementType::ELLIPSE:
		  return new CEllipse(m_FirstPoint, m_SecondPoint, color);
       

      default:
         // Something's gone wrong
         AfxMessageBox(_T("Bad Element code"), MB_OK);
         AfxAbort();
         return nullptr;
   }
}
