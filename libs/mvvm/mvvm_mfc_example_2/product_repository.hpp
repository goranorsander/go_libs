#ifndef GO_PRODUCT_REPOSITORY_HPP_INCLUDED
#define GO_PRODUCT_REPOSITORY_HPP_INCLUDED

//
//  product_repository.hpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "product_repository_interface.hpp"

class product_repository
    : public product_repository_interface
    , public std::enable_shared_from_this<product_repository>
    , public u::noncopyable_nonmovable
{
public:
    typedef product_repository this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~product_repository() = default;

protected:
    product_repository() = default;

public:
    static ptr create();

    virtual product_model::ptr get(const product_model::product_id_type& product_id) const;
    virtual bool insert(const product_model::ptr& product);
    virtual bool remove(const product_model::product_id_type& product_id);

private:
    typedef std::map<product_model::product_id_type, product_model::ptr> products_type;

    products_type _products;
};

#endif  // #ifndef GO_PRODUCT_REPOSITORY_HPP_INCLUDED