#ifndef GO_EQUIPMENT_MODEL_HPP_INCLUDED
#define GO_EQUIPMENT_MODEL_HPP_INCLUDED

//
//  equipment_model.hpp
//
//  Copyright 2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm.hpp>
#include "equipment_interface.hpp"

class equipment_model
    : public equipment_interface
    , public m::wobservable_object
    , private boost::noncopyable
{
public:
    typedef equipment_model this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~equipment_model();

protected:
    equipment_model(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_);

private:
    equipment_model() = delete;

public:
    static ptr create(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_);

protected:
    virtual void bind_properties();

private:
    const std::wstring _category;
    const std::wstring _name;
    unsigned int _quantity;
};

#endif  // #ifndef GO_EQUIPMENT_MODEL_HPP_INCLUDED
