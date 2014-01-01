#include "stdafx.h"
#include "Element.h"


CElement::CElement()
{
}

CElement::CElement(const CPoint& start, COLORREF color, int penWidth = 1) : m_StartPoint(start), m_Color(color), m_PenWidth(penWidth)
{
}

CElement::~CElement()
{
}
