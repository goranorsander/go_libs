#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_PROPERTIES_VIEW_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_PROPERTIES_VIEW_HPP_INCLUDED

//
//  properties_view.hpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "properties_view_model.hpp"
#include "properties_view_grid.hpp"
#include "properties_view_tool_bar.hpp"

class properties_view
    : public CDockablePane
    , public m::data_context_interface<properties_view_model::ptr>
    , public m::object_wobserver_interface
{
public:
    virtual ~properties_view() GO_DEFAULT_DESTRUCTOR
    properties_view();

    void AdjustLayout();

public:
    void SetVSDotNetLook(BOOL bSet)
    {
        _wndPropList.SetVSDotNetLook(bSet);
        _wndPropList.SetGroupNameFullWidth(bSet);
    }

    virtual void on_view_model_will_change(const m::view_model_will_change_arguments::ptr& a);
    virtual void on_view_model_changed(const m::view_model_changed_arguments::ptr& a);

protected:
    virtual void on_data_context_will_change() override;
    virtual void on_data_context_changed() override;
    virtual void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a) override;
    virtual void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a) override;

    void populate();

private:
    void populate_with(const fleet_organization_interface::ptr& fleet_organization);
    void populate_with(const spaceship_interface::ptr& spaceship);
    void populate_with(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment);

protected:
    properties_view_tool_bar _wndToolBar;
    properties_view_grid _wndPropList;

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnExpandAllProperties();
    afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
    afx_msg void OnSortProperties();
    afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
    afx_msg void OnSetFocus(CWnd* pOldWnd);

    DECLARE_MESSAGE_MAP()

    void InitPropList();

private:
    s::slot_key _on_data_context_container_changed_slot_key;
    s::slot_key _on_data_context_property_changed_slot_key;
};

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_PROPERTIES_VIEW_HPP_INCLUDED
