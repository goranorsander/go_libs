#ifndef GO_BOOST_MVVM_EXAMPLE_3_OUTPUT_VIEW_LIST_HPP_INCLUDED
#define GO_BOOST_MVVM_EXAMPLE_3_OUTPUT_VIEW_LIST_HPP_INCLUDED

//
//  output_view_list.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

class output_view_list
    : public CListBox
{
public:
    virtual ~output_view_list();
    output_view_list();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

#endif  // #ifndef GO_BOOST_MVVM_EXAMPLE_3_OUTPUT_VIEW_LIST_HPP_INCLUDED
