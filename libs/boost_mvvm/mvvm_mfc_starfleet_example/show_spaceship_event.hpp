#ifndef GO_BOOST_SHOW_SPACESHIP_EVENT_HPP_INCLUDED
#define GO_BOOST_SHOW_SPACESHIP_EVENT_HPP_INCLUDED

//
//  show_spaceship_event.hpp
//
//  Copyright 2016-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go_boost/mvvm/event.hpp>
#include <go_boost/property/nameless/read_only_value_property.hpp>
#include "fleet_organization_id_type.hpp"
#include "spaceship_view_model.hpp"

class show_spaceship_event
    : public m::wevent
{
public:
    typedef show_spaceship_event this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~show_spaceship_event();

protected:
    explicit show_spaceship_event(const fleet_organization_id_type& id_);

private:
    show_spaceship_event();

public:
    pnro::value_property<fleet_organization_id_type> id;

public:
    static ptr create(const fleet_organization_id_type& id_);
};

#endif  // #ifndef GO_BOOST_SHOW_SPACESHIP_EVENT_HPP_INCLUDED
