#ifndef GO_BOOST_PRODUCT_VIEW_MODEL_HPP_INCLUDED
#define GO_BOOST_PRODUCT_VIEW_MODEL_HPP_INCLUDED

//
//  product_view_model.hpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

#include "product_model.hpp"
#include "product_repository_interface.hpp"

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace rop = go_boost::property::read_only;

class product_view_model
    : public m::wobservable_object
    , public m::data_context_interface<product_model::ptr>
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
    p::wproperty<product_model::product_id_type> product_id;
    p::wproperty<product_model::product_id_type> current_product_id;
    p::wproperty<std::wstring> current_product_name;
    p::wproperty<double> current_unit_price;

    rop::wproperty<m::wcommand::ptr> get_product_command;
    rop::wproperty<m::wcommand::ptr> save_product_command;

private:
    product_model::product_id_type get_current_product_id() const;
    void set_current_product_id(const product_model::product_id_type& v);

    std::wstring get_current_product_name() const;
    void set_current_product_name(const std::wstring& v);

    double get_current_unit_price() const;
    void set_current_unit_price(const double& v);

    void get_product(const m::command_parameters::ptr& /*params*/);
    bool can_get_product(const m::command_parameters::ptr& /*params*/) const;

    void save_product(const m::command_parameters::ptr& /*params*/);
    bool can_save_product(const m::command_parameters::ptr& /*params*/) const;

private:
    product_model::product_id_type _product_id;
    m::wcommand::ptr _get_product_command;
    m::wcommand::ptr _save_product_command;

    product_repository_interface::ptr _products;
};

#endif  // #ifndef GO_BOOST_PRODUCT_VIEW_MODEL_HPP_INCLUDED
