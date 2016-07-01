#ifndef GO_PRODUCT_VIEW_MODEL_HPP_INCLUDED
#define GO_PRODUCT_VIEW_MODEL_HPP_INCLUDED

//
//  product_view_model.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <map>

#include <go/mvvm.hpp>
#include <go/property.hpp>

#include "product_model.hpp"

namespace m = go::mvvm;
namespace p = go::property;
namespace rop = go::property::read_only;

class product_view_model
    : public m::wobservable_object
{
public:
    typedef product_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~product_view_model() = default;

private:
    product_view_model();
    product_view_model(const product_view_model&) = delete;
    product_view_model(product_view_model&&) = delete;

public:
    static ptr create();

private:
    product_view_model& operator=(const product_view_model&) = delete;
    product_view_model& operator=(product_view_model&&) = delete;

private:
    void bind_properties();

public:
    p::wproperty<int> product_id;
    p::wproperty<product_model::ptr> current_product;
    rop::wproperty<m::wcommand::ptr> get_product_command;
    rop::wproperty<m::wcommand::ptr> save_product_command;

private:
    int _product_id;
    product_model::ptr _current_product;
    m::wcommand::ptr _get_product_command;
    m::wcommand::ptr _save_product_command;

    typedef std::map<int, product_model::ptr> products_type;

    products_type _products;
};

#endif  // #ifndef GO_PRODUCT_VIEW_MODEL_HPP_INCLUDED
