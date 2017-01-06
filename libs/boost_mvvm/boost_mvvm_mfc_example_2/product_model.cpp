//
//  product_model.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "product_model.hpp"

#include <go_boost/mvvm/utility.hpp>

namespace bp = boost::phoenix;
namespace bph = boost::phoenix::placeholders;
namespace mu = go_boost::mvvm::utility;

product_model::~product_model()
{
}

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
        virtual ~make_shared_enabler() {}
        make_shared_enabler() : this_type() {}
    };

    return boost::make_shared<make_shared_enabler>();
}

void product_model::bind_properties()
{
    product_id.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_product_id)));
    product_id.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(product_id.name(), boost::bind(&product_model::on_property_changed, this, _1), bp::ref(_product_id), bph::arg1));
    product_name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_product_name)));
    product_name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(product_name.name(), boost::bind(&product_model::on_property_changed, this, _1), bp::ref(_product_name), bph::arg1));
    unit_price.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_unit_price)));
    unit_price.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(unit_price.name(), boost::bind(&product_model::on_property_changed, this, _1), bp::ref(_unit_price), bph::arg1));
}
