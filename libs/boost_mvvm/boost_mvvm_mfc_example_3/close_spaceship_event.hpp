#ifndef GO_BOOST_CLOSE_SPACESHIP_EVENT_HPP_INCLUDED
#define GO_BOOST_CLOSE_SPACESHIP_EVENT_HPP_INCLUDED

//
//  close_spaceship_event.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm/event.hpp>
#include <go_boost/property/nameless/read_only_value_property.hpp>
#include "spaceship_view_model.hpp"

class close_spaceship_event
    : public m::wevent
{
public:
    typedef close_spaceship_event this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~close_spaceship_event();

protected:
    explicit close_spaceship_event(const spaceship_view_model::ptr& vm);

private:
    close_spaceship_event();

public:
    nrop::value_property<spaceship_view_model::ptr> spaceship_vm;

public:
    static ptr create(const spaceship_view_model::ptr& vm);
};

#endif  // #ifndef GO_BOOST_CLOSE_SPACESHIP_EVENT_HPP_INCLUDED
