//
//  properties_view_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "properties_view_model.hpp"

#include <functional>

properties_view_model::properties_view_model()
    : m::view_model_interface()
    , m::wobservable_object()
    , m::data_context_interface<fleet_organization_model::ptr>(fleet_organization_model::create())
    , u::noncopyable_nonmovable()
    , fleet_organization(L"properties_view_model::fleet_organization")
    , _on_data_context_property_changed_slot_key(0)
{
    bind_properties();
}

properties_view_model::ptr properties_view_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler() : this_type() {}
    };

    return std::make_shared<make_shared_enabler>();
}

void properties_view_model::set_data_context(const fleet_organization_model::ptr& context)
{
    data_context = context;
}

void properties_view_model::on_data_context_changing()
{
    if(data_context())
    {
        data_context()->property_changed.disconnect(_on_data_context_property_changed_slot_key);
        _on_data_context_property_changed_slot_key = 0;
    }
    m::data_context_interface<fleet_organization_model::ptr>::on_data_context_changing();
    on_view_model_changing();
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
    fleet_organization.getter([this]() -> fleet_organization_interface::ptr { return data_context(); });
}
