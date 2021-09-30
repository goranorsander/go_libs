//
//  lambda_binding.cpp
//
//  Copyright 2019-2021 Göran Orsander
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

namespace std { namespace placeholders {}}
namespace ph = std::placeholders;

GO_USING(test_function_signature, std::function<void(const std::string&)>);

void foo(const std::string& message = std::string("unexpected"))
{
    static unsigned int counter = 0;
    std::cout << (++counter) << ": void foo(const std::string&) executed, " << message.c_str() << std::endl;
}

void executor(std::function<void(const std::string&)> f)
{
    f(std::string("called after being passed as argument to executor function"));
}

class bar
{
public:
    ~bar() GO_DEFAULT_DESTRUCTOR

    bar()
        : _counter(0)
        , _foo()
    {
#if defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)
        _foo = [this](const std::string& message) mutable -> void { std::cout << (++_counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; };
#else
        _foo = [this](const std::string& message = std::string("unexpected")) mutable -> void { std::cout << (++_counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; };
#endif  // #if defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)
    }

    bar(const bar&) GO_DEFAULT_CONSTRUCTOR
#if defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)
    bar(bar&& other)
        : _counter(std::move(other._counter))
        , _foo(std::move(other._foo))
    {
    }
#else
    bar(bar&&) = default;
#endif  // #if defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

#if defined(GO_NO_CXX11_DEFAULTED_COPY_ASSIGN_OPERATOR)
    bar& operator=(const bar& other)
    {
        if (this != &other)
        {
            _counter = other._counter;
            _foo = other._foo;
        }
        return *this;
    }
#else
    bar& operator=(const bar&) = default;
#endif  // #if defined(GO_NO_CXX11_DEFAULTED_COPY_ASSIGN_OPERATOR)
#if defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)
    bar& operator=(bar&& other)
    {
        if (this != &other)
        {
            _counter = std::move(other._counter);
            _foo = std::move(other._foo);
        }
        return *this;
    }
#else
    bar& operator=(bar&&) = default;
#endif  // #if defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

public:
    void foo(const std::string& message)
    {
        _foo(message);
    }

private:
#if defined(GO_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS)
    unsigned int _counter;
#else
    unsigned int _counter = 0;
#endif // #if defined(GO_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS)
    test_function_signature _foo;
};

int main()
{
    std::cout << "--- std::bind ---" << std::endl << std::endl;
    {
        std::cout << "Before: test_function_signature f = std::bind(foo, ph::_1);" << std::endl;
        test_function_signature f = std::bind(foo, ph::_1);
        std::cout << "After: test_function_signature f = std::bind(foo, ph::_1);" << std::endl;
        std::cout << "Before: f(std::string(...));" << std::endl;
        f(std::string("called after binding to local variable"));
        std::cout << "After: f(std::string(...));" << std::endl << std::endl;

        std::cout << "Before: test_function_signature f2 = f;" << std::endl;
        test_function_signature f2 = f;
        std::cout << "After: test_function_signature f2 = f;" << std::endl;
        std::cout << "Before: f2(std::string(...));" << std::endl;
        f2(std::string("called after binding to local variable"));
        std::cout << "After: f2(std::string(...));" << std::endl << std::endl;
    }
    {
        std::cout << "Before: executor(std::bind(foo, ph::_1));" << std::endl;
        executor(std::bind(foo, ph::_1));
        std::cout << "After: executor(std::bind(foo, ph::_1));" << std::endl;
    }

    std::cout << std::endl << "--- lambda ---" << std::endl << std::endl;
    {
        unsigned int counter = 0;
        {
            std::cout << "Before: test_function_signature f = [counter](...) mutable -> void { ... };" << std::endl;
#if !defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)
            test_function_signature f = [counter](const std::string& message = std::string("unexpected")) mutable -> void { std::cout << (++counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; };
#else
            test_function_signature f = [counter](const std::string& message) mutable -> void { std::cout << (++counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; };
#endif  // #if !defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)
            std::cout << "After: test_function_signature f = [counter](...) mutable -> void { ... };" << std::endl;
            std::cout << "Before: f(std::string(...));" << std::endl;
            f(std::string("called after binding to local variable"));
            std::cout << "After: f(std::string(...));" << std::endl << std::endl;

            std::cout << "Before: test_function_signature f2 = f;" << std::endl;
            test_function_signature f2 = f;
            std::cout << "After: test_function_signature f2 = f;" << std::endl;
            std::cout << "Before: f2(std::string(...));" << std::endl;
            f2(std::string("called after binding to local variable"));
            std::cout << "After: f2(std::string(...));" << std::endl << std::endl;
        }
        {
            std::cout << "Before: executor([counter](...) mutable -> void { ... });" << std::endl;
#if !defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)
            executor([counter](const std::string& message = std::string("unexpected")) mutable -> void { std::cout << (++counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; });
#else
            executor([counter](const std::string& message) mutable -> void { std::cout << (++counter) << ": [](const std::string&) -> void executed, " << message.c_str() << std::endl; });
#endif  // #if !defined(GO_NO_CXX14_LAMBDA_DEFAULT_ARGUMENTS)
            std::cout << "After: executor([counter](...) mutable -> void { ... });" << std::endl << std::endl;
        }
        {
            std::cout << "Before: bar b;" << std::endl;
            bar b;
            std::cout << "After: bar b;" << std::endl;
            std::cout << "Before: b.foo(std::string(...));" << std::endl;
            b.foo(std::string("called after binding to local variable"));
            std::cout << "After: b.foo(std::string(...));" << std::endl << std::endl;

            std::cout << "Before: bar b2 = b;" << std::endl;
            bar b2 = b;
            std::cout << "After: bar b2 = b;" << std::endl;
            std::cout << "Before: b2.foo(std::string(...));" << std::endl;
            b2.foo(std::string("called after binding to local variable"));
            std::cout << "After: b2.foo(std::string(...));" << std::endl << std::endl;
        }
    }

    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
