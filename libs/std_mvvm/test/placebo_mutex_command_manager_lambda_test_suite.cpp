//
//  placebo_mutex_command_manager_lambda_test_suite.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_LAMBDA_EXPRESSIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_command_manager_lambda_placebo_mutex_test_suite, cpp11_not_supported) {}
#else

#include <go/mvvm.hpp>
#include <go/property.hpp>
#include <go/utility.hpp>

namespace m = go::mvvm;
namespace mst = go::mvvm::single_threaded;
namespace p = go::property;
namespace ph = std::placeholders;
namespace rop = go::property::read_only;
namespace s = go::signals;
namespace u = go::utility;

namespace
{

// Test command_manager
class spaceship
    : public mst::observable_object
    , public u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_DEFAULT_DESTRUCTOR

private:
    explicit spaceship(const mst::command_manager::ptr& command_manager_)
        : mst::observable_object()
        , u::noncopyable_nonmovable()
        , name("name")
        , captain("captain")
        , impulse_speed_command("impulse_speed_command")
        , warp_speed_command("warp_speed_command")
        , _command_manager(command_manager_)
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name()
        , _captain()
        , _impulse_speed_command()
        , _warp_speed_command()
    {
    }

    spaceship(const mst::command_manager::ptr& command_manager_, const std::string& name_, const std::string& captain_)
        : mst::observable_object()
        , u::noncopyable_nonmovable()
        , name("name")
        , captain("captain")
        , impulse_speed_command("impulse_speed_command")
        , warp_speed_command("warp_speed_command")
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
    static std::shared_ptr<spaceship> create(mst::command_manager::ptr& command_manager_)
    {
        std::shared_ptr<spaceship> ship(new spaceship(command_manager_));
        ship->bind_properties();
        return ship;
    }

    static std::shared_ptr<spaceship> create(const mst::command_manager::ptr& command_manager_, const std::string& name_, const std::string& captain_)
    {
        std::shared_ptr<spaceship> ship(new spaceship(command_manager_, name_, captain_));
        ship->bind_properties();
        return ship;
    }

private:
    void bind_properties()
    {
        name.getter([this]() -> std::string { return _name; });
        name.setter([this](const std::string& v) { if(v != _name) { _name = v; notify_property_changed(this->shared_from_this(), name.name()); } });
        captain.getter([this]() -> std::string { return _captain; });
        captain.setter([this](const std::string& v) { if(v != _captain) { _captain = v; notify_property_changed(this->shared_from_this(), captain.name()); } });
        impulse_speed_command.getter(
            [this]() -> mst::command_interface::ptr { if(!_impulse_speed_command) {
            _impulse_speed_command = mst::relay_command::create("impulse_speed",
                [this](const m::command_parameters::ptr&) { _at_impulse_speed = true; _at_warp_speed = false; if(_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); } if(_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); } },
                [this](const m::command_parameters::ptr&) { return _at_warp_speed; }, m::command_parameters::create());
        } return _impulse_speed_command; });
        warp_speed_command.getter(
            [this]() -> mst::command_interface::ptr { if(!_warp_speed_command) {
            _warp_speed_command = mst::relay_command::create("warp_speed",
                [this](const m::command_parameters::ptr&) { _at_impulse_speed = false; _at_warp_speed = true; if(_impulse_speed_command) { _impulse_speed_command->notify_can_execute_changed(); } if(_warp_speed_command) { _warp_speed_command->notify_can_execute_changed(); } },
                [this](const m::command_parameters::ptr&) { return !_at_warp_speed; }, m::command_parameters::create());
        } return _warp_speed_command; });
    }

public:
    p::property<std::string> name;
    p::property<std::string> captain;
    rop::property<mst::command_interface::ptr> impulse_speed_command;
    rop::property<mst::command_interface::ptr> warp_speed_command;

public:
    bool at_impulse_speed() const { return _at_impulse_speed; }
    bool at_warp_speed() const { return _at_warp_speed; }

private:
    mst::command_manager::ptr _command_manager;
    bool _at_impulse_speed;
    bool _at_warp_speed;
    std::string _name;
    std::string _captain;
    mst::command_interface::ptr _impulse_speed_command;
    mst::command_interface::ptr _warp_speed_command;
};

class spaceship_observer
{
public:
    virtual ~spaceship_observer() GO_DEFAULT_DESTRUCTOR

     spaceship_observer()
        : _on_property_changed_slot_key()
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

    s::slot_key _on_property_changed_slot_key;
    on_property_changed_counter_type _on_property_changed_count;
};

#define TEST_CASE_SHIPYARD \
    mst::command_manager::ptr command_mgr = mst::command_manager::create(); \
\
    std::shared_ptr<spaceship> ship1 = spaceship::create(command_mgr, "USS Enterprise", "Captain James T Kirk"); \
    std::shared_ptr<spaceship> ship2 = spaceship::create(command_mgr, "Millennium Falcon", "Han Solo"); \
    std::shared_ptr<spaceship> ship3 = spaceship::create(command_mgr, "Executor", "Lord Darth Vader"); \
    std::shared_ptr<spaceship> ship4 = spaceship::create(command_mgr, "Battlestar Galactica", "Admiral William Adama"); \
    std::shared_ptr<spaceship> ship5 = spaceship::create(command_mgr, "Serenity", "Captain Malcolm 'Mal' Reynolds"); \
\
    std::shared_ptr<spaceship_observer> observer = std::make_shared<spaceship_observer>(); \
\
    observer->connect(ship1); \
    observer->connect(ship2); \
    observer->connect(ship3); \
    observer->connect(ship4); \
    observer->connect(ship5);

TEST(std_command_manager_lambda_placebo_mutex_test_suite, test_command_manager)
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

TEST(std_command_manager_lambda_placebo_mutex_test_suite, test_spaceship_observer)
{
    TEST_CASE_SHIPYARD

    // Verify first captain
    EXPECT_EQ(true, ship1->captain() == std::string("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == std::string("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == std::string("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == std::string("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == std::string("Captain Malcolm 'Mal' Reynolds"));

    // Verify initial 'on property changed' count
    EXPECT_EQ(0, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Serenity", "captain"));

    // Give Mr Spock command of USS Enterprise
    ship1->captain = "Mr Spock";

    EXPECT_EQ(true, ship1->captain() == std::string("Mr Spock"));
    EXPECT_EQ(true, ship2->captain() == std::string("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == std::string("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == std::string("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == std::string("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(1, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Serenity", "captain"));

    // Return command of USS Enterprise to Captain Kirk
    ship1->captain = "Captain James T Kirk";

    EXPECT_EQ(true, ship1->captain() == std::string("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == std::string("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == std::string("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == std::string("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == std::string("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(2, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Serenity", "captain"));
}

}

#endif  // Required C++11 feature is not supported by this compiler
