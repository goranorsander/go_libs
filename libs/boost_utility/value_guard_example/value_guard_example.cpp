//
//  value_guard_example.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/utility/value_guard.hpp>
#include <iostream>

namespace u = go_boost::utility;

int main()
{
    std::string value("First scope");
    std::cout << value.c_str() << std::endl;
    {
        const u::value_guard<std::string> guard(value, std::string("Second scope"));
        std::cout << value.c_str() << std::endl;
    }
    std::cout << value.c_str() << std::endl;
    return 0;
}
