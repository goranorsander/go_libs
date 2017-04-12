//
//  add_equipment_view_model.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "add_equipment_view_model.hpp"
#include "equipment_model.hpp"

#include <functional>

add_equipment_view_model::add_equipment_view_model(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment)
    : m::wobservable_object()
    , u::noncopyable_nonmovable()
    , category(L"add_equipment_view_model::category")
    , name(L"add_equipment_view_model::name")
    , quantity(L"add_equipment_view_model::quantity")
    , _equipment(equipment)
    , _category(L"New category")
    , _name(L"New equipment")
    , _quantity(0)
{
    bind_properties();
}

add_equipment_view_model::ptr add_equipment_view_model::create(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        explicit make_shared_enabler(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment) : this_type(equipment) {}
    };

    return std::make_shared<make_shared_enabler>(equipment);
}

void add_equipment_view_model::on_add_equipment() const
{
    m::wobservable_deque<equipment_interface::ptr>::ptr equipment_list = _equipment.lock();
    if (equipment_list)
    {
        equipment_interface::ptr new_equipment = equipment_model::create(category, name, quantity);
        if (new_equipment)
        {
            equipment_list->push_back(new_equipment);
        }
    }
    on_close();
}

void add_equipment_view_model::on_cancel() const
{
    on_close();
}

void add_equipment_view_model::on_close() const
{
}

void add_equipment_view_model::bind_properties()
{
    category.getter([this]() { return _category; });
    category.setter([this](const std::wstring& v) { if (v != _category) { _category = v; on_property_changed(category.name()); } });
    name.getter([this]() { return _name; });
    name.setter([this](const std::wstring& v) { if (v != _name) { _name = v; on_property_changed(name.name()); } });
    quantity.getter([this]() { return _quantity; });
    quantity.setter([this](const unsigned int& v) { if (v != _quantity) { _quantity = v; on_property_changed(quantity.name()); } });
}
