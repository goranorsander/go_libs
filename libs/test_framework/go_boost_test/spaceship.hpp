#ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_SPACESHIP_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_BOOST_TEST_SPACESHIP_HPP_INCLUDED

//
//  spaceship.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#include <go_boost/property.hpp>
#include <go_boost_test/fleet_commander_changed_event.hpp>

namespace go_boost_test
{

template <class Traits>
class spaceship
    : private tt::noncopyable_nonmovable
{
public:
    typedef spaceship<Traits> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef Traits traits_type;
    typedef typename traits_type::string_value_type string_value_type;
    typedef typename traits_type::lockable_type lockable_type;
    typedef typename traits_type::string_identifier_type string_identifier_type;
    typedef typename traits_type::double_property_type double_property_type;
    typedef typename traits_type::int_property_type int_property_type;
    typedef typename traits_type::string_property_type string_property_type;
    typedef typename traits_type::read_only_command_property_type read_only_command_property_type;
    typedef typename traits_type::read_only_string_property_type read_only_string_property_type;
    typedef typename traits_type::read_only_string_value_property_type read_only_string_value_property_type;
    typedef typename traits_type::command_value_type command_value_type;
    typedef typename command_value_type command_ptr;
    typedef typename traits_type::fleet_commander_changed_event_type fleet_commander_changed_event_type;
    typedef typename traits_type::fleet_commander_changed_event_ptr fleet_commander_changed_event_ptr;
    typedef typename traits_type::event_type event_type;
    typedef typename traits_type::event_ptr event_ptr;

public:
    virtual ~spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    spaceship()
        : tt::noncopyable_nonmovable()
        , name(s::create<string_identifier_type>("name"))
        , captain(s::create<string_identifier_type>("captain"))
        , crew_complement(s::create<string_identifier_type>("crew_complement"))
        , max_speed(s::create<string_identifier_type>("max_speed"))
        , fleet_commander(s::create<string_identifier_type>("fleet_commander"))
        , impulse_speed_command(s::create<string_identifier_type>("impulse_speed_command"))
        , warp_speed_command(s::create<string_identifier_type>("warp_speed_command"))
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name()
        , _captain()
        , _crew_complement(0)
        , _max_speed(0.0)
        , _fleet_commander()
        , _impulse_speed_command()
        , _warp_speed_command()
    {
    }

    spaceship(const string_value_type& name_, const string_value_type& captain_)
        : tt::noncopyable_nonmovable()
        , name(s::create<string_identifier_type>("name"))
        , captain(s::create<string_identifier_type>("captain"))
        , crew_complement(s::create<string_identifier_type>("crew_complement"))
        , max_speed(s::create<string_identifier_type>("max_speed"))
        , fleet_commander(s::create<string_identifier_type>("fleet_commander"))
        , impulse_speed_command(s::create<string_identifier_type>("impulse_speed_command"))
        , warp_speed_command(s::create<string_identifier_type>("warp_speed_command"))
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name(name_)
        , _captain(captain_)
        , _crew_complement(0)
        , _max_speed(0.0)
        , _fleet_commander()
        , _impulse_speed_command()
        , _warp_speed_command()
    {
    }

    spaceship(const string_value_type& name_, const string_value_type& captain_, const string_value_type& fleet_commander_)
        : tt::noncopyable_nonmovable()
        , name(s::create<string_identifier_type>("name"))
        , captain(s::create<string_identifier_type>("captain"))
        , crew_complement(s::create<string_identifier_type>("crew_complement"))
        , max_speed(s::create<string_identifier_type>("max_speed"))
        , fleet_commander(s::create<string_identifier_type>("fleet_commander"))
        , impulse_speed_command(s::create<string_identifier_type>("impulse_speed_command"))
        , warp_speed_command(s::create<string_identifier_type>("warp_speed_command"))
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name(name_)
        , _captain(captain_)
        , _crew_complement(0)
        , _max_speed(0.0)
        , _fleet_commander(fleet_commander_)
        , _impulse_speed_command()
        , _warp_speed_command()
    {
    }

public:
    static ptr create()
    {
        ptr ship(new this_type());
        return ship;
    }

    static ptr create(const string_value_type& name_, const string_value_type& captain_)
    {
        ptr ship(new this_type(name_, captain_));
        return ship;
    }

    static ptr create(const string_value_type& name_, const string_value_type& captain_, const string_value_type& fleet_commander_)
    {
        ptr ship(new this_type(name_, captain_, fleet_commander_));
        return ship;
    }

public:
    string_property_type name;
    string_property_type captain;
    int_property_type crew_complement;
    double_property_type max_speed;
    read_only_string_property_type fleet_commander;
    read_only_command_property_type impulse_speed_command;
    read_only_command_property_type warp_speed_command;

public:
    bool at_impulse_speed() const { return this->_at_impulse_speed; }
    bool at_warp_speed() const { return this->_at_warp_speed; }

    void on_fleet_commander_changed(const event_ptr& e)
    {
        fleet_commander_changed_event_ptr fleet_commander_changed = boost::dynamic_pointer_cast<fleet_commander_changed_event_type>(e);
        if (fleet_commander_changed)
        {
            _fleet_commander = fleet_commander_changed->fleet_commander();
        }
    }

protected:
    // impulse_speed_command property
    void go_to_impulse(const m::command_parameters::ptr& /*params*/)
    {
        this->_at_impulse_speed = true;
        this->_at_warp_speed = false;
        if(this->_impulse_speed_command) { this->_impulse_speed_command->notify_can_execute_changed(); }
        if(this->_warp_speed_command) { this->_warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_impulse(const m::command_parameters::ptr& /*params*/)
    {
        return this->_at_warp_speed;
    }

    // warp_speed_command property
    void go_to_warp(const m::command_parameters::ptr& /*params*/)
    {
        this->_at_impulse_speed = false;
        this->_at_warp_speed = true;
        if(this->_impulse_speed_command) { this->_impulse_speed_command->notify_can_execute_changed(); }
        if(this->_warp_speed_command) { this->_warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_warp(const m::command_parameters::ptr& /*params*/)
    {
        return !this->_at_warp_speed;
    }

protected:
    bool _at_impulse_speed;
    bool _at_warp_speed;
    string_value_type _name;
    string_value_type _captain;
    int _crew_complement;
    double _max_speed;
    string_value_type _fleet_commander;
    command_ptr _impulse_speed_command;
    command_ptr _warp_speed_command;
};

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_SPACESHIP_HPP_INCLUDED
