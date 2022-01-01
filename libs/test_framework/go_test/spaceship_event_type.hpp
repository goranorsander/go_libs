#ifndef GO_TEST_FRAMEWORK_GO_TEST_SPACESHIP_EVENT_TYPE_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_SPACESHIP_EVENT_TYPE_HPP_INCLUDED

//
//  spaceship_event_type.hpp
//
//  Copyright 2021-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/namespace_alias.hpp>
#include <go/string.hpp>

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

namespace go_test
{

template <class S>
struct spaceship_event_type
{
    GO_USING(this_type, spaceship_event_type<S>);
    GO_USING(string_identifier_type, S);

    static const string_identifier_type& fleet_commander_changed()
    {
        static const string_identifier_type e = s::create<string_identifier_type>("fleet commander changed");
        return e;
    }
};

}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_SPACESHIP_EVENT_TYPE_HPP_INCLUDED
