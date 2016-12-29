//
//  wcommand_manager_test_suite.cpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <gtest/gtest.h>
#include <go_boost/config.hpp>

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

namespace m = go_boost::mvvm;
namespace p = go_boost::property;
namespace rop = go_boost::property::read_only;
namespace s = go_boost::signals;
namespace u = go_boost::utility;

namespace
{

// Test command_manager
class spaceship
    : public m::wobservable_object
    , private u::noncopyable_nonmovable
{
public:
    virtual ~spaceship()
    {
    }

public:
    spaceship(const m::wcommand_manager::ptr& cmd_mgr)
        : m::wobservable_object()
        , _command_manager(cmd_mgr)
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name()
        , _captain()
        , _impulse_speed_command()
        , _warp_speed_command()
        , name(L"name")
        , captain(L"captain")
        , impulse_speed_command(L"impulse_speed_command")
        , warp_speed_command(L"warp_speed_command")
    {
        bind_properties();
    }

    spaceship(const m::wcommand_manager::ptr& cmd_mgr, const std::wstring& nme, const std::wstring& cpt)
        : m::wobservable_object()
        , _command_manager(cmd_mgr)
        , _at_impulse_speed(false)
        , _at_warp_speed(false)
        , _name(nme)
        , _captain(cpt)
        , _impulse_speed_command()
        , _warp_speed_command()
        , name(L"name")
        , captain(L"captain")
        , impulse_speed_command(L"impulse_speed_command")
        , warp_speed_command(L"warp_speed_command")
    {
        bind_properties();
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
    p::wproperty<std::wstring> name;
    p::wproperty<std::wstring> captain;
    rop::wproperty<m::wcommand_interface::ptr> impulse_speed_command;
    rop::wproperty<m::wcommand_interface::ptr> warp_speed_command;

public:
    bool at_impulse_speed() const { return _at_impulse_speed; }
    bool at_warp_speed() const { return _at_warp_speed; }

private:
    // name property
    std::wstring get_name() const
    {
        return _name;
    }

    void set_name(const std::wstring& v)
    {
        if(v != _name)
        {
            _name = v;
            on_property_changed(name.name());
        }
    }

    // captain property
    std::wstring get_captain() const
    {
        return _captain;
    }

    void set_captain(const std::wstring& v)
    {
        if(v != _captain)
        {
            _captain = v;
            on_property_changed(captain.name());
        }
    }

    // impulse_speed_command property
    m::wcommand_interface::ptr get_impulse_speed_command()
    {
        if(!_impulse_speed_command)
        {
            _impulse_speed_command = m::relay_wcommand::create(L"impulse_speed", boost::bind(&spaceship::go_to_impulse, this, _1), boost::bind(&spaceship::can_go_to_impulse, this, _1), m::command_parameters::create());
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
    m::wcommand_interface::ptr get_warp_speed_command()
    {
        if(!_warp_speed_command)
        {
            _warp_speed_command = m::relay_wcommand::create(L"warp_speed", boost::bind(&spaceship::go_to_warp, this, _1), boost::bind(&spaceship::can_go_to_warp, this, _1), m::command_parameters::create());
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
    m::wcommand_manager::ptr _command_manager;
    bool _at_impulse_speed;
    bool _at_warp_speed;
    std::wstring _name;
    std::wstring _captain;
    m::wcommand_interface::ptr _impulse_speed_command;
    m::wcommand_interface::ptr _warp_speed_command;
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

    void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
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

    unsigned int get_on_property_changed_count(const std::wstring& ship_name, const std::wstring& property_name) const
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
    typedef std::pair<std::wstring, std::wstring> ship_and_property_type;
    typedef std::map<ship_and_property_type, unsigned int> on_property_changed_counter_type;

    on_property_changed_counter_type _on_property_changed_count;
};

#if BOOST_MSVC > 1500
#define TEST_CASE_SHIPYARD \
    m::wcommand_manager::ptr cmd_mgr = m::wcommand_manager::create(); \
\
    boost::shared_ptr<spaceship> ship1 = boost::make_shared<spaceship, const m::wcommand_manager::ptr&, const std::wstring&, const std::wstring&>(cmd_mgr, L"USS Enterprise", L"Captain James T Kirk"); \
    boost::shared_ptr<spaceship> ship2 = boost::make_shared<spaceship, const m::wcommand_manager::ptr&, const std::wstring&, const std::wstring&>(cmd_mgr, L"Millennium Falcon", L"Han Solo"); \
    boost::shared_ptr<spaceship> ship3 = boost::make_shared<spaceship, const m::wcommand_manager::ptr&, const std::wstring&, const std::wstring&>(cmd_mgr, L"Executor", L"Lord Darth Vader"); \
    boost::shared_ptr<spaceship> ship4 = boost::make_shared<spaceship, const m::wcommand_manager::ptr&, const std::wstring&, const std::wstring&>(cmd_mgr, L"Battlestar Galactica", L"Admiral William Adama"); \
    boost::shared_ptr<spaceship> ship5 = boost::make_shared<spaceship, const m::wcommand_manager::ptr&, const std::wstring&, const std::wstring&>(cmd_mgr, L"Serenity", L"Captain Malcolm 'Mal' Reynolds"); \
\
    boost::shared_ptr<spaceship_observer> observer = boost::make_shared<spaceship_observer>(); \
\
    observer->connect(ship1); \
    observer->connect(ship2); \
    observer->connect(ship3); \
    observer->connect(ship4); \
    observer->connect(ship5);
#else
#define TEST_CASE_SHIPYARD \
    m::wcommand_manager::ptr cmd_mgr = m::wcommand_manager::create(); \
\
    boost::shared_ptr<spaceship> ship1(new spaceship(cmd_mgr, L"USS Enterprise", L"Captain James T Kirk")); \
    boost::shared_ptr<spaceship> ship2(new spaceship(cmd_mgr, L"Millennium Falcon", L"Han Solo")); \
    boost::shared_ptr<spaceship> ship3(new spaceship(cmd_mgr, L"Executor", L"Lord Darth Vader")); \
    boost::shared_ptr<spaceship> ship4(new spaceship(cmd_mgr, L"Battlestar Galactica", L"Admiral William Adama")); \
    boost::shared_ptr<spaceship> ship5(new spaceship(cmd_mgr, L"Serenity", L"Captain Malcolm 'Mal' Reynolds")); \
\
    boost::shared_ptr<spaceship_observer> observer(new spaceship_observer()); \
\
    observer->connect(ship1); \
    observer->connect(ship2); \
    observer->connect(ship3); \
    observer->connect(ship4); \
    observer->connect(ship5);
#endif  // BOOST_MSVC > 1500

TEST(boost_wcommand_manager_test_suite, test_wcommand_manager)
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

TEST(boost_wcommand_manager_test_suite, test_spaceship_observer)
{
    TEST_CASE_SHIPYARD

    // Verify first captain
    EXPECT_EQ(true, ship1->captain() == std::wstring(L"Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == std::wstring(L"Han Solo"));
    EXPECT_EQ(true, ship3->captain() == std::wstring(L"Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == std::wstring(L"Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == std::wstring(L"Captain Malcolm 'Mal' Reynolds"));

    // Verify initial 'on property changed' count
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"USS Enterprise", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Millennium Falcon", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Executor", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Battlestar Galactica", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Serenity", L"captain"));

    // Give Mr Spock command_interface of USS Enterprise
    ship1->captain = L"Mr Spock";

    EXPECT_EQ(true, ship1->captain() == std::wstring(L"Mr Spock"));
    EXPECT_EQ(true, ship2->captain() == std::wstring(L"Han Solo"));
    EXPECT_EQ(true, ship3->captain() == std::wstring(L"Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == std::wstring(L"Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == std::wstring(L"Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(1, observer->get_on_property_changed_count(L"USS Enterprise", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Millennium Falcon", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Executor", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Battlestar Galactica", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Serenity", L"captain"));

    // Return command_interface of USS Enterprise to Captain Kirk
    ship1->captain = L"Captain James T Kirk";

    EXPECT_EQ(true, ship1->captain() == std::wstring(L"Captain James T Kirk"));
    EXPECT_EQ(true, ship2->captain() == std::wstring(L"Han Solo"));
    EXPECT_EQ(true, ship3->captain() == std::wstring(L"Lord Darth Vader"));
    EXPECT_EQ(true, ship4->captain() == std::wstring(L"Admiral William Adama"));
    EXPECT_EQ(true, ship5->captain() == std::wstring(L"Captain Malcolm 'Mal' Reynolds"));

    EXPECT_EQ(2, observer->get_on_property_changed_count(L"USS Enterprise", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Millennium Falcon", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Executor", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Battlestar Galactica", L"captain"));
    EXPECT_EQ(0, observer->get_on_property_changed_count(L"Serenity", L"captain"));
}

}
