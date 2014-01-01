#pragma once
#include "Element.h"
#include <vector>
class CCurve :
	public CElement
{
public:
	virtual ~CCurve();

	CCurve(const CPoint& start, const CPoint& end, COLORREF color);

	void AddSegment(const CPoint& point);                //Add segment to curve

protected:
	CCurve(void);

	std::vector<CPoint> m_Points;                      //Vector to contain points on curve


};

