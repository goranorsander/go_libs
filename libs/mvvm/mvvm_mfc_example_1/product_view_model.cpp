//
//  product_view_model.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "product_view_model.hpp"
#include "product_repository.hpp"

#include <functional>

namespace ph = std::placeholders;

product_view_model::product_view_model()
    : m::wobservable_object()
    , m::data_context_interface<product_model::ptr>(product_model::create())
    , u::noncopyable_nonmovable()
    , product_id(L"product_id")
    , current_product_id(L"current_product_id")
    , current_product_name(L"current_product_name")
    , current_unit_price(L"current_unit_price")
    , get_product_command(L"get_product_command")
    , save_product_command(L"save_product_command")
    , _product_id(0)
    , _get_product_command()
    , _save_product_command()
    , _products(product_repository::create())
{
    bind_properties();
}

product_view_model::ptr product_view_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    return std::make_shared<make_shared_enabler>();
}

void product_view_model::bind_properties()
{
    product_id.getter(std::bind(&product_view_model::get_product_id, this));
    product_id.setter(std::bind(&product_view_model::set_product_id, this, ph::_1));
    current_product_id.getter(std::bind(&product_view_model::get_current_product_id, this));
    current_product_id.setter(std::bind(&product_view_model::set_current_product_id, this, ph::_1));
    current_product_name.getter(std::bind(&product_view_model::get_current_product_name, this));
    current_product_name.setter(std::bind(&product_view_model::set_current_product_name, this, ph::_1));
    current_unit_price.getter(std::bind(&product_view_model::get_current_unit_price, this));
    current_unit_price.setter(std::bind(&product_view_model::set_current_unit_price, this, ph::_1));
    get_product_command.getter(std::bind(&product_view_model::get_get_product_command, this));
    save_product_command.getter(std::bind(&product_view_model::get_save_product_command, this));
}

product_model::product_id_type product_view_model::get_product_id() const
{
    return _product_id;
}

void product_view_model::set_product_id(const product_model::product_id_type& v)
{
    if(v != _product_id)
    {
        _product_id = v;
        on_property_changed(product_id.name());
    }
}

product_model::product_id_type product_view_model::get_current_product_id() const
{
    if(*data_context)
    {
        return data_context()->product_id;
    }
    return 0;
}

void product_view_model::set_current_product_id(const product_model::product_id_type& v)
{
    if(*data_context)
    {
        data_context()->product_id = v;
    }
}

std::wstring product_view_model::get_current_product_name() const
{
    if(*data_context)
    {
        return data_context()->product_name;
    }
    return std::wstring();
}

void product_view_model::set_current_product_name(const std::wstring& v)
{
    if(*data_context)
    {
        data_context()->product_name = v;
    }
}

double product_view_model::get_current_unit_price() const
{
    if(*data_context)
    {
        return data_context()->unit_price;
    }
    return 0.0;
}

void product_view_model::set_current_unit_price(const double& v)
{
    if(*data_context)
    {
        data_context()->unit_price = v;
    }
}

m::wcommand_interface::ptr product_view_model::get_get_product_command()
{
    if(!_get_product_command)
    {
        _get_product_command = m::relay_wcommand::create(L"get_product", std::bind(&product_view_model::get_product, this, ph::_1), std::bind(&product_view_model::can_get_product, this, ph::_1), m::command_parameters::create());
    }
    return _get_product_command;
}

void product_view_model::get_product(const m::command_parameters::ptr& /*params*/)
{
    product_model::ptr product = _products->get(product_id);
    if(product)
    {
        data_context = product;
    }
    else
    {
        product_model::ptr new_product = product_model::create();
        new_product->product_id = product_id;
        new_product->product_name = L"New product";
        new_product->unit_price = 10.0;
        data_context = new_product;
    }
}

bool product_view_model::can_get_product(const m::command_parameters::ptr& /*params*/) const
{
    return true;
}

m::wcommand_interface::ptr product_view_model::get_save_product_command()
{
    if(!_save_product_command)
    {
        _save_product_command = m::relay_wcommand::create(L"save_product", std::bind(&product_view_model::save_product, this, ph::_1), std::bind(&product_view_model::can_save_product, this, ph::_1), m::command_parameters::create());
    }
    return _save_product_command;
}

void product_view_model::save_product(const m::command_parameters::ptr& /*params*/)
{
    product_model::ptr product = _products->get(current_product_id);
    if(!product)
    {
        _products->insert(data_context);
    }
}

bool product_view_model::can_save_product(const m::command_parameters::ptr& /*params*/) const
{
    return true;
}
