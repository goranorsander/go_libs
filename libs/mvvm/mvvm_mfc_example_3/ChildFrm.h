#ifndef GO_MVVM_EXAMPLE_3_CHILDFRM_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_CHILDFRM_H_INCLUDED

//
//  ChildFrm.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

// ChildFrame.h : interface of the CChildFrame class
//

#pragma once

class CChildFrame
    : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
    virtual ~CChildFrame();
    CChildFrame();

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_CHILDFRM_H_INCLUDED
