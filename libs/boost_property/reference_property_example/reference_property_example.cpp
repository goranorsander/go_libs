//
//  reference_property_example.cpp
//
//  Copyright 2017-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/property.hpp>
#include <iostream>

class spaceship
{
public:
    ~spaceship() {}

    spaceship()
        : crew_complement(std::string("crew_complement"))
        , max_speed(std::string("max_speed"))
        , name(std::string("name"))
    {
    }

    p::reference_property<int> crew_complement;
    p::reference_property<double> max_speed;
    p::reference_property<std::string> name;
};

int main()
{
    spaceship s;
    int store_crew_complement = 1012;
    double store_max_speed = 9.8;
    std::string store_name("USS Enterprise (NCC-1701-D)");
    s.crew_complement.bind(store_crew_complement);
    s.max_speed.bind(store_max_speed);
    s.name.bind(store_name);
    std::cout << "Name: " << s.name().c_str() << ", crew: " << s.crew_complement << ", speed: " << s.max_speed << std::endl;

    s.crew_complement = 430;
    s.max_speed = 9.0;
    s.name = "USS Enterprise (NCC-1701)";
    std::cout << "Name: " << s.name().c_str() << ", crew: " << s.crew_complement << ", speed: " << s.max_speed << std::endl;

    return 0;
}
