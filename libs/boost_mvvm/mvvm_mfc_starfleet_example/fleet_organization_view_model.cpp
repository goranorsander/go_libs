//
//  fleet_organization_view_model.cpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "fleet_organization_view_model.hpp"
#include "fleet_organization_command_parameters.hpp"
#include "fleet_organization_model.hpp"
#include "select_fleet_organization_event.hpp"
#include "show_spaceship_event.hpp"
#include "spaceship_model.hpp"

namespace
{

bool is_spaceship(const fleet_organization_interface::ptr& fleet_org, const fleet_organization_id_type id)
{
    fleet_organization_model::ptr fleet_org_ = boost::dynamic_pointer_cast<fleet_organization_model>(fleet_org);
    if(fleet_org_)
    {
        if(fleet_org_->id == id)
        {
            return fleet_org_->spaceship_model() != NULL;
        }
        bool is_spaceship_ = is_spaceship(fleet_org->first_child(), id);
        if(is_spaceship_) { return true; }
        is_spaceship_ = is_spaceship(fleet_org->next_sibling(), id);
        if(is_spaceship_) { return true; }
    }
    return false;
}

}

fleet_organization_view_model::~fleet_organization_view_model()
{
    unsubscribe_events();
}

fleet_organization_view_model::fleet_organization_view_model()
    : m::view_model_interface<u::placebo_lockable>()
    , m::wobservable_object()
    , m::data_context_interface<fleet_organization_interface::ptr>(fleet_organization_model::create())
    , u::noncopyable_nonmovable()
    , main_frame_vm(L"fleet_organization_view_model::main_frame_vm")
    , selected_fleet_organization_id(L"fleet_organization_view_model::selected_fleet_organization_id")
    , on_left_double_click_command(L"fleet_organization_view_model::on_left_double_click_command")
    , fleet_organization_root()
    , _main_frame_vm()
    , _selected_fleet_organization_id(0)
    , _on_left_double_click_command()
    , _select_fleet_organization_event_key(0)
{
}

fleet_organization_view_model::ptr fleet_organization_view_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    fleet_organization_view_model::ptr view_model = boost::make_shared<make_shared_enabler>();
    view_model->bind_properties();
    return view_model;
}

void fleet_organization_view_model::set_data_context(const fleet_organization_interface::ptr& context)
{
    data_context = context;
}

void fleet_organization_view_model::on_data_context_will_change()
{
    m::data_context_interface<fleet_organization_interface::ptr>::on_data_context_will_change();
    on_view_model_will_change();
}

void fleet_organization_view_model::on_data_context_changed()
{
    m::data_context_interface<fleet_organization_interface::ptr>::on_data_context_changed();
    on_view_model_changed();
}

void fleet_organization_view_model::bind_properties()
{
    main_frame_vm.getter(boost::bind(&this_type::get_main_frame_vm, this));
    main_frame_vm.setter(boost::bind(&this_type::set_main_frame_vm, this, _1));
    selected_fleet_organization_id.getter(boost::bind(&this_type::get_property_value<fleet_organization_id_type>, this, boost::cref(_selected_fleet_organization_id)));
    selected_fleet_organization_id.setter(boost::bind(&this_type::set_selected_fleet_organization_id, this, _1));
    on_left_double_click_command.getter(boost::bind(&this_type::get_on_left_double_click_command, this));
    fleet_organization_root.getter(boost::bind(&this_type::get_fleet_organization_root, this));
}

void fleet_organization_view_model::subscribe_events()
{
    main_frame_view_model::ptr vm = _main_frame_vm.lock();
    if(vm)
    {
        m::wevent_manager::ptr event_mgr = vm->event_manager();
        if(event_mgr)
        {
            _select_fleet_organization_event_key = event_mgr->subscribe(L"select fleet organization event", boost::bind(&this_type::on_select_fleet_organization_event, this, _1));
        }
    }
}

void fleet_organization_view_model::unsubscribe_events()
{
    main_frame_view_model::ptr vm = _main_frame_vm.lock();
    if(vm)
    {
        m::wevent_manager::ptr event_mgr = vm->event_manager();
        if(event_mgr)
        {
            event_mgr->unsubscribe(L"select fleet organization event", _select_fleet_organization_event_key);
            m::reset(_select_fleet_organization_event_key);
        }
    }
}

void fleet_organization_view_model::on_select_fleet_organization_event(const m::wevent::ptr& e)
{
    select_fleet_organization_event::ptr select_event = boost::dynamic_pointer_cast<select_fleet_organization_event>(e);
    if(select_event && select_event->selected_by() != std::wstring(L"fleet_organization_view_model"))
    {
        if(_selected_fleet_organization_id != select_event->id)
        {
            _selected_fleet_organization_id = select_event->id;
            notify_property_changed(this->shared_from_this(), selected_fleet_organization_id.name());
        }
    }
}

main_frame_view_model::ptr fleet_organization_view_model::get_main_frame_vm() const
{
    return _main_frame_vm.lock();
}

void fleet_organization_view_model::set_main_frame_vm(const main_frame_view_model::ptr& v)
{
    if(_main_frame_vm.lock() != v)
    {
        unsubscribe_events();
        _main_frame_vm = v;
        subscribe_events();
        notify_property_changed(this->shared_from_this(), main_frame_vm.name());
    }
}

void fleet_organization_view_model::set_selected_fleet_organization_id(const fleet_organization_id_type& v)
{
    if(_selected_fleet_organization_id != v)
    {
        _selected_fleet_organization_id = v;
        notify_property_changed(this->shared_from_this(), selected_fleet_organization_id.name());
        main_frame_view_model::ptr vm = _main_frame_vm.lock();
        if(vm)
        {
            m::wevent_manager::ptr event_mgr = vm->event_manager();
            if(event_mgr)
            {
                event_mgr->post(select_fleet_organization_event::create(_selected_fleet_organization_id, L"fleet_organization_view_model"));
            }
        }
    }
}

fleet_organization_interface::ptr fleet_organization_view_model::get_fleet_organization_root() const
{
    if(*data_context)
    {
        return data_context;
    }
    return fleet_organization_interface::ptr();
}

m::wcommand_interface::ptr fleet_organization_view_model::get_on_left_double_click_command()
{
    _on_left_double_click_command = m::relay_wcommand::create(L"fleet_organization_view_model::on_left_double_click",
        boost::bind(&this_type::execute_on_left_double_click_command, this, _1),
        boost::bind(&this_type::can_execute_on_left_double_click_command, this, _1),
        fleet_organization_command_parameters::create(_selected_fleet_organization_id));
    return _on_left_double_click_command;
}

bool fleet_organization_view_model::can_execute_on_left_double_click_command(const m::command_parameters::ptr& p)
{
    fleet_organization_command_parameters::ptr params = boost::dynamic_pointer_cast<fleet_organization_command_parameters>(p);
    if(params)
    {
        return params->id > 0;
    }
    return false;
}

void fleet_organization_view_model::execute_on_left_double_click_command(const m::command_parameters::ptr& p)
{
    fleet_organization_command_parameters::ptr params = boost::dynamic_pointer_cast<fleet_organization_command_parameters>(p);
    if(params)
    {
        if(is_spaceship(*data_context, params->id))
        {
            main_frame_view_model::ptr vm = _main_frame_vm.lock();
            if(vm)
            {
                m::wevent_manager::ptr event_mgr = vm->event_manager();
                if(event_mgr)
                {
                    event_mgr->post(show_spaceship_event::create(params->id));
                }
            }
        }
    }
}
