//
//  properties_view_model.cpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "properties_view_model.hpp"
#include "fleet_repository.hpp"
#include "select_fleet_organization_event.hpp"

#include <functional>

properties_view_model::~properties_view_model()
{
    unsubscribe_events();
}

properties_view_model::properties_view_model()
    : m::view_model_interface<go::utility::recursive_spin_lock>()
    , m::wobservable_object()
    , m::data_context_interface<fleet_organization_model::ptr>(fleet_organization_model::create())
    , u::noncopyable_nonmovable()
    , main_frame_vm(L"properties_view_model::main_frame_vm")
    , fleet_organization(L"properties_view_model::fleet_organization")
    , _main_frame_vm()
    , _on_data_context_property_changed_slot_key()
    , _select_fleet_organization_event_key(0)
{
}

properties_view_model::ptr properties_view_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    properties_view_model::ptr view_model = std::make_shared<make_shared_enabler>();
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
        data_context()->property_changed.disconnect(_on_data_context_property_changed_slot_key);
        _on_data_context_property_changed_slot_key.reset();
    }
    m::data_context_interface<fleet_organization_model::ptr>::on_data_context_will_change();
    on_view_model_will_change();
}

void properties_view_model::on_data_context_changed()
{
    if(data_context())
    {
        _on_data_context_property_changed_slot_key = data_context()->property_changed.connect(std::bind(&properties_view_model::on_property_changed, this, ph::_1, ph::_2));
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
    main_frame_vm.getter([this]() -> main_frame_view_model::ptr { return _main_frame_vm.lock(); });
    main_frame_vm.setter([this](const main_frame_view_model::ptr& v) { if(_main_frame_vm.lock() != v) { unsubscribe_events(); _main_frame_vm = v; subscribe_events(); m::wobservable_object::notify_property_changed(this->shared_from_this(), main_frame_vm.name()); } });
    fleet_organization.getter([this]() -> fleet_organization_interface::ptr { return data_context(); });
}

void properties_view_model::subscribe_events()
{
    main_frame_view_model::ptr vm = _main_frame_vm.lock();
    if(vm)
    {
        m::wevent_manager::ptr event_mgr = vm->event_manager();
        if(event_mgr)
        {
            _select_fleet_organization_event_key = event_mgr->subscribe(L"select fleet organization event",
                [this](const m::wevent::ptr& e)
            {
                select_fleet_organization_event::ptr select_event = std::dynamic_pointer_cast<select_fleet_organization_event>(e);
                if(select_event && select_event->selected_by() != std::wstring(L"properties_view_model"))
                {
                    main_frame_view_model::ptr vm_ = _main_frame_vm.lock();
                    if(vm_)
                    {
                        fleet_repository::ptr fleet_repo = std::dynamic_pointer_cast<fleet_repository>(vm_->fleet_repository());
                        if(fleet_repo)
                        {
                            fleet_organization_model::ptr fleet_org = std::dynamic_pointer_cast<fleet_organization_model>(fleet_repo->fleet_organization_model(select_event->id));
                            if(fleet_org)
                            {
                                data_context = fleet_org;
                            }
                        }
                    }
                }
            });
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
            _select_fleet_organization_event_key = 0;
        }
    }
}
