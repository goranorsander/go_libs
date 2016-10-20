#ifndef GO_SPACESHIP_VIEW_H_INCLUDED
#define GO_SPACESHIP_VIEW_H_INCLUDED

//
//  spaceship_view.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

// spaceship_view.h : interface of the spaceship_view class
//

#pragma once

class spaceship_view
    : public CFormView
{
public:
    virtual ~spaceship_view();

    spaceship_view();

protected:
    DECLARE_DYNCREATE(spaceship_view)

public:
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MVVM_EXAMPLE_3_FORM };
#endif

public:
    virtual BOOL DestroyWindow();
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual void OnInitialUpdate();

public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual void PostNcDestroy();

    DECLARE_MESSAGE_MAP()
};

#endif  // #ifndef GO_SPACESHIP_VIEW_H_INCLUDED
