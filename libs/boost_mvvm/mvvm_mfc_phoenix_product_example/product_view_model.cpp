//
//  product_view_model.cpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include <go_boost/config.hpp>

#if defined(GO_BOOST_NO_BOOST_PHOENIX)
GO_BOOST_MESSAGE("Boost.Phoenix is not supported by this compiler")
#else

#include "product_view_model.hpp"
#include "product_repository.hpp"

#include <go_boost/mvvm/utility.hpp>

product_view_model::~product_view_model()
{
}

product_view_model::product_view_model()
    : m::wobservable_object()
    , m::data_context_interface<product_model::ptr>(product_model::create())
    , tt::noncopyable_nonmovable()
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
}

product_view_model::ptr product_view_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    product_view_model::ptr view_model = boost::make_shared<make_shared_enabler>();
    view_model->bind_properties();
    return view_model;
}

void product_view_model::bind_properties()
{
    product_id.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_product_id)));
    product_id.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), product_id.name(), boost::bind(&product_view_model::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(_product_id), bph::arg1, bph::arg2));
    current_product_id.getter(boost::bind(&product_view_model::get_current_product_id, this));
    current_product_id.setter(boost::bind(&product_view_model::set_current_product_id, this, boost::placeholders::_1));
    current_product_name.getter(boost::bind(&product_view_model::get_current_product_name, this));
    current_product_name.setter(boost::bind(&product_view_model::set_current_product_name, this, boost::placeholders::_1));
    current_unit_price.getter(boost::bind(&product_view_model::get_current_unit_price, this));
    current_unit_price.setter(boost::bind(&product_view_model::set_current_unit_price, this, boost::placeholders::_1));
    get_product_command.getter(bp::bind(mu::get_wproperty_relay_wcommand, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(std::wstring(L"get_product"), boost::bind(&product_view_model::get_product, this, boost::placeholders::_1), boost::bind(&product_view_model::can_get_product, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(_get_product_command)));
    save_product_command.getter(bp::bind(mu::get_wproperty_relay_wcommand, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(std::wstring(L"save_product"), boost::bind(&product_view_model::save_product, this, boost::placeholders::_1), boost::bind(&product_view_model::can_save_product, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(_save_product_command)));
}

product_id_type product_view_model::get_current_product_id() const
{
    if(*data_context)
    {
        return data_context()->product_id;
    }
    return product_id_type(0);
}

void product_view_model::set_current_product_id(const product_id_type& v)
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

currency_type product_view_model::get_current_unit_price() const
{
    if(*data_context)
    {
        return data_context()->unit_price;
    }
    return currency_type(0.0);
}

void product_view_model::set_current_unit_price(const currency_type& v)
{
    if(*data_context)
    {
        data_context()->unit_price = v;
    }
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
        new_product->unit_price = currency_type(10.0);
        data_context = new_product;
    }
}

bool product_view_model::can_get_product(const m::command_parameters::ptr& /*params*/) const
{
    return true;
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

#endif  // #if defined(GO_BOOST_NO_BOOST_PHOENIX)
