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


class mvvm_example_3_view : public CView
{
protected: // create from serialization only
	mvvm_example_3_view();
	DECLARE_DYNCREATE(mvvm_example_3_view)

// Attributes
public:
	mvvm_example_3_doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~mvvm_example_3_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mvvm_example_3_view.cpp
inline mvvm_example_3_doc* mvvm_example_3_view::GetDocument() const
   { return reinterpret_cast<mvvm_example_3_doc*>(m_pDocument); }
#endif

#endif  // #ifndef GO_MVVM_EXAMPLE_3_VIEW_H_INCLUDED
