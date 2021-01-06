#ifndef GO_PRODUCT_REPOSITORY_HPP_INCLUDED
#define GO_PRODUCT_REPOSITORY_HPP_INCLUDED

//
//  product_repository.hpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "product_repository_interface.hpp"

class product_repository
    : public product_repository_interface
    , public std::enable_shared_from_this<product_repository>
    , public tt::noncopyable_nonmovable
{
public:
    typedef product_repository this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~product_repository() GO_DEFAULT_DESTRUCTOR

protected:
    product_repository() GO_DEFAULT_CONSTRUCTOR

public:
    static ptr create();

    virtual product_model::ptr get(const product_id_type& product_id) const override;
    virtual bool insert(const product_model::ptr& product) override;
    virtual bool remove(const product_id_type& product_id) override;

private:
    typedef std::map<product_id_type, product_model::ptr> products_type;

    products_type _products;
};

#endif  // #ifndef GO_PRODUCT_REPOSITORY_HPP_INCLUDED
