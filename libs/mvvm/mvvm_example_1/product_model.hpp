#ifndef GO_PRODUCT_MODEL_HPP_INCLUDED
#define GO_PRODUCT_MODEL_HPP_INCLUDED

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

#include <go/mvvm.hpp>
#include <go/property.hpp>

namespace m = go::mvvm;
namespace p = go::property;

class product_model
    : public m::wobservable_object
{
public:
    typedef product_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~product_model() = default;

private:
    product_model();
    product_model(const product_model&) = delete;
    product_model(product_model&&) = delete;

public:
    static ptr create();

private:
    product_model& operator=(const product_model&) = delete;
    product_model& operator=(product_model&&) = delete;

private:
    void bind_properties();

public:
    p::wproperty<int> product_id;
    p::wproperty<std::wstring> product_name;
    p::wproperty<double> unit_price;

private:
    int get_product_id() const;
    void set_product_id(const int& v);

    std::wstring get_product_name() const;
    void set_product_name(const std::wstring& v);

    double get_unit_price() const;
    void set_unit_price(const double& v);

private:
    int _product_id;
    std::wstring _product_name;
    double _unit_price;
};

#endif  // #ifndef GO_PRODUCT_MODEL_HPP_INCLUDED
