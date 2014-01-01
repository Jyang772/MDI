#pragma once
#include "afx.h"
class CElement :
	public CObject
{
public:	
		virtual void Draw(CDC* pDC){}
		virtual ~CElement();

		const CRect& GetEnclosingRect() const { return m_EnclosingRect; }

protected:
	CPoint m_StartPoint;           //Element Position
	int m_PenWidth;                //Pen Width
	COLORREF m_Color;              //Color of element
	CRect m_EnclosingRect;         //Enclosing rectangle

	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);
};

