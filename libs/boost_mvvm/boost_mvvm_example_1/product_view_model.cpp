//
//  product_view_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "product_view_model.hpp"

product_view_model::~product_view_model()
{
}

product_view_model::product_view_model()
    : m::wobservable_object()
    , boost::noncopyable()
    , _product_id(0)
    , _current_product(product_model::create())
    , _get_product_command()
    , _save_product_command()
    , _products()
    , product_id(L"product_id")
    , current_product(L"current_product")
    , get_product_command(L"get_product_command")
    , save_product_command(L"save_product_command")
{
    bind_properties();
}

product_view_model::ptr product_view_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler() : this_type() {}
    };

    return boost::make_shared<make_shared_enabler>();
}

void product_view_model::bind_properties()
{
    product_id.getter(boost::bind(&product_view_model::get_product_id, this));
    product_id.setter(boost::bind(&product_view_model::set_product_id, this, _1));
    current_product.getter(boost::bind(&product_view_model::get_current_product, this));
    current_product.setter(boost::bind(&product_view_model::set_current_product, this, _1));
    get_product_command.getter(boost::bind(&product_view_model::get_get_product_command, this));
    save_product_command.getter(boost::bind(&product_view_model::get_save_product_command, this));
}

int product_view_model::get_product_id() const
{
    return _product_id;
}

void product_view_model::set_product_id(const int& v)
{
    if(v != _product_id)
    {
        _product_id = v;
        on_property_changed(L"product_id");
    }
}

product_model::ptr product_view_model::get_current_product() const
{
    return _current_product;
}

void product_view_model::set_current_product(const product_model::ptr& v)
{
    if(v != _current_product)
    {
        _current_product = v;
        on_property_changed(L"current_product");
    }
}

m::wcommand::ptr product_view_model::get_get_product_command()
{
    if(!_get_product_command)
    {
        _get_product_command = m::relay_wcommand::create(L"get_product", boost::bind(&product_view_model::get_product, this, _1), boost::bind(&product_view_model::can_get_product, this, _1), m::command_parameters::create());
    }
    return _get_product_command;
}

void product_view_model::get_product(const m::command_parameters::ptr& /*params*/)
{
    products_type::const_iterator it = _products.find(product_id);
    if(it != _products.end())
    {
        current_product = it->second;
    }
    else
    {
        product_model::ptr new_product = product_model::create();
        new_product->product_id = product_id;
        new_product->product_name = L"New product";
        new_product->unit_price = 10.0;
        current_product = new_product;
    }
}

bool product_view_model::can_get_product(const m::command_parameters::ptr& /*params*/) const
{
    return true;
}

m::wcommand::ptr product_view_model::get_save_product_command()
{
    if(!_save_product_command)
    {
        _save_product_command = m::relay_wcommand::create(L"save_product", boost::bind(&product_view_model::save_product, this, _1), boost::bind(&product_view_model::can_save_product, this, _1), m::command_parameters::create());
    }
    return _save_product_command;
}

void product_view_model::save_product(const m::command_parameters::ptr& /*params*/)
{
    _products[product_id] = current_product;
}

bool product_view_model::can_save_product(const m::command_parameters::ptr& /*params*/) const
{
    return true;
}
