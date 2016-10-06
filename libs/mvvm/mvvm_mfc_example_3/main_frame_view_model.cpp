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
#include "fleet_organization_view_model.hpp"

#include <functional>

namespace ph = std::placeholders;

main_frame_view_model::main_frame_view_model(const fleet_repository::ptr& fleet_repository_, const properties_view_model::ptr& properties_view_model_)
    : m::object_wobserver_interface()
    , u::noncopyable_nonmovable()
    , _fleet_repository(fleet_repository_)
    , _properties_view_model(properties_view_model_)
{
}

main_frame_view_model::ptr main_frame_view_model::create(const fleet_repository::ptr& fleet_repository_, const properties_view_model::ptr& properties_view_model_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const fleet_repository::ptr& fleet_repository_, const properties_view_model::ptr& properties_view_model_) : this_type(fleet_repository_, properties_view_model_) {}
    };

    return std::make_shared<make_shared_enabler, const fleet_repository::ptr&, const properties_view_model::ptr&>(fleet_repository_, properties_view_model_);
}

void main_frame_view_model::on_container_changed(const m::object::ptr& o, const std::shared_ptr<m::container_changed_arguments>& a)
{
    if(o && a)
    {
        // TODO
    }
}

void main_frame_view_model::on_property_changed(const m::object::ptr& o, const std::shared_ptr<m::wproperty_changed_arguments>& a)
{
    if(o && a)
    {
        if(a->property_name() == L"fleet_organization_view_model::selected_fleet_organization_id")
        {
            fleet_organization_view_model::ptr fleet_org_view_model = std::dynamic_pointer_cast<fleet_organization_view_model>(o);
            fleet_repository::ptr fleet_repo = _fleet_repository.lock();
            if(fleet_org_view_model && fleet_repo)
            {
                fleet_organization_interface::ptr selected_fleet_org = fleet_repo->fleet_organization_model(fleet_org_view_model->selected_fleet_organization_id.get());
                _properties_view_model->data_context.set(std::dynamic_pointer_cast<fleet_organization_model>(selected_fleet_org));
            }
        }
    }
}
