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
    product_id.getter([this]() { return _product_id; });
    product_id.setter([this](const product_id_type& v) { if(v != _product_id) { _product_id = v; on_property_changed(product_id.name()); } });
    product_name.getter([this]() { return _product_name; });
    product_name.setter([this](const std::wstring& v) { if(v != _product_name) { _product_name = v; on_property_changed(product_name.name()); } });
    unit_price.getter([this]() { return _unit_price; });
    unit_price.setter([this](const double& v) { if(v != _unit_price) { _unit_price = v; on_property_changed(unit_price.name()); } });
}
