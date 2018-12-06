//
//  scope_guard_example.cpp
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

void delete_foo(foo* p)
{
    delete p;
}

int main()
{
    foo* f = new foo;
    const u::scope_guard guard(u::scope_guard::on_scope_exit_function_type(boost::bind(&delete_foo, f)));
    return 0;
}
