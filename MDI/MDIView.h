
// MDIView.h : interface of the CMDIView class
//

#pragma once
#include "atltypes.h"
#include "Element.h"
#include <memory>


class CMDIView : public CView
{
protected: // create from serialization only
	CMDIView();
	DECLARE_DYNCREATE(CMDIView)

// Attributes
public:
	CMDIDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CElement* CreateElement(void) const;                                 // Create a new element on the heap
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);


protected:
  CPoint m_FirstPoint;                           // First point recorded for an element
  CPoint m_SecondPoint;                          // Second point recorded for an element
  std::shared_ptr<CElement> m_pTempElement;

  bool m_File = false;

};

#ifndef _DEBUG  // debug version in MDIView.cpp
inline CMDIDoc* CMDIView::GetDocument() const
   { return reinterpret_cast<CMDIDoc*>(m_pDocument); }
#endif

