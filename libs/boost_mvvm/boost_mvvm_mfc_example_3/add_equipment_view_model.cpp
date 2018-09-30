//
//  add_equipment_view_model.cpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "add_equipment_view_model.hpp"
#include "equipment_model.hpp"

#include <functional>

add_equipment_view_model::~add_equipment_view_model()
{
}

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
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment) : this_type(equipment) {}
    };

    return boost::make_shared<make_shared_enabler>(equipment);
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
    category.getter(boost::bind(&this_type::get_category, this));
    category.setter(boost::bind(&this_type::set_category, this, _1));
    name.getter(boost::bind(&this_type::get_name, this));
    name.setter(boost::bind(&this_type::set_name, this, _1));
    quantity.getter(boost::bind(&this_type::get_quantity, this));
    quantity.setter(boost::bind(&this_type::set_quantity, this, _1));
}

std::wstring add_equipment_view_model::get_category() const
{
    return _category;
}

void add_equipment_view_model::set_category(const std::wstring& v)
{
    if (v != _category)
    {
        _category = v;
        notify_property_changed(category.name());
    }
}

std::wstring add_equipment_view_model::get_name() const
{
    return _name;
}

void add_equipment_view_model::set_name(const std::wstring& v)
{
    if (v != _name)
    {
        _name = v;
        notify_property_changed(name.name());
    }
}

unsigned int add_equipment_view_model::get_quantity() const
{
    return _quantity;
}

void add_equipment_view_model::set_quantity(const unsigned int& v)
{
    if (v != _quantity)
    {
        _quantity = v;
        notify_property_changed(quantity.name());
    }
}
