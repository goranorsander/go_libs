//
//  fleet_organization_view_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "fleet_organization_view_model.hpp"

#include <functional>

namespace ph = std::placeholders;

fleet_organization_view_model::fleet_organization_view_model()
    : m::wobservable_object()
    , m::data_context_interface<fleet_organization_model::ptr>(fleet_organization_model::create())
    , fleet_organization_root(L"fleet_organization_view_model::fleet_organization_root")
    , selected_fleet_organization_id(L"fleet_organization_view_model::selected_fleet_organization_id")
    , _selected_fleet_organization_id(0)
{
    bind_properties();
}

fleet_organization_view_model::ptr fleet_organization_view_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler() : this_type() {}
    };

    return std::make_shared<make_shared_enabler>();
}

void fleet_organization_view_model::bind_properties()
{
    fleet_organization_root.getter([this]() -> fleet_organization_model::ptr { if(*data_context) { return data_context; } return 0; });
    fleet_organization_root.setter([this](const fleet_organization_model::ptr& v) { if(*data_context) { data_context.set(v); on_property_changed(fleet_organization_root.name()); } });
    selected_fleet_organization_id.getter([this]() -> fleet_organization_id_type { return _selected_fleet_organization_id; });
    selected_fleet_organization_id.setter([this](const fleet_organization_id_type& v) { if(_selected_fleet_organization_id != v) { _selected_fleet_organization_id = v; on_property_changed(selected_fleet_organization_id.name()); } });
}
