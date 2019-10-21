//
//  add_equipment_command_parameters.cpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "add_equipment_command_parameters.hpp"

add_equipment_command_parameters::~add_equipment_command_parameters()
{
}

add_equipment_command_parameters::add_equipment_command_parameters(const fleet_organization_id_type& spaceship_id_)
    : m::command_parameters()
    , spaceship_id(spaceship_id_)
{
}

add_equipment_command_parameters::add_equipment_command_parameters()
    : m::command_parameters()
    , spaceship_id(fleet_organization_id_type(0))
{
}

add_equipment_command_parameters::ptr add_equipment_command_parameters::create(const fleet_organization_id_type& spaceship_id_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const fleet_organization_id_type& spaceship_id_) : this_type(spaceship_id_) {}
    };

    return boost::make_shared<make_shared_enabler, const fleet_organization_id_type&>(spaceship_id_);
#else
    return boost::shared_ptr<this_type>(new this_type(spaceship_id_));
#endif // BOOST_MSVC > 1500
}
