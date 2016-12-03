#ifndef GO_FLEET_REPOSITORY_HPP_INCLUDED
#define GO_FLEET_REPOSITORY_HPP_INCLUDED

//
//  fleet_repository.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "fleet_repository_interface.hpp"

typedef unsigned long fleet_organization_id_type;

class fleet_repository
    : public fleet_repository_interface
    , private boost::noncopyable
{
public:
    typedef fleet_repository this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_repository();

protected:
    fleet_repository();

public:
    static ptr create();

public:
    virtual fleet_organization_interface::ptr fleet_organization_model() const;
    virtual fleet_organization_interface::ptr fleet_organization_model(const std::wstring& name) const;
    virtual fleet_organization_interface::ptr fleet_organization_model(const spaceship_interface::ptr& spaceship_model) const;
    virtual fleet_organization_interface::ptr fleet_organization_model(const fleet_organization_id_type id) const;
    virtual spaceship_interface::ptr spaceship_model(const std::wstring& name) const;

private:
    fleet_organization_interface::ptr _fleet_organization;
};

bool operator==(const fleet_repository::wptr& lhs, const fleet_repository::wptr& rhs);
bool operator!=(const fleet_repository::wptr& lhs, const fleet_repository::wptr& rhs);

#endif  // #ifndef GO_FLEET_REPOSITORY_HPP_INCLUDED
