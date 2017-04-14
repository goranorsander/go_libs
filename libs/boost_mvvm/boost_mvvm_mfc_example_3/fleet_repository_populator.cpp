//
//  fleet_repository_populator.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "fleet_repository_populator.hpp"
#include "equipment_model.hpp"
#include "fleet_organization_model.hpp"
#include "output_view.hpp"
#include "spaceship_model.hpp"

namespace
{

template<class T, typename A1, typename A2>
boost::shared_ptr<T> create(output_view* object_observer, const A1& a1, const A2& a2)
{
    boost::shared_ptr<T> t = T::create(a1, a2);
    if(t != NULL)
    {
        t->property_changed.connect(boost::bind(&output_view::on_property_changed, object_observer, _1, _2));
    }
    return t;
}

template<class T, typename A1, typename A2, typename A3>
boost::shared_ptr<T> create(output_view* object_observer, const A1& a1, const A2& a2, const A3& a3)
{
    boost::shared_ptr<T> t = T::create(a1, a2, a3);
    if(t != NULL)
    {
        t->property_changed.connect(boost::bind(&output_view::on_property_changed, object_observer, _1, _2));
    }
    return t;
}

void add_colonial_fleet(const fleet_organization_model::ptr& good_guys, output_view* object_observer)
{
    fleet_organization_model::ptr colonial_fleet = create<fleet_organization_model>(object_observer, L"Colonial Fleet", spaceship_interface::ptr());
    good_guys->add_child(colonial_fleet);

    spaceship_model::ptr ship_battlestar_galactica = create<spaceship_model>(object_observer, L"Galactica class", L"Battlestar Galactica");
    ship_battlestar_galactica->captain = L"Admiral William Adama";
    ship_battlestar_galactica->crew_complement = 5000;
    ship_battlestar_galactica->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_battlestar_galactica->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"FTL drive", 2));
    ship_battlestar_galactica->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Sublight engine", 6));
    ship_battlestar_galactica->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Maneuvering engine", 40));
    ship_battlestar_galactica->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Primary battery", 50));
    ship_battlestar_galactica->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Dual point-defense battery", 514));
    ship_battlestar_galactica->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Missile tube", 12));
    fleet_organization_model::ptr battlestar_galactica = create<fleet_organization_model>(object_observer, L"Battlestar Galactica", ship_battlestar_galactica);
    colonial_fleet->add_child(battlestar_galactica);

    spaceship_model::ptr ship_raptor_312 = create<spaceship_model>(object_observer, L"Raptor", L"Raptor 312");
    ship_raptor_312->captain = L"Sharon \"Boomer\" Valerii";
    ship_raptor_312->crew_complement = 2;
    ship_raptor_312->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_raptor_312->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Movable sublight engine pods", 2));
    ship_raptor_312->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"RCS thruster", 4));
    ship_raptor_312->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Ship to ship missile", 10));
    ship_raptor_312->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Rear \"Toaster Slayer\" automatic cannon", 1));
    ship_raptor_312->equipment()->push_back(create<equipment_model>(object_observer, L"Defense", L"Electronic countermeasure", 1));
    fleet_organization_model::ptr raptor_312 = create<fleet_organization_model>(object_observer, L"Raptor 312", ship_raptor_312);
    battlestar_galactica->add_child(raptor_312);

    spaceship_model::ptr ship_viper_8757 = create<spaceship_model>(object_observer, L"Viper Mark VII", L"Viper 8757");
    ship_viper_8757->captain = L"Kara \"Starbuck\" Thrace";
    ship_viper_8757->crew_complement = 1;
    ship_viper_8757->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_viper_8757->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Turbo-thrust engine", 3));
    ship_viper_8757->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"RCS thruster", 4));
    ship_viper_8757->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Kinetic Energy Weapon", 3));
    ship_viper_8757->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Missile", 6));
    fleet_organization_model::ptr viper_8757 = create<fleet_organization_model>(object_observer, L"Viper 8757", ship_viper_8757);
    battlestar_galactica->add_child(viper_8757);
}

void add_rebel_alliance(const fleet_organization_model::ptr& good_guys, output_view* object_observer)
{
    fleet_organization_model::ptr rebel_alliance = create<fleet_organization_model>(object_observer, L"Rebel Alliance", spaceship_interface::ptr());
    good_guys->add_child(rebel_alliance);

    spaceship_model::ptr ship_millennium_falcon = create<spaceship_model>(object_observer, L"Corellian YT-1300 light freighter", L"Millennium Falcon");
    ship_millennium_falcon->captain = L"Han Solo";
    ship_millennium_falcon->crew_complement = 2;
    ship_millennium_falcon->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_millennium_falcon->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Hyperdrive, Class 0.5", 1));
    ship_millennium_falcon->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Girodyne SRB42 sublight engine (heavily modified)", 2));
    ship_millennium_falcon->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Modified Corellian Engineering Corporation AG-2G quad laser cannon", 2));
    ship_millennium_falcon->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Concealed BlasTech Ax-108 \"Ground Buzzer\" surface-defense blaster cannon", 1));
    ship_millennium_falcon->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Arakyd ST2 concussion missile", 8));
    ship_millennium_falcon->equipment()->push_back(create<equipment_model>(object_observer, L"Defense", L"Carbanti 29L electromagnetic countermeasures package", 1));
    ship_millennium_falcon->equipment()->push_back(create<equipment_model>(object_observer, L"Defense", L"Carbanti signal-augmented sensor jammer", 1));
    ship_millennium_falcon->equipment()->push_back(create<equipment_model>(object_observer, L"Defense", L"Carbanti Whistler encryption module", 1));
    fleet_organization_model::ptr millennium_falcon = create<fleet_organization_model>(object_observer, L"Millennium Falcon", ship_millennium_falcon);
    rebel_alliance->add_child(millennium_falcon);

    spaceship_model::ptr ship_xwing_red_two = create<spaceship_model>(object_observer, L"T-65B X-wing starfighter", L"X-Wing Red Two");
    ship_xwing_red_two->captain = L"Wedge Antilles";
    ship_xwing_red_two->crew_complement = 1;
    ship_xwing_red_two->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_xwing_red_two->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Hyperdrive", 1));
    ship_xwing_red_two->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Incom 4L4 fusial thrust engine", 4));
    ship_xwing_red_two->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Taim & Bak KX9 laser cannon", 2));
    ship_xwing_red_two->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Krupx MG7 proton torpedo launcher", 2));
    ship_xwing_red_two->equipment()->push_back(create<equipment_model>(object_observer, L"Shielding", L"Chepat \"Defender\" deflector shield projector", 1));
    ship_xwing_red_two->equipment()->push_back(create<equipment_model>(object_observer, L"Shielding", L"Deflector shield generator", 1));
    fleet_organization_model::ptr xwing_red_two = create<fleet_organization_model>(object_observer, L"X-Wing Red Two", ship_xwing_red_two);
    rebel_alliance->add_child(xwing_red_two);

    spaceship_model::ptr ship_xwing_red_five = create<spaceship_model>(object_observer, L"T-65B X-wing starfighter", L"X-Wing Red Five");
    ship_xwing_red_five->captain = L"Luke Skywalker";
    ship_xwing_red_five->crew_complement = 1;
    ship_xwing_red_five->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_xwing_red_five->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Hyperdrive", 1));
    ship_xwing_red_five->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Incom 4L4 fusial thrust engine", 4));
    ship_xwing_red_five->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Taim & Bak KX9 laser cannon", 2));
    ship_xwing_red_five->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Krupx MG7 proton torpedo launcher", 2));
    ship_xwing_red_five->equipment()->push_back(create<equipment_model>(object_observer, L"Shielding", L"Chepat \"Defender\" deflector shield projector", 1));
    ship_xwing_red_five->equipment()->push_back(create<equipment_model>(object_observer, L"Shielding", L"Deflector shield generator", 1));
    fleet_organization_model::ptr xwing_red_five = create<fleet_organization_model>(object_observer, L"X-Wing Red Five", ship_xwing_red_five);
    rebel_alliance->add_child(xwing_red_five);
}

void add_starfleet(const fleet_organization_model::ptr& good_guys, output_view* object_observer)
{
    fleet_organization_model::ptr starfleet = create<fleet_organization_model>(object_observer, L"Starfleet", spaceship_interface::ptr());
    good_guys->add_child(starfleet);

    spaceship_model::ptr ship_uss_enterprise = create<spaceship_model>(object_observer, L"Constitution class", L"USS Enterprise");
    ship_uss_enterprise->captain = L"Captain James T Kirk";
    ship_uss_enterprise->crew_complement = 205;
    ship_uss_enterprise->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_uss_enterprise->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Warp drive", 1));
    ship_uss_enterprise->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Impulse drive", 1));
    ship_uss_enterprise->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Phaser emitter", 18));
    ship_uss_enterprise->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Photon torpedo launcher", 2));
    ship_uss_enterprise->equipment()->push_back(create<equipment_model>(object_observer, L"Defense", L"Deflector shield ", 1));
    fleet_organization_model::ptr uss_enterprise = create<fleet_organization_model>(object_observer, L"USS Enterprise", ship_uss_enterprise);
    starfleet->add_child(uss_enterprise);
}

void add_galactic_empire(const fleet_organization_model::ptr& evil_menace, output_view* object_observer)
{
    fleet_organization_model::ptr galactic_empire = create<fleet_organization_model>(object_observer, L"Galactic Empire", spaceship_interface::ptr());
    evil_menace->add_child(galactic_empire);

    spaceship_model::ptr ship_death_star_i = create<spaceship_model>(object_observer, L"DS-1 Orbital Battle Station", L"Death Star I");
    ship_death_star_i->captain = L"Grand Moff Tarkin";
    ship_death_star_i->crew_complement = 1556296;
    ship_death_star_i->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Hyperdrive", 1));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Concave Dish Composite Beam Superlaser", 1));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"D6 turbolaser battery", 5000));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"XX-9 heavy turbolaser", 5000));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"SB-920 laser cannon", 2500));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"MS-1 ion cannon", 2500));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Modified Q7 tractor beam projector", 768));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Complement", L"Starfighter", 7000));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Complement", L"Strike cruiser", 4));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Complement", L"Assault shuttle", 3600));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Complement", L"AT-AT", 1400));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Complement", L"AT-ST", 1400));
    ship_death_star_i->equipment()->push_back(create<equipment_model>(object_observer, L"Complement", L"Dropship", 1860));
    fleet_organization_model::ptr death_star = create<fleet_organization_model>(object_observer, L"Death Star", ship_death_star_i);
    galactic_empire->add_child(death_star);

    spaceship_model::ptr ship_executor = create<spaceship_model>(object_observer, L"Executor-class Star Dreadnought", L"Executor");
    ship_executor->captain = L"Darth Vader";
    ship_executor->crew_complement = 280734;
    ship_executor->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Hyperdrive, Class 2.0", 1));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Executor-50.x engine", 13));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Turbolaser cannon", 2000));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Heavy turbolaser cannon", 2000));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Assault concussion missile", 7500));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Heavy ion cannon", 250));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Phylon Transport Q7 tractor beam projector", 40));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Point-defense laser cannon", 500));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Complement", L"TIE Series starfighter", 144));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Complement", L"AT-AT", 30));
    ship_executor->equipment()->push_back(create<equipment_model>(object_observer, L"Complement", L"AT-ST", 40));
    fleet_organization_model::ptr executor = create<fleet_organization_model>(object_observer, L"Executor", ship_executor);
    galactic_empire->add_child(executor);
}

void add_spaceball_fleet(const fleet_organization_model::ptr& evil_menace, output_view* object_observer)
{
    fleet_organization_model::ptr spaceball_fleet = create<fleet_organization_model>(object_observer, L"Spaceball Fleet", spaceship_interface::ptr());
    evil_menace->add_child(spaceball_fleet);

    spaceship_model::ptr ship_spaceball_one = create<spaceship_model>(object_observer, L"Custom Transforming Battle Ship", L"Spaceball One");
    ship_spaceball_one->captain = L"Dark Helmet";
    ship_spaceball_one->crew_complement = 50645;
    ship_spaceball_one->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_spaceball_one->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Hyperdrive Multiplier", 1));
    ship_spaceball_one->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Turbolaser cannon", 200));
    ship_spaceball_one->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Ion cannon", 200));
    ship_spaceball_one->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Super tractor beam", 1));
    ship_spaceball_one->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Tractor beam", 50));
    ship_spaceball_one->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Spaceball X missile tube", 60));
    ship_spaceball_one->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Vaccu-suck atmospheric removal system", 1));
    fleet_organization_model::ptr spaceball_one = create<fleet_organization_model>(object_observer, L"Spaceball One", ship_spaceball_one);
    spaceball_fleet->add_child(spaceball_one);
}

void add_the_borg(const fleet_organization_model::ptr& evil_menace, output_view* object_observer)
{
    fleet_organization_model::ptr the_borg = create<fleet_organization_model>(object_observer, L"The Borg", spaceship_interface::ptr());
    evil_menace->add_child(the_borg);

    spaceship_model::ptr ship_tactical_cube_138 = create<spaceship_model>(object_observer, L"Class-4 tactical cube", L"Tactical Cube 138");
    ship_tactical_cube_138->captain = L"The Collective";
    ship_tactical_cube_138->crew_complement = 129000;
    ship_tactical_cube_138->equipment()->container_changed.connect(boost::bind(&output_view::on_container_changed, object_observer, _1, _2));
    ship_tactical_cube_138->equipment()->push_back(create<equipment_model>(object_observer, L"Propulsion", L"Transwarp drive", 1));
    ship_tactical_cube_138->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Torpedo", 10000));
    ship_tactical_cube_138->equipment()->push_back(create<equipment_model>(object_observer, L"Armament", L"Beam weapon", 100));
    ship_tactical_cube_138->equipment()->push_back(create<equipment_model>(object_observer, L"Defense", L"Hull armor", 1));
    ship_tactical_cube_138->equipment()->push_back(create<equipment_model>(object_observer, L"Defense", L"Shield", 1));
    ship_tactical_cube_138->equipment()->push_back(create<equipment_model>(object_observer, L"Defense", L"Multi-regenerative security field", 1));
    fleet_organization_model::ptr tactical_cube_138 = create<fleet_organization_model>(object_observer, L"Tactical Cube 138", ship_tactical_cube_138);
    the_borg->add_child(tactical_cube_138);
}

void add_good_guys(const fleet_repository_interface::ptr& fleet_repo, output_view* object_observer)
{
    fleet_organization_model::ptr good_guys = create<fleet_organization_model>(object_observer, L"Good Guys", spaceship_interface::ptr());
    fleet_repo->fleet_organization_model()->add_child(good_guys);
    add_colonial_fleet(good_guys, object_observer);
    add_rebel_alliance(good_guys, object_observer);
    add_starfleet(good_guys, object_observer);
}

void add_evil_menace(const fleet_repository_interface::ptr& fleet_repo, output_view* object_observer)
{
    fleet_organization_model::ptr evil_menace = create<fleet_organization_model>(object_observer, L"Evil Menaces", spaceship_interface::ptr());
    fleet_repo->fleet_organization_model()->add_child(evil_menace);
    add_galactic_empire(evil_menace, object_observer);
    add_spaceball_fleet(evil_menace, object_observer);
    add_the_borg(evil_menace, object_observer);
}

}

fleet_repository_populator::~fleet_repository_populator()
{
}

fleet_repository_populator::fleet_repository_populator()
    : u::noncopyable_nonmovable()
{
}

fleet_repository_populator::ptr fleet_repository_populator::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler() : this_type() {}
    };

    return boost::make_shared<make_shared_enabler>();
}

void fleet_repository_populator::populate(const fleet_repository_interface::ptr& fleet_repo, output_view* object_observer) const
{
    if(fleet_repo && object_observer != NULL)
    {
        fleet_organization_model::ptr fleet = boost::dynamic_pointer_cast<fleet_organization_model>(fleet_repo->fleet_organization_model());
        if(fleet)
        {
            fleet->property_changed.connect(boost::bind(&output_view::on_property_changed, object_observer, _1, _2));
            add_good_guys(fleet_repo, object_observer);
            add_evil_menace(fleet_repo, object_observer);
        }
    }
}
