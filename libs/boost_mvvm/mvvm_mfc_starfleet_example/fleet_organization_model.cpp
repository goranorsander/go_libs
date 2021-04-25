//
//  fleet_organization_model.cpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "fleet_organization_model.hpp"
#include "spaceship_model.hpp"

#include <boost/bind/bind.hpp>

fleet_organization_id_type fleet_organization_model::_next_id = fleet_organization_id_type(0ull);

fleet_organization_model::~fleet_organization_model()
{
    spaceship_model::ptr spaceship = boost::dynamic_pointer_cast<::spaceship_model>(_spaceship);
    if(spaceship)
    {
        _on_property_changed_connection.disconnect();
    }
}

fleet_organization_model::fleet_organization_model(const std::wstring& name_, const spaceship_interface::ptr& spaceship_)
    : fleet_organization_interface()
    , m::wobservable_object()
    , m::object_wobserver_interface()
    , tt::noncopyable_nonmovable()
    , id(L"fleet_organization_model::id")
    , _id(_next_id++)
    , _name(name_)
    , _spaceship(spaceship_)
    , _parent()
    , _first_child()
    , _previous_sibling()
    , _next_sibling()
{
}

fleet_organization_model::fleet_organization_model()
    : fleet_organization_interface()
    , m::wobservable_object()
    , m::object_wobserver_interface()
    , tt::noncopyable_nonmovable()
    , id(L"fleet_organization_model::id")
    , _id(0)
    , _name(L"")
    , _spaceship()
    , _parent()
    , _first_child()
    , _previous_sibling()
    , _next_sibling()
    , _on_property_changed_connection()
{
}

fleet_organization_model::ptr fleet_organization_model::create()
{
    return create(L"", spaceship_interface::ptr());
}

fleet_organization_model::ptr fleet_organization_model::create(const std::wstring& name_, const spaceship_interface::ptr& spaceship_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& name_, const spaceship_interface::ptr& spaceship_) : this_type(name_, spaceship_) {}
    };

    fleet_organization_model::ptr model = boost::make_shared<make_shared_enabler, const std::wstring&, const spaceship_interface::ptr&>(name_, spaceship_);
#else
    fleet_organization_model::ptr model = boost::shared_ptr<this_type>(new this_type(name_, spaceship_));
#endif // BOOST_MSVC > 1500
    model->bind_properties();
    return model;
}

bool fleet_organization_model::add_child(const fleet_organization_interface::ptr& child)
{
    if(!child) { return false; }
    if(*child->parent) { return false; }
    fleet_organization_interface::ptr sibling = last_child();
    if(sibling)
    {
        sibling->next_sibling = child;
        child->previous_sibling = sibling;
    }
    else
    {
        first_child = child;
    }
    child->parent = boost::dynamic_pointer_cast<fleet_organization_interface>(this->shared_from_this());
    return true;
}

bool fleet_organization_model::remove_child(const fleet_organization_interface::ptr& child)
{
    if(!child) { return false; }
    if(!child->parent()) { return false; }
    if(!is_parent_to(child)) { return false; }
    if(child == first_child())
    {
        fleet_organization_interface::ptr next_child = child->next_sibling();
        first_child.set(next_child);
        child->parent.set(fleet_organization_interface::ptr());
        child->next_sibling.set(fleet_organization_interface::ptr());
    }
    else
    {
        fleet_organization_interface::ptr previous_child = child->previous_sibling();
        fleet_organization_interface::ptr next_child = child->next_sibling();
        if(previous_child) { previous_child->next_sibling(next_child); }
        if(next_child) { next_child->previous_sibling(previous_child); }
        child->parent.set(fleet_organization_interface::ptr());
        child->previous_sibling.set(fleet_organization_interface::ptr());
        child->next_sibling.set(fleet_organization_interface::ptr());
    }
    return false;
}

void fleet_organization_model::on_container_changed(const m::object::ptr& /*o*/, const m::container_changed_arguments::ptr& /*a*/)
{
}

void fleet_organization_model::on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
{
    if(o && a && !property_changed.empty())
    {
        property_changed(o, a);
    }
}

void fleet_organization_model::bind_properties()
{
    id.getter(boost::bind(&this_type::get_property_value<fleet_organization_id_type>, this, boost::cref(_id)));
    name.getter(boost::bind(&this_type::get_property_value<std::wstring>, this, boost::cref(_name)));
    spaceship_model.getter(boost::bind(&this_type::get_property_value<spaceship_interface::ptr>, this, boost::cref(_spaceship)));
    parent.getter(boost::bind(&this_type::get_property_value<fleet_organization_interface::ptr>, this, boost::cref(_parent)));
    parent.setter(boost::bind(&this_type::set_property_value<p::wproperty<fleet_organization_interface::ptr>>, this, boost::cref(parent), boost::ref(_parent), boost::placeholders::_1));
    first_child.getter(boost::bind(&this_type::get_property_value<fleet_organization_interface::ptr>, this, boost::cref(_first_child)));
    first_child.setter(boost::bind(&this_type::set_property_value<p::wproperty<fleet_organization_interface::ptr>>, this, boost::cref(first_child), boost::ref(_first_child), boost::placeholders::_1));
    previous_sibling.getter(boost::bind(&this_type::get_property_value<fleet_organization_interface::ptr>, this, boost::cref(_previous_sibling)));
    previous_sibling.setter(boost::bind(&this_type::set_property_value<p::wproperty<fleet_organization_interface::ptr>>, this, boost::cref(previous_sibling), boost::ref(_previous_sibling), boost::placeholders::_1));
    next_sibling.getter(boost::bind(&this_type::get_property_value<fleet_organization_interface::ptr>, this, boost::cref(_next_sibling)));
    next_sibling.setter(boost::bind(&this_type::set_property_value<p::wproperty<fleet_organization_interface::ptr>>, this, boost::cref(next_sibling), boost::ref(_next_sibling), boost::placeholders::_1));
    spaceship_model::ptr spaceship = boost::dynamic_pointer_cast<::spaceship_model>(_spaceship);
    if(spaceship)
    {
        _on_property_changed_connection = spaceship->property_changed.connect(boost::bind(&this_type::on_property_changed, this, boost::placeholders::_1, boost::placeholders::_2));
    }
}

bool fleet_organization_model::is_parent_to(const fleet_organization_interface::ptr& child) const
{
    if(!child) { return false; }
    return child->parent().get() == this;
}

fleet_organization_interface::ptr fleet_organization_model::last_child() const
{
    fleet_organization_interface::ptr child = first_child();
    if(!child) { return fleet_organization_interface::ptr(); }
    while(child->next_sibling())
    {
        child = child->next_sibling();
    }
    return child;
}
