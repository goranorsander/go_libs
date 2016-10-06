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

namespace ph = std::placeholders;

properties_view_model::properties_view_model(const fleet_repository_interface::ptr& fleet_repository_)
    : m::data_context_interface<fleet_organization_model::ptr>(fleet_organization_model::create())
    , u::noncopyable_nonmovable()
{
}

properties_view_model::ptr properties_view_model::create(const fleet_repository_interface::ptr& fleet_repository_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const fleet_repository_interface::ptr& fleet_repository_) : this_type(fleet_repository_) {}
    };

    return std::make_shared<make_shared_enabler, const fleet_repository_interface::ptr&>(fleet_repository_);
}
