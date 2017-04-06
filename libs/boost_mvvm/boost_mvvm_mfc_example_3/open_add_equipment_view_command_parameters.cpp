//
//  open_add_equipment_view_command_parameters.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "open_add_equipment_view_command_parameters.hpp"

open_add_equipment_view_command_parameters::~open_add_equipment_view_command_parameters()
{
}

open_add_equipment_view_command_parameters::open_add_equipment_view_command_parameters(const spaceship_interface::ptr& spaceship_)
    : m::command_parameters()
    , spaceship(spaceship_)
{
}

open_add_equipment_view_command_parameters::ptr open_add_equipment_view_command_parameters::create(const spaceship_interface::ptr& spaceship_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        explicit make_shared_enabler(const spaceship_interface::ptr& spaceship_) : this_type(spaceship_) {}
    };

    return boost::make_shared<make_shared_enabler, const spaceship_interface::ptr&>(spaceship_);
}
