//
//  close_spaceship_event.cpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "close_spaceship_event.hpp"

close_spaceship_event::~close_spaceship_event()
{
}

close_spaceship_event::close_spaceship_event(const spaceship_view_model::ptr& vm)
    : m::wevent(L"close spaceship event")
    , spaceship_vm(vm)
{
}

close_spaceship_event::close_spaceship_event()
    : m::wevent(L"")
    , spaceship_vm(spaceship_view_model::ptr())
{
}

close_spaceship_event::ptr close_spaceship_event::create(const spaceship_view_model::ptr& vm)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const spaceship_view_model::ptr& vm) : this_type(vm) {}
    };

    return boost::make_shared<make_shared_enabler, const spaceship_view_model::ptr&>(vm);
#else
    return boost::shared_ptr<this_type>(new this_type(vm));
#endif // BOOST_MSVC > 1500
}
