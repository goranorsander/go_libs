//
//  mvvm_mfc_example_3_view.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "mvvm_mfc_example_3_view.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mvvm_mfc_example_3.h"
#endif

#include "mvvm_mfc_example_3_doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(mvvm_mfc_example_3_view, CFormView)

BEGIN_MESSAGE_MAP(mvvm_mfc_example_3_view, CFormView)
END_MESSAGE_MAP()

mvvm_mfc_example_3_view::~mvvm_mfc_example_3_view()
{
}

mvvm_mfc_example_3_view::mvvm_mfc_example_3_view()
    : CFormView(IDD_MVVM_EXAMPLE_3_FORM)
{
}

void mvvm_mfc_example_3_view::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
}

BOOL mvvm_mfc_example_3_view::PreCreateWindow(CREATESTRUCT& cs)
{
    return CFormView::PreCreateWindow(cs);
}

void mvvm_mfc_example_3_view::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    ResizeParentToFit();
}

#ifdef _DEBUG
void mvvm_mfc_example_3_view::AssertValid() const
{
    CFormView::AssertValid();
}

void mvvm_mfc_example_3_view::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

mvvm_mfc_example_3_doc* mvvm_mfc_example_3_view::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(mvvm_mfc_example_3_doc)));
    return (mvvm_mfc_example_3_doc*)m_pDocument;
}
#endif //_DEBUG
