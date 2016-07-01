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

#include <functional>

namespace ph = std::placeholders;

product_view_model::product_view_model()
    : m::wobservable_object()
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
        virtual ~make_shared_enabler() = default;
        make_shared_enabler() : this_type() {}
    };

    return std::make_shared<make_shared_enabler>();
}

void product_view_model::bind_properties()
{
    product_id.getter([this]() { return _product_id; });
    product_id.setter([this](const int& v) { if(v != _product_id) { _product_id = v; on_property_changed(product_id.name()); } });
    current_product.getter([this]() { return _current_product; });
    current_product.setter([this](const product_model::ptr& v) { if(v != _current_product) { _current_product = v; on_property_changed(current_product.name()); } });
    get_product_command.getter(
        [this]()
        {
            if(!_get_product_command)
            {
                _get_product_command = m::relay_wcommand::create(L"get_product",
                    [this](const m::command_parameters::ptr&)
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
                    },
                    [this](const m::command_parameters::ptr&) { return true; },
                    m::command_parameters::create());
            }
            return _get_product_command;
        });
    save_product_command.getter(
        [this]()
        {
            if(!_save_product_command)
            {
                _save_product_command = m::relay_wcommand::create(L"save_product",
                    [this](const m::command_parameters::ptr&)
                    {
                        _products[product_id] = current_product;
                    },
                    [this](const m::command_parameters::ptr&) { return true; },
                    m::command_parameters::create());
            }
            return _save_product_command;
        });
}
