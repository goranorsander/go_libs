//
//  close_spaceship_command_parameters.cpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
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
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const spaceship_view_model::ptr& vm) : this_type(vm) {}
    };

    return boost::make_shared<make_shared_enabler, const spaceship_view_model::ptr&>(vm);
#else
    return boost::shared_ptr<this_type>(new this_type(vm));
#endif // BOOST_MSVC > 1500
}
