//
//  command_manager_test_suite.cpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <functional>
#include <string>

#include <gtest/gtest.h>

#include <go/property.hpp>
#include <go/signals.hpp>

namespace p = go::property;
namespace ph = std::placeholders;
namespace s = go::signals;

namespace
{

// Test signals
class fleet_commander
{
public:
    typedef std::shared_ptr<fleet_commander> ptr;
    typedef std::weak_ptr<fleet_commander> wptr;
    typedef go::signals::signal<std::function<void(const bool&)>> fire_lasers_signal;
    typedef go::signals::signal<std::function<bool()>> fire_proton_torpedoes_signal;

public:
    ~fleet_commander()
    {
    }

private:
    fleet_commander(const fleet_commander&) = delete;

    fleet_commander(const std::string& cmd, const std::string& btl)
        : commander("commander", cmd)
        , battle("battle", btl)
        , fire_lasers()
        , fire_proton_torpedoes()
    {
    }

public:
    static ptr create(const std::string& cmd, const std::string& btl)
    {
        return ptr(new fleet_commander(cmd, btl));
    }

public:
    p::value_scalar_property<std::string, std::string> commander;
    p::value_scalar_property<std::string, std::string> battle;

    fire_lasers_signal fire_lasers;
    fire_proton_torpedoes_signal fire_proton_torpedoes;
};

class spaceship
{
public:
    ~spaceship()
    {
        fleet_commander::ptr flt_cmd = _fleet_commander.lock();
        if(flt_cmd)
        {
            flt_cmd->fire_lasers.disconnect(_fire_lasers_slot_key);
            flt_cmd->fire_proton_torpedoes.disconnect(_fire_proton_torpedoes_slot_key);
        }
    }

private:
    spaceship(const spaceship&) = delete;

public:
    spaceship(const fleet_commander::ptr& flt_cmd, const std::string& nme, const std::string& cpt, const int trpds)
        : name("name", nme)
        , captain("captain", cpt)
        , lasers_firing("lasers_firing", false)
        , proton_torpedoes("proton_torpedoes", trpds)
        , _fleet_commander(flt_cmd)
        , _fire_lasers_slot_key(0)
        , _fire_proton_torpedoes_slot_key(0)
    {
        _fire_lasers_slot_key = flt_cmd->fire_lasers.connect(std::bind(&p::value_scalar_property<bool, std::string>::set, &lasers_firing, ph::_1));
        _fire_proton_torpedoes_slot_key = flt_cmd->fire_proton_torpedoes.connect(std::bind(&spaceship::fire_proton_torpedo, this));
    }

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
    p::value_scalar_property<std::string, std::string> name;
    p::value_scalar_property<std::string, std::string> captain;
    p::value_scalar_property<bool, std::string> lasers_firing;
    p::value_scalar_property<int, std::string> proton_torpedoes;

private:
    fleet_commander::wptr _fleet_commander;
    s::slot_key_type _fire_lasers_slot_key;
    s::slot_key_type _fire_proton_torpedoes_slot_key;
};

#define TEST_CASE_SHIPYARD \
    fleet_commander::ptr flt_cmd = fleet_commander::create("General Jan Dodonna", "Battle of Yavin"); \
\
    std::shared_ptr<spaceship> ship1(new spaceship(flt_cmd, "Millennium Falcon", "Han Solo", 0)); \
    std::shared_ptr<spaceship> ship2(new spaceship(flt_cmd, "X-Wing Red Leader", "Garven Dreis", 6)); \
    std::shared_ptr<spaceship> ship3(new spaceship(flt_cmd, "X-Wing Red Two", "Wedge Antilles", 6)); \
    std::shared_ptr<spaceship> ship4(new spaceship(flt_cmd, "X-Wing Red Three", "Biggs Darklighter", 6)); \
    std::shared_ptr<spaceship> ship5(new spaceship(flt_cmd, "X-Wing Red Four", " John D. Branon", 6)); \
    std::shared_ptr<spaceship> ship6(new spaceship(flt_cmd, "X-Wing Red Five", "Luke Skywalker", 6)); \
    std::shared_ptr<spaceship> ship7(new spaceship(flt_cmd, "Y-Wing Gold Leader", "Jon 'Dutch' Vander", 20)); \
    std::shared_ptr<spaceship> ship8(new spaceship(flt_cmd, "Y-Wing Gold Two", "Dex Tiree", 20));

TEST(signals_test_suite, test_fire_lasers)
{
    TEST_CASE_SHIPYARD

        // After connect
        EXPECT_TRUE(std::string("General Jan Dodonna") == flt_cmd->commander);
    EXPECT_TRUE(std::string("Battle of Yavin") == flt_cmd->battle);
    EXPECT_EQ(false, flt_cmd->fire_lasers.empty());
    EXPECT_EQ(false, flt_cmd->fire_proton_torpedoes.empty());

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
    flt_cmd->fire_lasers(true);

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
    flt_cmd->fire_lasers(false);

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

TEST(signals_test_suite, test_fire_proton_torpedoes)
{
    TEST_CASE_SHIPYARD

        // After connect
        EXPECT_TRUE(std::string("General Jan Dodonna") == flt_cmd->commander);
    EXPECT_TRUE(std::string("Battle of Yavin") == flt_cmd->battle);
    EXPECT_EQ(false, flt_cmd->fire_lasers.empty());
    EXPECT_EQ(false, flt_cmd->fire_proton_torpedoes.empty());

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
    flt_cmd->fire_proton_torpedoes();

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

TEST(signals_test_suite, test_fire_all_weapons)
{
    TEST_CASE_SHIPYARD

        // After connect
        EXPECT_TRUE(std::string("General Jan Dodonna") == flt_cmd->commander);
    EXPECT_TRUE(std::string("Battle of Yavin") == flt_cmd->battle);
    EXPECT_EQ(false, flt_cmd->fire_lasers.empty());
    EXPECT_EQ(false, flt_cmd->fire_proton_torpedoes.empty());

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
    flt_cmd->fire_lasers(true);

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
        flt_cmd->fire_proton_torpedoes();
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
    flt_cmd->fire_lasers(false);

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
    flt_cmd->fire_proton_torpedoes();

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
