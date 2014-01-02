// Element.cpp : implementation file
//

#include "stdafx.h"
#include "MDI.h"
#include "Element.h"


static UINT BASED_CODE indicators[] =
{
	ID_INDICATOR_COORD,
};



// CElement

CElement::CElement()
{
}

CElement::CElement(const CPoint& start, COLORREF color, int penWidth) :
  m_StartPoint(start), m_PenWidth(penWidth), m_Color(color)
{
}

CElement::~CElement()
{
}


// CElement member functions
