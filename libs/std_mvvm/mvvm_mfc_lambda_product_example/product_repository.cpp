//
//  product_repository.cpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "product_repository.hpp"

product_repository::ptr product_repository::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
    };

    return std::make_shared<make_shared_enabler>();
}

product_model::ptr product_repository::get(const product_model::product_id_type& product_id) const
{
    products_type::const_iterator it = _products.find(product_id);
    if(it != _products.end())
    {
        return it->second;
    }
    return nullptr;
}

bool product_repository::insert(const product_model::ptr& product)
{
    if(!product)
    {
        return false;
    }
    products_type::const_iterator it = _products.find(product->product_id);
    if(it == _products.end())
    {
        _products[product->product_id] = product;
        return true;
    }
    return false;
}

bool product_repository::remove(const product_model::product_id_type& product_id)
{
    products_type::const_iterator it = _products.find(product_id);
    if(it != _products.end())
    {
        _products.erase(it);
        return true;
    }
    return false;
}
