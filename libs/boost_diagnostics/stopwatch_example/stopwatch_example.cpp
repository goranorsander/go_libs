//
//  stopwatch_example.cpp
//
//  Copyright 2019-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <iostream>
#include <go_boost/config.hpp>
#include <go_boost/diagnostics.hpp>
#include <go_boost/namespace_alias.hpp>

boost::uint64_t fibonacci_number(const boost::uint64_t n)
{
    return ((n == 0) || (n == 1)) ? 1 : fibonacci_number(n - 1) + fibonacci_number(n - 2);
}

int main()
{
    db::stopwatch sw;
    boost::uint64_t n = 0;
    while (n < 31)
    {
        boost::uint64_t fn = 0;
        {
            db::stopwatch_guard g(sw);
            fn = fibonacci_number(n);
        }

        std::cout << "Fibonacci number " << n << " = " << fn << " (time = " << sw.last_duration().count() << " microseconds, total time = " << sw.total_duration().count() << " microseconds)" << std::endl;

        ++n;
    }

    return 0;
}
