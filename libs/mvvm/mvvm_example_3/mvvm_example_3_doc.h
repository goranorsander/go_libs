#ifndef GO_MVVM_EXAMPLE_3_DOC_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_DOC_H_INCLUDED

//
//  mvvm_example_3_doc.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

// mvvm_example_3_doc.h : interface of the mvvm_example_3_doc class
//


#pragma once


class mvvm_example_3_doc : public CDocument
{
protected: // create from serialization only
	mvvm_example_3_doc();
	DECLARE_DYNCREATE(mvvm_example_3_doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~mvvm_example_3_doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_DOC_H_INCLUDED
