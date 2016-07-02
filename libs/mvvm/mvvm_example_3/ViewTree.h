#ifndef GO_MVVM_EXAMPLE_3_VIEWTREE_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_VIEWTREE_H_INCLUDED

//
//  ViewTree.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree window

class CViewTree : public CTreeCtrl
{
// Construction
public:
	CViewTree();

// Overrides
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementation
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_VIEWTREE_H_INCLUDED
