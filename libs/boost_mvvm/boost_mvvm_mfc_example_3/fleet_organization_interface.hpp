#ifndef GO_BOOST_FLEET_ORGANIZATION_INTERFACE_HPP_INCLUDED
#define GO_BOOST_FLEET_ORGANIZATION_INTERFACE_HPP_INCLUDED

//
//  fleet_organization_interface.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "spaceship_interface.hpp"

class fleet_organization_interface
{
public:
    typedef fleet_organization_interface this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_organization_interface() = 0;

protected:
    fleet_organization_interface();

public:
    rop::wproperty<std::wstring> name;
    rop::wproperty<spaceship_interface::ptr> spaceship_model;

    p::wproperty<ptr> parent;
    p::wproperty<ptr> first_child;
    p::wproperty<ptr> previous_sibling;
    p::wproperty<ptr> next_sibling;

public:
    virtual bool add_child(const ptr& child) = 0;
    virtual bool remove_child(const ptr& child) = 0;

protected:
    virtual void bind_properties() = 0;
};

inline fleet_organization_interface::~fleet_organization_interface()
{
}

inline fleet_organization_interface::fleet_organization_interface()
    : name(L"fleet_organization_interface::name")
    , spaceship_model(L"fleet_organization_interface::spaceship_model")
    , parent(L"fleet_organization_interface::parent")
    , first_child(L"fleet_organization_interface::first_child")
    , previous_sibling(L"fleet_organization_interface::previous_sibling")
    , next_sibling(L"fleet_organization_interface::next_sibling")
{
}

#endif  // #ifndef GO_BOOST_FLEET_ORGANIZATION_INTERFACE_HPP_INCLUDED
