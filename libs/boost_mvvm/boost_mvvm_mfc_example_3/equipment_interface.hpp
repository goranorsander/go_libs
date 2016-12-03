#ifndef GO_EQUIPMENT_INTERFACE_HPP_INCLUDED
#define GO_EQUIPMENT_INTERFACE_HPP_INCLUDED

//
//  equipment_interface.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/property.hpp>

class equipment_interface
{
public:
    typedef equipment_interface this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~equipment_interface() = 0;

protected:
    equipment_interface();

public:
    rop::wproperty<std::wstring> category;
    rop::wproperty<std::wstring> name;
    p::wproperty<unsigned int> quantity;

protected:
    virtual void bind_properties() = 0;
};

inline equipment_interface::~equipment_interface()
{
}

inline equipment_interface::equipment_interface()
    : category(L"equipment_interface::category")
    , name(L"equipment_interface::name")
    , quantity(L"equipment_interface::quantity")
{
}

#endif  // #ifndef GO_EQUIPMENT_INTERFACE_HPP_INCLUDED
