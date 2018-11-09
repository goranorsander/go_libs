#ifndef GO_EQUIPMENT_MODEL_HPP_INCLUDED
#define GO_EQUIPMENT_MODEL_HPP_INCLUDED

//
//  equipment_model.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm.hpp>
#include "equipment_interface.hpp"

typedef unsigned long equipment_id_type;

class equipment_model
    : public equipment_interface
    , public mst::wobservable_object
    , private u::noncopyable_nonmovable
{
public:
    typedef equipment_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~equipment_model() GO_DEFAULT_DESTRUCTOR

protected:
    equipment_model(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_);

private:
    equipment_model() = delete;

public:
    rop::wproperty<equipment_id_type> id;

public:
    static ptr create(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_);

protected:
    virtual void bind_properties();

private:
    static equipment_id_type _next_id;
    const equipment_id_type _id;

    const std::wstring _category;
    const std::wstring _name;
    unsigned int _quantity;
};

#endif  // #ifndef GO_EQUIPMENT_MODEL_HPP_INCLUDED
