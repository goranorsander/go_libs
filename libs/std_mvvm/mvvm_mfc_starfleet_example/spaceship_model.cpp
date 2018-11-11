//
//  spaceship_model.cpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "spaceship_model.hpp"

spaceship_model::~spaceship_model()
{
    _equipment->container_changed.disconnect(_on_equipment_list_changed_slot_key);
}

spaceship_model::spaceship_model(const std::wstring& spaceship_class_, const std::wstring& name_)
    : spaceship_interface()
    , mst::wobservable_object()
    , u::noncopyable_nonmovable()
    , _spaceship_class(spaceship_class_)
    , _name(name_)
    , _equipment(m::wobservable_deque<equipment_interface::ptr>::create())
    , _captain()
    , _crew_complement(0)
    , _on_equipment_list_changed_slot_key()
{
}

spaceship_model::ptr spaceship_model::create(const std::wstring& spaceship_class_, const std::wstring& name_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& spaceship_class_, const std::wstring& name_) : this_type(spaceship_class_, name_) {}
    };

    spaceship_model::ptr model = std::make_shared<make_shared_enabler, const std::wstring&, const std::wstring&>(spaceship_class_, name_);
    model->bind_properties();
    return model;
}

void spaceship_model::bind_properties()
{
    spaceship_class.getter([this]() { return _spaceship_class; });
    name.getter([this]() { return _name; });
    captain.getter([this]() { return _captain; });
    captain.setter([this](const std::wstring& v) { if(v != _captain) { _captain = v; notify_property_changed(this->shared_from_this(), captain.name()); } });
    crew_complement.getter([this]() { return _crew_complement; });
    crew_complement.setter([this](const unsigned int& v) { if(v != _crew_complement) { _crew_complement = v; notify_property_changed(this->shared_from_this(), crew_complement.name()); } });
    equipment.getter([this]() { return _equipment; });
    equipment.setter([this](const m::wobservable_deque<equipment_interface::ptr>::ptr& v) { if(v != _equipment) { _equipment = v; notify_property_changed(this->shared_from_this(), equipment.name()); } });
    _on_equipment_list_changed_slot_key = _equipment->container_changed.connect([this](const m::object::ptr&, const m::container_changed_arguments::ptr&) { notify_property_changed(this->shared_from_this(), equipment.name()); });
}
