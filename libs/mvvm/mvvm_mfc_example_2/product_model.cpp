//
//  product_model.cpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "product_model.hpp"

#include <functional>

namespace ph = std::placeholders;

product_model::product_model()
    : m::wobservable_object()
    , u::noncopyable_nonmovable()
    , product_id(L"product_id")
    , product_name(L"product_name")
    , unit_price(L"unit_price")
    , _product_id(0)
    , _product_name()
    , _unit_price(0.0)
{
    bind_properties();
}

product_model::ptr product_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
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
