#ifndef GO_MVVM_EXAMPLE_3_VIEW_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_VIEW_H_INCLUDED

//
//  mvvm_example_3_view.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

// mvvm_example_3_view.h : interface of the mvvm_example_3_view class
//

#pragma once

#include "mvvm_example_3_doc.h"

class mvvm_example_3_view
    : public CFormView
{
public:
    virtual ~mvvm_example_3_view();

protected:
    mvvm_example_3_view();

    DECLARE_DYNCREATE(mvvm_example_3_view)

public:
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MVVM_EXAMPLE_3_FORM };
#endif

public:
    mvvm_example_3_doc* GetDocument() const;

public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual void OnInitialUpdate();

public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CFormViewMDIView.cpp
inline mvvm_example_3_doc* mvvm_example_3_view::GetDocument() const
{
    return reinterpret_cast<mvvm_example_3_doc*>(m_pDocument);
}
#endif

#endif  // #ifndef GO_MVVM_EXAMPLE_3_VIEW_H_INCLUDED
