#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_FLEET_ORGANIZATION_VIEW_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_FLEET_ORGANIZATION_VIEW_HPP_INCLUDED

//
//  fleet_organization_view.hpp
//
//  Copyright 2016-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "fleet_organization_view_model.hpp"
#include "fleet_organization_view_tool_bar.hpp"
#include "tree_control.hpp"

class fleet_organization_view
    : public CDockablePane
    , public m::data_context_interface<fleet_organization_view_model::ptr>
    , public tree_control_observer
{
public:
    virtual ~fleet_organization_view() GO_DEFAULT_DESTRUCTOR

    fleet_organization_view();

    void AdjustLayout();
    void OnChangeVisualStyle();

public:
    virtual void on_selected(const HTREEITEM hItem, DWORD_PTR pItemData) override;
    virtual void on_deselect(const HTREEITEM hItem, DWORD_PTR pItemData) override;
    virtual void on_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton) override;
    virtual void on_double_click(const HTREEITEM hItem, DWORD_PTR pItemData, const CPoint& screenPos, const MouseButton mouseButton) override;

    virtual void on_view_model_will_change(const m::view_model_will_change_arguments::ptr& a);
    virtual void on_view_model_changed(const m::view_model_changed_arguments::ptr& a);

protected:
    virtual void on_data_context_will_change() override;
    virtual void on_data_context_changed() override;

    void populate();

    void add_fleet_organization(HTREEITEM parent, const fleet_organization_interface::ptr& child);

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    afx_msg void OnSetFocus(CWnd* pOldWnd);

    DECLARE_MESSAGE_MAP()

protected:
    std::unique_ptr<tree_control> _wndFileView;
    CImageList _fileViewImages;
    fleet_organization_view_tool_bar _wndToolBar;
};

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_FLEET_ORGANIZATION_VIEW_HPP_INCLUDED
