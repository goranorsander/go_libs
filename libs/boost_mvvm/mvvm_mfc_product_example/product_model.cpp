//
//  product_model.cpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "product_model.hpp"

product_model::~product_model()
{
}

product_model::product_model()
    : m::wobservable_object()
    , tt::noncopyable_nonmovable()
    , product_id(L"product_id")
    , product_name(L"product_name")
    , unit_price(L"unit_price")
    , _product_id(0)
    , _product_name()
    , _unit_price(0.0)
{
}

product_model::ptr product_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    product_model::ptr model = boost::make_shared<make_shared_enabler>();
    model->bind_properties();
    return model;
}

void product_model::bind_properties()
{
    product_id.getter(boost::bind(&product_model::get_product_id, this));
    product_id.setter(boost::bind(&product_model::set_product_id, this, boost::placeholders::_1));
    product_name.getter(boost::bind(&product_model::get_product_name, this));
    product_name.setter(boost::bind(&product_model::set_product_name, this, boost::placeholders::_1));
    unit_price.getter(boost::bind(&product_model::get_unit_price, this));
    unit_price.setter(boost::bind(&product_model::set_unit_price, this, boost::placeholders::_1));
}

product_id_type product_model::get_product_id() const
{
    return _product_id;
}

void product_model::set_product_id(const product_id_type& v)
{
    if(v != _product_id)
    {
        _product_id = v;
        notify_property_changed(this->shared_from_this(), product_id.name());
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
        notify_property_changed(this->shared_from_this(), product_name.name());
    }
}

currency_type product_model::get_unit_price() const
{
    return _unit_price;
}

void product_model::set_unit_price(const currency_type& v)
{
    if(v != _unit_price)
    {
        _unit_price = v;
        notify_property_changed(this->shared_from_this(), unit_price.name());
    }
}
