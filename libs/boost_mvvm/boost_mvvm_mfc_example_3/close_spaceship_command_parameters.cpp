//
//  close_spaceship_command_parameters.cpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "close_spaceship_command_parameters.hpp"

close_spaceship_command_parameters::~close_spaceship_command_parameters()
{
}

close_spaceship_command_parameters::close_spaceship_command_parameters(const spaceship_view_model::ptr& vm)
    : m::command_parameters()
    , spaceship_vm(vm)
{
}

close_spaceship_command_parameters::close_spaceship_command_parameters()
    : m::command_parameters()
    , spaceship_vm()
{
}

close_spaceship_command_parameters::ptr close_spaceship_command_parameters::create(const spaceship_view_model::ptr& vm)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const spaceship_view_model::ptr& vm) : this_type(vm) {}
    };

    return boost::make_shared<make_shared_enabler, const spaceship_view_model::ptr&>(vm);
}