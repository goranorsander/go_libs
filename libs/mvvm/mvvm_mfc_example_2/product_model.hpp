#ifndef GO_PRODUCT_MODEL_HPP_INCLUDED
#define GO_PRODUCT_MODEL_HPP_INCLUDED

//
//  product_model.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm.hpp>
#include <go/property.hpp>

namespace m = go::mvvm;
namespace p = go::property;
namespace u = go::utility;

class product_model
    : public m::wobservable_object
    , public u::noncopyable_nonmovable
{
public:
    typedef product_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;
    typedef int product_id_type;

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
    p::wproperty<double> unit_price;

private:
    product_id_type _product_id;
    std::wstring _product_name;
    double _unit_price;
};

#endif  // #ifndef GO_PRODUCT_MODEL_HPP_INCLUDED
