#ifndef GO_BOOST_PRODUCT_REPOSITORY_INTERFACE_HPP_INCLUDED
#define GO_BOOST_PRODUCT_REPOSITORY_INTERFACE_HPP_INCLUDED

//
//  product_repository_interface.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "product_model.hpp"

class product_repository_interface
{
public:
    typedef product_repository_interface this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~product_repository_interface() = 0;

protected:
    product_repository_interface();

public:
    virtual product_model::ptr get(const product_model::product_id_type& product_id) const = 0;
    virtual bool insert(const product_model::ptr& product) = 0;
    virtual bool remove(const product_model::product_id_type& product_id) = 0;
};

inline product_repository_interface::~product_repository_interface()
{
}

inline product_repository_interface::product_repository_interface()
{
}

#endif  // #ifndef GO_BOOST_PRODUCT_REPOSITORY_INTERFACE_HPP_INCLUDED
