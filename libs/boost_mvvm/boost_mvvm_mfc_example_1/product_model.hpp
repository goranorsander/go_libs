#ifndef GO_BOOST_PRODUCT_MODEL_HPP_INCLUDED
#define GO_BOOST_PRODUCT_MODEL_HPP_INCLUDED

//
//  product_model.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace u = go_boost::utility;

class product_model
    : public m::wobservable_object
    , u::noncopyable_nonmovable
{
public:
    typedef product_model this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;
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
    product_id_type get_product_id() const;
    void set_product_id(const product_id_type& v);

    std::wstring get_product_name() const;
    void set_product_name(const std::wstring& v);

    double get_unit_price() const;
    void set_unit_price(const double& v);

private:
    product_id_type _product_id;
    std::wstring _product_name;
    double _unit_price;
};

#endif  // #ifndef GO_BOOST_PRODUCT_MODEL_HPP_INCLUDED
