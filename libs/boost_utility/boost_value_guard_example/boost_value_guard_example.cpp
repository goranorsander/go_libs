//
//  boost_value_guard_example.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/utility.hpp>
#include <iostream>

namespace u = go_boost::utility;

int main()
{
    std::string value("First scope");
    std::cout << value << std::endl;
    {
        const u::value_guard<std::string> guard(value, std::string("Second scope"));
        std::cout << value << std::endl;
    }
    std::cout << value << std::endl;
    return 0;
}
