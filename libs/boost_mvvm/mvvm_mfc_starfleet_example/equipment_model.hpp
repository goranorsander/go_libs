#ifndef GO_BOOST_EQUIPMENT_MODEL_HPP_INCLUDED
#define GO_BOOST_EQUIPMENT_MODEL_HPP_INCLUDED

//
//  equipment_model.hpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go_boost/mvvm.hpp>
#include "equipment_id_type.hpp"
#include "equipment_interface.hpp"

class equipment_model
    : public equipment_interface
    , public m::wobservable_object
    , private tt::noncopyable_nonmovable
{
public:
    typedef equipment_model this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~equipment_model();

protected:
    equipment_model(const std::wstring& category_, const std::wstring& name_, const quantity_type& quantity_);

private:
    equipment_model();

public:
    pro::wproperty<equipment_id_type> id;

public:
    static ptr create(const std::wstring& category_, const std::wstring& name_, const quantity_type& quantity_);

protected:
    virtual void bind_properties() GO_BOOST_OVERRIDE;

private:
    static equipment_id_type _next_id;
    const equipment_id_type _id;

    const std::wstring _category;
    const std::wstring _name;
    quantity_type _quantity;
};

#endif  // #ifndef GO_BOOST_EQUIPMENT_MODEL_HPP_INCLUDED
