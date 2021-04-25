#ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_FLEET_COMMANDER_CHANGED_EVENT_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_BOOST_TEST_FLEET_COMMANDER_CHANGED_EVENT_HPP_INCLUDED

//
//  fleet_commander_changed_event.hpp
//
//  Copyright 2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#include <go_boost/mvvm.hpp>
#include <go_boost_test/spaceship_event_type.hpp>

namespace go_boost_test
{

template <class S, class ROSVP>
class fleet_commander_changed_event
    : public m::basic_event<S>
{
public:
    typedef fleet_commander_changed_event<S, ROSVP> this_type;
    typedef S string_identifier_type;
    typedef ROSVP read_only_string_value_property_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<fleet_commander_changed_event> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<fleet_commander_changed_event> wptr;

public:
    virtual ~fleet_commander_changed_event() GO_BOOST_DEFAULT_DESTRUCTOR

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
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const string_identifier_type& fleet_commander_) : this_type(fleet_commander_) {}
        };
        return boost::make_shared<make_shared_enabler, const string_identifier_type&>(fleet_commander_);
#else
        return boost::shared_ptr<this_type>(new this_type(fleet_commander_));
#endif // BOOST_MSVC > 1500
    }
};

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_FLEET_COMMANDER_CHANGED_EVENT_HPP_INCLUDED
