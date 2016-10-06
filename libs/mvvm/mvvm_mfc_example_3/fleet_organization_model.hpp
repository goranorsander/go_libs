#ifndef GO_FLEET_ORGANIZATION_MODEL_HPP_INCLUDED
#define GO_FLEET_ORGANIZATION_MODEL_HPP_INCLUDED

//
//  fleet_organization_model.hpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "fleet_organization_interface.hpp"

namespace u = go::utility;

typedef unsigned long fleet_organization_id_type;

class fleet_organization_model
    : public fleet_organization_interface
    , public m::wobservable_object
    , public u::noncopyable_nonmovable
{
public:
    typedef fleet_organization_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_organization_model();

protected:
    fleet_organization_model(const std::wstring& name_, const spaceship_interface::ptr& spaceship_);

private:
    fleet_organization_model() = delete;

public:
    static ptr create();
    static ptr create(const std::wstring& name_, const spaceship_interface::ptr& spaceship_);

public:
    rop::wproperty<fleet_organization_id_type> id;

public:
    virtual bool add_child(const fleet_organization_interface::ptr& child);
    virtual bool remove_child(const fleet_organization_interface::ptr& child);

protected:
    virtual void bind_properties();

private:
    bool is_parent_to(const fleet_organization_interface::ptr& child) const;
    fleet_organization_interface::ptr last_child() const;

private:
    static fleet_organization_id_type _next_id;
    const fleet_organization_id_type _id;

    const std::wstring _name;
    const spaceship_interface::ptr _spaceship;

    ptr _parent;
    ptr _first_child;
    ptr _previous_sibling;
    ptr _next_sibling;
};

#endif  // #ifndef GO_FLEET_ORGANIZATION_MODEL_HPP_INCLUDED
