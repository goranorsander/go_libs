#ifndef GO_BOOST_SPACESHIP_VIEW_H_INCLUDED
#define GO_BOOST_SPACESHIP_VIEW_H_INCLUDED
#include "afxwin.h"

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

#include "spaceship_view_model.hpp"

class spaceship_view
    : public CFormView
    , public m::data_context_interface<spaceship_view_model::ptr>
{
public:
    virtual ~spaceship_view();

    spaceship_view();

protected:
    DECLARE_DYNCREATE(spaceship_view)

public:
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SPACESHIP_VIEW };
#endif

public:
    virtual BOOL DestroyWindow();
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
    virtual BOOL PreTranslateMessage(MSG* pMsg);

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

public:
    void initialization_complete();

    void on_close() const;
    void on_activate() const;
    void on_deactivate() const;

    virtual void on_view_model_will_change(const m::view_model_will_change_arguments::ptr& a);
    virtual void on_view_model_changed(const m::view_model_changed_arguments::ptr& a);

protected:
    virtual void on_data_context_will_change();
    virtual void on_data_context_changed();

private:
    void on_view_model_changed();

private:
    bool _initialization_complete;
    CStatic _spaceship_class_static;
    CStatic _spaceship_name_static;
};

#endif  // #ifndef GO_BOOST_SPACESHIP_VIEW_H_INCLUDED
