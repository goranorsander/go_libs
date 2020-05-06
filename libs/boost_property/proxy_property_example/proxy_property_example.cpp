//
//  proxy_property_example.cpp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/property.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>

class spaceship
{
public:
    ~spaceship() {}

    spaceship()
        : crew_complement(std::string("crew_complement"))
        , max_speed(std::string("max_speed"))
        , name(std::string("name"))
        , _crew_complement(1012)
        , _max_speed(9.8)
        , _name("USS Enterprise (NCC-1701-D)")
    {
        crew_complement.getter(boost::bind(&spaceship::get_crew_complement, this));
        crew_complement.setter(boost::bind(&spaceship::set_crew_complement, this, boost::placeholders::_1));
        max_speed.getter(boost::bind(&spaceship::get_max_speed, this));
        max_speed.setter(boost::bind(&spaceship::set_max_speed, this, boost::placeholders::_1));
        name.getter(boost::bind(&spaceship::get_name, this));
        name.setter(boost::bind(&spaceship::set_name, this, boost::placeholders::_1));
    }

    p::property<int> crew_complement;
    p::property<double> max_speed;
    p::property<std::string> name;

private:
    int get_crew_complement() const { return _crew_complement; }

    void set_crew_complement(const int& v) { if (v != _crew_complement) { _crew_complement = v; } }

    double get_max_speed() const { return _max_speed; }

    void set_max_speed(const double& v) { if (v != _max_speed) { _max_speed = v; } }

    std::string get_name() const { return _name; }

    void set_name(const std::string& v) { if (v != _name) { _name = v; } }

private:
    int _crew_complement;
    double _max_speed;
    std::string _name;
};

int main()
{
    spaceship s;
    std::cout << "Name: " << s.name().c_str() << ", crew: " << s.crew_complement << ", speed: " << s.max_speed << std::endl;

    s.crew_complement = 430;
    s.max_speed = 9.0;
    s.name = "USS Enterprise (NCC-1701)";
    std::cout << "Name: " << s.name().c_str() << ", crew: " << s.crew_complement << ", speed: " << s.max_speed << std::endl;

    return 0;
}
