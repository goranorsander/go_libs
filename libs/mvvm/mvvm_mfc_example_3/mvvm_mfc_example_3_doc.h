#ifndef GO_MVVM_EXAMPLE_3_DOC_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_DOC_H_INCLUDED

//
//  mvvm_mfc_example_3_doc.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

// mvvm_mfc_example_3_doc.h : interface of the mvvm_mfc_example_3_doc class
//


#pragma once


class mvvm_mfc_example_3_doc
    : public CDocument
{
public:
    virtual ~mvvm_mfc_example_3_doc();

protected:
    mvvm_mfc_example_3_doc();

	DECLARE_DYNCREATE(mvvm_mfc_example_3_doc)

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_DOC_H_INCLUDED
