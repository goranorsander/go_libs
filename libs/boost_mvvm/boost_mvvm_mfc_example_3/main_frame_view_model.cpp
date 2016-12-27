//
//  main_frame_view_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "main_frame_view_model.hpp"
#include "close_spaceship_event.hpp"
#include "fleet_organization_view_model.hpp"
#include "main_frame_view.hpp"
#include "boost_mvvm_mfc_example_3.hpp"
#include "show_spaceship_event.hpp"

main_frame_view_model::~main_frame_view_model()
{
    unsubscribe_events();
}

main_frame_view_model::main_frame_view_model(mdi_frame_interface::pointer mdi_frame_mgr, const m::wcommand_manager::ptr& command_mgr, const m::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo)
    : m::view_model_interface()
    , m::wobservable_object()
    , m::data_context_interface<fleet_repository::wptr>(fleet_repository::wptr(fleet_repo))
    , u::noncopyable_nonmovable()
    , mdi_frame_manager(mdi_frame_mgr)
    , command_manager(command_mgr)
    , event_manager(event_mgr)
    , fleet_repository(fleet_repo)
    , _close_spaceship_event_key(0)
    , _show_spaceship_event_key(0)
{
    subscribe_events();
}

main_frame_view_model::ptr main_frame_view_model::create(mdi_frame_interface::pointer mdi_frame_mgr, const m::wcommand_manager::ptr& command_mgr, const m::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(mdi_frame_interface::pointer mdi_frame_mgr, const m::wcommand_manager::ptr& command_mgr, const m::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo) : this_type(mdi_frame_mgr, command_mgr, event_mgr, fleet_repo) {}
    };

    return boost::make_shared<make_shared_enabler, mdi_frame_interface::pointer, const m::wcommand_manager::ptr&, const m::wevent_manager::ptr&, const fleet_repository::ptr&>(std::forward<mdi_frame_interface::pointer>(mdi_frame_mgr), command_mgr, event_mgr, fleet_repo);
}

void main_frame_view_model::on_data_context_will_change()
{
    m::data_context_interface<fleet_repository::wptr>::on_data_context_will_change();
    on_view_model_will_change();
}

void main_frame_view_model::on_data_context_changed()
{
    m::data_context_interface<fleet_repository::wptr>::on_data_context_changed();
    on_view_model_changed();
}

void main_frame_view_model::subscribe_events()
{
    m::wevent_manager::ptr event_mgr = event_manager();
    if(event_mgr)
    {
        _close_spaceship_event_key = event_mgr->subscribe(L"close spaceship event", boost::bind(&this_type::on_close_spaceship_event, this, _1));
        _show_spaceship_event_key = event_mgr->subscribe(L"show spaceship event", boost::bind(&this_type::on_show_spaceship_event, this, _1));
    }
}

void main_frame_view_model::unsubscribe_events()
{
    m::wevent_manager::ptr event_mgr = event_manager();
    if(event_mgr)
    {
        event_mgr->unsubscribe(L"close spaceship event", _close_spaceship_event_key);
        _close_spaceship_event_key = 0;
        event_mgr->unsubscribe(L"show spaceship event", _show_spaceship_event_key);
        _show_spaceship_event_key = 0;
    }
}

void main_frame_view_model::on_close_spaceship_event(const m::wevent::ptr& e)
{
    close_spaceship_event::ptr close_event = boost::dynamic_pointer_cast<close_spaceship_event>(e);
    if(close_event && close_event->spaceship_vm())
    {
        mdi_frame_interface::pointer mdi_frame_mgr = mdi_frame_manager;
        if(mdi_frame_mgr != NULL)
        {
            mdi_frame_mgr->on_close_spaceship(close_event->spaceship_vm()->spaceship_id());
        }
    }
}

void main_frame_view_model::on_show_spaceship_event(const m::wevent::ptr& e)
{
    show_spaceship_event::ptr show_event = boost::dynamic_pointer_cast<show_spaceship_event>(e);
    if(show_event && show_event->id > 0)
    {
        mdi_frame_interface::pointer mdi_frame_mgr = mdi_frame_manager;
        if(mdi_frame_mgr != NULL)
        {
            mdi_frame_mgr->on_show_spaceship(show_event->id);
        }
    }
}
