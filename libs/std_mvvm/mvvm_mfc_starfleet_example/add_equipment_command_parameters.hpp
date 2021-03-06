#ifndef GO_ADD_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_ADD_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  add_equipment_command_parameters.hpp
//
//  Copyright 2017-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm/command_parameters.hpp>
#include <go/property/nameless/value_property.hpp>
#include "fleet_organization_id_type.hpp"

class add_equipment_command_parameters
    : public m::command_parameters
{
public:
    typedef add_equipment_command_parameters this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~add_equipment_command_parameters() GO_DEFAULT_DESTRUCTOR

protected:
    explicit add_equipment_command_parameters(const fleet_organization_id_type& spaceship_id_);

private:
    add_equipment_command_parameters() = delete;

public:
    pn::value_property<fleet_organization_id_type> spaceship_id;

public:
    static ptr create(const fleet_organization_id_type& spaceship_id_);
};

#endif  // #ifndef GO_ADD_EQUIPMENT_COMMAND_PARAMETERS_HPP_INCLUDED
