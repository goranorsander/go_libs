//
//  equipment_model.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "equipment_model.hpp"

#include <boost/bind.hpp>

equipment_model::~equipment_model()
{
}

equipment_model::equipment_model(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_)
    : equipment_interface()
    , m::wobservable_object()
    , u::noncopyable_nonmovable()
    , _category(category_)
    , _name(name_)
    , _quantity(quantity_)
{
    bind_properties();
}

equipment_model::equipment_model()
    : equipment_interface()
    , m::wobservable_object()
    , u::noncopyable_nonmovable()
    , _category(L"")
    , _name(L"")
    , _quantity(0)
{
}

equipment_model::ptr equipment_model::create(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_) : this_type(category_, name_, quantity_) {}
    };

    return boost::make_shared<make_shared_enabler, const std::wstring&, const std::wstring&, const unsigned int&>(category_, name_, quantity_);
}

void equipment_model::bind_properties()
{
    category.getter(boost::bind(&this_type::get_category, this));
    name.getter(boost::bind(&this_type::get_name, this));
    quantity.getter(boost::bind(&this_type::get_quantity, this));
    quantity.setter(boost::bind(&this_type::set_quantity, this, _1));
}

std::wstring equipment_model::get_category() const
{
    return _category;
}

std::wstring equipment_model::get_name() const
{
    return _name;
}

unsigned int equipment_model::get_quantity() const
{
    return _quantity;
}

void equipment_model::set_quantity(const unsigned int& v)
{
    if(v != _quantity)
    {
        _quantity = v;
        on_property_changed(quantity.name());
    }
}
