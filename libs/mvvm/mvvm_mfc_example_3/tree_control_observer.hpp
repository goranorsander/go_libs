#ifndef GO_MVVM_EXAMPLE_3_TREE_CONTROL_OBSERVER_HPP_INCLUDED
#define GO_MVVM_EXAMPLE_3_TREE_CONTROL_OBSERVER_HPP_INCLUDED

//
//  tree_control_observer.hpp
//
//  Copyright 2016-2017 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
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

inline tree_control_observer::~tree_control_observer()
{
}

#endif  // #ifndef GO_MVVM_EXAMPLE_3_TREE_CONTROL_OBSERVER_HPP_INCLUDED
