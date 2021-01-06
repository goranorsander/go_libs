//
//  activate_spaceship_command_parameters.cpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "activate_spaceship_command_parameters.hpp"

activate_spaceship_command_parameters::~activate_spaceship_command_parameters()
{
}

activate_spaceship_command_parameters::activate_spaceship_command_parameters(const fleet_organization_id_type& id_)
    : m::command_parameters()
    , id(id_)
{
}

activate_spaceship_command_parameters::activate_spaceship_command_parameters()
    : m::command_parameters()
    , id(fleet_organization_id_type(0ull))
{
}

activate_spaceship_command_parameters::ptr activate_spaceship_command_parameters::create(const fleet_organization_id_type& id_)
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
