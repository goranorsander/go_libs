//
//  product_view_model.cpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include <go_boost/config.hpp>

#if (BOOST_COMP_MSVC) && (BOOST_MSVC <= 1700)
GO_BOOST_MESSAGE("Boost.Phoenix is not supported by this compiler")
#else

#include "product_view_model.hpp"
#include "product_repository.hpp"

#include <go_boost/mvvm/utility.hpp>

namespace bp = boost::phoenix;
namespace bph = boost::phoenix::placeholders;
namespace mu = go_boost::mvvm::utility;

product_view_model::~product_view_model()
{
}

product_view_model::product_view_model()
    : m::wobservable_object()
    , m::data_context_interface<product_model::ptr>(product_model::create())
    , u::noncopyable_nonmovable()
    , _product_id(0)
    , _get_product_command()
    , _save_product_command()
    , _products(product_repository::create())
    , product_id(L"product_id")
    , current_product_id(L"current_product_id")
    , current_product_name(L"current_product_name")
    , current_unit_price(L"current_unit_price")
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
    current_product_id.getter(boost::bind(&product_view_model::get_current_product_id, this));
    current_product_id.setter(boost::bind(&product_view_model::set_current_product_id, this, _1));
    current_product_name.getter(boost::bind(&product_view_model::get_current_product_name, this));
    current_product_name.setter(boost::bind(&product_view_model::set_current_product_name, this, _1));
    current_unit_price.getter(boost::bind(&product_view_model::get_current_unit_price, this));
    current_unit_price.setter(boost::bind(&product_view_model::set_current_unit_price, this, _1));
    get_product_command.getter(bp::bind(mu::get_wproperty_relay_wcommand, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(std::wstring(L"get_product"), boost::bind(&product_view_model::get_product, this, _1), boost::bind(&product_view_model::can_get_product, this, _1), m::command_parameters::create(), bp::ref(_get_product_command)));
    save_product_command.getter(bp::bind(mu::get_wproperty_relay_wcommand, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(std::wstring(L"save_product"), boost::bind(&product_view_model::save_product, this, _1), boost::bind(&product_view_model::can_save_product, this, _1), m::command_parameters::create(), bp::ref(_save_product_command)));
}

product_model::product_id_type product_view_model::get_current_product_id() const
{
    if(*data_context)
    {
        return data_context.get()->product_id;
    }
    return 0;
}

void product_view_model::set_current_product_id(const product_model::product_id_type& v)
{
    if(*data_context)
    {
        data_context.get()->product_id = v;
    }
}

std::wstring product_view_model::get_current_product_name() const
{
    if(*data_context)
    {
        return data_context.get()->product_name;
    }
    return std::wstring();
}

void product_view_model::set_current_product_name(const std::wstring& v)
{
    if(*data_context)
    {
        data_context.get()->product_name = v;
    }
}

double product_view_model::get_current_unit_price() const
{
    if(*data_context)
    {
        return data_context.get()->unit_price;
    }
    return 0.0;
}

void product_view_model::set_current_unit_price(const double& v)
{
    if(*data_context)
    {
        data_context.get()->unit_price = v;
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
        new_product->unit_price = 10.0;
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

#endif  // Boost.Phoenix is not supported by this compiler