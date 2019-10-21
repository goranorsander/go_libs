//
//  show_spaceship_event.cpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "show_spaceship_event.hpp"

show_spaceship_event::~show_spaceship_event()
{
}

show_spaceship_event::show_spaceship_event(const fleet_organization_id_type& id_)
    : m::wevent(L"show spaceship event")
    , id(id_)
{
}

show_spaceship_event::show_spaceship_event()
    : m::wevent(L"")
    , id(fleet_organization_id_type(0))
{
}

show_spaceship_event::ptr show_spaceship_event::create(const fleet_organization_id_type& id_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const fleet_organization_id_type& id_) : this_type(id_) {}
    };

    return boost::make_shared<make_shared_enabler, const fleet_organization_id_type&>(id_);
#else
    return boost::shared_ptr<this_type>(new this_type(id_));
#endif // BOOST_MSVC > 1500
}
