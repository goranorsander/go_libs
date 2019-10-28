//
//  add_equipment_view_model.cpp
//
//  Copyright 2017-2019 Göran Orsander
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
    , tt::noncopyable_nonmovable()
    , category(L"add_equipment_view_model::category")
    , name(L"add_equipment_view_model::name")
    , quantity(L"add_equipment_view_model::quantity")
    , _equipment(equipment)
    , _category(L"New category")
    , _name(L"New equipment")
    , _quantity(quantity_type(0))
{
}

add_equipment_view_model::ptr add_equipment_view_model::create(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment) : this_type(equipment) {}
    };

    add_equipment_view_model::ptr view_model = boost::make_shared<make_shared_enabler>(equipment);
    view_model->bind_properties();
    return view_model;
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
    category.getter(boost::bind(&this_type::get_property_value<std::wstring>, this, boost::cref(_category)));
    category.setter(boost::bind(&this_type::set_property_value<p::wproperty<std::wstring>>, this, boost::cref(category), boost::ref(_category), _1));
    name.getter(boost::bind(&this_type::get_property_value<std::wstring>, this, boost::cref(_name)));
    name.setter(boost::bind(&this_type::set_property_value<p::wproperty<std::wstring>>, this, boost::cref(name), boost::ref(_name), _1));
    quantity.getter(boost::bind(&this_type::get_property_value<quantity_type>, this, boost::cref(_quantity)));
    quantity.setter(boost::bind(&this_type::set_property_value<p::wproperty<quantity_type>>, this, boost::cref(quantity), boost::ref(_quantity), _1));
}
