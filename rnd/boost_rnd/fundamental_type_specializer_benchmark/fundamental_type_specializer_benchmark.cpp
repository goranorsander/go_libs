//
//  fundamental_type_specializer_benchmark.cpp
//
//  Copyright 2019-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#if defined(GO_BOOST_NO_CXX11) || defined(GO_BOOST_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_BOOST_MESSAGE("Required C++11 feature is not supported by this compiler")
int main() { return -1; }
#else

#include <iostream>
#include <go_boost/diagnostics/benchmark/stopwatch.hpp>
#include <go_boost/type_traits/fundamental_type_specializer.hpp>
#include <go_boost/namespace_alias.hpp>

GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(UnsignedLongLong, unsigned long long)
GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(Double, double)

template <typename SpecializedFundamentalType, typename FundamentalType = SpecializedFundamentalType>
SpecializedFundamentalType fibonacci_number(const SpecializedFundamentalType& n)
{
    static const SpecializedFundamentalType one(static_cast<FundamentalType>(1));
    static const SpecializedFundamentalType two(static_cast<FundamentalType>(2));
    return ((n <= one)) ? one : fibonacci_number(n - one) + fibonacci_number(n - two);
}

template <typename SpecializedFundamentalType, typename FundamentalType = SpecializedFundamentalType>
auto make_fibonacci()
{
    static const SpecializedFundamentalType one(static_cast<FundamentalType>(1));
    static const SpecializedFundamentalType two(static_cast<FundamentalType>(2));
    auto fib = [](const SpecializedFundamentalType& n, auto& self)
    {
        if (n <= one)
        {
            return one;
        }
        return self(n - one, self) + self(n - two, self);
    };
    return [fib](const SpecializedFundamentalType& n)
    {
        return fib(n, fib);
    };
};

template <typename SpecializedFundamentalType, typename FundamentalType = SpecializedFundamentalType>
void benchmark_add(const std::size_t iterations, db::stopwatch& sw)
{
    SpecializedFundamentalType c(static_cast<FundamentalType>(0));
    std::size_t i = 0;
    while (i < iterations)
    {
        const SpecializedFundamentalType a(static_cast<FundamentalType>(rand()));
        const SpecializedFundamentalType b(static_cast<FundamentalType>(rand()));
        {
            db::stopwatch_guard g(sw);
            c = a + b;
        }
        ++i;
    }
}

template <typename SpecializedFundamentalType, typename FundamentalType = SpecializedFundamentalType>
void benchmark_subtract(const std::size_t iterations, db::stopwatch& sw)
{
    SpecializedFundamentalType c(static_cast<FundamentalType>(0));
    std::size_t i = 0;
    while (i < iterations)
    {
        SpecializedFundamentalType a(static_cast<FundamentalType>(rand()));
        SpecializedFundamentalType b(static_cast<FundamentalType>(rand()));
        if (a < b)
        {
            std::swap(a, b);
        }
        {
            db::stopwatch_guard g(sw);
            c = a - b;
        }
        ++i;
    }
}

template <typename SpecializedFundamentalType, typename FundamentalType = SpecializedFundamentalType>
void benchmark_multiply(const std::size_t iterations, db::stopwatch& sw)
{
    SpecializedFundamentalType c(static_cast<FundamentalType>(0));
    std::size_t i = 0;
    while (i < iterations)
    {
        const SpecializedFundamentalType a(static_cast<FundamentalType>(rand()));
        const SpecializedFundamentalType b(static_cast<FundamentalType>(rand()));
        {
            db::stopwatch_guard g(sw);
            c = a * b;
        }
        ++i;
    }
}

template <typename SpecializedFundamentalType, typename FundamentalType = SpecializedFundamentalType>
void benchmark_divide(const std::size_t iterations, db::stopwatch& sw)
{
    SpecializedFundamentalType c(static_cast<FundamentalType>(0));
    std::size_t i = 0;
    while (i < iterations)
    {
        SpecializedFundamentalType a(static_cast<FundamentalType>(rand()));
        SpecializedFundamentalType b(static_cast<FundamentalType>(rand()));
        if (a < b)
        {
            std::swap(a, b);
        }
        {
            db::stopwatch_guard g(sw);
            c = a / b;
        }
        ++i;
    }
}

template <typename SpecializedFundamentalType, typename FundamentalType = SpecializedFundamentalType>
SpecializedFundamentalType benchmark_fibonacci_number(const SpecializedFundamentalType& n, db::stopwatch& sw)
{
    SpecializedFundamentalType fn(static_cast<FundamentalType>(0));
    {
        db::stopwatch_guard g(sw);
        fn = fibonacci_number<SpecializedFundamentalType, FundamentalType>(n);
    }
    return fn;
}

template <typename SpecializedFundamentalType, typename FundamentalType = SpecializedFundamentalType>
SpecializedFundamentalType benchmark_fibonacci_number_lambda(const SpecializedFundamentalType& n, db::stopwatch& sw)
{
    auto fibonacci = make_fibonacci<SpecializedFundamentalType, FundamentalType>();
    SpecializedFundamentalType fn(static_cast<FundamentalType>(0));
    {
        db::stopwatch_guard g(sw);
        fn = fibonacci(n);
    }
    return fn;
}

int main()
{
    const std::size_t iterations = 100000000ull;
    const unsigned long long fibonacci_n = 36ull;

    {
        std::cout << std::endl;
        std::cout << "Fundamental Type unsigned long long" << std::endl;
        {
            db::stopwatch sw;
            benchmark_add<unsigned long long>(iterations, sw);
            std::cout << "Add, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_subtract<unsigned long long>(iterations, sw);
            std::cout << "Subtract, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_multiply<unsigned long long>(iterations, sw);
            std::cout << "Multiply, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_divide<unsigned long long>(iterations, sw);
            std::cout << "Divide, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            const unsigned long long fn = benchmark_fibonacci_number(fibonacci_n, sw);
            std::cout << "Basic, Fibonacci number " << fibonacci_n << " = " << fn << " (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            const unsigned long long fn = benchmark_fibonacci_number_lambda(fibonacci_n, sw);
            std::cout << "Lambda, Fibonacci number " << fibonacci_n << " = " << fn << " (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
    }

    {
        std::cout << std::endl;
        std::cout << "Specialized Fundamental Type UnsignedLongLong" << std::endl;
        {
            db::stopwatch sw;
            benchmark_add<UnsignedLongLong>(iterations, sw);
            std::cout << "Add, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_subtract<UnsignedLongLong>(iterations, sw);
            std::cout << "Subtract, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_multiply<UnsignedLongLong>(iterations, sw);
            std::cout << "Multiply, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_divide<UnsignedLongLong>(iterations, sw);
            std::cout << "Divide, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            const UnsignedLongLong fn = benchmark_fibonacci_number<UnsignedLongLong, unsigned long long>(UnsignedLongLong(fibonacci_n), sw);
            std::cout << "Basic, Fibonacci number " << fibonacci_n << " = " << fn.get() << " (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            const UnsignedLongLong fn = benchmark_fibonacci_number_lambda<UnsignedLongLong, unsigned long long>(UnsignedLongLong(fibonacci_n), sw);
            std::cout << "Lambda, Fibonacci number " << fibonacci_n << " = " << fn.get() << " (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
    }

    {
        std::cout << std::endl;
        std::cout << "Fundamental Type double" << std::endl;
        {
            db::stopwatch sw;
            benchmark_add<double>(iterations, sw);
            std::cout << "Add, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_subtract<double>(iterations, sw);
            std::cout << "Subtract, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_multiply<double>(iterations, sw);
            std::cout << "Multiply, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_divide<double>(iterations, sw);
            std::cout << "Divide, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            const double fn = benchmark_fibonacci_number(static_cast<double>(fibonacci_n), sw);
            std::cout << "Basic, Fibonacci number " << fibonacci_n << " = " << fn << " (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            const double fn = benchmark_fibonacci_number_lambda(static_cast<double>(fibonacci_n), sw);
            std::cout << "Lambda, Fibonacci number " << fibonacci_n << " = " << fn << " (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
    }

    {
        std::cout << std::endl;
        std::cout << "Specialized Fundamental Type Double" << std::endl;
        {
            db::stopwatch sw;
            benchmark_add<Double>(iterations, sw);
            std::cout << "Add, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_subtract<Double>(iterations, sw);
            std::cout << "Subtract, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_multiply<Double>(iterations, sw);
            std::cout << "Multiply, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            benchmark_divide<Double>(iterations, sw);
            std::cout << "Divide, " << iterations << " iterations (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            const Double fn = benchmark_fibonacci_number<Double, unsigned long long>(Double(fibonacci_n), sw);
            std::cout << "Basic, Fibonacci number " << fibonacci_n << " = " << fn.get() << " (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
        {
            db::stopwatch sw;
            const Double fn = benchmark_fibonacci_number_lambda<Double, unsigned long long>(Double(fibonacci_n), sw);
            std::cout << "Lambda, Fibonacci number " << fibonacci_n << " = " << fn.get() << " (total time = " << sw.total_duration().count() << " microseconds)" << std::endl;
        }
    }

    std::cout << std::endl;

    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
