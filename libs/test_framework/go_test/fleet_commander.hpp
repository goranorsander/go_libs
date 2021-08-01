#ifndef GO_TEST_FRAMEWORK_GO_TEST_FLEET_COMMANDER_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_FLEET_COMMANDER_HPP_INCLUDED

//
//  fleet_commander.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/mvvm.hpp>
#include <go_test/fleet_commander_changed_event.hpp>

namespace go_test
{

template <class E, class SP, class SVP, class ROSVP>
class fleet_commander
    : private tt::noncopyable_nonmovable
{
public:
    typedef fleet_commander<E, SP, SVP, ROSVP> this_type;
    typedef E event_manager_type;
    typedef SP string_property_type;
    typedef SVP string_value_property_type;
    typedef ROSVP read_only_string_value_property_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;
    typedef typename event_manager_type::ptr event_manager_ptr;
    typedef typename event_manager_type::wptr event_manager_wptr;
    typedef typename event_manager_type::string_type string_identifier_type;
    typedef fleet_commander_changed_event<string_identifier_type, read_only_string_value_property_type> fleet_commander_changed_event_type;
    typedef typename fleet_commander_changed_event_type::ptr fleet_commander_changed_event_ptr;

public:
    virtual ~fleet_commander() GO_DEFAULT_DESTRUCTOR

private:
    fleet_commander(const event_manager_ptr& event_manager_, const string_identifier_type& commander_, const string_identifier_type& battle_)
        : tt::noncopyable_nonmovable()
        , commander(s::create<string_identifier_type>("commander"))
        , battle(s::create<string_identifier_type>("battle"), battle_)
        , _event_manager(event_manager_)
        , _commander(commander_)
    {
    }

public:
    static ptr create(const event_manager_ptr& event_manager_, const string_identifier_type& commander_, const string_identifier_type& battle_)
    {
#if GO_MSVC_VER > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                make_shared_enabler(const event_manager_ptr& event_manager_, const string_identifier_type& commander_, const string_identifier_type& battle_) : this_type(event_manager_, commander_, battle_) {}
        };
        ptr fleet_cmdr = std::make_shared<make_shared_enabler, const event_manager_ptr&, const string_identifier_type&, const string_identifier_type&>(event_manager_, commander_, battle_);
#else
        ptr fleet_cmdr = std::shared_ptr<this_type>(new this_type(event_manager_, commander_, battle_));
#endif // GO_MSVC_VER > 1500
        fleet_cmdr->bind_properties();
        return fleet_cmdr;
    }

public:
    string_property_type commander;
    string_value_property_type battle;

private:
    string_identifier_type get_commander() const
    {
        return this->_commander;
    }

    void set_commander(const string_identifier_type& v)
    {
        if (v != this->_commander)
        {
            this->_commander = v;
            this->_event_manager->post(fleet_commander_changed_event_type::create(v));
        }
    }

    void bind_properties()
    {
        this->commander.getter(std::bind(&fleet_commander::get_commander, this));
        this->commander.setter(std::bind(&fleet_commander::set_commander, this, std::placeholders::_1));
    }

private:
    event_manager_ptr _event_manager;
    string_identifier_type _commander;
};

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_FLEET_COMMANDER_HPP_INCLUDED
