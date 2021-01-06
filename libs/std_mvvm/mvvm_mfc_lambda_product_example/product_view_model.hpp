#ifndef GO_PRODUCT_VIEW_MODEL_HPP_INCLUDED
#define GO_PRODUCT_VIEW_MODEL_HPP_INCLUDED

//
//  product_view_model.hpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>
#include <go/property.hpp>

#include "product_model.hpp"
#include "product_repository_interface.hpp"

class product_view_model
    : public m::wobservable_object
    , public m::data_context_interface<product_model::ptr>
    , public tt::noncopyable_nonmovable
{
public:
    typedef product_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~product_view_model() GO_DEFAULT_DESTRUCTOR

private:
    product_view_model();

public:
    static ptr create();

private:
    void bind_properties();

public:
    p::wproperty<product_id_type> product_id;
    p::wproperty<product_id_type> current_product_id;
    p::wproperty<std::wstring> current_product_name;
    p::wproperty<currency_type> current_unit_price;

    pro::wproperty<m::wcommand_interface::ptr> get_product_command;
    pro::wproperty<m::wcommand_interface::ptr> save_product_command;

private:
    product_id_type _product_id;
    m::wcommand_interface::ptr _get_product_command;
    m::wcommand_interface::ptr _save_product_command;

    product_repository_interface::ptr _products;
};

#endif  // #ifndef GO_PRODUCT_VIEW_MODEL_HPP_INCLUDED
