#ifndef GO_BOOST_REMOVE_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_BOOST_REMOVE_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  remove_equipment_command_parameters.hpp
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

typedef unsigned long equipment_id_type;
typedef unsigned long fleet_organization_id_type;

class remove_equipment_command_parameters
    : public m::command_parameters
{
public:
    typedef remove_equipment_command_parameters this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~remove_equipment_command_parameters();

protected:
    remove_equipment_command_parameters(const fleet_organization_id_type& spaceship_id_, const equipment_id_type& equipment_id_);

private:
    remove_equipment_command_parameters() = delete;

public:
    np::value_property<fleet_organization_id_type> spaceship_id;
    np::value_property<equipment_id_type> equipment_id;

public:
    static ptr create(const fleet_organization_id_type& spaceship_id_, const equipment_id_type& equipment_id_);
};

#endif  // #ifndef GO_BOOST_REMOVE_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED
