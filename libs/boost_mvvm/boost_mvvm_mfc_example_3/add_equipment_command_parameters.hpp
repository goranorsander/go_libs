#ifndef GO_BOOST_ADD_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_BOOST_ADD_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  add_equipment_command_parameters.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm/command_parameters.hpp>
#include <go_boost/property/nameless/value_property.hpp>

typedef unsigned long fleet_organization_id_type;

class add_equipment_command_parameters
    : public m::command_parameters
{
public:
    typedef add_equipment_command_parameters this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~add_equipment_command_parameters();

protected:
    explicit add_equipment_command_parameters(const fleet_organization_id_type& spaceship_id_);

private:
    add_equipment_command_parameters() = delete;

public:
    np::value_property<fleet_organization_id_type> spaceship_id;

public:
    static ptr create(const fleet_organization_id_type& spaceship_id_);
};

#endif  // #ifndef GO_BOOST_ADD_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED
