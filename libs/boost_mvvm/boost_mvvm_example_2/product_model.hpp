#ifndef GO_BOOST_PRODUCT_MODEL_HPP_INCLUDED
#define GO_BOOST_PRODUCT_MODEL_HPP_INCLUDED

//
//  product_model.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

namespace m = go_boost::mvvm;
namespace p = go_boost::property;

class product_model
    : public m::wobservable_object
    , boost::noncopyable
{
public:
    typedef product_model this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;
    typedef int product_id_type;

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
    p::wproperty<double> unit_price;

private:
    product_id_type _product_id;
    std::wstring _product_name;
    double _unit_price;
};

#endif  // #ifndef GO_BOOST_PRODUCT_MODEL_HPP_INCLUDED
