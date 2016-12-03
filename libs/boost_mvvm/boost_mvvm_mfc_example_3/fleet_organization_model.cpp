//
//  fleet_organization_model.cpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "fleet_organization_model.hpp"
#include "spaceship_model.hpp"

fleet_organization_id_type fleet_organization_model::_next_id = 0;

fleet_organization_model::~fleet_organization_model()
{
    spaceship_model::ptr spaceship = boost::dynamic_pointer_cast<::spaceship_model>(_spaceship);
    if(spaceship)
    {
        spaceship->property_changed.disconnect(boost::bind(&fleet_organization_model::on_property_changed, this, _1, _2));
    }
}

fleet_organization_model::fleet_organization_model(const std::wstring& name_, const spaceship_interface::ptr& spaceship_)
    : fleet_organization_interface()
    , m::wobservable_object()
    , m::object_wobserver_interface()
    , boost::noncopyable()
    , id(L"fleet_organization_model::id")
    , _id(_next_id++)
    , _name(name_)
    , _spaceship(spaceship_)
    , _parent()
    , _first_child()
    , _previous_sibling()
    , _next_sibling()
{
    bind_properties();
    spaceship_model::ptr spaceship = boost::dynamic_pointer_cast<::spaceship_model>(_spaceship);
    if(spaceship)
    {
        spaceship->property_changed.connect(boost::bind(&fleet_organization_model::on_property_changed, this, _1, _2));
    }
}

fleet_organization_model::ptr fleet_organization_model::create()
{
    return create(L"", NULL);
}

fleet_organization_model::ptr fleet_organization_model::create(const std::wstring& name_, const spaceship_interface::ptr& spaceship_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const std::wstring& name_, const spaceship_interface::ptr& spaceship_) : this_type(name_, spaceship_) {}
    };

    return boost::make_shared<make_shared_enabler, const std::wstring&, const spaceship_interface::ptr&>(name_, spaceship_);
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
    child->parent = boost::dynamic_pointer_cast<fleet_organization_interface>(shared_from_this());
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
        child->parent.set(NULL);
        child->next_sibling.set(NULL);
    }
    else
    {
        fleet_organization_interface::ptr previous_child = child->previous_sibling();
        fleet_organization_interface::ptr next_child = child->next_sibling();
        if(previous_child) { previous_child->next_sibling(next_child); }
        if(next_child) { next_child->previous_sibling(previous_child); }
        child->parent.set(NULL);
        child->previous_sibling.set(NULL);
        child->next_sibling.set(NULL);
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
    id.getter([this]() { return _id; });
    name.getter([this]() { return _name; });
    spaceship_model.getter([this]() { return _spaceship; });
    parent.getter([this]() { return _parent; });
    parent.setter([this](const fleet_organization_interface::ptr& v) { if(boost::dynamic_pointer_cast<fleet_organization_model>(v) != _parent) { _parent = boost::dynamic_pointer_cast<fleet_organization_model>(v); m::wobservable_object::on_property_changed(parent.name()); } });
    first_child.getter([this]() { return _first_child; });
    first_child.setter([this](const fleet_organization_interface::ptr& v) { if(boost::dynamic_pointer_cast<fleet_organization_model>(v) != _first_child) { _first_child = boost::dynamic_pointer_cast<fleet_organization_model>(v); m::wobservable_object::on_property_changed(first_child.name()); } });
    previous_sibling.getter([this]() { return _previous_sibling; });
    previous_sibling.setter([this](const fleet_organization_interface::ptr& v) { if(boost::dynamic_pointer_cast<fleet_organization_model>(v) != _previous_sibling) { _previous_sibling = boost::dynamic_pointer_cast<fleet_organization_model>(v); m::wobservable_object::on_property_changed(previous_sibling.name()); } });
    next_sibling.getter([this]() { return _next_sibling; });
    next_sibling.setter([this](const fleet_organization_interface::ptr& v) { if(boost::dynamic_pointer_cast<fleet_organization_model>(v) != _next_sibling) { _next_sibling = boost::dynamic_pointer_cast<fleet_organization_model>(v); m::wobservable_object::on_property_changed(next_sibling.name()); } });
}

bool fleet_organization_model::is_parent_to(const fleet_organization_interface::ptr& child) const
{
    if(!child) { return false; }
    return child->parent().get() == this;
}

fleet_organization_interface::ptr fleet_organization_model::last_child() const
{
    fleet_organization_interface::ptr child = first_child();
    if(!child) { return NULL; }
    while(child->next_sibling())
    {
        child = child->next_sibling();
    }
    return child;
}
