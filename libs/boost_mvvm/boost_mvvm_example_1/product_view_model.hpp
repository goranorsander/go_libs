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

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

#include "product_model.hpp"

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace rop = go_boost::property::read_only;

class product_view_model
    : public m::wobservable_object
    , boost::noncopyable
{
public:
    typedef product_view_model this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~product_view_model();

private:
    product_view_model();

public:
    static ptr create();

private:
    void bind_properties();

public:
    p::wproperty<int> product_id;
    p::wproperty<product_model::ptr> current_product;
    rop::wproperty<m::wcommand::ptr> get_product_command;
    rop::wproperty<m::wcommand::ptr> save_product_command;

private:
    int get_product_id() const;
    void set_product_id(const int& v);

    product_model::ptr get_current_product() const;
    void set_current_product(const product_model::ptr& v);

    m::wcommand::ptr get_get_product_command();
    void get_product(const m::command_parameters::ptr& /*params*/);
    bool can_get_product(const m::command_parameters::ptr& /*params*/) const;

    m::wcommand::ptr get_save_product_command();
    void save_product(const m::command_parameters::ptr& /*params*/);
    bool can_save_product(const m::command_parameters::ptr& /*params*/) const;

private:
    int _product_id;
    product_model::ptr _current_product;
    m::wcommand::ptr _get_product_command;
    m::wcommand::ptr _save_product_command;

    typedef std::map<int, product_model::ptr> products_type;

    products_type _products;
};

#endif  // #ifndef GO_PRODUCT_VIEW_MODEL_HPP_INCLUDED
