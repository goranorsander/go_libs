#ifndef GO_TEST_FRAMEWORK_GO_TEST_FLEET_COMMANDER_CHANGED_EVENT_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_FLEET_COMMANDER_CHANGED_EVENT_HPP_INCLUDED

//
//  fleet_commander_changed_event.hpp
//
//  Copyright 2021-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/mvvm.hpp>
#include <go_test/spaceship_event_type.hpp>

#if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

namespace go_test
{

template <class S, class ROSVP>
class fleet_commander_changed_event
    : public m::basic_event<S>
{
public:
#if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    typedef fleet_commander_changed_event<S, ROSVP> this_type;
#else
    using this_type = fleet_commander_changed_event<S, ROSVP>;
#endif  // #if defined(GO_NO_CXX11_TEMPLATE_ALIASES)
    GO_USING(string_identifier_type, S);
    GO_USING(read_only_string_value_property_type, ROSVP);
    GO_USING(ptr, GO_TYPENAME std::shared_ptr<fleet_commander_changed_event>);
    GO_USING(wptr, GO_TYPENAME std::weak_ptr<fleet_commander_changed_event>);

public:
    virtual ~fleet_commander_changed_event() GO_DEFAULT_DESTRUCTOR

protected:
    explicit fleet_commander_changed_event(const string_identifier_type& fleet_commander_)
        : m::basic_event<string_identifier_type>(spaceship_event_type<string_identifier_type>::fleet_commander_changed())
        , fleet_commander(s::create<string_identifier_type>("fleet_commander"), fleet_commander_)
    {
    }

public:
    read_only_string_value_property_type fleet_commander;

public:
    static ptr create(const string_identifier_type& fleet_commander_)
    {
#if GO_MSVC_VER > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const string_identifier_type& fleet_commander_) : this_type(fleet_commander_) {}
        };
        return std::make_shared<make_shared_enabler, const string_identifier_type&>(fleet_commander_);
#else
        return std::shared_ptr<this_type>(new this_type(fleet_commander_));
#endif // GO_MSVC_VER > 1500
    }
};

}

#endif  // #if !(defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_MUTEX))

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_FLEET_COMMANDER_CHANGED_EVENT_HPP_INCLUDED
