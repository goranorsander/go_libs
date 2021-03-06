//
//  lambda_binding.cpp
//
//  Copyright 2019-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_LAMBDA_EXPRESSIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
int main() { return -1; }
#else

#include <functional>
#include <iostream>
#include <go/namespace_alias.hpp>

unsigned int counter = 0;

void foo(const std::string& message = std::string("unexpected"))
{
    std::cout << (++counter) << ": void foo(const std::string&) executed, " << message.c_str() << std::endl;
}

void executor(std::function<void(const std::string&)> f)
{
    f(std::string("called after being passed as argument to executor function"));
}

int main()
{
    {
        auto f = std::bind(foo, ph::_1);
        f(std::string("called after binding to local variable"));
    }

    {
        executor(std::bind(foo, ph::_1));
    }

    {
#if !defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)
        auto f = [](const std::string& message = std::string("unexpected")) -> void { std::cout << (++counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; };
#else
        auto f = [](const std::string& message) -> void { std::cout << (++counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; };
#endif  // #if !defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)

        f(std::string("called after binding to local variable"));
    }

    {
#if !defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)
        executor([](const std::string& message = std::string("unexpected")) -> void { std::cout << (++counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; });
#else
        executor([](const std::string& message) -> void { std::cout << (++counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; });
#endif  // #if !defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)
    }

    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
