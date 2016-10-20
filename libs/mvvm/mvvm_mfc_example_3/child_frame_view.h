#ifndef GO_MVVM_EXAMPLE_3_CHILD_FRAME_VIEW_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_CHILD_FRAME_VIEW_H_INCLUDED

//
//  child_frame_view.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

// child_frame_view.h : interface of the child_frame_view class
//

#pragma once

#include "spaceship_view.h"

class child_frame_view
    : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(child_frame_view)
public:
    virtual ~child_frame_view();
    child_frame_view();

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    afx_msg void OnFileClose();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    DECLARE_MESSAGE_MAP()

public:
    spaceship_view _wndView;
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_CHILD_FRAME_VIEW_H_INCLUDED
