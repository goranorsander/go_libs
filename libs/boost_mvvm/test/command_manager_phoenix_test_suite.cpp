//
//  command_manager_phoenix_test_suite.cpp
//
//  Copyright 2015-2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_BOOST_NO_BOOST_PHOENIX)
GO_BOOST_MESSAGE("Boost.Phoenix is not supported by this compiler")
TEST(boost_command_manager_phoenix_test_suite, boost_phoenix_not_supported) {}
#else

#include <go_boost/mvvm.hpp>
#include <go_boost/mvvm/utility.hpp>
#include <go_boost/property.hpp>

namespace bp = boost::phoenix;
namespace bph = boost::phoenix::placeholders;
namespace m = go_boost::mvvm;
namespace mu = go_boost::mvvm::utility;
namespace p = go_boost::property;
namespace rop = go_boost::property::read_only;
namespace u = go_boost::utility;

namespace
{

// Test command_manager
class spaceship
    : public m::observable_object
    , private u::noncopyable_nonmovable
{
public:
    virtual ~spaceship() GO_BOOST_DEFAULT_DESTRUCTOR

private:
    explicit spaceship(const m::command_manager::ptr& command_manager_)
        : m::observable_object()
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

    spaceship(const m::command_manager::ptr& command_manager_, const std::string& name_, const std::string& captain_)
        : m::observable_object()
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
    static boost::shared_ptr<spaceship> create(m::command_manager::ptr& command_manager_)
    {
        boost::shared_ptr<spaceship> ship(new spaceship(command_manager_));
        ship->bind_properties();
        return ship;
    }

    static boost::shared_ptr<spaceship> create(const m::command_manager::ptr& command_manager_, const std::string& name_, const std::string& captain_)
    {
        boost::shared_ptr<spaceship> ship(new spaceship(command_manager_, name_, captain_));
        ship->bind_properties();
        return ship;
    }

private:
    void bind_properties()
    {
        name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_name)));
        name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), name.name(), boost::bind(&spaceship::notify_property_changed, this, _1, _2), bp::ref(_name), bph::arg1, bph::arg2));
        captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_captain)));
        captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(this->shared_from_this(), captain.name(), boost::bind(&spaceship::notify_property_changed, this, _1, _2), bp::ref(_captain), bph::arg1, bph::arg2));
        impulse_speed_command.getter(bp::bind(mu::get_property_relay_command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(std::string("impulse_speed"), boost::bind(&spaceship::go_to_impulse, this, _1), boost::bind(&spaceship::can_go_to_impulse, this, _1), m::command_parameters::create(), bp::ref(_impulse_speed_command)));
        warp_speed_command.getter(bp::bind(mu::get_property_relay_command, bph::arg1, bph::arg2, bph::arg3, bph::arg4, bph::arg5)(std::string("warp_speed"), boost::bind(&spaceship::go_to_warp, this, _1), boost::bind(&spaceship::can_go_to_warp, this, _1), m::command_parameters::create(), bp::ref(_warp_speed_command)));
    }

public:
    p::property<std::string> name;
    p::property<std::string> captain;
    rop::property<m::command_interface::ptr> impulse_speed_command;
    rop::property<m::command_interface::ptr> warp_speed_command;

public:
    bool at_impulse_speed() const { return _at_impulse_speed; }
    bool at_warp_speed() const { return _at_warp_speed; }

private:
    // impulse_speed_command property
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
    m::command_manager::ptr _command_manager;
    bool _at_impulse_speed;
    bool _at_warp_speed;
    std::string _name;
    std::string _captain;
    m::command_interface::ptr _impulse_speed_command;
    m::command_interface::ptr _warp_speed_command;
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

    void on_property_changed(const m::object::ptr& o, const m::property_changed_arguments::ptr& a)
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

    on_property_changed_counter_type _on_property_changed_count;
};

#define TEST_CASE_SHIPYARD \
    m::command_manager::ptr command_mgr = m::command_manager::create(); \
\
    boost::shared_ptr<spaceship> ship1 = spaceship::create(command_mgr, "USS Enterprise", "Captain James T Kirk"); \
    boost::shared_ptr<spaceship> ship2 = spaceship::create(command_mgr, "Millennium Falcon", "Han Solo"); \
    boost::shared_ptr<spaceship> ship3 = spaceship::create(command_mgr, "Executor", "Lord Darth Vader"); \
    boost::shared_ptr<spaceship> ship4 = spaceship::create(command_mgr, "Battlestar Galactica", "Admiral William Adama"); \
    boost::shared_ptr<spaceship> ship5 = spaceship::create(command_mgr, "Serenity", "Captain Malcolm 'Mal' Reynolds"); \
\
    boost::shared_ptr<spaceship_observer> observer = boost::make_shared<spaceship_observer>(); \
\
    observer->connect(ship1); \
    observer->connect(ship2); \
    observer->connect(ship3); \
    observer->connect(ship4); \
    observer->connect(ship5);

TEST(boost_command_manager_phoenix_test_suite, test_command_manager)
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

TEST(boost_command_manager_phoenix_test_suite, test_spaceship_observer)
{
    TEST_CASE_SHIPYARD

    // Verify first captain
    EXPECT_EQ(true, ship1->captain() == std::string("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == std::string("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == std::string("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == std::string("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == std::string("Captain Malcolm 'Mal' Reynolds"));

    // Verify initial 'on property changed' count
    EXPECT_EQ(0u, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Serenity", "captain"));

    // Give Mr Spock command of USS Enterprise
    ship1->captain = "Mr Spock";

    EXPECT_EQ(true, ship1->captain() == std::string("Mr Spock"));
    EXPECT_EQ(true, ship2->captain() == std::string("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == std::string("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == std::string("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == std::string("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(1u, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Serenity", "captain"));

    // Return command of USS Enterprise to Captain Kirk
    ship1->captain = "Captain James T Kirk";

    EXPECT_EQ(true, ship1->captain() == std::string("Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == std::string("Han Solo"));
    EXPECT_EQ(true, ship3->captain() == std::string("Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == std::string("Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == std::string("Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(2u, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0u, observer->get_on_property_changed_count("Serenity", "captain"));
}

}

#endif  // #if defined(GO_BOOST_NO_BOOST_PHOENIX)
