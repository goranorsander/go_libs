//
//  scope_guard_new_example.cpp
//
//  Copyright 2018-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/utility.hpp>
#include <iostream>

class foo
{
public:
    ~foo()
    {
        std::cout << "Destroy foo" << std::endl;
    }

    foo()
    {
        std::cout << "Create foo" << std::endl;
    }
};

int main()
{
    const u::scope_guard_new<foo> guardg(new foo);
    return 0;
}
