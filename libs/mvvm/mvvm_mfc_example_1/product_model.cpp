//
//  product_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "product_model.hpp"

#include <functional>

namespace ph = std::placeholders;

product_model::product_model()
    : m::wobservable_object()
    , u::noncopyable_nonmovable()
    , _product_id(0)
    , _product_name()
    , _unit_price(0.0)
    , product_id(L"product_id")
    , product_name(L"product_name")
    , unit_price(L"unit_price")
{
    bind_properties();
}

product_model::ptr product_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler() : this_type() {}
    };

    return std::make_shared<make_shared_enabler>();
}

void product_model::bind_properties()
{
    product_id.getter(std::bind(&product_model::get_product_id, this));
    product_id.setter(std::bind(&product_model::set_product_id, this, ph::_1));
    product_name.getter(std::bind(&product_model::get_product_name, this));
    product_name.setter(std::bind(&product_model::set_product_name, this, ph::_1));
    unit_price.getter(std::bind(&product_model::get_unit_price, this));
    unit_price.setter(std::bind(&product_model::set_unit_price, this, ph::_1));
}

product_model::product_id_type product_model::get_product_id() const
{
    return _product_id;
}

void product_model::set_product_id(const product_model::product_id_type& v)
{
    if(v != _product_id)
    {
        _product_id = v;
        on_property_changed(product_id.name());
    }
}

std::wstring product_model::get_product_name() const
{
    return _product_name;
}

void product_model::set_product_name(const std::wstring& v)
{
    if(v != _product_name)
    {
        _product_name = v;
        on_property_changed(product_name.name());
    }
}

double product_model::get_unit_price() const
{
    return _unit_price;
}

void product_model::set_unit_price(const double& v)
{
    if(v != _unit_price)
    {
        _unit_price = v;
        on_property_changed(unit_price.name());
    }
}
