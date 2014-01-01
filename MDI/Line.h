#pragma once
#include "Element.h"
class CLine :
	public CElement
{
public:
	virtual ~CLine();
	virtual void Draw(CDC* pDC) override;

	CLine(const CPoint& start, const CPoint& end, COLORREF aColor);

protected:
	CPoint m_EndPoint;

	CLine(void);
};

