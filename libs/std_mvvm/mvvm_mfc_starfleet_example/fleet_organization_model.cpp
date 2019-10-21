//
//  fleet_organization_model.cpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "fleet_organization_model.hpp"
#include "spaceship_model.hpp"

#include <go/diagnostics/log.hpp>

fleet_organization_id_type fleet_organization_model::_next_id = fleet_organization_id_type(0);

fleet_organization_model::~fleet_organization_model()
{
    spaceship_model::ptr spaceship = std::dynamic_pointer_cast<::spaceship_model>(_spaceship);
    if(spaceship)
    {
        spaceship->property_changed.disconnect(_on_spaceship_property_changed_slot_key);
        s::reset(_on_spaceship_property_changed_slot_key);
    }
}

fleet_organization_model::fleet_organization_model(const std::wstring& name_, const spaceship_interface::ptr& spaceship_)
    : fleet_organization_interface()
    , m::wobservable_object()
    , m::object_wobserver_interface()
    , u::noncopyable_nonmovable()
    , id(L"fleet_organization_model::id")
    , _id(_next_id++)
    , _name(name_)
    , _spaceship(spaceship_)
    , _on_spaceship_property_changed_slot_key()
    , _parent()
    , _first_child()
    , _previous_sibling()
    , _next_sibling()
{
}

fleet_organization_model::ptr fleet_organization_model::create()
{
    return create(L"", nullptr);
}

fleet_organization_model::ptr fleet_organization_model::create(const std::wstring& name_, const spaceship_interface::ptr& spaceship_)
{
    GO_LOG_TRACE << "fleet_organization_model::create: " << name_;

    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& name_, const spaceship_interface::ptr& spaceship_) : this_type(name_, spaceship_) {}
    };

    fleet_organization_model::ptr model = std::make_shared<make_shared_enabler, const std::wstring&, const spaceship_interface::ptr&>(name_, spaceship_);
    model->bind_properties();

    GO_LOG_TRACE << "fleet_organization_model::create: done";

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
    child->parent = std::dynamic_pointer_cast<fleet_organization_interface>(this->shared_from_this());
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
        child->parent.set(nullptr);
        child->next_sibling.set(nullptr);
    }
    else
    {
        fleet_organization_interface::ptr previous_child = child->previous_sibling();
        fleet_organization_interface::ptr next_child = child->next_sibling();
        if(previous_child) { previous_child->next_sibling(next_child); }
        if(next_child) { next_child->previous_sibling(previous_child); }
        child->parent.set(nullptr);
        child->previous_sibling.set(nullptr);
        child->next_sibling.set(nullptr);
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
    id.getter([this]() -> fleet_organization_id_type { return _id; });
    name.getter([this]() -> std::wstring { return _name; });
    spaceship_model.getter([this]() -> spaceship_interface::ptr { return _spaceship; });
    parent.getter([this]() -> fleet_organization_interface::ptr { return _parent; });
    parent.setter(std::bind(&this_type::set_property_value<p::wproperty<fleet_organization_interface::ptr>>, this, std::cref(parent), std::ref(_parent), ph::_1));
    first_child.getter([this]() -> fleet_organization_interface::ptr { return _first_child; });
    first_child.setter(std::bind(&this_type::set_property_value<p::wproperty<fleet_organization_interface::ptr>>, this, std::cref(first_child), std::ref(_first_child), ph::_1));
    previous_sibling.getter([this]() -> fleet_organization_interface::ptr { return _previous_sibling; });
    previous_sibling.setter(std::bind(&this_type::set_property_value<p::wproperty<fleet_organization_interface::ptr>>, this, std::cref(previous_sibling), std::ref(_previous_sibling), ph::_1));
    next_sibling.getter([this]() -> fleet_organization_interface::ptr { return _next_sibling; });
    next_sibling.setter(std::bind(&this_type::set_property_value<p::wproperty<fleet_organization_interface::ptr>>, this, std::cref(next_sibling), std::ref(_next_sibling), ph::_1));
    spaceship_model::ptr spaceship = std::dynamic_pointer_cast<::spaceship_model>(_spaceship);
    if(spaceship)
    {
        _on_spaceship_property_changed_slot_key = spaceship->property_changed.connect(std::bind(&this_type::on_property_changed, this, ph::_1, ph::_2));
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
    if(!child) { return nullptr; }
    while(child->next_sibling())
    {
        child = child->next_sibling();
    }
    return child;
}
