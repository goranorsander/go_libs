#ifndef GO_SHOW_SPACESHIP_EVENT_HPP_INCLUDED
#define GO_SHOW_SPACESHIP_EVENT_HPP_INCLUDED

//
//  show_spaceship_event.hpp
//
//  Copyright 2016-2017 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go/mvvm/event.hpp>
#include <go/property/nameless/read_only_value_property.hpp>
#include "spaceship_view_model.hpp"

typedef unsigned long fleet_organization_id_type;

class show_spaceship_event
    : public m::wevent
{
public:
    typedef show_spaceship_event this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~show_spaceship_event() = default;

protected:
    show_spaceship_event(const fleet_organization_id_type& id_);

private:
    show_spaceship_event() = delete;

public:
    nrop::value_property<fleet_organization_id_type> id;

public:
    static ptr create(const fleet_organization_id_type& id_);
};

#endif  // #ifndef GO_SHOW_SPACESHIP_EVENT_HPP_INCLUDED
