//
//  product_view_model.cpp
//
//  Copyright 2016-2018 Göran Orsander
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
    product_id.getter([this]() { return _product_id; });
    product_id.setter([this](const product_model::product_id_type& v) { if(v != _product_id) { _product_id = v; notify_property_changed(product_id.name()); } });
    current_product_id.getter([this]() -> product_model::product_id_type { if(*data_context) { return data_context()->product_id; } return 0; });
    current_product_id.setter([this](const product_model::product_id_type& v) { if(*data_context) { data_context()->product_id = v; } });
    current_product_name.getter([this]() -> std::wstring { if(*data_context) { return data_context()->product_name; } return std::wstring(); });
    current_product_name.setter([this](const std::wstring& v) { if(*data_context) { data_context()->product_name = v; } });
    current_unit_price.getter([this]() -> double { if(*data_context) { return data_context()->unit_price; } return 0.0; });
    current_unit_price.setter([this](const double& v) { if(*data_context) { data_context()->unit_price = v; } });
    get_product_command.getter(
        [this]()
        {
            if(!_get_product_command)
            {
                _get_product_command = m::relay_wcommand::create(L"get_product",
                    [this](const m::command_parameters::ptr&)
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
                        product_model::ptr product = _products->get(current_product_id);
                        if(!product)
                        {
                            _products->insert(data_context);
                        }
                    },
                    [this](const m::command_parameters::ptr&) { return true; },
                    m::command_parameters::create());
            }
            return _save_product_command;
        });
}
