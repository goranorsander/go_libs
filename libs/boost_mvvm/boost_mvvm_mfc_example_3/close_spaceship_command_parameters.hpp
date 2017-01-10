#ifndef GO_BOOST_CLOSE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_BOOST_CLOSE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  close_spaceship_command_parameters.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm/command_parameters.hpp>
#include <go_boost/property/nameless/value_property.hpp>
#include "spaceship_view_model.hpp"

class close_spaceship_command_parameters
    : public m::command_parameters
{
public:
    typedef close_spaceship_command_parameters this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~close_spaceship_command_parameters();

protected:
    explicit close_spaceship_command_parameters(const spaceship_view_model::ptr& vm);

private:
    close_spaceship_command_parameters();

public:
    np::value_property<spaceship_view_model::ptr> spaceship_vm;

public:
    static ptr create(const spaceship_view_model::ptr& vm);
};

#endif  // #ifndef GO_BOOST_CLOSE_SPACESHIP_COMMAND_PARAMETERS_HPP_INCLUDED
