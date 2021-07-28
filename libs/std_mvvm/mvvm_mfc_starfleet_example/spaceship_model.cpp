//
//  spaceship_model.cpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "spaceship_model.hpp"

#include <go/diagnostics/log.hpp>

spaceship_model::~spaceship_model()
{
    _equipment->container_changed.disconnect(_on_equipment_list_changed_connection);
}

spaceship_model::spaceship_model(const std::wstring& spaceship_class_, const std::wstring& name_)
    : spaceship_interface()
    , m::wobservable_object()
    , tt::noncopyable_nonmovable()
    , _spaceship_class(spaceship_class_)
    , _name(name_)
    , _equipment(m::wobservable_deque<equipment_interface::ptr>::create())
    , _captain()
    , _crew_complement(0)
    , _on_equipment_list_changed_connection()
{
}

spaceship_model::ptr spaceship_model::create(const std::wstring& spaceship_class_, const std::wstring& name_)
{
    GO_LOG_TRACE << "spaceship_model::create: " << spaceship_class_ << ", " << name_;

    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& spaceship_class_, const std::wstring& name_) : this_type(spaceship_class_, name_) {}
    };

    spaceship_model::ptr model = std::make_shared<make_shared_enabler, const std::wstring&, const std::wstring&>(spaceship_class_, name_);
    model->bind_properties();

    GO_LOG_TRACE << "spaceship_model::create: done";

    return model;
}

void spaceship_model::bind_properties()
{
    spaceship_class.getter([this]() -> std::wstring { return _spaceship_class; });
    name.getter([this]() -> std::wstring { return _name; });
    captain.getter([this]() -> std::wstring { return _captain; });
    captain.setter(std::bind(&this_type::set_property_value<p::wproperty<std::wstring>>, this, std::cref(captain), std::ref(_captain), ph::_1));
    crew_complement.getter([this]() -> unsigned int { return _crew_complement; });
    crew_complement.setter(std::bind(&this_type::set_property_value<p::wproperty<unsigned int>>, this, std::cref(crew_complement), std::ref(_crew_complement), ph::_1));
    equipment.getter([this]() -> m::wobservable_deque<equipment_interface::ptr>::ptr { return _equipment; });
    equipment.setter(std::bind(&this_type::set_property_value<p::wproperty<m::wobservable_deque<equipment_interface::ptr>::ptr>>, this, std::cref(equipment), std::ref(_equipment), ph::_1));
    _on_equipment_list_changed_connection = _equipment->container_changed.connect([this](const m::object::ptr&, const m::container_changed_arguments::ptr&) { notify_property_changed(this->shared_from_this(), equipment.name()); });
}
