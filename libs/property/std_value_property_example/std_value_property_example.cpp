//
//  std_value_property_example.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
int main() { return -1; }
#else

#include <iostream>
#include <go/property.hpp>

namespace p = go::property;

class spaceship
{
public:
    ~spaceship() = default;

    spaceship()
        : crew_complement(std::string("crew_complement"), 1012)
        , max_speed(std::string("max_speed"), 9.8)
        , name(std::string("name"), std::string("USS Enterprise (NCC-1701-D)"))
    {
    }

    p::value_property<int> crew_complement;
    p::value_property<double> max_speed;
    p::value_property<std::string> name;
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

#endif  // Required C++11 feature is not supported by this compiler
