#ifndef GO_MVVM_EXAMPLE_3_PROPERTIES_VIEW_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_PROPERTIES_VIEW_H_INCLUDED

//
//  properties_view.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "properties_view_model.hpp"
#include "properties_view_grid.h"
#include "properties_view_tool_bar.h"

class properties_view
    : public CDockablePane
    , public m::data_context_interface<properties_view_model::ptr>
    , public m::object_wobserver_interface
{
public:
    virtual ~properties_view() = default;
    properties_view();

	void AdjustLayout();

public:
	void SetVSDotNetLook(BOOL bSet)
	{
		_wndPropList.SetVSDotNetLook(bSet);
		_wndPropList.SetGroupNameFullWidth(bSet);
	}

    virtual void on_view_model_changing(const m::view_model_changing_arguments::ptr& a);
    virtual void on_view_model_changed(const m::view_model_changed_arguments::ptr& a);

protected:
    virtual void on_data_context_changing();
    virtual void on_data_context_changed();
    virtual void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a);
    virtual void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a);

    void populate();

private:
    void populate_with(const fleet_organization_interface::ptr& fleet_organization);
    void populate_with(const spaceship_interface::ptr& spaceship);
    void populate_with(const m::wobservable_list<equipment_interface::ptr>::ptr& equipment);

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
    s::slot_key_type _on_data_context_property_changed_slot_key;
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_PROPERTIES_VIEW_H_INCLUDED
