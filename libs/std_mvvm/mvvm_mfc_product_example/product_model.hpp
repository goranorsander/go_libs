#ifndef GO_PRODUCT_MODEL_HPP_INCLUDED
#define GO_PRODUCT_MODEL_HPP_INCLUDED

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

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>
#include <go/property.hpp>
#include <go/utility.hpp>

GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(currency_type, double);
GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(product_id_type, int);

class product_model
    : public m::wobservable_object
    , public tt::noncopyable_nonmovable
{
public:
    typedef product_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~product_model() GO_DEFAULT_DESTRUCTOR

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
    product_id_type get_product_id() const;
    void set_product_id(const product_id_type& v);

    std::wstring get_product_name() const;
    void set_product_name(const std::wstring& v);

    currency_type get_unit_price() const;
    void set_unit_price(const currency_type& v);

private:
    product_id_type _product_id;
    std::wstring _product_name;
    currency_type _unit_price;
};

#endif  // #ifndef GO_PRODUCT_MODEL_HPP_INCLUDED
