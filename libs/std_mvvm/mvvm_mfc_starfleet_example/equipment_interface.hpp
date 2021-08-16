#ifndef GO_EQUIPMENT_INTERFACE_HPP_INCLUDED
#define GO_EQUIPMENT_INTERFACE_HPP_INCLUDED

//
//  equipment_interface.hpp
//
//  Copyright 2016-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/property.hpp>

class equipment_interface
{
public:
    using this_type = equipment_interface;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

public:
    virtual ~equipment_interface() = 0;

protected:
    equipment_interface();

public:
    pro::wproperty<std::wstring> category;
    pro::wproperty<std::wstring> name;
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
