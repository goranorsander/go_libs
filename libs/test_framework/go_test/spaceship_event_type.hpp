#ifndef GO_TEST_FRAMEWORK_GO_TEST_SPACESHIP_EVENT_TYPE_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_SPACESHIP_EVENT_TYPE_HPP_INCLUDED

//
//  spaceship_event_type.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/namespace_alias.hpp>
#include <go/string.hpp>

namespace go_test
{

template <class S>
struct spaceship_event_type
{
    typedef spaceship_event_type<S> this_type;
    typedef S string_identifier_type;

    static const string_identifier_type& fleet_commander_changed()
    {
        static const string_identifier_type e = s::create<string_identifier_type>("fleet commander changed");
        return e;
    }
};

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_SPACESHIP_EVENT_TYPE_HPP_INCLUDED
