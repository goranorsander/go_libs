#ifndef GO_BOOST_FLEET_ORGANIZATION_MODEL_HPP_INCLUDED
#define GO_BOOST_FLEET_ORGANIZATION_MODEL_HPP_INCLUDED

//
//  fleet_organization_model.hpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "fleet_organization_id_type.hpp"
#include "fleet_organization_interface.hpp"

class fleet_organization_model
    : public fleet_organization_interface
    , public m::wobservable_object
    , public m::object_wobserver_interface
    , private tt::noncopyable_nonmovable
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
    pro::wproperty<fleet_organization_id_type> id;

public:
    static ptr create();
    static ptr create(const std::wstring& name_, const spaceship_interface::ptr& spaceship_);

public:
    bool add_child(const fleet_organization_interface::ptr& child);
    bool remove_child(const fleet_organization_interface::ptr& child);

protected:
    virtual void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a) GO_BOOST_OVERRIDE;
    virtual void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a) GO_BOOST_OVERRIDE;

private:
    void bind_properties();

    bool is_parent_to(const fleet_organization_interface::ptr& child) const;
    fleet_organization_interface::ptr last_child() const;

private:
    static fleet_organization_id_type _next_id;
    const fleet_organization_id_type _id;

    const std::wstring _name;
    spaceship_interface::ptr _spaceship;

    fleet_organization_interface::ptr _parent;
    fleet_organization_interface::ptr _first_child;
    fleet_organization_interface::ptr _previous_sibling;
    fleet_organization_interface::ptr _next_sibling;

    boost::signals2::connection _on_property_changed_connection;
};

#endif  // #ifndef GO_BOOST_FLEET_ORGANIZATION_MODEL_HPP_INCLUDED
