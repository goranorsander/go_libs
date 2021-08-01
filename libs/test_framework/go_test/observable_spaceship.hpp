#ifndef GO_TEST_FRAMEWORK_GO_TEST_OBSERVABLE_SPACESHIP_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_OBSERVABLE_SPACESHIP_HPP_INCLUDED

//
//  observable_spaceship.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/mvvm/utility.hpp>
#include <go/type_traits/identity.hpp>
#include <go_test/spaceship.hpp>

namespace go_test
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
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

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
    virtual ~observable_spaceship() GO_DEFAULT_DESTRUCTOR

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
        this->name.getter(std::bind(&this_type::get_name, this));
        this->name.setter(std::bind(&this_type::set_name, this, std::placeholders::_1));
        this->captain.getter(std::bind(&this_type::get_captain, this));
        this->captain.setter(std::bind(&this_type::set_captain, this, std::placeholders::_1));
        this->crew_complement.getter(std::bind(&this_type::get_crew_complement, this));
        this->crew_complement.setter(std::bind(&this_type::set_crew_complement, this, std::placeholders::_1));
        this->max_speed.getter(std::bind(&this_type::get_max_speed, this));
        this->max_speed.setter(std::bind(&this_type::set_max_speed, this, std::placeholders::_1));
        this->fleet_commander.getter(std::bind(&this_type::get_fleet_commander, this));
        this->impulse_speed_command.getter(std::bind(&this_type::get_impulse_speed_command, this));
        this->warp_speed_command.getter(std::bind(&this_type::get_warp_speed_command, this));
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
            this->_impulse_speed_command = m::basic_relay_command<string_identifier_type, lockable_type>::create(s::create<string_identifier_type>("impulse_speed"), std::bind(&this_type::go_to_impulse, this, std::placeholders::_1), std::bind(&this_type::can_go_to_impulse, this, std::placeholders::_1), m::command_parameters::create());
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
            this->_warp_speed_command = m::basic_relay_command<string_identifier_type, lockable_type>::create(s::create<string_identifier_type>("warp_speed"), std::bind(&this_type::go_to_warp, this, std::placeholders::_1), std::bind(&this_type::can_go_to_warp, this, std::placeholders::_1), m::command_parameters::create());
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

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

namespace lambda
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
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

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
    virtual ~observable_spaceship() GO_DEFAULT_DESTRUCTOR

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

    template <>
    void bind_properties(const tt::identity<string_identifier_type>)
    {
        this->name.getter([this]() { return this->_name; });
        this->name.setter([this](const string_identifier_type& v) { if (v != this->_name) { this->_name = v; this->notify_property_changed(this->shared_from_this(), this->name.name()); } });
        this->captain.getter([this]() -> string_identifier_type { return this->_captain; });
        this->captain.setter([this](const string_identifier_type& v) { if (v != this->_captain) { this->_captain = v; this->notify_property_changed(this->shared_from_this(), this->captain.name()); } });
        this->crew_complement.getter([this]() { return this->_crew_complement; });
        this->crew_complement.setter([this](const int& v) { if (v != this->_crew_complement) { this->_crew_complement = v; this->notify_property_changed(this->shared_from_this(), this->crew_complement.name()); } });
        this->max_speed.getter([this]() { return this->_max_speed; });
        this->max_speed.setter([this](const double& v) { if (v != this->_max_speed) { this->_max_speed = v; this->notify_property_changed(this->shared_from_this(), this->max_speed.name()); } });
        this->fleet_commander.getter([this]() -> string_identifier_type { return this->_fleet_commander; });
        this->impulse_speed_command.getter(
            [this]() -> m::basic_command_interface<string_identifier_type>::ptr { if (!this->_impulse_speed_command) {
            this->_impulse_speed_command = m::basic_relay_command<string_identifier_type>::create(s::create<string_identifier_type>("impulse_speed"),
                [this](const m::command_parameters::ptr&) { this->_at_impulse_speed = true; this->_at_warp_speed = false; if (this->_impulse_speed_command) { this->_impulse_speed_command->notify_can_execute_changed(); } if (this->_warp_speed_command) { this->_warp_speed_command->notify_can_execute_changed(); } },
                [this](const m::command_parameters::ptr&) { return this->_at_warp_speed; }, m::command_parameters::create());
        } return this->_impulse_speed_command; });
        this->warp_speed_command.getter(
            [this]() -> m::basic_command_interface<string_identifier_type>::ptr { if (!this->_warp_speed_command) {
            this->_warp_speed_command = m::basic_relay_command<string_identifier_type>::create(s::create<string_identifier_type>("warp_speed"),
                [this](const m::command_parameters::ptr&) { this->_at_impulse_speed = false; this->_at_warp_speed = true; if (this->_impulse_speed_command) { this->_impulse_speed_command->notify_can_execute_changed(); } if (this->_warp_speed_command) { this->_warp_speed_command->notify_can_execute_changed(); } },
                [this](const m::command_parameters::ptr&) { return !this->_at_warp_speed; }, m::command_parameters::create());
        } return this->_warp_speed_command; });
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
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

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
    virtual ~observable_spaceship() GO_DEFAULT_DESTRUCTOR

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

    template <>
    void bind_properties(const tt::identity<string_identifier_type>)
    {
        this->name.getter([this]() { return this->_name; });
        this->name.setter([this](const string_identifier_type& v) { if (v != this->_name) { this->_name = v; this->notify_property_changed(this->shared_from_this(), this->name.name()); } });
        this->captain.getter([this]() -> string_identifier_type { return this->_captain; });
        this->captain.setter([this](const string_identifier_type& v) { if (v != this->_captain) { this->_captain = v; this->notify_property_changed(this->shared_from_this(), this->captain.name()); } });
        this->crew_complement.getter([this]() { return this->_crew_complement; });
        this->crew_complement.setter([this](const int& v) { if (v != this->_crew_complement) { this->_crew_complement = v; this->notify_property_changed(this->shared_from_this(), this->crew_complement.name()); } });
        this->max_speed.getter([this]() { return this->_max_speed; });
        this->max_speed.setter([this](const double& v) { if (v != this->_max_speed) { this->_max_speed = v; this->notify_property_changed(this->shared_from_this(), this->max_speed.name()); } });
        this->fleet_commander.getter([this]() -> string_identifier_type { return this->_fleet_commander; });
        this->impulse_speed_command.getter(
            [this]() -> m::basic_command_interface<string_identifier_type>::ptr { if (!this->_impulse_speed_command) {
            this->_impulse_speed_command = m::basic_relay_command<string_identifier_type>::create(s::create<string_identifier_type>("impulse_speed"),
                [this](const m::command_parameters::ptr&) { this->_at_impulse_speed = true; this->_at_warp_speed = false; if (this->_impulse_speed_command) { this->_impulse_speed_command->notify_can_execute_changed(); } if (this->_warp_speed_command) { this->_warp_speed_command->notify_can_execute_changed(); } },
                [this](const m::command_parameters::ptr&) { return this->_at_warp_speed; }, m::command_parameters::create());
        } return this->_impulse_speed_command; });
        this->warp_speed_command.getter(
            [this]() -> m::basic_command_interface<string_identifier_type>::ptr { if (!this->_warp_speed_command) {
            this->_warp_speed_command = m::basic_relay_command<string_identifier_type>::create(s::create<string_identifier_type>("warp_speed"),
                [this](const m::command_parameters::ptr&) { this->_at_impulse_speed = false; this->_at_warp_speed = true; if (this->_impulse_speed_command) { this->_impulse_speed_command->notify_can_execute_changed(); } if (this->_warp_speed_command) { this->_warp_speed_command->notify_can_execute_changed(); } },
                [this](const m::command_parameters::ptr&) { return !this->_at_warp_speed; }, m::command_parameters::create());
        } return this->_warp_speed_command; });
    }
};

}

#endif  // #if defined(GO_NO_CXX11)

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_OBSERVABLE_SPACESHIP_HPP_INCLUDED
