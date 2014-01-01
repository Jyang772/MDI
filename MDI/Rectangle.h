#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
public:
	
	virtual ~CRectangle();
	//virtual void Draw(CDC* pDC);
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color);

protected:

	CPoint m_BottomRight;
	CRectangle(void);

};

