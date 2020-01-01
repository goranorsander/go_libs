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

#include <go_boost/mvvm/utility.hpp>

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
    product_id.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_product_id)));
    product_id.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), product_id.name(), boost::bind(&product_model::notify_property_changed, this, _1, _2), bp::ref(_product_id), bph::arg1, bph::arg2));
    product_name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_product_name)));
    product_name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), product_name.name(), boost::bind(&product_model::notify_property_changed, this, _1, _2), bp::ref(_product_name), bph::arg1, bph::arg2));
    unit_price.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_unit_price)));
    unit_price.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), unit_price.name(), boost::bind(&product_model::notify_property_changed, this, _1, _2), bp::ref(_unit_price), bph::arg1, bph::arg2));
}
