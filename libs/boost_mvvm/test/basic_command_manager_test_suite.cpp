//
//  basic_command_manager_test_suite.cpp
//
//  Copyright 2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>
#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>
#include <go_boost/utility.hpp>

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace rop = go_boost::property::read_only;
namespace s = go_boost::signals;
namespace u = go_boost::utility;
namespace us = go_boost::utility::string;

namespace
{

// Test command_manager
class spaceship
    : public m::basic_observable_object<u::u8string>
    , private u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

private:
    explicit spaceship(const m::basic_command_manager<u::u8string>::ptr& command_manager_)
        : m::basic_observable_object<u::u8string>()
        , u::noncopyable_nonmovable()
        , name(us::create<u::u8string>("name"))
        , captain(us::create<u::u8string>("captain"))
        , impulse_speed_command(us::create<u::u8string>("impulse_speed_command"))
        , warp_speed_command(us::create<u::u8string>("warp_speed_command"))
        , _command_manager(command_manager_)
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name()
        , _captain()
        , _impulse_speed_command()
        , _warp_speed_command()
    {
    }

    spaceship(const m::basic_command_manager<u::u8string>::ptr& command_manager_, const u::u8string& name_, const u::u8string& captain_)
        : m::basic_observable_object<u::u8string>()
        , u::noncopyable_nonmovable()
        , name(us::create<u::u8string>("name"))
        , captain(us::create<u::u8string>("captain"))
        , impulse_speed_command(us::create<u::u8string>("impulse_speed_command"))
        , warp_speed_command(us::create<u::u8string>("warp_speed_command"))
        , _command_manager(command_manager_)
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name(name_)
        , _captain(captain_)
        , _impulse_speed_command()
        , _warp_speed_command()
    {
    }

public:
    static boost::shared_ptr<spaceship> create(m::basic_command_manager<u::u8string>::ptr& command_manager_)
    {
        boost::shared_ptr<spaceship> ship(new spaceship(command_manager_));
        ship->bind_properties();
        return ship;
    }

    static boost::shared_ptr<spaceship> create(const m::basic_command_manager<u::u8string>::ptr& command_manager_, const u::u8string& name_, const u::u8string& captain_)
    {
        boost::shared_ptr<spaceship> ship(new spaceship(command_manager_, name_, captain_));
        ship->bind_properties();
        return ship;
    }

private:
    void bind_properties()
    {
        name.getter(boost::bind(&spaceship::get_name, this));
        name.setter(boost::bind(&spaceship::set_name, this, _1));
        captain.getter(boost::bind(&spaceship::get_captain, this));
        captain.setter(boost::bind(&spaceship::set_captain, this, _1));
        impulse_speed_command.getter(boost::bind(&spaceship::get_impulse_speed_command, this));
        warp_speed_command.getter(boost::bind(&spaceship::get_warp_speed_command, this));
    }

public:
    p::u8property<u::u8string> name;
    p::u8property<u::u8string> captain;
    rop::u8property<m::basic_command_interface<u::u8string>::ptr> impulse_speed_command;
    rop::u8property<m::basic_command_interface<u::u8string>::ptr> warp_speed_command;

public:
    bool at_impulse_speed() const { return _at_impulse_speed; }
    bool at_warp_speed() const { return _at_warp_speed; }

private:
    // name property
    u::u8string get_name() const
    {
        return _name;
    }

    void set_name(const u::u8string& v)
    {
        if(v != _name)
        {
            _name = v;
            notify_property_changed(this->shared_from_this(), name.name());
        }
    }

    // captain property
    u::u8string get_captain() const
    {
        return _captain;
    }

    void set_captain(const u::u8string& v)
    {
        if(v != _captain)
        {
            _captain = v;
            notify_property_changed(this->shared_from_this(), captain.name());
        }
    }

    // impulse_speed_command property
    m::basic_command_interface<u::u8string>::ptr get_impulse_speed_command()
    {
        if(!_impulse_speed_command)
        {
            _impulse_speed_command = m::basic_relay_command<u::u8string>::create(us::create<u::u8string>("impulse_speed"), boost::bind(&spaceship::go_to_impulse, this, _1), boost::bind(&spaceship::can_go_to_impulse, this, _1), m::command_parameters::create());
        }
        return _impulse_speed_command;
    }

    void go_to_impulse(const m::command_parameters::ptr& /*params*/)
    {
        _at_impulse_speed = true;
        _at_warp_speed = false;
        if(_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); }
        if(_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_impulse(const m::command_parameters::ptr& /*params*/)
    {
        return _at_warp_speed;
    }

    // warp_speed_command property
    m::basic_command_interface<u::u8string>::ptr get_warp_speed_command()
    {
        if(!_warp_speed_command)
        {
            _warp_speed_command = m::basic_relay_command<u::u8string>::create(us::create<u::u8string>("warp_speed"), boost::bind(&spaceship::go_to_warp, this, _1), boost::bind(&spaceship::can_go_to_warp, this, _1), m::command_parameters::create());
        }
        return _warp_speed_command;
    }

    void go_to_warp(const m::command_parameters::ptr& /*params*/)
    {
        _at_impulse_speed = false;
        _at_warp_speed = true;
        if(_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); }
        if(_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_warp(const m::command_parameters::ptr& /*params*/)
    {
        return !_at_warp_speed;
    }

private:
    m::basic_command_manager<u::u8string>::ptr _command_manager;
    bool _at_impulse_speed;
    bool _at_warp_speed;
    u::u8string _name;
    u::u8string _captain;
    m::basic_command_interface<u::u8string>::ptr _impulse_speed_command;
    m::basic_command_interface<u::u8string>::ptr _warp_speed_command;
};

class spaceship_observer
{
public:
    virtual ~spaceship_observer() GO_BOOST_DEFAULT_DESTRUCTOR

     spaceship_observer()
        : _on_property_changed_count()
    {
    }

    void connect(const boost::shared_ptr<spaceship>& ship)
    {
        if(ship)
        {
            ship->property_changed.connect(boost::bind(&spaceship_observer::on_property_changed, this, _1, _2));
        }
    }

    void disconnect(const boost::shared_ptr<spaceship>& ship)
    {
        if(ship)
        {
            ship->property_changed.disconnect(boost::bind(&spaceship_observer::on_property_changed, this, _1, _2));
        }
    }

    void on_property_changed(const m::object::ptr& o, const m::basic_property_changed_arguments<u::u8string>::ptr& a)
    {
        if(o && a)
        {
            boost::shared_ptr<spaceship> ship = boost::dynamic_pointer_cast<spaceship>(o);
            if(ship)
            {
                const ship_and_property_type ship_and_property(ship->name(), a->property_name());
                const on_property_changed_counter_type::iterator it = _on_property_changed_count.find(ship_and_property);
                if(it == _on_property_changed_count.end())
                {
                    _on_property_changed_count[ship_and_property] = 1;
                }
                else
                {
                    ++(it->second);
                }
            }
        }
    }

    unsigned int get_on_property_changed_count(const u::u8string& ship_name, const u::u8string& property_name) const
    {
        const ship_and_property_type ship_and_property(ship_name, property_name);
        const on_property_changed_counter_type::const_iterator it = _on_property_changed_count.find(ship_and_property);
        if(it == _on_property_changed_count.end())
        {
            return 0;
        }
        return it->second;
    }

private:
    typedef std::pair<u::u8string, u::u8string> ship_and_property_type;
    typedef std::map<ship_and_property_type, unsigned int> on_property_changed_counter_type;

    on_property_changed_counter_type _on_property_changed_count;
};

#define TEST_CASE_SHIPYARD \
    m::basic_command_manager<u::u8string>::ptr command_mgr = m::basic_command_manager<u::u8string>::create(); \
\
    boost::shared_ptr<spaceship> ship1 = spaceship::create(command_mgr, us::create<u::u8string>("USS Enterprise"), us::create<u::u8string>("Captain James T Kirk")); \
    boost::shared_ptr<spaceship> ship2 = spaceship::create(command_mgr, us::create<u::u8string>("Millennium Falcon"), us::create<u::u8string>("Han Solo")); \
    boost::shared_ptr<spaceship> ship3 = spaceship::create(command_mgr, us::create<u::u8string>("Executor"), us::create<u::u8string>("Lord Darth Vader")); \
    boost::shared_ptr<spaceship> ship4 = spaceship::create(command_mgr, us::create<u::u8string>("Battlestar Galactica"), us::create<u::u8string>("Admiral William Adama")); \
    boost::shared_ptr<spaceship> ship5 = spaceship::create(command_mgr, us::create<u::u8string>("Serenity"), us::create<u::u8string>("Captain Malcolm 'Mal' Reynolds")); \
\
    boost::shared_ptr<spaceship_observer> observer = boost::make_shared<spaceship_observer>(); \
\
    observer->connect(ship1); \
    observer->connect(ship2); \
    observer->connect(ship3); \
    observer->connect(ship4); \
    observer->connect(ship5);

TEST(boost_basic_command_manager_test_suite, test_command_manager)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_EQ(false, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    // Give warp speed command to USS Enterprise
    command_mgr->post(ship1->warp_speed_command);

    EXPECT_EQ(false, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    command_mgr->execute_commands();

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    // Give warp speed command to Millennium Falcon and Battlestar Galactica
    command_mgr->post(ship2->warp_speed_command);
    command_mgr->post(ship4->warp_speed_command);

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    command_mgr->execute_commands();

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(true, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(true, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    // Give impulse speed command to USS Enterprise
    command_mgr->post(ship1->impulse_speed_command);

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(false, ship1->at_impulse_speed());
    EXPECT_EQ(true, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(true, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    command_mgr->execute_commands();

    EXPECT_EQ(false, ship1->at_warp_speed());
    EXPECT_EQ(true, ship1->at_impulse_speed());
    EXPECT_EQ(true, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(true, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());
}

TEST(boost_basic_command_manager_test_suite, test_spaceship_observer)
{
    TEST_CASE_SHIPYARD

    // Verify first captain
    EXPECT_EQ(true, ship1->captain() == us::create<u::u8string>("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == us::create<u::u8string>("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == us::create<u::u8string>("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == us::create<u::u8string>("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == us::create<u::u8string>("Captain Malcolm 'Mal' Reynolds"));

    // Verify initial 'on property changed' count
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("USS Enterprise"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Millennium Falcon"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Executor"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Battlestar Galactica"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Serenity"), us::create<u::u8string>("captain")));

    // Give Mr Spock command of USS Enterprise
    ship1->captain = us::create<u::u8string>("Mr Spock");

    EXPECT_EQ(true, ship1->captain() == us::create<u::u8string>("Mr Spock"));
    EXPECT_EQ(true, ship2->captain() == us::create<u::u8string>("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == us::create<u::u8string>("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == us::create<u::u8string>("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == us::create<u::u8string>("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(1, observer->get_on_property_changed_count(us::create<u::u8string>("USS Enterprise"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Millennium Falcon"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Executor"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Battlestar Galactica"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Serenity"), us::create<u::u8string>("captain")));

    // Return command of USS Enterprise to Captain Kirk
    ship1->captain = us::create<u::u8string>("Captain James T Kirk");

    EXPECT_EQ(true, ship1->captain() == us::create<u::u8string>("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == us::create<u::u8string>("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == us::create<u::u8string>("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == us::create<u::u8string>("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == us::create<u::u8string>("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(2, observer->get_on_property_changed_count(us::create<u::u8string>("USS Enterprise"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Millennium Falcon"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Executor"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Battlestar Galactica"), us::create<u::u8string>("captain")));
    EXPECT_EQ(0, observer->get_on_property_changed_count(us::create<u::u8string>("Serenity"), us::create<u::u8string>("captain")));
}

}