#ifndef GO_BOOST_MVVM_EXAMPLE_3_OUTPUT_VIEW_HPP_INCLUDED
#define GO_BOOST_MVVM_EXAMPLE_3_OUTPUT_VIEW_HPP_INCLUDED

//
//  output_view.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go_boost/mvvm/command_execution_observer_interface.hpp>
#include <go_boost/mvvm/event_firing_observer_interface.hpp>
#include <go_boost/mvvm/object_observer_interface.hpp>
#include "output_view_list.hpp"

class output_view
    : public CDockablePane
    , public m::wcommand_execution_wobserver_interface
    , public m::object_wobserver_interface
{
public:
    virtual ~output_view();
    output_view();

    void UpdateFonts();

    virtual void on_command_executed(const m::wcommand_interface::ptr& c);
    virtual void on_command_not_executed(const m::wcommand_interface::ptr& c);

    virtual void on_event_fired(const m::wevent::ptr& e);

    virtual void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a);
    virtual void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a);

protected:
    CMFCTabCtrl _wndTabs;

    output_view_list _wndOutputAllMvvmEvents;
    output_view_list _wndOutputCommandEvents;
    output_view_list _wndOutputEventEvents;
    output_view_list _wndOutputObservableObjectEvents;

protected:
    void AdjustHorzScroll(CListBox& wndListBox);

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);

    DECLARE_MESSAGE_MAP()
};

#endif  // #ifndef GO_BOOST_MVVM_EXAMPLE_3_OUTPUT_VIEW_HPP_INCLUDED
