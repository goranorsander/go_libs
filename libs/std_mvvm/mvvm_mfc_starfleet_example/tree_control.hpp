#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_TREE_CONTROL_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_TREE_CONTROL_HPP_INCLUDED

//
//  tree_control.hpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "tree_control_observer.hpp"

class tree_control
    : public CTreeCtrl
{
public:
    virtual ~tree_control() GO_DEFAULT_DESTRUCTOR
    explicit tree_control(tree_control_observer* observer);

protected:
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
    afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);

    CPoint GetClickPos() const;

protected:
    DECLARE_MESSAGE_MAP()

private:
    tree_control_observer* _observer;
    HTREEITEM _hSelectedItem;
};

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_TREE_CONTROL_HPP_INCLUDED
