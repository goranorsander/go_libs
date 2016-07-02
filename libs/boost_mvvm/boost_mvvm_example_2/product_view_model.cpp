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

#include <go_boost/mvvm/utility.hpp>

namespace bp = boost::phoenix;
namespace bph = boost::phoenix::placeholders;
namespace mu = go_boost::mvvm::utility;

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
    product_id.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_product_id)));
    product_id.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(product_id.name(), boost::bind(&product_view_model::on_property_changed, this, _1), bp::ref(_product_id), bph::arg1));
    current_product.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_current_product)));
    current_product.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(current_product.name(), boost::bind(&product_view_model::on_property_changed, this, _1), bp::ref(_current_product), bph::arg1));
    get_product_command.getter(boost::bind(&product_view_model::get_get_product_command, this));
    save_product_command.getter(boost::bind(&product_view_model::get_save_product_command, this));
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
