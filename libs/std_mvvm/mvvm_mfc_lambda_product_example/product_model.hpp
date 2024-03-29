#ifndef GO_PRODUCT_MODEL_HPP_INCLUDED
#define GO_PRODUCT_MODEL_HPP_INCLUDED

//
//  product_model.hpp
//
//  Copyright 2016-2022 G�ran Orsander
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
    using this_type = product_model;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

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
    product_id_type _product_id;
    std::wstring _product_name;
    currency_type _unit_price;
};

#endif  // #ifndef GO_PRODUCT_MODEL_HPP_INCLUDED
