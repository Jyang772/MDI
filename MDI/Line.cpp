#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(const CPoint& start, const CPoint& end, COLORREF aColor)
{
	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);

}

CLine::~CLine()
{
}

void CLine::Draw(CDC* pDC)
{
	CPen aPen;
	CElement::CreatePen(aPen);

	CPen* pOldPen = pDC->SelectObject(&aPen);

	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);
}