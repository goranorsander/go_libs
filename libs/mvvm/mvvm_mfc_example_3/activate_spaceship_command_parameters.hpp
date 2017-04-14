#ifndef GO_ACTIVATE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_ACTIVATE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  activate_spaceship_command_parameters.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm/command_parameters.hpp>
#include <go/property/nameless/value_property.hpp>

typedef unsigned long fleet_organization_id_type;

class activate_spaceship_command_parameters
    : public m::command_parameters
{
public:
    typedef activate_spaceship_command_parameters this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~activate_spaceship_command_parameters() = default;

protected:
    explicit activate_spaceship_command_parameters(const fleet_organization_id_type& id_);

private:
    activate_spaceship_command_parameters() = delete;

public:
    np::value_property<fleet_organization_id_type> id;

public:
    static ptr create(const fleet_organization_id_type& id_);
};

#endif  // #ifndef GO_ACTIVATE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED
