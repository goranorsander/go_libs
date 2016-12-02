//
//  spaceship_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "spaceship_model.hpp"

spaceship_model::~spaceship_model()
{
    _equipment->container_changed.disconnect(_on_equipment_list_changed_slot_key);
}

spaceship_model::spaceship_model(const std::wstring& spaceship_class_, const std::wstring& name_)
    : spaceship_interface()
    , m::wobservable_object()
    , u::noncopyable_nonmovable()
    , _spaceship_class(spaceship_class_)
    , _name(name_)
    , _equipment(m::wobservable_list<equipment_interface::ptr>::create())
    , _captain()
    , _crew_complement(0)
    , _on_equipment_list_changed_slot_key(0)
{
    _on_equipment_list_changed_slot_key = _equipment->container_changed.connect(std::bind(&this_type::on_equipment_list_changed, this, ph::_1, ph::_2));
    bind_properties();
}

spaceship_model::ptr spaceship_model::create(const std::wstring& spaceship_class_, const std::wstring& name_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const std::wstring& spaceship_class_, const std::wstring& name_) : this_type(spaceship_class_, name_) {}
    };

    return std::make_shared<make_shared_enabler, const std::wstring&, const std::wstring&>(spaceship_class_, name_);
}

void spaceship_model::bind_properties()
{
    spaceship_class.getter([this]() { return _spaceship_class; });
    name.getter([this]() { return _name; });
    captain.getter([this]() { return _captain; });
    captain.setter([this](const std::wstring& v) { if(v != _captain) { _captain = v; on_property_changed(captain.name()); } });
    crew_complement.getter([this]() { return _crew_complement; });
    crew_complement.setter([this](const unsigned int& v) { if(v != _crew_complement) { _crew_complement = v; on_property_changed(crew_complement.name()); } });
    equipment.getter([this]() { return _equipment; });
    equipment.setter([this](const m::wobservable_list<equipment_interface::ptr>::ptr& v) { if(v != _equipment) { _equipment = v; on_property_changed(equipment.name()); } });
}

void spaceship_model::on_equipment_list_changed(const m::object::ptr& /*o*/, const m::container_changed_arguments::ptr& /*a*/)
{
    on_property_changed(equipment.name());
}
