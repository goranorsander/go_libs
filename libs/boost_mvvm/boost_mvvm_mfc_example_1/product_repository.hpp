#ifndef GO_BOOST_PRODUCT_REPOSITORY_HPP_INCLUDED
#define GO_BOOST_PRODUCT_REPOSITORY_HPP_INCLUDED

//
//  product_repository.hpp
//
//  Copyright 2016-2017 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "product_repository_interface.hpp"

namespace u = go_boost::utility;

class product_repository
    : public product_repository_interface
    , public boost::enable_shared_from_this<product_repository>
    , u::noncopyable_nonmovable
{
public:
    typedef product_repository this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~product_repository();

protected:
    product_repository();

public:
    static ptr create();

    virtual product_model::ptr get(const product_model::product_id_type& product_id) const;
    virtual bool insert(const product_model::ptr& product);
    virtual bool remove(const product_model::product_id_type& product_id);

private:
    typedef std::map<product_model::product_id_type, product_model::ptr> products_type;

    products_type _products;
};

#endif  // #ifndef GO_BOOST_PRODUCT_REPOSITORY_HPP_INCLUDED
