#ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_OBSERVABLE_SPACESHIP_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_BOOST_TEST_OBSERVABLE_SPACESHIP_HPP_INCLUDED

//
//  observable_spaceship.hpp
//
//  Copyright 2021-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#include <go_boost/mvvm/utility.hpp>
#include <go_boost/type_traits/identity.hpp>
#include <go_boost_test/spaceship.hpp>

namespace go_boost_test
{

namespace bind_function
{

template <class Traits>
class observable_spaceship
    : public spaceship<Traits>
    , public m::basic_observable_object<typename Traits::string_identifier_type, typename Traits::lockable_type>
{
public:
    typedef observable_spaceship<Traits> this_type;
    typedef spaceship<Traits> spaceship_base_type;
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
    typedef typename traits_type::observable_object_base_type observable_object_base_type;
    typedef typename traits_type::command_value_type command_value_type;
    typedef typename traits_type::command_value_type command_ptr;
    typedef typename traits_type::fleet_commander_changed_event_type fleet_commander_changed_event_type;
    typedef typename traits_type::fleet_commander_changed_event_ptr fleet_commander_changed_event_ptr;
    typedef typename traits_type::event_type event_type;
    typedef typename traits_type::event_ptr event_ptr;

public:
    virtual ~observable_spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    explicit observable_spaceship(const string_value_type& name_)
        : spaceship_base_type(name_, string_value_type())
        , observable_object_base_type()
    {
    }

    observable_spaceship(const string_value_type& name_, const string_value_type& captain_)
        : spaceship_base_type(name_, captain_)
        , observable_object_base_type()
    {
    }

    observable_spaceship(const string_value_type& name_, const string_value_type& captain_, const string_value_type& fleet_commander_)
        : spaceship_base_type(name_, captain_, fleet_commander_)
        , observable_object_base_type()
    {
    }

public:
    static ptr create(const string_value_type& name_)
    {
        ptr ship(new this_type(name_));
        ship->bind_properties();
        return ship;
    }

    static ptr create(const string_value_type& name_, const string_value_type& captain_)
    {
        ptr ship(new this_type(name_, captain_));
        ship->bind_properties();
        return ship;
    }

    static ptr create(const string_value_type& name_, const string_value_type& captain_, const string_value_type& fleet_commander_)
    {
        ptr ship(new this_type(name_, captain_, fleet_commander_));
        ship->bind_properties();
        return ship;
    }

protected:
    void bind_properties()
    {
        this->name.getter(boost::bind(&this_type::get_name, this));
        this->name.setter(boost::bind(&this_type::set_name, this, boost::placeholders::_1));
        this->captain.getter(boost::bind(&this_type::get_captain, this));
        this->captain.setter(boost::bind(&this_type::set_captain, this, boost::placeholders::_1));
        this->crew_complement.getter(boost::bind(&this_type::get_crew_complement, this));
        this->crew_complement.setter(boost::bind(&this_type::set_crew_complement, this, boost::placeholders::_1));
        this->max_speed.getter(boost::bind(&this_type::get_max_speed, this));
        this->max_speed.setter(boost::bind(&this_type::set_max_speed, this, boost::placeholders::_1));
        this->fleet_commander.getter(boost::bind(&this_type::get_fleet_commander, this));
        this->impulse_speed_command.getter(boost::bind(&this_type::get_impulse_speed_command, this));
        this->warp_speed_command.getter(boost::bind(&this_type::get_warp_speed_command, this));
    }

    // name property
    string_value_type get_name() const
    {
        return this->_name;
    }

    void set_name(const string_value_type& v)
    {
        if (v != this->_name)
        {
            this->_name = v;
            this->notify_property_changed(this->shared_from_this(), this->name.name());
        }
    }

    // captain property
    string_value_type get_captain() const
    {
        return this->_captain;
    }

    void set_captain(const string_value_type& v)
    {
        if (v != this->_captain)
        {
            this->_captain = v;
            this->notify_property_changed(this->shared_from_this(), this->captain.name());
        }
    }

    // crew_complement property
    int get_crew_complement() const
    {
        return this->_crew_complement;
    }

    void set_crew_complement(const int& v)
    {
        if (v != this->_crew_complement)
        {
            this->_crew_complement = v;
            this->notify_property_changed(this->shared_from_this(), this->crew_complement.name());
        }
    }

    // max_speed property
    double get_max_speed() const
    {
        return this->_max_speed;
    }

    void set_max_speed(const double& v)
    {
        if (v != this->_max_speed)
        {
            this->_max_speed = v;
            this->notify_property_changed(this->shared_from_this(), this->max_speed.name());
        }
    }

    // fleet_commander property
    string_value_type get_fleet_commander() const
    {
        return this->_fleet_commander;
    }

    // impulse_speed_command property
    command_ptr get_impulse_speed_command()
    {
        if (!this->_impulse_speed_command)
        {
            this->_impulse_speed_command = m::basic_relay_command<string_identifier_type, lockable_type>::create(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create());
        }
        return this->_impulse_speed_command;
    }

    void go_to_impulse(const m::command_parameters::ptr& /*params*/)
    {
        this->_at_impulse_speed = true;
        this->_at_warp_speed = false;
        if (this->_impulse_speed_command) { this->_impulse_speed_command->notify_can_execute_changed(); }
        if (this->_warp_speed_command) { this->_warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_impulse(const m::command_parameters::ptr& /*params*/)
    {
        return this->_at_warp_speed;
    }

    // warp_speed_command property
    command_ptr get_warp_speed_command()
    {
        if (!this->_warp_speed_command)
        {
            this->_warp_speed_command = m::basic_relay_command<string_identifier_type, lockable_type>::create(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create());
        }
        return this->_warp_speed_command;
    }

    void go_to_warp(const m::command_parameters::ptr& /*params*/)
    {
        this->_at_impulse_speed = false;
        this->_at_warp_speed = true;
        if (this->_impulse_speed_command) { this->_impulse_speed_command->notify_can_execute_changed(); }
        if (this->_warp_speed_command) { this->_warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_warp(const m::command_parameters::ptr& /*params*/)
    {
        return !this->_at_warp_speed;
    }
};

}

#if defined(GO_BOOST_NO_BOOST_PHOENIX)
GO_BOOST_MESSAGE("Boost.Phoenix is not supported by this compiler")
#else

namespace phoenix
{
namespace single_threaded
{

template <class Traits>
class observable_spaceship
    : public spaceship<Traits>
    , public m::basic_observable_object<typename Traits::string_identifier_type, typename Traits::lockable_type>
{
public:
    typedef observable_spaceship<Traits> this_type;
    typedef spaceship<Traits> spaceship_base_type;
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
    typedef typename traits_type::observable_object_base_type observable_object_base_type;
    typedef typename traits_type::command_value_type command_value_type;
    typedef typename traits_type::command_value_type command_ptr;
    typedef typename traits_type::fleet_commander_changed_event_type fleet_commander_changed_event_type;
    typedef typename traits_type::fleet_commander_changed_event_ptr fleet_commander_changed_event_ptr;
    typedef typename traits_type::event_type event_type;
    typedef typename traits_type::event_ptr event_ptr;

public:
    virtual ~observable_spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    explicit observable_spaceship(const string_value_type& name_)
        : spaceship_base_type(name_, string_value_type())
        , observable_object_base_type()
    {
    }

    observable_spaceship(const string_value_type& name_, const string_value_type& captain_)
        : spaceship_base_type(name_, captain_)
        , observable_object_base_type()
    {
    }

    observable_spaceship(const string_value_type& name_, const string_value_type& captain_, const string_value_type& fleet_commander_)
        : spaceship_base_type(name_, captain_, fleet_commander_)
        , observable_object_base_type()
    {
    }

public:
    static ptr create(const string_value_type& name_)
    {
        ptr ship(new this_type(name_));
        ship->bind_properties(string_identifier_type());
        return ship;
    }

    static ptr create(const string_value_type& name_, const string_value_type& captain_)
    {
        ptr ship(new observable_spaceship(name_, captain_));
        ship->bind_properties(string_identifier_type());
        return ship;
    }

    static ptr create(const string_value_type& name_, const string_value_type& captain_, const string_value_type& fleet_commander_)
    {
        ptr ship(new observable_spaceship(name_, captain_, fleet_commander_));
        ship->bind_properties(string_identifier_type());
        return ship;
    }

protected:
    template <class S>
    void bind_properties(const S&)
    {
        this->bind_properties(tt::identity<S>());
    }

private:
    template <class S>
    void bind_properties(const tt::identity<S>)
    {
        throw std::domain_error("Unsupported string class");
    }

    void bind_properties(const tt::identity<std::string>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(must::get_property_relay_command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(must::get_property_relay_command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }

    void bind_properties(const tt::identity<std::wstring>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(must::get_wproperty_relay_wcommand, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(must::get_wproperty_relay_wcommand, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }

    void bind_properties(const tt::identity<s::u8string>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(must::get_u8property_relay_u8command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(must::get_u8property_relay_u8command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }

    void bind_properties(const tt::identity<s::u16string>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(must::get_u16property_relay_u16command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(must::get_u16property_relay_u16command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }

    void bind_properties(const tt::identity<s::u32string>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(must::get_u32property_relay_u32command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(must::get_u32property_relay_u32command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }
};

}

template <class Traits>
class observable_spaceship
    : public spaceship<Traits>
    , public m::basic_observable_object<typename Traits::string_identifier_type, typename Traits::lockable_type>
{
public:
    typedef observable_spaceship<Traits> this_type;
    typedef spaceship<Traits> spaceship_base_type;
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
    typedef typename traits_type::observable_object_base_type observable_object_base_type;
    typedef typename traits_type::command_value_type command_value_type;
    typedef typename traits_type::command_value_type command_ptr;
    typedef typename traits_type::fleet_commander_changed_event_type fleet_commander_changed_event_type;
    typedef typename traits_type::fleet_commander_changed_event_ptr fleet_commander_changed_event_ptr;
    typedef typename traits_type::event_type event_type;
    typedef typename traits_type::event_ptr event_ptr;

public:
    virtual ~observable_spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    explicit observable_spaceship(const string_value_type& name_)
        : spaceship_base_type(name_, string_value_type())
        , observable_object_base_type()
    {
    }

    observable_spaceship(const string_value_type& name_, const string_value_type& captain_)
        : spaceship_base_type(name_, captain_)
        , observable_object_base_type()
    {
    }

    observable_spaceship(const string_value_type& name_, const string_value_type& captain_, const string_value_type& fleet_commander_)
        : spaceship_base_type(name_, captain_, fleet_commander_)
        , observable_object_base_type()
    {
    }

public:
    static ptr create(const string_value_type& name_)
    {
        ptr ship(new this_type(name_));
        ship->bind_properties(string_identifier_type());
        return ship;
    }

    static ptr create(const string_value_type& name_, const string_value_type& captain_)
    {
        ptr ship(new observable_spaceship(name_, captain_));
        ship->bind_properties(string_identifier_type());
        return ship;
    }

    static ptr create(const string_value_type& name_, const string_value_type& captain_, const string_value_type& fleet_commander_)
    {
        ptr ship(new observable_spaceship(name_, captain_, fleet_commander_));
        ship->bind_properties(string_identifier_type());
        return ship;
    }

protected:
    template <class S>
    void bind_properties(const S&)
    {
        this->bind_properties(tt::identity<S>());
    }

private:
    template <class S>
    void bind_properties(const tt::identity<S>)
    {
        throw std::domain_error("Unsupported string class");
    }

    void bind_properties(const tt::identity<std::string>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(mu::get_property_relay_command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(mu::get_property_relay_command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }

    void bind_properties(const tt::identity<std::wstring>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(mu::get_wproperty_relay_wcommand, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(mu::get_wproperty_relay_wcommand, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }

    void bind_properties(const tt::identity<s::u8string>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(mu::get_u8property_relay_u8command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(mu::get_u8property_relay_u8command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }

    void bind_properties(const tt::identity<s::u16string>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(mu::get_u16property_relay_u16command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(mu::get_u16property_relay_u16command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }

    void bind_properties(const tt::identity<s::u32string>)
    {
        this->name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_name)));
        this->name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->name.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_name), bph::arg1, bph::arg2));
        this->captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_captain)));
        this->captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->captain.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_captain), bph::arg1, bph::arg2));
        this->crew_complement.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_crew_complement)));
        this->crew_complement.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->crew_complement.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_crew_complement), bph::arg1, bph::arg2));
        this->max_speed.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_max_speed)));
        this->max_speed.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), this->max_speed.name(), boost::bind(&this_type::notify_property_changed, this, boost::placeholders::_1, boost::placeholders::_2), bp::ref(this->_max_speed), bph::arg1, bph::arg2));
        this->fleet_commander.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(this->_fleet_commander)));
        this->impulse_speed_command.getter(bp::bind(mu::get_u32property_relay_u32command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("impulse_speed"), boost::bind(&this_type::go_to_impulse, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_impulse, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_impulse_speed_command)));
        this->warp_speed_command.getter(bp::bind(mu::get_u32property_relay_u32command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(s::create<string_identifier_type>("warp_speed"), boost::bind(&this_type::go_to_warp, this, boost::placeholders::_1), boost::bind(&this_type::can_go_to_warp, this, boost::placeholders::_1), m::command_parameters::create(), bp::ref(this->_warp_speed_command)));
    }
};

}

#endif  // #if defined(GO_BOOST_NO_BOOST_PHOENIX)

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_OBSERVABLE_SPACESHIP_HPP_INCLUDED
