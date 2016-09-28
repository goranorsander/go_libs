//
//  fleet_organization_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "fleet_organization_model.hpp"

fleet_organization_id_type fleet_organization_model::_next_id = 0;

fleet_organization_model::~fleet_organization_model()
{
}

fleet_organization_model::fleet_organization_model(const std::wstring& name_, const spaceship_interface::ptr& spaceship_)
    : fleet_organization_interface()
    , m::wobservable_object()
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
}

fleet_organization_model::ptr fleet_organization_model::create()
{
    return create(L"", nullptr);
}

fleet_organization_model::ptr fleet_organization_model::create(const std::wstring& name_, const spaceship_interface::ptr& spaceship_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const std::wstring& name_, const spaceship_interface::ptr& spaceship_) : this_type(name_, spaceship_) {}
    };

    return std::make_shared<make_shared_enabler, const std::wstring&, const spaceship_interface::ptr&>(name_, spaceship_);
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
    child->parent = std::dynamic_pointer_cast<fleet_organization_interface>(shared_from_this());
    return true;
}

bool fleet_organization_model::remove_child(const fleet_organization_interface::ptr& child)
{
    if(!child) { return false; }
    if(!child->parent.get()) { return false; }
    if(!is_parent_to(child)) { return false; }
    if(child == first_child.get())
    {
        fleet_organization_interface::ptr next_child = child->next_sibling.get();
        first_child.set(next_child);
        child->parent.set(nullptr);
        child->next_sibling.set(nullptr);
    }
    else
    {
        fleet_organization_interface::ptr previous_child = child->previous_sibling.get();
        fleet_organization_interface::ptr next_child = child->next_sibling.get();
        if(previous_child) { previous_child->next_sibling(next_child); }
        if(next_child) { next_child->previous_sibling(previous_child); }
        child->parent.set(nullptr);
        child->previous_sibling.set(nullptr);
        child->next_sibling.set(nullptr);
    }
    return false;
}

void fleet_organization_model::bind_properties()
{
    id.getter([this]() { return _id; });
    name.getter([this]() { return _name; });
    spaceship_model.getter([this]() { return _spaceship; });
    parent.getter([this]() { return _parent; });
    parent.setter([this](const fleet_organization_interface::ptr& v) { if(std::dynamic_pointer_cast<fleet_organization_model>(v) != _parent) { _parent = std::dynamic_pointer_cast<fleet_organization_model>(v); on_property_changed(parent.name()); } });
    first_child.getter([this]() { return _first_child; });
    first_child.setter([this](const fleet_organization_interface::ptr& v) { if(std::dynamic_pointer_cast<fleet_organization_model>(v) != _first_child) { _first_child = std::dynamic_pointer_cast<fleet_organization_model>(v); on_property_changed(first_child.name()); } });
    previous_sibling.getter([this]() { return _previous_sibling; });
    previous_sibling.setter([this](const fleet_organization_interface::ptr& v) { if(std::dynamic_pointer_cast<fleet_organization_model>(v) != _previous_sibling) { _previous_sibling = std::dynamic_pointer_cast<fleet_organization_model>(v); on_property_changed(previous_sibling.name()); } });
    next_sibling.getter([this]() { return _next_sibling; });
    next_sibling.setter([this](const fleet_organization_interface::ptr& v) { if(std::dynamic_pointer_cast<fleet_organization_model>(v) != _next_sibling) { _next_sibling = std::dynamic_pointer_cast<fleet_organization_model>(v); on_property_changed(next_sibling.name()); } });
}

bool fleet_organization_model::is_parent_to(const fleet_organization_interface::ptr& child) const
{
    if(!child) { return false; }
    return child->parent.get().get() == this;
}

fleet_organization_interface::ptr fleet_organization_model::last_child() const
{
    fleet_organization_interface::ptr child = first_child.get();
    if(!child) { return nullptr; }
    while(child->next_sibling.get())
    {
        child = child->next_sibling.get();
    }
    return child;
}
