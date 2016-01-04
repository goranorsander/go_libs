//
//  command_manager_test_suite.cpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <functional>
//#include <boost/noncopyable.hpp>
//#include <boost/test/unit_test.hpp>
#include <string>

#include <go/mvvm.hpp>
#include <go/property.hpp>

BOOST_AUTO_TEST_SUITE(command_manager_test_suite)

namespace b = boost;
namespace m = boost::mvvm;
namespace p = boost::property;

// Test command_manager
class spaceship
    : public b::noncopyable
    , public m::observable_object<std::string>
{
public:
    ~spaceship()
    {
    }

    spaceship(const m::command_manager<std::string>::ptr& cmd_mgr)
        : b::noncopyable()
        , m::observable_object<std::string>()
        , _command_manager(cmd_mgr)
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name()
        , _captain()
        , name("name", std::bind(&spaceship::get_name, this), std::bind(&spaceship::set_name, this, ph::_1))
        , captain("captain", std::bind(&spaceship::get_captain, this), std::bind(&spaceship::set_captain, this, ph::_1))
        , impulse_speed_command("impulse_speed_command", std::bind(&spaceship::get_impulse_speed_command, this))
        , warp_speed_command("warp_speed_command", std::bind(&spaceship::get_warp_speed_command, this))
    {
    }

    spaceship(const m::command_manager<std::string>::ptr& cmd_mgr, const std::string& nme, const std::string& cpt)
        : b::noncopyable()
        , m::observable_object<std::string>()
        , _command_manager(cmd_mgr)
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name(nme)
        , _captain(cpt)
        , _impulse_speed_command()
        , _warp_speed_command()
        , name("name", std::bind(&spaceship::get_name, this), std::bind(&spaceship::set_name, this, ph::_1))
        , captain("captain", std::bind(&spaceship::get_captain, this), std::bind(&spaceship::set_captain, this, ph::_1))
        , impulse_speed_command("impulse_speed_command", std::bind(&spaceship::get_impulse_speed_command, this))
        , warp_speed_command("warp_speed_command", std::bind(&spaceship::get_warp_speed_command, this))
    {
    }

public:
    p::property<std::string> name;
    p::property<std::string> captain;
    p::ro_property<m::command<std::string>::ptr> impulse_speed_command;
    p::ro_property<m::command<std::string>::ptr> warp_speed_command;

public:
    bool at_impulse_speed() const { return _at_impulse_speed; }
    bool at_warp_speed() const { return _at_warp_speed; }

private:
    // name property
    std::string get_name() const
    {
        return _name;
    }

    void set_name(const std::string& v)
    {
        if(v != _name)
        {
            _name = v;
            on_property_changed("name");
        }
    }

    // captain property
    std::string get_captain() const
    {
        return _captain;
    }

    void set_captain(const std::string& v)
    {
        if(v != _captain)
        {
            _captain = v;
            on_property_changed("captain");
        }
    }

    // impulse_speed_command property
    m::command<std::string>::ptr get_impulse_speed_command()
    {
        if(!_impulse_speed_command)
        {
            _impulse_speed_command = m::relay_command<std::string>::create("impulse_speed", std::bind(&spaceship::go_to_impulse, this, ph::_1), std::bind(&spaceship::can_go_to_impulse, this, ph::_1), m::command_parameters::create());
        }
        return _impulse_speed_command;
    }

    void go_to_impulse(const m::command_parameters::ptr& params)
    {
        _at_impulse_speed = true;
        _at_warp_speed = false;
        if(_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); }
        if(_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_impulse(const m::command_parameters::ptr& params)
    {
        return _at_warp_speed;
    }

    // warp_speed_command property
    m::command<std::string>::ptr get_warp_speed_command()
    {
        if(!_warp_speed_command)
        {
            _warp_speed_command = m::relay_command<std::string>::create("warp_speed", std::bind(&spaceship::go_to_warp, this, ph::_1), std::bind(&spaceship::can_go_to_warp, this, ph::_1), m::command_parameters::create());
        }
        return _warp_speed_command;
    }

    void go_to_warp(const m::command_parameters::ptr& params)
    {
        _at_impulse_speed = false;
        _at_warp_speed = true;
        if(_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); }
        if(_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); }
    }

    bool can_go_to_warp(const m::command_parameters::ptr& params)
    {
        return !_at_warp_speed;
    }

private:
    m::command_manager<std::string>::ptr _command_manager;
    bool _at_impulse_speed;
    bool _at_warp_speed;
    std::string _name;
    std::string _captain;
    m::command<std::string>::ptr _impulse_speed_command;
    m::command<std::string>::ptr _warp_speed_command;
};

class spaceship_observer
{
public:
    ~spaceship_observer()
    {
    }

    spaceship_observer()
    {
    }

    void connect(const b::shared_ptr<spaceship>& ship)
    {
        if(ship)
        {
            ship->property_changed.connect(std::bind(&spaceship_observer::on_property_changed, this, ph::_1, ph::_2));
        }
    }

    void disconnect(const b::shared_ptr<spaceship>& ship)
    {
        if(ship)
        {
            ship->property_changed.disconnect(std::bind(&spaceship_observer::on_property_changed, this, ph::_1, ph::_2));
        }
    }

    void on_property_changed(const m::object::ptr& o, const m::property_changed_arguments<std::string>::ptr& a)
    {
        if(o && a)
        {
            b::shared_ptr<spaceship> ship = b::dynamic_pointer_cast<spaceship>(o);
            if(ship)
            {
                std::cout << "Changed property " << a->property_name() << " on " << ship->name.get() << std::endl;
            }
        }
    }

private:
};

#define TEST_CASE_SHIPYARD \
    m::command_manager<std::string>::ptr cmd_mgr = m::command_manager<std::string>::create(); \
\
    b::shared_ptr<spaceship> ship1(new spaceship(cmd_mgr, "USS Enterprise", "Captain James T Kirk")); \
    b::shared_ptr<spaceship> ship2(new spaceship(cmd_mgr, "Millennium Falcon", "Han Solo")); \
    b::shared_ptr<spaceship> ship3(new spaceship(cmd_mgr, "Executor", "Lord Darth Vader")); \
    b::shared_ptr<spaceship> ship4(new spaceship(cmd_mgr, "Battlestar Galactica", "Admiral William Adama")); \
    b::shared_ptr<spaceship> ship5(new spaceship(cmd_mgr, "Serenity", "Captain Malcolm 'Mal' Reynolds")); \
\
    b::shared_ptr<spaceship_observer> observer(new spaceship_observer()); \
\
    observer->connect(ship1); \
    observer->connect(ship2); \
    observer->connect(ship3); \
    observer->connect(ship4); \
    observer->connect(ship5);

BOOST_AUTO_TEST_CASE(test_command_manager)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_EQ(false, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    // Give warp speed command to USS Enterprise
    cmd_mgr->add_command(ship1->warp_speed_command);

    EXPECT_EQ(false, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    cmd_mgr->execute_commands();

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    // Give warp speed command to Millennium Falcon and Battlestar Galactica
    cmd_mgr->add_command(ship2->warp_speed_command);
    cmd_mgr->add_command(ship4->warp_speed_command);

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(false, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(false, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    cmd_mgr->execute_commands();

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(true, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(true, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    // Give impulse speed command to USS Enterprise
    cmd_mgr->add_command(ship1->impulse_speed_command);

    EXPECT_EQ(true, ship1->at_warp_speed());
    EXPECT_EQ(false, ship1->at_impulse_speed());
    EXPECT_EQ(true, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(true, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());

    cmd_mgr->execute_commands();

    EXPECT_EQ(false, ship1->at_warp_speed());
    EXPECT_EQ(true, ship1->at_impulse_speed());
    EXPECT_EQ(true, ship2->at_warp_speed());
    EXPECT_EQ(false, ship3->at_warp_speed());
    EXPECT_EQ(true, ship4->at_warp_speed());
    EXPECT_EQ(false, ship5->at_warp_speed());
}

BOOST_AUTO_TEST_CASE(test_spaceship_observer)
{
    TEST_CASE_SHIPYARD

    // Give Mr Spock command of USS Enterprise
    EXPECT_EQ(true, std::equal(ship1->captain.get(), "Captain James T Kirk"));

    ship1->captain = "Mr Spock";

    EXPECT_EQ(true, std::equal(ship1->captain.get(), "Mr Spock"));

    // Return command of USS Enterprise to Captain Kirk
    ship1->captain = "Captain James T Kirk";

    EXPECT_EQ(true, std::equal(ship1->captain.get(), "Captain James T Kirk"));
}

BOOST_AUTO_TEST_SUITE_END()
