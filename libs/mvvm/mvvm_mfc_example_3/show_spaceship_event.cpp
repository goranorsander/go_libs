//
//  show_spaceship_event.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "show_spaceship_event.hpp"

show_spaceship_event::show_spaceship_event(const fleet_organization_id_type& id_)
    : m::wevent(L"show spaceship event")
    , id(id_)
{
}

show_spaceship_event::ptr show_spaceship_event::create(const fleet_organization_id_type& id_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const fleet_organization_id_type& id_) : this_type(id_) {}
    };

    return std::make_shared<make_shared_enabler, const fleet_organization_id_type&>(id_);
}
