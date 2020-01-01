//
//  stopwatch_example.cpp
//
//  Copyright 2019-2020 Göran Orsander
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
#include <go/diagnostics.hpp>
#include <go/namespace_alias.hpp>

uint64_t fibonacci_number(const uint64_t n)
{
    return ((n == 0) || (n == 1)) ? 1 : fibonacci_number(n - 1) + fibonacci_number(n - 2);
}

int main()
{
    db::stopwatch sw;
    uint64_t n = 0;
    while (n < 31)
    {
        uint64_t fn = 0;
        {
            db::stopwatch_guard g(sw);
            fn = fibonacci_number(n);
        }

        std::cout << "Fibonacci number " << n << " = " << fn << " (time = " << sw.last_duration().count() << " microseconds, total time = " << sw.total_duration().count() << " microseconds)" << std::endl;

        ++n;
    }

    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
