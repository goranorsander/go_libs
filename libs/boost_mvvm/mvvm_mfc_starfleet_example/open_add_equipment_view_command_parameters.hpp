#ifndef GO_BOOST_OPEN_ADD_EQUIPMENT_VIEW_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_BOOST_OPEN_ADD_EQUIPMENT_VIEW_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  open_add_equipment_view_command_parameters.hpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go_boost/mvvm/command_parameters.hpp>
#include <go_boost/property/nameless/value_property.hpp>
#include "spaceship_interface.hpp"

class open_add_equipment_view_command_parameters
    : public m::command_parameters
{
public:
    typedef open_add_equipment_view_command_parameters this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~open_add_equipment_view_command_parameters();

protected:
    explicit open_add_equipment_view_command_parameters(const spaceship_interface::ptr& spaceship_);

private:
    open_add_equipment_view_command_parameters();

public:
    pn::value_property<spaceship_interface::ptr> spaceship;

public:
    static ptr create(const spaceship_interface::ptr& spaceship_);
};

#endif  // #ifndef GO_BOOST_OPEN_ADD_EQUIPMENT_VIEW_COMMAND_PARAMETERS_HPP_INCLUDED
