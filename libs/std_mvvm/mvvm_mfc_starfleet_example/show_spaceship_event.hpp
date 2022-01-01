#ifndef GO_SHOW_SPACESHIP_EVENT_HPP_INCLUDED
#define GO_SHOW_SPACESHIP_EVENT_HPP_INCLUDED

//
//  show_spaceship_event.hpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm/event.hpp>
#include <go/property/nameless/read_only_value_property.hpp>
#include "fleet_organization_id_type.hpp"
#include "spaceship_view_model.hpp"

class show_spaceship_event
    : public m::wevent
{
public:
    using this_type = show_spaceship_event;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

public:
    virtual ~show_spaceship_event() GO_DEFAULT_DESTRUCTOR

protected:
    explicit show_spaceship_event(const fleet_organization_id_type& id_);

private:
    show_spaceship_event() = delete;

public:
    pnro::value_property<fleet_organization_id_type> id;

public:
    static ptr create(const fleet_organization_id_type& id_);
};

#endif  // #ifndef GO_SHOW_SPACESHIP_EVENT_HPP_INCLUDED
