//
//  open_add_equipment_view_command_parameters.cpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "open_add_equipment_view_command_parameters.hpp"

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
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const spaceship_interface::ptr& spaceship_) : this_type(spaceship_) {}
    };

    return std::make_shared<make_shared_enabler, const spaceship_interface::ptr&>(spaceship_);
}
