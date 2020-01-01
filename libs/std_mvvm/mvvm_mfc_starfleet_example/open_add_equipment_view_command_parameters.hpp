#ifndef GO_OPEN_ADD_EQUIPMENT_VIEW_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_OPEN_ADD_EQUIPMENT_VIEW_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  open_add_equipment_view_command_parameters.hpp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm/command_parameters.hpp>
#include <go/property/nameless/value_property.hpp>
#include "spaceship_interface.hpp"

class open_add_equipment_view_command_parameters
    : public m::command_parameters
{
public:
    typedef open_add_equipment_view_command_parameters this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~open_add_equipment_view_command_parameters() GO_DEFAULT_DESTRUCTOR

protected:
    explicit open_add_equipment_view_command_parameters(const spaceship_interface::ptr& spaceship_);

private:
    open_add_equipment_view_command_parameters() = delete;

public:
    pn::value_property<spaceship_interface::ptr> spaceship;

public:
    static ptr create(const spaceship_interface::ptr& spaceship_);
};

#endif  // #ifndef GO_OPEN_ADD_EQUIPMENT_VIEW_COMMAND_PARAMETERS_HPP_INCLUDED
