#ifndef GO_FLEET_ORGANIZATION_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_FLEET_ORGANIZATION_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  fleet_organization_command_parameters.hpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm/command_parameters.hpp>
#include <go/property/nameless/value_property.hpp>
#include "fleet_organization_id_type.hpp"

class fleet_organization_command_parameters
    : public m::command_parameters
{
public:
    using this_type = fleet_organization_command_parameters;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

public:
    virtual ~fleet_organization_command_parameters() GO_DEFAULT_DESTRUCTOR

protected:
    explicit fleet_organization_command_parameters(const fleet_organization_id_type& id_);

private:
    fleet_organization_command_parameters() = delete;

public:
    pn::value_property<fleet_organization_id_type> id;

public:
    static ptr create(const fleet_organization_id_type& id_);
};

#endif  // #ifndef GO_FLEET_ORGANIZATION_COMMAND_PARAMETERS_HPP_INCLUDED
