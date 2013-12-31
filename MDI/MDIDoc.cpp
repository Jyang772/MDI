
// MDIDoc.cpp : implementation of the CMDIDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MDI.h"
#endif

#include "MDIDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMDIDoc

IMPLEMENT_DYNCREATE(CMDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDIDoc, CDocument)
	ON_COMMAND(ID_COLOR_BLACK, &CMDIDoc::OnColorBlack)
	ON_COMMAND(ID_COLOR_RED, &CMDIDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CMDIDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CMDIDoc::OnColorBlue)
	ON_COMMAND(ID_ELEMENT_LINE, &CMDIDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CMDIDoc::OnElementRectangle)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CMDIDoc::OnElementCircle)
	ON_COMMAND(ID_ELEMENT_CURVE, &CMDIDoc::OnElementCurve)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CMDIDoc::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CMDIDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CMDIDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CMDIDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CMDIDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CMDIDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CMDIDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CMDIDoc::OnUpdateElementCurve)	
	ON_COMMAND(ID_ELEMENT_ELLIPSE, &CMDIDoc::OnElementEllipse)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_ELLIPSE, &CMDIDoc::OnUpdateElementEllipse)
END_MESSAGE_MAP()


// CMDIDoc construction/destruction

CMDIDoc::CMDIDoc() : m_Element(ElementType::LINE), m_Color(ElementColor::BLACK)
{
	
	// TODO: add one-time construction code here
}

CMDIDoc::~CMDIDoc()
{
}

BOOL CMDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMDIDoc serialization

void CMDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMDIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMDIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMDIDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMDIDoc diagnostics

#ifdef _DEBUG
void CMDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMDIDoc commands


void CMDIDoc::OnColorBlack()
{
	m_Color = ElementColor::BLACK;
	
	// TODO: Add your command handler code here
}


void CMDIDoc::OnColorRed()
{
	m_Color = ElementColor::RED;
	// TODO: Add your command handler code here
}


void CMDIDoc::OnColorGreen()
{
	m_Color = ElementColor::GREEN;
	// TODO: Add your command handler code here
}


void CMDIDoc::OnColorBlue()
{
	m_Color = ElementColor::BLUE;
	// TODO: Add your command handler code here
}


void CMDIDoc::OnElementLine()
{
	m_Element = ElementType::LINE;
	// TODO: Add your command handler code here
}


void CMDIDoc::OnElementRectangle()
{
	m_Element = ElementType::RECTANGLE;
	// TODO: Add your command handler code here
}


void CMDIDoc::OnElementCircle()
{
	m_Element = ElementType::CIRCLE;

}


void CMDIDoc::OnElementCurve()
{
	m_Element = ElementType::CURVE;
}

void CMDIDoc::OnElementEllipse()
{
	m_Element = ElementType::ELLIPSE;
}



void CMDIDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColor::BLACK);
}


void CMDIDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColor::RED);
}


void CMDIDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColor::GREEN);
}


void CMDIDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColor::BLUE);
	//pCmdUI->SetText(L"Blue");                    //Set Text to uppercase when selected
}


void CMDIDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::LINE);
}


void CMDIDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::RECTANGLE);
}


void CMDIDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::CIRCLE);
}


void CMDIDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::CURVE);
}


void CMDIDoc::OnUpdateElementEllipse(CCmdUI *pCmdUI)
{

	pCmdUI->SetCheck(m_Element == ElementType::ELLIPSE);
}
