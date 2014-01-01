#pragma once
#include "Element.h"
class CCircle :
	public CElement
{
public:
	
	virtual ~CCircle();
	virtual void Draw(CDC* pDC);
	CCircle(const CPoint& start, const CPoint& end, COLORREF color);

protected:
	CCircle(void);
	CPoint m_BottomRight;
};

