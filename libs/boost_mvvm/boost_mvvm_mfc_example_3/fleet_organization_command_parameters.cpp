//
//  fleet_organization_command_parameters.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "fleet_organization_command_parameters.hpp"

fleet_organization_command_parameters::~fleet_organization_command_parameters()
{
}

fleet_organization_command_parameters::fleet_organization_command_parameters(const fleet_organization_id_type& id_)
    : m::command_parameters()
    , id(id_)
{
}

fleet_organization_command_parameters::fleet_organization_command_parameters()
    : m::command_parameters()
    , id(0)
{
}

fleet_organization_command_parameters::ptr fleet_organization_command_parameters::create(const fleet_organization_id_type& id_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const fleet_organization_id_type& id_) : this_type(id_) {}
    };

    return boost::make_shared<make_shared_enabler, const fleet_organization_id_type&>(id_);
#else
    return boost::shared_ptr<this_type>(new this_type(id_));
#endif // BOOST_MSVC > 1500
}
