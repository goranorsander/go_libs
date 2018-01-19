#ifndef GO_REMOVE_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_REMOVE_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  remove_equipment_command_parameters.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm/command_parameters.hpp>
#include <go/property/nameless/value_property.hpp>

typedef unsigned long equipment_id_type;
typedef unsigned long fleet_organization_id_type;

class remove_equipment_command_parameters
    : public m::command_parameters
{
public:
    typedef remove_equipment_command_parameters this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~remove_equipment_command_parameters() GO_DEFAULT_DESTRUCTOR

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

#endif  // #ifndef GO_REMOVE_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED
