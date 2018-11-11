//
//  fleet_organization_view_model.cpp
//
//  Copyright 2016-2018 G�ran Orsander
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

#include <functional>

namespace
{

bool is_spaceship(const fleet_organization_interface::ptr& fleet_org, const fleet_organization_id_type id)
{
    fleet_organization_model::ptr fleet_org_ = std::dynamic_pointer_cast<fleet_organization_model>(fleet_org);
    if(fleet_org_)
    {
        if(fleet_org_->id == id)
        {
            return fleet_org_->spaceship_model() != nullptr;
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
    : m::view_model_interface<u::placebo_mutex>()
    , mst::wobservable_object()
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
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    fleet_organization_view_model::ptr view_model = std::make_shared<make_shared_enabler>();
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
    main_frame_vm.getter([this]() -> main_frame_view_model::ptr { return _main_frame_vm.lock(); });
    main_frame_vm.setter([this](const main_frame_view_model::ptr& v) { if(_main_frame_vm.lock() != v) { unsubscribe_events(); _main_frame_vm = v; subscribe_events(); notify_property_changed(this->shared_from_this(), main_frame_vm.name()); } });
    selected_fleet_organization_id.getter([this]() -> fleet_organization_id_type { return _selected_fleet_organization_id; });
    selected_fleet_organization_id.setter(
        [this](const fleet_organization_id_type& v)
        {
            if(_selected_fleet_organization_id != v)
            {
                _selected_fleet_organization_id = v;
                notify_property_changed(this->shared_from_this(), selected_fleet_organization_id.name());
                main_frame_view_model::ptr vm = _main_frame_vm.lock();
                if(vm)
                {
                    mst::wevent_manager::ptr event_mgr = vm->event_manager();
                    if(event_mgr)
                    {
                        event_mgr->post(select_fleet_organization_event::create(_selected_fleet_organization_id, L"fleet_organization_view_model"));
                    }
                }
            }
        });
    on_left_double_click_command.getter(
        [this]()
        {
            _on_left_double_click_command = mst::relay_wcommand::create(L"fleet_organization_view_model::on_left_double_click",
                [this](const m::command_parameters::ptr& p)
                {
                    fleet_organization_command_parameters::ptr params = std::dynamic_pointer_cast<fleet_organization_command_parameters>(p);
                    if(params)
                    {
                        if(is_spaceship(*data_context, params->id))
                        {
                            main_frame_view_model::ptr vm = _main_frame_vm.lock();
                            if(vm)
                            {
                                mst::wevent_manager::ptr event_mgr = vm->event_manager();
                                if(event_mgr)
                                {
                                    event_mgr->post(show_spaceship_event::create(params->id));
                                }
                            }
                        }
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    fleet_organization_command_parameters::ptr params = std::dynamic_pointer_cast<fleet_organization_command_parameters>(p);
                    if(params)
                    {
                        return params->id > 0;
                    }
                    return false;
                },
                fleet_organization_command_parameters::create(_selected_fleet_organization_id));
            return _on_left_double_click_command;
        });
    fleet_organization_root.getter([this]() -> fleet_organization_interface::ptr { if(*data_context) { return data_context; } return nullptr; });
}

void fleet_organization_view_model::subscribe_events()
{
    main_frame_view_model::ptr vm = _main_frame_vm.lock();
    if(vm)
    {
        mst::wevent_manager::ptr event_mgr = vm->event_manager();
        if(event_mgr)
        {
            _select_fleet_organization_event_key = event_mgr->subscribe(L"select fleet organization event",
                [this](const m::wevent::ptr& e)
                {
                    select_fleet_organization_event::ptr select_event = std::dynamic_pointer_cast<select_fleet_organization_event>(e);
                    if(select_event && select_event->selected_by() != std::wstring(L"fleet_organization_view_model"))
                    {
                        if(_selected_fleet_organization_id != select_event->id)
                        {
                            _selected_fleet_organization_id = select_event->id;
                            notify_property_changed(this->shared_from_this(), selected_fleet_organization_id.name());
                        }
                    }
                });
        }
    }
}

void fleet_organization_view_model::unsubscribe_events()
{
    main_frame_view_model::ptr vm = _main_frame_vm.lock();
    if(vm)
    {
        mst::wevent_manager::ptr event_mgr = vm->event_manager();
        if(event_mgr)
        {
            event_mgr->unsubscribe(L"select fleet organization event", _select_fleet_organization_event_key);
            _select_fleet_organization_event_key = 0;
        }
    }
}