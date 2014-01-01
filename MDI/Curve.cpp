#include "stdafx.h"
#include <algorithm>
#include "Curve.h"


CCurve::CCurve()
{
}

CCurve::CCurve(const CPoint& first, const CPoint& second, COLORREF color) : CElement(first, color)
{
	m_Points.push_back(second);
	m_EnclosingRect = CRect((std::min)(first.x, second.x), (std::min)(first.y, second.y), (std::max)(first.x, second.x), (std::max)(first.y, second.y));
	
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

CCurve::~CCurve()
{
}
