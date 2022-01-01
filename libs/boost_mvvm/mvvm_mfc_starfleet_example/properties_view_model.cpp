//
//  properties_view_model.cpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "properties_view_model.hpp"
#include "fleet_repository.hpp"
#include "select_fleet_organization_event.hpp"

properties_view_model::~properties_view_model()
{
    unsubscribe_events();
}

properties_view_model::properties_view_model()
    : m::view_model_interface<a::placebo_lockable>()
    , m::wobservable_object()
    , m::data_context_interface<fleet_organization_model::ptr>(fleet_organization_model::create())
    , tt::noncopyable_nonmovable()
    , main_frame_vm(L"properties_view_model::main_frame_vm")
    , fleet_organization(L"properties_view_model::fleet_organization")
    , _main_frame_vm()
    , _select_fleet_organization_event_key(0)
    , _on_data_context_property_changed_connection()
{
}

properties_view_model::ptr properties_view_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    properties_view_model::ptr view_model = boost::make_shared<make_shared_enabler>();
    view_model->bind_properties();
    return view_model;
}

void properties_view_model::set_data_context(const fleet_organization_model::ptr& context)
{
    data_context = context;
}

void properties_view_model::on_data_context_will_change()
{
    if(data_context())
    {
        _on_data_context_property_changed_connection.disconnect();
    }
    m::data_context_interface<fleet_organization_model::ptr>::on_data_context_will_change();
    on_view_model_will_change();
}

void properties_view_model::on_data_context_changed()
{
    if(data_context())
    {
        _on_data_context_property_changed_connection = data_context()->property_changed.connect(boost::bind(&properties_view_model::on_property_changed, this, boost::placeholders::_1, boost::placeholders::_2));
    }
    m::data_context_interface<fleet_organization_model::ptr>::on_data_context_changed();
    on_view_model_changed();
}

void properties_view_model::on_container_changed(const m::object::ptr& /*o*/, const m::container_changed_arguments::ptr& /*a*/)
{
}

void properties_view_model::on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
{
    if(o && a && !property_changed.empty())
    {
        property_changed(o, a);
    }
}

void properties_view_model::bind_properties()
{
    main_frame_vm.getter(boost::bind(&this_type::get_main_frame_vm, this));
    main_frame_vm.setter(boost::bind(&this_type::set_main_frame_vm, this, boost::placeholders::_1));
    fleet_organization.getter(boost::bind(&this_type::get_fleet_organization, this));
}

void properties_view_model::subscribe_events()
{
    main_frame_view_model::ptr vm = _main_frame_vm.lock();
    if(vm)
    {
        m::wevent_manager::ptr event_mgr = vm->event_manager();
        if(event_mgr)
        {
            _select_fleet_organization_event_key = event_mgr->subscribe(L"select fleet organization event", boost::bind(&this_type::on_select_fleet_organization_event, this, boost::placeholders::_1));
        }
    }
}

void properties_view_model::unsubscribe_events()
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

void properties_view_model::on_select_fleet_organization_event(const m::wevent::ptr& e)
{
    select_fleet_organization_event::ptr select_event = boost::dynamic_pointer_cast<select_fleet_organization_event>(e);
    if(select_event && select_event->selected_by() != std::wstring(L"properties_view_model"))
    {
        main_frame_view_model::ptr vm_ = _main_frame_vm.lock();
        if(vm_)
        {
            fleet_repository::ptr fleet_repo = boost::dynamic_pointer_cast<fleet_repository>(vm_->fleet_repository());
            if(fleet_repo)
            {
                fleet_organization_model::ptr fleet_org = boost::dynamic_pointer_cast<fleet_organization_model>(fleet_repo->fleet_organization_model(select_event->id));
                if(fleet_org)
                {
                    data_context = fleet_org;
                }
            }
        }
    }
}

main_frame_view_model::ptr properties_view_model::get_main_frame_vm() const
{
    return _main_frame_vm.lock();
}

void properties_view_model::set_main_frame_vm(const main_frame_view_model::ptr& v)
{
    if(_main_frame_vm.lock() != v)
    {
        unsubscribe_events();
        _main_frame_vm = v;
        subscribe_events();
        m::wobservable_object::notify_property_changed(this->shared_from_this(), main_frame_vm.name());
    }
}

fleet_organization_interface::ptr properties_view_model::get_fleet_organization() const
{
    if(*data_context)
    {
        return data_context();
    }
    return fleet_organization_interface::ptr();
}
