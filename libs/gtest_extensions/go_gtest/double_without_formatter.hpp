#ifndef GO_GTEST_DOUBLE_WITHOUT_FORMATTER_HPP_INCLUDED
#define GO_GTEST_DOUBLE_WITHOUT_FORMATTER_HPP_INCLUDED

//
//  double_without_formatter.hpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go_gtest/stdint.hpp>

namespace testing
{
namespace internal2
{

template <>
class TypeWithoutFormatter<double, kConvertibleToInteger>
{
public:
	static void PrintValue(const double& value, ::std::ostream* os)
	{
		const double vd = value;
		const int64_t vi = *(reinterpret_cast<const int64_t*>(&vd));
		const internal::BiggestInt kBigInt = static_cast<internal::BiggestInt>(vi);
		*os << kBigInt;
	}
};

}
}

#endif  // #ifndef GO_GTEST_DOUBLE_WITHOUT_FORMATTER_HPP_INCLUDED
