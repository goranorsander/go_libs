#ifndef GO_BOOST_SPACESHIP_INTERFACE_HPP_INCLUDED
#define GO_BOOST_SPACESHIP_INTERFACE_HPP_INCLUDED

//
//  spaceship_interface.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm.hpp>
#include "equipment_interface.hpp"

class spaceship_interface
{
public:
    typedef spaceship_interface this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~spaceship_interface() = 0;

protected:
    spaceship_interface();

public:
    rop::wproperty<std::wstring> spaceship_class;
    rop::wproperty<std::wstring> name;

    p::wproperty<std::wstring> captain;
    p::wproperty<unsigned int> crew_complement;
    p::wproperty<m::wobservable_list<equipment_interface::ptr>::ptr> equipment;

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

#endif  // #ifndef GO_BOOST_SPACESHIP_INTERFACE_HPP_INCLUDED
