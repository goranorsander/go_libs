#ifndef GO_SPACESHIP_INTERFACE_HPP_INCLUDED
#define GO_SPACESHIP_INTERFACE_HPP_INCLUDED

//
//  spaceship_interface.hpp
//
//  Copyright 2016-2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm.hpp>
#include "equipment_interface.hpp"

class spaceship_interface
{
public:
    typedef spaceship_interface this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~spaceship_interface() = 0;

protected:
     spaceship_interface();

public:
    rop::wproperty<std::wstring> spaceship_class;
    rop::wproperty<std::wstring> name;

    p::wproperty<std::wstring> captain;
    p::wproperty<unsigned int> crew_complement;
    p::wproperty<m::wobservable_deque<equipment_interface::ptr>::ptr> equipment;

protected:
    virtual void bind_properties() = 0;
};

inline spaceship_interface::~spaceship_interface()
{
}

inline spaceship_interface::spaceship_interface()
    : spaceship_class(L"spaceship_interface::spaceship_class")
    , name(L"spaceship_interface::name")
    , captain(L"spaceship_interface::captain")
    , crew_complement(L"spaceship_interface::crew_complement")
    , equipment(L"spaceship_interface::equipment")
{
}

#endif  // #ifndef GO_SPACESHIP_INTERFACE_HPP_INCLUDED