//
//  command_manager_phoenix_test_suite.cpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

#if (BOOST_COMP_MSVC) && (BOOST_MSVC <= 1700)
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
namespace s = go_boost::signals;
namespace u = go_boost::utility;

namespace
{

// Test command_manager
class spaceship
    : public m::observable_object
    , private u::noncopyable_nonmovable
{
public:
    virtual ~spaceship()
    {
    }

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
        name.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_name)));
        name.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(name.name(), boost::bind(&spaceship::on_property_changed, this, _1), bp::ref(_name), bph::arg1));
        captain.getter(bp::bind(mu::get_property_value, bph::arg1)(bp::cref(_captain)));
        captain.setter(bp::bind(mu::set_property_value_notify_changed, bph::arg1, bph::arg2, bph::arg3, bph::arg4)(captain.name(), boost::bind(&spaceship::on_property_changed, this, _1), bp::ref(_captain), bph::arg1));
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
    virtual ~spaceship_observer()
    {
    }

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
    m::command_manager::ptr cmd_mgr = m::command_manager::create(); \
\
    boost::shared_ptr<spaceship> ship1 = boost::make_shared<spaceship, const m::command_manager::ptr&, const std::string&, const std::string&>(cmd_mgr, "USS Enterprise", "Captain James T Kirk"); \
    boost::shared_ptr<spaceship> ship2 = boost::make_shared<spaceship, const m::command_manager::ptr&, const std::string&, const std::string&>(cmd_mgr, "Millennium Falcon", "Han Solo"); \
    boost::shared_ptr<spaceship> ship3 = boost::make_shared<spaceship, const m::command_manager::ptr&, const std::string&, const std::string&>(cmd_mgr, "Executor", "Lord Darth Vader"); \
    boost::shared_ptr<spaceship> ship4 = boost::make_shared<spaceship, const m::command_manager::ptr&, const std::string&, const std::string&>(cmd_mgr, "Battlestar Galactica", "Admiral William Adama"); \
    boost::shared_ptr<spaceship> ship5 = boost::make_shared<spaceship, const m::command_manager::ptr&, const std::string&, const std::string&>(cmd_mgr, "Serenity", "Captain Malcolm 'Mal' Reynolds"); \
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

    // Give warp speed command_interface to USS Enterprise
    cmd_mgr->post(ship1->warp_speed_command);

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

    // Give warp speed command_interface to Millennium Falcon and Battlestar Galactica
    cmd_mgr->post(ship2->warp_speed_command);
    cmd_mgr->post(ship4->warp_speed_command);

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

    // Give impulse speed command_interface to USS Enterprise
    cmd_mgr->post(ship1->impulse_speed_command);

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
    EXPECT_EQ(0, observer->get_on_property_changed_count("USS Enterprise", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Millennium Falcon", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Executor", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Battlestar Galactica", "captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count("Serenity", "captain"));

    // Give Mr Spock command_interface of USS Enterprise
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

    // Return command_interface of USS Enterprise to Captain Kirk
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

#endif  // Boost.Phoenix is not supported by this compiler
