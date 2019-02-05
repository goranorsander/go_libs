//
//  placebo_lockable_signals_string_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_signals_string_placebo_lockable_test_suite, cpp11_not_supported) {}
#else

#include <string>
#include <go/property.hpp>
#include <go/signals.hpp>
#include <go/utility.hpp>

namespace p = go::property;
namespace ph = std::placeholders;
namespace s = go::signals;
namespace u = go::utility;

namespace
{

// Test signals
class fleet_commander
    : public u::noncopyable_nonmovable
{
public:
    typedef fleet_commander this_type;
    typedef std::shared_ptr<fleet_commander> ptr;
    typedef std::weak_ptr<fleet_commander> wptr;
    typedef s::signal<void(const bool&), s::default_collector<typename std::function<void(const bool&)>::result_type>, u::placebo_lockable> fire_lasers_signal;
    typedef s::signal<bool(), s::default_collector<typename std::function<bool()>::result_type>, u::placebo_lockable> fire_proton_torpedoes_signal;

public:
    virtual ~fleet_commander() GO_DEFAULT_DESTRUCTOR

private:
    fleet_commander(const std::string& commander_, const std::string& battle_)
        : u::noncopyable_nonmovable()
        , commander("commander", commander_)
        , battle("battle", battle_)
        , fire_lasers()
        , fire_proton_torpedoes()
    {
    }

public:
    static ptr create(const std::string& commander_, const std::string& battle_)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(const std::string& commander_, const std::string& battle_) : this_type(commander_, battle_) {}
        };

        return std::make_shared<make_shared_enabler, const std::string&, const std::string&>(commander_, battle_);
    }

public:
    p::value_property<std::string> commander;
    p::value_property<std::string> battle;

    fire_lasers_signal fire_lasers;
    fire_proton_torpedoes_signal fire_proton_torpedoes;
};

class spaceship
    : public u::noncopyable_nonmovable
{
public:
    virtual ~spaceship()
    {
        fleet_commander::ptr fleet_commander_ = _fleet_commander.lock();
        if(fleet_commander_)
        {
            fleet_commander_->fire_lasers.disconnect(_fire_lasers_slot_key);
            fleet_commander_->fire_proton_torpedoes.disconnect(_fire_proton_torpedoes_slot_key);
        }
    }

public:
    spaceship(const fleet_commander::ptr& fleet_commander_, const std::string& name_, const std::string& captain_, const int proton_torpedoes_)
        : u::noncopyable_nonmovable()
        , name("name", name_)
        , captain("captain", captain_)
        , lasers_firing("lasers_firing", false)
        , proton_torpedoes("proton_torpedoes", proton_torpedoes_)
        , _fleet_commander(fleet_commander_)
        , _fire_lasers_slot_key()
        , _fire_proton_torpedoes_slot_key()
    {
        _fire_lasers_slot_key = fleet_commander_->fire_lasers.connect(std::bind(&p::value_property<bool>::set, &lasers_firing, ph::_1));
        _fire_proton_torpedoes_slot_key = fleet_commander_->fire_proton_torpedoes.connect(std::bind(&spaceship::fire_proton_torpedo, this));
    }

public:
    bool fire_proton_torpedo()
    {
        if(proton_torpedoes > 0)
        {
            proton_torpedoes = proton_torpedoes - 1;
            return true;
        }
        return false;
    }

public:
    p::value_property<std::string> name;
    p::value_property<std::string> captain;
    p::value_property<bool> lasers_firing;
    p::value_property<int> proton_torpedoes;

private:
    fleet_commander::wptr _fleet_commander;
    s::slot_key _fire_lasers_slot_key;
    s::slot_key _fire_proton_torpedoes_slot_key;
};

#define TEST_CASE_SHIPYARD \
    fleet_commander::ptr fleet_commander_ = fleet_commander::create("General Jan Dodonna", "Battle of Yavin"); \
\
    std::shared_ptr<spaceship> ship1 = std::make_shared<spaceship, const fleet_commander::ptr&, const std::string&, const std::string&, const int>(fleet_commander_, "Millennium Falcon", "Han Solo", 0); \
    std::shared_ptr<spaceship> ship2 = std::make_shared<spaceship, const fleet_commander::ptr&, const std::string&, const std::string&, const int>(fleet_commander_, "X-Wing Red Leader", "Garven Dreis", 6); \
    std::shared_ptr<spaceship> ship3 = std::make_shared<spaceship, const fleet_commander::ptr&, const std::string&, const std::string&, const int>(fleet_commander_, "X-Wing Red Two", "Wedge Antilles", 6); \
    std::shared_ptr<spaceship> ship4 = std::make_shared<spaceship, const fleet_commander::ptr&, const std::string&, const std::string&, const int>(fleet_commander_, "X-Wing Red Three", "Biggs Darklighter", 6); \
    std::shared_ptr<spaceship> ship5 = std::make_shared<spaceship, const fleet_commander::ptr&, const std::string&, const std::string&, const int>(fleet_commander_, "X-Wing Red Four", "John D. Branon", 6); \
    std::shared_ptr<spaceship> ship6 = std::make_shared<spaceship, const fleet_commander::ptr&, const std::string&, const std::string&, const int>(fleet_commander_, "X-Wing Red Five", "Luke Skywalker", 6); \
    std::shared_ptr<spaceship> ship7 = std::make_shared<spaceship, const fleet_commander::ptr&, const std::string&, const std::string&, const int>(fleet_commander_, "Y-Wing Gold Leader", "Jon 'Dutch' Vander", 20); \
    std::shared_ptr<spaceship> ship8 = std::make_shared<spaceship, const fleet_commander::ptr&, const std::string&, const std::string&, const int>(fleet_commander_, "Y-Wing Gold Two", "Dex Tiree", 20);

TEST(std_signals_string_placebo_lockable_test_suite, test_fire_lasers)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_TRUE(std::string("General Jan Dodonna") == fleet_commander_->commander);
    EXPECT_TRUE(std::string("Battle of Yavin") == fleet_commander_->battle);
    EXPECT_EQ(false, fleet_commander_->fire_lasers.empty());
    EXPECT_EQ(false, fleet_commander_->fire_proton_torpedoes.empty());

    EXPECT_EQ(false, ship1->lasers_firing());
    EXPECT_EQ(false, ship2->lasers_firing());
    EXPECT_EQ(false, ship3->lasers_firing());
    EXPECT_EQ(false, ship4->lasers_firing());
    EXPECT_EQ(false, ship5->lasers_firing());
    EXPECT_EQ(false, ship6->lasers_firing());
    EXPECT_EQ(false, ship7->lasers_firing());
    EXPECT_EQ(false, ship8->lasers_firing());

    EXPECT_EQ(0, ship1->proton_torpedoes());
    EXPECT_EQ(6, ship2->proton_torpedoes());
    EXPECT_EQ(6, ship3->proton_torpedoes());
    EXPECT_EQ(6, ship4->proton_torpedoes());
    EXPECT_EQ(6, ship5->proton_torpedoes());
    EXPECT_EQ(6, ship6->proton_torpedoes());
    EXPECT_EQ(20, ship7->proton_torpedoes());
    EXPECT_EQ(20, ship8->proton_torpedoes());

    // Start fire lasers
    fleet_commander_->fire_lasers(true);

    EXPECT_EQ(true, ship1->lasers_firing());
    EXPECT_EQ(true, ship2->lasers_firing());
    EXPECT_EQ(true, ship3->lasers_firing());
    EXPECT_EQ(true, ship4->lasers_firing());
    EXPECT_EQ(true, ship5->lasers_firing());
    EXPECT_EQ(true, ship6->lasers_firing());
    EXPECT_EQ(true, ship7->lasers_firing());
    EXPECT_EQ(true, ship8->lasers_firing());

    EXPECT_EQ(0, ship1->proton_torpedoes());
    EXPECT_EQ(6, ship2->proton_torpedoes());
    EXPECT_EQ(6, ship3->proton_torpedoes());
    EXPECT_EQ(6, ship4->proton_torpedoes());
    EXPECT_EQ(6, ship5->proton_torpedoes());
    EXPECT_EQ(6, ship6->proton_torpedoes());
    EXPECT_EQ(20, ship7->proton_torpedoes());
    EXPECT_EQ(20, ship8->proton_torpedoes());

    // Stop fire lasers
    fleet_commander_->fire_lasers(false);

    EXPECT_EQ(false, ship1->lasers_firing());
    EXPECT_EQ(false, ship2->lasers_firing());
    EXPECT_EQ(false, ship3->lasers_firing());
    EXPECT_EQ(false, ship4->lasers_firing());
    EXPECT_EQ(false, ship5->lasers_firing());
    EXPECT_EQ(false, ship6->lasers_firing());
    EXPECT_EQ(false, ship7->lasers_firing());
    EXPECT_EQ(false, ship8->lasers_firing());

    EXPECT_EQ(0, ship1->proton_torpedoes());
    EXPECT_EQ(6, ship2->proton_torpedoes());
    EXPECT_EQ(6, ship3->proton_torpedoes());
    EXPECT_EQ(6, ship4->proton_torpedoes());
    EXPECT_EQ(6, ship5->proton_torpedoes());
    EXPECT_EQ(6, ship6->proton_torpedoes());
    EXPECT_EQ(20, ship7->proton_torpedoes());
    EXPECT_EQ(20, ship8->proton_torpedoes());
}

TEST(std_signals_string_placebo_lockable_test_suite, test_fire_proton_torpedoes)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_TRUE(std::string("General Jan Dodonna") == fleet_commander_->commander);
    EXPECT_TRUE(std::string("Battle of Yavin") == fleet_commander_->battle);
    EXPECT_EQ(false, fleet_commander_->fire_lasers.empty());
    EXPECT_EQ(false, fleet_commander_->fire_proton_torpedoes.empty());

    EXPECT_EQ(false, ship1->lasers_firing());
    EXPECT_EQ(false, ship2->lasers_firing());
    EXPECT_EQ(false, ship3->lasers_firing());
    EXPECT_EQ(false, ship4->lasers_firing());
    EXPECT_EQ(false, ship5->lasers_firing());
    EXPECT_EQ(false, ship6->lasers_firing());
    EXPECT_EQ(false, ship7->lasers_firing());
    EXPECT_EQ(false, ship8->lasers_firing());

    EXPECT_EQ(0, ship1->proton_torpedoes());
    EXPECT_EQ(6, ship2->proton_torpedoes());
    EXPECT_EQ(6, ship3->proton_torpedoes());
    EXPECT_EQ(6, ship4->proton_torpedoes());
    EXPECT_EQ(6, ship5->proton_torpedoes());
    EXPECT_EQ(6, ship6->proton_torpedoes());
    EXPECT_EQ(20, ship7->proton_torpedoes());
    EXPECT_EQ(20, ship8->proton_torpedoes());

    // Fire proton torpedoes
    fleet_commander_->fire_proton_torpedoes();

    EXPECT_EQ(false, ship1->lasers_firing());
    EXPECT_EQ(false, ship2->lasers_firing());
    EXPECT_EQ(false, ship3->lasers_firing());
    EXPECT_EQ(false, ship4->lasers_firing());
    EXPECT_EQ(false, ship5->lasers_firing());
    EXPECT_EQ(false, ship6->lasers_firing());
    EXPECT_EQ(false, ship7->lasers_firing());
    EXPECT_EQ(false, ship8->lasers_firing());

    EXPECT_EQ(0, ship1->proton_torpedoes());
    EXPECT_EQ(5, ship2->proton_torpedoes());
    EXPECT_EQ(5, ship3->proton_torpedoes());
    EXPECT_EQ(5, ship4->proton_torpedoes());
    EXPECT_EQ(5, ship5->proton_torpedoes());
    EXPECT_EQ(5, ship6->proton_torpedoes());
    EXPECT_EQ(19, ship7->proton_torpedoes());
    EXPECT_EQ(19, ship8->proton_torpedoes());
}

TEST(std_signals_string_placebo_lockable_test_suite, test_fire_all_weapons)
{
    TEST_CASE_SHIPYARD

    // After connect
    EXPECT_TRUE(std::string("General Jan Dodonna") == fleet_commander_->commander);
    EXPECT_TRUE(std::string("Battle of Yavin") == fleet_commander_->battle);
    EXPECT_EQ(false, fleet_commander_->fire_lasers.empty());
    EXPECT_EQ(false, fleet_commander_->fire_proton_torpedoes.empty());

    EXPECT_EQ(false, ship1->lasers_firing());
    EXPECT_EQ(false, ship2->lasers_firing());
    EXPECT_EQ(false, ship3->lasers_firing());
    EXPECT_EQ(false, ship4->lasers_firing());
    EXPECT_EQ(false, ship5->lasers_firing());
    EXPECT_EQ(false, ship6->lasers_firing());
    EXPECT_EQ(false, ship7->lasers_firing());
    EXPECT_EQ(false, ship8->lasers_firing());

    EXPECT_EQ(0, ship1->proton_torpedoes());
    EXPECT_EQ(6, ship2->proton_torpedoes());
    EXPECT_EQ(6, ship3->proton_torpedoes());
    EXPECT_EQ(6, ship4->proton_torpedoes());
    EXPECT_EQ(6, ship5->proton_torpedoes());
    EXPECT_EQ(6, ship6->proton_torpedoes());
    EXPECT_EQ(20, ship7->proton_torpedoes());
    EXPECT_EQ(20, ship8->proton_torpedoes());

    // Start fire lasers
    fleet_commander_->fire_lasers(true);

    EXPECT_EQ(true, ship1->lasers_firing());
    EXPECT_EQ(true, ship2->lasers_firing());
    EXPECT_EQ(true, ship3->lasers_firing());
    EXPECT_EQ(true, ship4->lasers_firing());
    EXPECT_EQ(true, ship5->lasers_firing());
    EXPECT_EQ(true, ship6->lasers_firing());
    EXPECT_EQ(true, ship7->lasers_firing());
    EXPECT_EQ(true, ship8->lasers_firing());

    EXPECT_EQ(0, ship1->proton_torpedoes());
    EXPECT_EQ(6, ship2->proton_torpedoes());
    EXPECT_EQ(6, ship3->proton_torpedoes());
    EXPECT_EQ(6, ship4->proton_torpedoes());
    EXPECT_EQ(6, ship5->proton_torpedoes());
    EXPECT_EQ(6, ship6->proton_torpedoes());
    EXPECT_EQ(20, ship7->proton_torpedoes());
    EXPECT_EQ(20, ship8->proton_torpedoes());

    // Fire six volleys of proton torpedoes
    int volley_count = 0;
    while(volley_count < 6)
    {
        fleet_commander_->fire_proton_torpedoes();
        ++volley_count;

        EXPECT_EQ(true, ship1->lasers_firing());
        EXPECT_EQ(true, ship2->lasers_firing());
        EXPECT_EQ(true, ship3->lasers_firing());
        EXPECT_EQ(true, ship4->lasers_firing());
        EXPECT_EQ(true, ship5->lasers_firing());
        EXPECT_EQ(true, ship6->lasers_firing());
        EXPECT_EQ(true, ship7->lasers_firing());
        EXPECT_EQ(true, ship8->lasers_firing());

        EXPECT_EQ(0, ship1->proton_torpedoes());
        EXPECT_EQ(6 - volley_count, ship2->proton_torpedoes());
        EXPECT_EQ(6 - volley_count, ship3->proton_torpedoes());
        EXPECT_EQ(6 - volley_count, ship4->proton_torpedoes());
        EXPECT_EQ(6 - volley_count, ship5->proton_torpedoes());
        EXPECT_EQ(6 - volley_count, ship6->proton_torpedoes());
        EXPECT_EQ(20 - volley_count, ship7->proton_torpedoes());
        EXPECT_EQ(20 - volley_count, ship8->proton_torpedoes());
    }

    // Stop fire lasers
    fleet_commander_->fire_lasers(false);

    EXPECT_EQ(false, ship1->lasers_firing());
    EXPECT_EQ(false, ship2->lasers_firing());
    EXPECT_EQ(false, ship3->lasers_firing());
    EXPECT_EQ(false, ship4->lasers_firing());
    EXPECT_EQ(false, ship5->lasers_firing());
    EXPECT_EQ(false, ship6->lasers_firing());
    EXPECT_EQ(false, ship7->lasers_firing());
    EXPECT_EQ(false, ship8->lasers_firing());

    EXPECT_EQ(0, ship1->proton_torpedoes());
    EXPECT_EQ(0, ship2->proton_torpedoes());
    EXPECT_EQ(0, ship3->proton_torpedoes());
    EXPECT_EQ(0, ship4->proton_torpedoes());
    EXPECT_EQ(0, ship5->proton_torpedoes());
    EXPECT_EQ(0, ship6->proton_torpedoes());
    EXPECT_EQ(14, ship7->proton_torpedoes());
    EXPECT_EQ(14, ship8->proton_torpedoes());

    // Fire proton torpedoes
    fleet_commander_->fire_proton_torpedoes();

    EXPECT_EQ(false, ship1->lasers_firing());
    EXPECT_EQ(false, ship2->lasers_firing());
    EXPECT_EQ(false, ship3->lasers_firing());
    EXPECT_EQ(false, ship4->lasers_firing());
    EXPECT_EQ(false, ship5->lasers_firing());
    EXPECT_EQ(false, ship6->lasers_firing());
    EXPECT_EQ(false, ship7->lasers_firing());
    EXPECT_EQ(false, ship8->lasers_firing());

    EXPECT_EQ(0, ship1->proton_torpedoes());
    EXPECT_EQ(0, ship2->proton_torpedoes());
    EXPECT_EQ(0, ship3->proton_torpedoes());
    EXPECT_EQ(0, ship4->proton_torpedoes());
    EXPECT_EQ(0, ship5->proton_torpedoes());
    EXPECT_EQ(0, ship6->proton_torpedoes());
    EXPECT_EQ(13, ship7->proton_torpedoes());
    EXPECT_EQ(13, ship8->proton_torpedoes());
}

}

#endif  // Required C++11 feature is not supported by this compiler
