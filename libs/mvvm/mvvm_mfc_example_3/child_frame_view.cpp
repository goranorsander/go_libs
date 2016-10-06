//
//  child_frame_view.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "child_frame_view.h"
#include "mvvm_mfc_example_3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(child_frame_view, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(child_frame_view, CMDIChildWndEx)
END_MESSAGE_MAP()

child_frame_view::~child_frame_view()
{
}

child_frame_view::child_frame_view()
{
}


BOOL child_frame_view::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

#ifdef _DEBUG
void child_frame_view::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void child_frame_view::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG
