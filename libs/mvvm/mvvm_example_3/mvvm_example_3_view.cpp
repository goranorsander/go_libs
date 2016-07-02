//
//  mvvm_example_3_view.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mvvm_example_3.h"
#endif

#include "mvvm_example_3_doc.h"
#include "mvvm_example_3_view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// mvvm_example_3_view

IMPLEMENT_DYNCREATE(mvvm_example_3_view, CView)

BEGIN_MESSAGE_MAP(mvvm_example_3_view, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// mvvm_example_3_view construction/destruction

mvvm_example_3_view::mvvm_example_3_view()
{
	// TODO: add construction code here

}

mvvm_example_3_view::~mvvm_example_3_view()
{
}

BOOL mvvm_example_3_view::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// mvvm_example_3_view drawing

void mvvm_example_3_view::OnDraw(CDC* /*pDC*/)
{
	mvvm_example_3_doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void mvvm_example_3_view::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void mvvm_example_3_view::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// mvvm_example_3_view diagnostics

#ifdef _DEBUG
void mvvm_example_3_view::AssertValid() const
{
	CView::AssertValid();
}

void mvvm_example_3_view::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

mvvm_example_3_doc* mvvm_example_3_view::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(mvvm_example_3_doc)));
	return (mvvm_example_3_doc*)m_pDocument;
}
#endif //_DEBUG


// mvvm_example_3_view message handlers
