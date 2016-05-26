//
//  command_manager_lambda_test_suite.cpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if (GO_COMP_MSVC) && (_MSC_VER <= 1800)
#pragma message("C++11/14 is not supported by this compiler")
#else

#include <gtest/gtest.h>

#include <go/mvvm.hpp>
#include <go/property.hpp>

namespace m = go::mvvm;
namespace p = go::property;
namespace ph = std::placeholders;
namespace rop = go::property::read_only;
namespace s = go::signals;

namespace
{

// Test command_manager
class spaceship
    : public m::observable_object
{
public:
    virtual ~spaceship()
    {
    }

private:
    spaceship(const spaceship&) = delete;

public:
    spaceship(const m::command_manager::ptr& cmd_mgr)
        : m::observable_object()
        , _command_manager(cmd_mgr)
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name()
        , _captain()
        , _impulse_speed_command()
        , _warp_speed_command()
        , name("name")
        , captain("captain")
        , impulse_speed_command("impulse_speed_command")
        , warp_speed_command("warp_speed_command")
    {
        bind_properties();
    }

    spaceship(const m::command_manager::ptr& cmd_mgr, const std::string& nme, const std::string& cpt)
        : m::observable_object()
        , _command_manager(cmd_mgr)
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name(nme)
        , _captain(cpt)
        , _impulse_speed_command()
        , _warp_speed_command()
        , name("name")
        , captain("captain")
        , impulse_speed_command("impulse_speed_command")
        , warp_speed_command("warp_speed_command")
    {
        bind_properties();
    }

private:
    void bind_properties()
    {
        name.getter([this]() { return _name; });
        name.setter([this](const std::string& v) { if(v != _name) { _name = v; on_property_changed("name"); } });
        captain.getter([this]() { return _captain; });
        captain.setter([this](const std::string& v) { if(v != _captain) { _captain = v; on_property_changed("captain"); } });
        impulse_speed_command.getter(
            [this]() { if(!_impulse_speed_command) {
            _impulse_speed_command = m::relay_command::create("impulse_speed",
                [this](const m::command_parameters::ptr&) { _at_impulse_speed = true; _at_warp_speed = false; if(_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); } if(_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); } },
                [this](const m::command_parameters::ptr&) { return _at_warp_speed; }, m::command_parameters::create());
        } return _impulse_speed_command; });
        warp_speed_command.getter(
            [this]() { if(!_warp_speed_command) {
            _warp_speed_command = m::relay_command::create("warp_speed",
                [this](const m::command_parameters::ptr&) { _at_impulse_speed = false; _at_warp_speed = true; if(_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); } if(_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); } },
                [this](const m::command_parameters::ptr&) { return !_at_warp_speed; }, m::command_parameters::create());
        } return _warp_speed_command; });
    }

public:
    p::property<std::string> name;
    p::property<std::string> captain;
    rop::property<m::command::ptr> impulse_speed_command;
    rop::property<m::command::ptr> warp_speed_command;

public:
    bool at_impulse_speed() const { return _at_impulse_speed; }
    bool at_warp_speed() const { return _at_warp_speed; }

private:
    m::command_manager::ptr _command_manager;
    bool _at_impulse_speed;
    bool _at_warp_speed;
    std::string _name;
    std::string _captain;
    m::command::ptr _impulse_speed_command;
    m::command::ptr _warp_speed_command;
};

class spaceship_observer
{
public:
    virtual ~spaceship_observer()
    {
    }

    spaceship_observer()
        : _on_property_changed_slot_key(0)
        , _on_property_changed_count()
    {
    }

    void connect(const std::shared_ptr<spaceship>& ship)
    {
        if(ship)
        {
            _on_property_changed_slot_key = ship->property_changed.connect(std::bind(&spaceship_observer::on_property_changed, this, ph::_1, ph::_2));
        }
    }

    void disconnect(const std::shared_ptr<spaceship>& ship)
    {
        if(ship)
        {
            ship->property_changed.disconnect(_on_property_changed_slot_key);
        }
    }

    void on_property_changed(const m::object::ptr& o, const m::property_changed_arguments::ptr& a)
    {
        if(o && a)
        {
            std::shared_ptr<spaceship> ship = std::dynamic_pointer_cast<spaceship>(o);
            if(ship)
            {
                const ship_and_property_type ship_and_property(ship->name.get(), a->property_name());
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

    unsigned int get_on_property_changed_count(const std::string& ship_name, const std::string& property_name) const
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
    typedef std::pair<std::string, std::string> ship_and_property_type;
    typedef std::map<ship_and_property_type, unsigned int> on_property_changed_counter_type;

    s::slot_key_type _on_property_changed_slot_key;
    on_property_changed_counter_type _on_property_changed_count;
};

#define TEST_CASE_SHIPYARD \
    m::command_manager::ptr cmd_mgr = m::command_manager::create(); \
\
    std::shared_ptr<spaceship> ship1(new spaceship(cmd_mgr, "USS Enterprise", "Captain James T Kirk")); \
    std::shared_ptr<spaceship> ship2(new spaceship(cmd_mgr, "Millennium Falcon", "Han Solo")); \
    std::shared_ptr<spaceship> ship3(new spaceship(cmd_mgr, "Executor", "Lord Darth Vader")); \
    std::shared_ptr<spaceship> ship4(new spaceship(cmd_mgr, "Battlestar Galactica", "Admiral William Adama")); \
    std::shared_ptr<spaceship> ship5(new spaceship(cmd_mgr, "Serenity", "Captain Malcolm 'Mal' Reynolds")); \
\
    std::shared_ptr<spaceship_observer> observer(new spaceship_observer()); \
\
    observer->connect(ship1); \
    observer->connect(ship2); \
    observer->connect(ship3); \
    observer->connect(ship4); \
    observer->connect(ship5);

TEST(std_command_manager_lambda_test_suite, test_command_manager)
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

TEST(std_command_manager_lambda_test_suite, test_spaceship_observer)
{
    TEST_CASE_SHIPYARD

    // Verify first captain
    EXPECT_EQ(true, ship1->captain.get() == std::string("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain.get() == std::string("Han Solo"));
    EXPECT_EQ(true, ship3->captain.get() == std::string("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain.get() == std::string("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain.get() == std::string("Captain Malcolm 'Mal' Reynolds"));

    // Verify initial 'on property changed' count
    EXPECT_EQ(0, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Serenity", "captain"));

    // Give Mr Spock command of USS Enterprise
    ship1->captain = "Mr Spock";

    EXPECT_EQ(true, ship1->captain.get() == std::string("Mr Spock"));
    EXPECT_EQ(true, ship2->captain.get() == std::string("Han Solo"));
    EXPECT_EQ(true, ship3->captain.get() == std::string("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain.get() == std::string("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain.get() == std::string("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(1, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Serenity", "captain"));

    // Return command of USS Enterprise to Captain Kirk
    ship1->captain = "Captain James T Kirk";

    EXPECT_EQ(true, ship1->captain.get() == std::string("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain.get() == std::string("Han Solo"));
    EXPECT_EQ(true, ship3->captain.get() == std::string("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain.get() == std::string("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain.get() == std::string("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(2, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Serenity", "captain"));
}

}

#endif // C++11/14 is not supported by this compiler
