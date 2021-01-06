#ifndef GO_BOOST_ACTIVATE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_BOOST_ACTIVATE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  activate_spaceship_command_parameters.hpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go_boost/mvvm/command_parameters.hpp>
#include <go_boost/property/nameless/value_property.hpp>
#include "fleet_organization_id_type.hpp"

class activate_spaceship_command_parameters
    : public m::command_parameters
{
public:
    typedef activate_spaceship_command_parameters this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~activate_spaceship_command_parameters();

protected:
    explicit activate_spaceship_command_parameters(const fleet_organization_id_type& id_);

private:
    activate_spaceship_command_parameters();

public:
    pn::value_property<fleet_organization_id_type> id;

public:
    static ptr create(const fleet_organization_id_type& id_);
};

#endif  // #ifndef GO_BOOST_ACTIVATE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED
