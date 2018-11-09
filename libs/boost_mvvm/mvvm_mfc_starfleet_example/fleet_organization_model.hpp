#ifndef GO_BOOST_FLEET_ORGANIZATION_MODEL_HPP_INCLUDED
#define GO_BOOST_FLEET_ORGANIZATION_MODEL_HPP_INCLUDED

//
//  fleet_organization_model.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "fleet_organization_interface.hpp"

typedef unsigned long fleet_organization_id_type;

class fleet_organization_model
    : public fleet_organization_interface
    , public m::wobservable_object
    , public m::object_wobserver_interface
    , private u::noncopyable_nonmovable
{
public:
    typedef fleet_organization_model this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_organization_model();

protected:
    fleet_organization_model(const std::wstring& name_, const spaceship_interface::ptr& spaceship_);

private:
    fleet_organization_model();

public:
    rop::wproperty<fleet_organization_id_type> id;

public:
    static ptr create();
    static ptr create(const std::wstring& name_, const spaceship_interface::ptr& spaceship_);

public:
    bool add_child(const fleet_organization_interface::ptr& child);
    bool remove_child(const fleet_organization_interface::ptr& child);

protected:
    virtual void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a);
    virtual void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a);

private:
    void bind_properties();

    bool is_parent_to(const fleet_organization_interface::ptr& child) const;
    fleet_organization_interface::ptr last_child() const;

    fleet_organization_id_type get_id() const;
    std::wstring get_name() const;
    spaceship_interface::ptr get_spaceship() const;
    fleet_organization_interface::ptr get_parent() const;
    void set_parent(const fleet_organization_interface::ptr& v);
    fleet_organization_interface::ptr get_first_child() const;
    void set_first_child(const fleet_organization_interface::ptr& v);
    fleet_organization_interface::ptr get_previous_sibling() const;
    void set_previous_sibling(const fleet_organization_interface::ptr& v);
    fleet_organization_interface::ptr get_next_sibling() const;
    void set_next_sibling(const fleet_organization_interface::ptr& v);

private:
    static fleet_organization_id_type _next_id;
    const fleet_organization_id_type _id;

    const std::wstring _name;
    spaceship_interface::ptr _spaceship;

    ptr _parent;
    ptr _first_child;
    ptr _previous_sibling;
    ptr _next_sibling;
};

#endif  // #ifndef GO_BOOST_FLEET_ORGANIZATION_MODEL_HPP_INCLUDED
