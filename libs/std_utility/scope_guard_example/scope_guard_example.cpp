//
//  scope_guard_example.cpp
//
//  Copyright 2018-2021 Göran Orsander
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
#include <go/utility.hpp>

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
    const u::scope_guard guard(u::scope_guard::on_scope_exit_function_type(std::bind(&delete_foo, f)));
    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
