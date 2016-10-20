//
//  spaceship_view.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "spaceship_view.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mvvm_mfc_example_3.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(spaceship_view, CFormView)

spaceship_view::~spaceship_view()
{
}

spaceship_view::spaceship_view()
    : CFormView(IDD_MVVM_EXAMPLE_3_FORM)
{
}

void spaceship_view::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
}

BOOL spaceship_view::DestroyWindow()
{
    return CFormView::DestroyWindow();
}

BOOL spaceship_view::PreCreateWindow(CREATESTRUCT& cs)
{
    return CFormView::PreCreateWindow(cs);
}

BOOL spaceship_view::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void spaceship_view::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    ResizeParentToFit();
}

#ifdef _DEBUG
void spaceship_view::AssertValid() const
{
    CFormView::AssertValid();
}

void spaceship_view::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}
#endif //_DEBUG

void spaceship_view::PostNcDestroy()
{
    // Disable CFormView::PostNcDestroy() from doing 'delete this;' causing '~spaceship_view()' to be called twice 
}

BEGIN_MESSAGE_MAP(spaceship_view, CFormView)
END_MESSAGE_MAP()
