//
//  remove_equipment_command_parameters.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "remove_equipment_command_parameters.hpp"

remove_equipment_command_parameters::remove_equipment_command_parameters(const fleet_organization_id_type& spaceship_id_, const equipment_id_type& equipment_id_)
    : m::command_parameters()
    , spaceship_id(spaceship_id_)
    , equipment_id(equipment_id_)
{
}

remove_equipment_command_parameters::ptr remove_equipment_command_parameters::create(const fleet_organization_id_type& spaceship_id_, const equipment_id_type& equipment_id_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const fleet_organization_id_type& spaceship_id_, const equipment_id_type& equipment_id_) : this_type(spaceship_id_, equipment_id_) {}
    };

    return std::make_shared<make_shared_enabler, const fleet_organization_id_type&>(spaceship_id_, equipment_id_);
}
