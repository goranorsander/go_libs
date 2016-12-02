#ifndef GO_MVVM_EXAMPLE_3_TREE_CONTROL_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_TREE_CONTROL_H_INCLUDED

//
//  tree_control.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

enum MouseButton
{
    mb_left = 0,
    mb_middle,
    mb_right,
    MouseButton_undefined = ~0
};

class tree_control_observer
{
public:
    virtual ~tree_control_observer() = 0;

protected:
    tree_control_observer() = default;

public:
    virtual void on_selected(const HTREEITEM hItem, DWORD_PTR pItemData) = 0;
    virtual void on_deselect(const HTREEITEM hItem, DWORD_PTR pItemData) = 0;
    virtual void on_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton) = 0;
    virtual void on_double_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton) = 0;
};

class tree_control
    : public CTreeCtrl
{
public:
    virtual ~tree_control() = default;
    tree_control(tree_control_observer* observer);

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
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

#endif  // #ifndef GO_MVVM_EXAMPLE_3_TREE_CONTROL_H_INCLUDED
