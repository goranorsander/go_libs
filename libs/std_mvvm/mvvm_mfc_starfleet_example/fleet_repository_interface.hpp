#ifndef GO_FLEET_REPOSITORY_INTERFACE_HPP_INCLUDED
#define GO_FLEET_REPOSITORY_INTERFACE_HPP_INCLUDED

//
//  fleet_repository_interface.hpp
//
//  Copyright 2016-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "fleet_organization_interface.hpp"

class fleet_repository_interface
{
public:
    typedef fleet_repository_interface this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_repository_interface() = 0;

protected:
    fleet_repository_interface() GO_DEFAULT_CONSTRUCTOR

public:
    virtual fleet_organization_interface::ptr fleet_organization_model() const = 0;
    virtual fleet_organization_interface::ptr fleet_organization_model(const std::wstring& name) const = 0;
    virtual fleet_organization_interface::ptr fleet_organization_model(const spaceship_interface::ptr& spaceship_model) const = 0;
    virtual spaceship_interface::ptr spaceship_model(const std::wstring& name) const = 0;
};

inline fleet_repository_interface::~fleet_repository_interface()
{
}

#endif  // #ifndef GO_FLEET_REPOSITORY_INTERFACE_HPP_INCLUDED
