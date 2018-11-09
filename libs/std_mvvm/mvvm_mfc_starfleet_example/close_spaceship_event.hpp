#ifndef GO_CLOSE_SPACESHIP_EVENT_HPP_INCLUDED
#define GO_CLOSE_SPACESHIP_EVENT_HPP_INCLUDED

//
//  close_spaceship_event.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm/event.hpp>
#include <go/property/nameless/read_only_value_property.hpp>
#include "spaceship_view_model.hpp"

class close_spaceship_event
    : public m::wevent
{
public:
    typedef close_spaceship_event this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~close_spaceship_event() GO_DEFAULT_DESTRUCTOR

protected:
    explicit close_spaceship_event(const spaceship_view_model::ptr& vm);

private:
    close_spaceship_event() = delete;

public:
    nrop::value_property<spaceship_view_model::ptr> spaceship_vm;

public:
    static ptr create(const spaceship_view_model::ptr& vm);
};

#endif  // #ifndef GO_CLOSE_SPACESHIP_EVENT_HPP_INCLUDED
