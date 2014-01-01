#include "stdafx.h"
#include <algorithm>
#include "Rectangle.h"


CRectangle::CRectangle()
{
}


CRectangle::CRectangle(const CPoint& start, const CPoint& end, COLORREF color)
{
	m_StartPoint = CPoint((std::min)(start.x, end.x), (std::min)(start.y, end.y));
	m_BottomRight = CPoint((std::min)(start.x, end.x), (std::min)(start.y, end.y));

	if ((m_BottomRight.x - m_StartPoint.x) < 2)
		m_BottomRight.x = m_StartPoint.x + 2;
	if ((m_BottomRight.y - m_StartPoint.y) < 2)
		m_BottomRight.y = m_StartPoint.y + 2;

	m_EnclosingRect = CRect(m_StartPoint, m_BottomRight);
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

CRectangle::~CRectangle()
{
}
