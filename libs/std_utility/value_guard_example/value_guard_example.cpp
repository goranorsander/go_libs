//
//  value_guard_example.cpp
//
//  Copyright 2018-2019 Göran Orsander
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
#include <go/utility/value_guard.hpp>

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

#endif  // Required C++11 feature is not supported by this compiler
