#pragma once
#include "Element.h"
class CEllipse :
	public CElement
{
public:

	virtual void Draw(CDC* pDC);

	virtual ~CEllipse();
	CEllipse(const CPoint& start, const CPoint& end, COLORREF color);


protected:

	CEllipse(void);

	CPoint m_BottomRight;
};

