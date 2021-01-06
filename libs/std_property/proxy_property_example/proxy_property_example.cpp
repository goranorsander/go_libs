//
//  proxy_property_example.cpp
//
//  Copyright 2017-2021 Göran Orsander
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
#include <go/namespace_alias.hpp>
#include <go/property.hpp>

class spaceship
{
public:
    ~spaceship() GO_DEFAULT_DESTRUCTOR

    spaceship()
        : crew_complement(std::string("crew_complement"))
        , max_speed(std::string("max_speed"))
        , name(std::string("name"))
        , _crew_complement(1012)
        , _max_speed(9.8)
        , _name("USS Enterprise (NCC-1701-D)")
    {
        crew_complement.getter([this]() -> int { return _crew_complement; });
        crew_complement.setter([this](const int& v) { if (v != _crew_complement) { _crew_complement = v; } });
        max_speed.getter([this]() -> double { return _max_speed; });
        max_speed.setter([this](const double& v) { if (v != _max_speed) { _max_speed = v; } });
        name.getter([this]() -> std::string { return _name; });
        name.setter([this](const std::string& v) { if (v != _name) { _name = v; } });
    }

    p::property<int> crew_complement;
    p::property<double> max_speed;
    p::property<std::string> name;

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

#endif  // Required C++11 feature is not supported by this compiler
