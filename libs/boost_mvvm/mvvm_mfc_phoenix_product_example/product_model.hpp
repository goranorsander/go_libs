#ifndef GO_BOOST_PRODUCT_MODEL_HPP_INCLUDED
#define GO_BOOST_PRODUCT_MODEL_HPP_INCLUDED

//
//  product_model.hpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go_boost/mvvm.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/property.hpp>
#include <go_boost/type_traits/fundamental_type_specializer.hpp>

GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(currency_type, double);
GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(product_id_type, int);

class product_model
    : public m::wobservable_object
    , tt::noncopyable_nonmovable
{
public:
    typedef product_model this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~product_model();

private:
    product_model();

public:
    static ptr create();

private:
    void bind_properties();

public:
    p::wproperty<product_id_type> product_id;
    p::wproperty<std::wstring> product_name;
    p::wproperty<currency_type> unit_price;

private:
    product_id_type _product_id;
    std::wstring _product_name;
    currency_type _unit_price;
};

#endif  // #ifndef GO_BOOST_PRODUCT_MODEL_HPP_INCLUDED
