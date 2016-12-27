#ifndef GO_BOOST_ACTIVATE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_BOOST_ACTIVATE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  activate_spaceship_command_parameters.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm/command_parameters.hpp>
#include <go_boost/property/nameless/value_property.hpp>

typedef unsigned long fleet_organization_id_type;

class activate_spaceship_command_parameters
    : public m::command_parameters
{
public:
    typedef activate_spaceship_command_parameters this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~activate_spaceship_command_parameters();

protected:
    activate_spaceship_command_parameters(const fleet_organization_id_type& id_);

private:
    activate_spaceship_command_parameters();

public:
    np::value_property<fleet_organization_id_type> id;

public:
    static ptr create(const fleet_organization_id_type& id_);
};

#endif  // #ifndef GO_BOOST_ACTIVATE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED
