//
//  primitive_type_specializer_test_suite.cpp
//
//  Copyright 2018-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/utility/primitive_type_implicit_specializer.hpp>
#include <go_boost/utility/primitive_type_specializer.hpp>

namespace u = go_boost::utility;

namespace
{

#if !defined(GO_BOOST_NO_CXX11_PRIMITIVE_TYPE_SPECIALIZER)

GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER(integer_type, int)
GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER(another_integer_type, int)

GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER(floating_point_type, double)
GO_BOOST_IMPLEMENT_PRIMITIVE_TYPE_SPECIALIZER(another_floating_point_type, double)

#else

GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER(integer_type, int)
GO_BOOST_IMPLEMENT_INTEGER_TYPE_SPECIALIZER(another_integer_type, int)

GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(floating_point_type, double)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(another_floating_point_type, double)

#endif  // #if !defined(GO_BOOST_NO_CXX11_PRIMITIVE_TYPE_SPECIALIZER)

# if !defined(GO_BOOST_NO_CXX11_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER)

GO_BOOST_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(implicit_integer_type, int)
GO_BOOST_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(another_implicit_integer_type, int)

GO_BOOST_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(implicit_floating_point_type, double)
GO_BOOST_IMPLEMENT_IMPLICIT_PRIMITIVE_TYPE_SPECIALIZER(another_implicit_floating_point_type, double)

#else

GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER(implicit_integer_type, int)
GO_BOOST_IMPLEMENT_INTEGER_TYPE_IMPLICIT_SPECIALIZER(another_implicit_integer_type, int)

GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(implicit_floating_point_type, double)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(another_implicit_floating_point_type, double)

#endif  // # if !defined(GO_BOOST_NO_CXX11_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER)

}

namespace testing
{
namespace internal2
{

template <>
class TypeWithoutFormatter<implicit_floating_point_type, kConvertibleToInteger>
{
public:
	static void PrintValue(const implicit_floating_point_type& value, ::std::ostream* os)
	{
		const double vd = value.get();
		const int64_t vi = *(reinterpret_cast<const int64_t*>(&vd));
		const internal::BiggestInt kBigInt = static_cast<internal::BiggestInt>(vi);
		*os << kBigInt;
	}
};

template <>
class TypeWithoutFormatter<another_implicit_floating_point_type, kConvertibleToInteger>
{
public:
	static void PrintValue(const another_implicit_floating_point_type& value, ::std::ostream* os)
	{
		const double vd = value.get();
		const int64_t vi = *(reinterpret_cast<const int64_t*>(&vd));
		const internal::BiggestInt kBigInt = static_cast<internal::BiggestInt>(vi);
		*os << kBigInt;
	}
};

}
}

namespace
{

TEST(boost_primitive_type_specializer_test_suite, test_explicit_integer_type_specializer)
{
    integer_type v1;
    EXPECT_EQ(0, v1.get());
    v1.set(42);
    EXPECT_EQ(42, v1.get());
    another_integer_type v2;
    EXPECT_EQ(0, v2.get());
    v1.set(v2.get());
    EXPECT_EQ(0, v1.get());
    EXPECT_EQ(0, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_default_value)
{
    const integer_type v;
    EXPECT_EQ(0, v.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_construction)
{
    {
        const integer_type v(0);
        EXPECT_EQ(0, v.get());
    }
    {
        const integer_type v1(1);
        EXPECT_EQ(1, v1.get());
        const integer_type v2(v1);
        EXPECT_EQ(1, v1.get());
        EXPECT_EQ(1, v2.get());
        EXPECT_EQ(v1, v2);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_get_set)
{
    integer_type v1;
    EXPECT_EQ(0, v1.get());
    v1.set(42);
    EXPECT_EQ(42, v1.get());
    integer_type v2(47);
    EXPECT_EQ(47, v2.get());
    v1.set(v2);
    EXPECT_EQ(47, v1.get());
    EXPECT_EQ(47, v2.get());
    v1.set(74);
    EXPECT_EQ(74, v1.get());
    EXPECT_EQ(47, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_simple_assignment_operator)
{
    const integer_type v1(100);
    EXPECT_EQ(100, v1.get());
    integer_type v2;
    EXPECT_EQ(0, v2.get());
    v2.set(42);
    EXPECT_EQ(42, v2.get());
    v2 = v1;
    EXPECT_EQ(100, v1.get());
    EXPECT_EQ(100, v2.get());
    EXPECT_EQ(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_addition_assignment_operator)
{
    const integer_type v1(100);
    EXPECT_EQ(100, v1.get());
    integer_type v2;
    EXPECT_EQ(0, v2.get());
    v2.set(42);
    EXPECT_EQ(42, v2.get());
    v2 += v1;
    EXPECT_EQ(100, v1.get());
    EXPECT_EQ(142, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_subtraction_assignment_operator)
{
    const integer_type v1(10);
    EXPECT_EQ(10, v1.get());
    integer_type v2;
    EXPECT_EQ(0, v2.get());
    v2.set(42);
    EXPECT_EQ(42, v2.get());
    v2 -= v1;
    EXPECT_EQ(10, v1.get());
    EXPECT_EQ(32, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_multiplication_assignment_operator)
{
    const integer_type v1(10);
    EXPECT_EQ(10, v1.get());
    integer_type v2;
    EXPECT_EQ(0, v2.get());
    v2.set(42);
    EXPECT_EQ(42, v2.get());
    v2 *= v1;
    EXPECT_EQ(10, v1.get());
    EXPECT_EQ(420, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_division_assignment_operator)
{
    const integer_type v1(7);
    EXPECT_EQ(7, v1.get());
    integer_type v2;
    EXPECT_EQ(0, v2.get());
    v2.set(42);
    EXPECT_EQ(42, v2.get());
    v2 /= v1;
    EXPECT_EQ(7, v1.get());
    EXPECT_EQ(6, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_modulo_assignment_operator)
{
    const integer_type v1(10);
    EXPECT_EQ(10, v1.get());
    integer_type v2;
    EXPECT_EQ(0, v2.get());
    v2.set(42);
    EXPECT_EQ(42, v2.get());
    v2 %= v1;
    EXPECT_EQ(10, v1.get());
    EXPECT_EQ(2, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_and_assignment_operator)
{
    const integer_type v1(74); // == 0x4A == 01001010
    EXPECT_EQ(74, v1.get());
    integer_type v2;           // == 0x2A == 00101010
    EXPECT_EQ(0, v2.get());
    v2.set(42);
    EXPECT_EQ(42, v2.get());
    v2 &= v1;                  // == 0x0A == 00001010
    EXPECT_EQ(74, v1.get());
    EXPECT_EQ(10, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_or_assignment_operator)
{
    const integer_type v1(74); // == 0x4A == 01001010
    EXPECT_EQ(74, v1.get());
    integer_type v2;           // == 0x2A == 00101010
    EXPECT_EQ(0, v2.get());
    v2.set(42);
    EXPECT_EQ(42, v2.get());
    v2 |= v1;                  // == 0x6A == 01101010
    EXPECT_EQ(74, v1.get());
    EXPECT_EQ(106, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_xor_assignment_operator)
{
    const integer_type v1(74); // == 0x4A == 01001010
    EXPECT_EQ(74, v1.get());
    integer_type v2;           // == 0x2A == 00101010
    EXPECT_EQ(0, v2.get());
    v2.set(42);
    EXPECT_EQ(42, v2.get());
    v2 ^= v1;                  // == 0x60 == 01100000
    EXPECT_EQ(74, v1.get());
    EXPECT_EQ(96, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_left_shift_assignment_operator)
{
    const integer_type v1(2);  // == 0x02 == 00000010
    EXPECT_EQ(2, v1.get());
    integer_type v2(27);       // == 0x1B == 00011011
    EXPECT_EQ(27, v2.get());
    v2 <<= v1;                 // == 0x6C == 01101100
    EXPECT_EQ(2, v1.get());
    EXPECT_EQ(108, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_right_shift_assignment_operator)
{
    const integer_type v1(2);  // == 0x02 == 00000010
    EXPECT_EQ(2, v1.get());
    integer_type v2(216);      // == 0xD8 == 11011000
    EXPECT_EQ(216, v2.get());
    v2 >>= v1;                 // == 0x36 == 00110110
    EXPECT_EQ(2, v1.get());
    EXPECT_EQ(54, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_unary_plus_arithmetic_operator)
{
    {
        const integer_type v1(42);
        EXPECT_EQ(42, v1.get());
        const integer_type v2 = +v1;
        EXPECT_EQ(42, v1.get());
        EXPECT_EQ(42, v2.get());
    }
    {
        const integer_type v1(-47);
        EXPECT_EQ(-47, v1.get());
        const integer_type v2 = +v1;
        EXPECT_EQ(-47, v1.get());
        EXPECT_EQ(-47, v2.get());
    }
}

#if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_unary_minus_arithmetic_operator)
{
    {
        const integer_type v1(42);
        EXPECT_EQ(42, v1.get());
        const integer_type v2 = -v1;
        EXPECT_EQ(42, v1.get());
        EXPECT_EQ(-42, v2.get());
    }
    {
        const integer_type v1(-47);
        EXPECT_EQ(-47, v1.get());
        const integer_type v2 = -v1;
        EXPECT_EQ(-47, v1.get());
        EXPECT_EQ(47, v2.get());
    }
}

#endif  // #if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_addition_arithmetic_operator)
{
    const integer_type v1(100);
    EXPECT_EQ(100, v1.get());
    const integer_type v2(42);
    EXPECT_EQ(42, v2.get());
    const integer_type v3 = v1 + v2;
    EXPECT_EQ(100, v1.get());
    EXPECT_EQ(42, v2.get());
    EXPECT_EQ(142, v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_subtraction_arithmetic_operator)
{
    const integer_type v1(100);
    EXPECT_EQ(100, v1.get());
    const integer_type v2(42);
    EXPECT_EQ(42, v2.get());
    const integer_type v3 = v1 - v2;
    EXPECT_EQ(100, v1.get());
    EXPECT_EQ(42, v2.get());
    EXPECT_EQ(58, v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_multiplication_arithmetic_operator)
{
    const integer_type v1(10);
    EXPECT_EQ(10, v1.get());
    const integer_type v2(42);
    EXPECT_EQ(42, v2.get());
    const integer_type v3 = v1 * v2;
    EXPECT_EQ(10, v1.get());
    EXPECT_EQ(42, v2.get());
    EXPECT_EQ(420, v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_division_arithmetic_operator)
{
    const integer_type v1(5);
    EXPECT_EQ(5, v1.get());
    const integer_type v2(10500);
    EXPECT_EQ(10500, v2.get());
    const integer_type v3 = v2 / v1;
    EXPECT_EQ(5, v1.get());
    EXPECT_EQ(10500, v2.get());
    EXPECT_EQ(2100, v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_modulo_arithmetic_operator)
{
    const integer_type v1(8472);
    EXPECT_EQ(8472, v1.get());
    const integer_type v2(42);
    EXPECT_EQ(42, v2.get());
    const integer_type v3 = v1 % v2;
    EXPECT_EQ(8472, v1.get());
    EXPECT_EQ(42, v2.get());
    EXPECT_EQ(30, v3.get());
}

#if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_not_arithmetic_operator)
{
    const integer_type v1(0xA0B3E7F9); //        10100000 10110011 11100111 11111001
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1.get());
    const integer_type v2 = ~v1; // 0x5F4C1806 = 01011111 01001100 00011000 00000110
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1.get());
    EXPECT_EQ(static_cast<int>(0x5F4C1806), v2.get());
}

#endif  // #if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_and_arithmetic_operator)
{
    const integer_type v1(0xA0B3E7F9); // 10100000 10110011 11100111 11111001
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1.get());
    const integer_type v2(0xB3A0F9E7); // 10110011 10100000 11111001 11100111
    EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2.get());
    const integer_type v3 = v1 & v2;   // 10100000 10100000 11100001 11100001 = 0xA0A0E1E1
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1.get());
    EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2.get());
    EXPECT_EQ(static_cast<int>(0xA0A0E1E1), v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_or_arithmetic_operator)
{
    const integer_type v1(0xA0B3E7F9); // 10100000 10110011 11100111 11111001
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1.get());
    const integer_type v2(0xB3A0F9E7); // 10110011 10100000 11111001 11100111
    EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2.get());
    const integer_type v3 = v1 | v2;   // 10110011 10110011 11111111 11111111 = 0xB3B3FFFF
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1.get());
    EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2.get());
    EXPECT_EQ(static_cast<int>(0xB3B3FFFF), v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_xor_arithmetic_operator)
{
    const integer_type v1(0xA0B3E7F9); // 10100000 10110011 11100111 11111001
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1.get());
    const integer_type v2(0xB3A0F9E7); // 10110011 10100000 11111001 11100111
    EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2.get());
    const integer_type v3 = v1 ^ v2;   // 00010011 00010011 00011110 00011110 = 0x13131E1E
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1.get());
    EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2.get());
    EXPECT_EQ(static_cast<int>(0x13131E1E), v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_left_shift_arithmetic_operator)
{
    const integer_type v1(0x0AB3E7F9); // 00001010 10110011 11100111 11111001
    EXPECT_EQ(static_cast<int>(0x0AB3E7F9), v1.get());
    const integer_type v2(3);
    EXPECT_EQ(3, v2.get());
    const integer_type v3 = v1 << v2;  // 01010101 10011111 00111111 11001000 = 0x559F3FC8
    EXPECT_EQ(static_cast<int>(0x0AB3E7F9), v1.get());
    EXPECT_EQ(3, v2.get());
    EXPECT_EQ(static_cast<int>(0x559F3FC8), v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_bitwise_right_shift_arithmetic_operator)
{
    const integer_type v1(0x0AB3E7F0); // 00001010 10110011 11100111 11111000
    EXPECT_EQ(static_cast<int>(0x0AB3E7F0), v1.get());
    const integer_type v2(3);
    EXPECT_EQ(3, v2.get());
    const integer_type v3 = v1 >> v2;  // 00000001 01010110 01111100 11111110 = 0x01567CFE
    EXPECT_EQ(static_cast<int>(0x0AB3E7F0), v1.get());
    EXPECT_EQ(3, v2.get());
    EXPECT_EQ(static_cast<int>(0x01567CFE), v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_equal_to_comparison_operator)
{
    const integer_type v1(1);
    const integer_type v2(2);
    const integer_type v3(3);
    EXPECT_EQ(1, v1.get());
    EXPECT_EQ(2, v2.get());
    EXPECT_EQ(3, v3.get());
    const bool comparison_result_1 = (v1 == v2);
    const bool comparison_result_2 = (v2 == v2);
    const bool comparison_result_3 = (v3 == v2);
    EXPECT_EQ(false, comparison_result_1);
    EXPECT_EQ(true, comparison_result_2);
    EXPECT_EQ(false, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_not_equal_to_comparison_operator)
{
    const integer_type v1(1);
    const integer_type v2(2);
    const integer_type v3(3);
    EXPECT_EQ(1, v1.get());
    EXPECT_EQ(2, v2.get());
    EXPECT_EQ(3, v3.get());
    const bool comparison_result_1 = (v1 != v2);
    const bool comparison_result_2 = (v2 != v2);
    const bool comparison_result_3 = (v3 != v2);
    EXPECT_EQ(true, comparison_result_1);
    EXPECT_EQ(false, comparison_result_2);
    EXPECT_EQ(true, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_less_than_comparison_operator)
{
    const integer_type v1(1);
    const integer_type v2(2);
    const integer_type v3(3);
    EXPECT_EQ(1, v1.get());
    EXPECT_EQ(2, v2.get());
    EXPECT_EQ(3, v3.get());
    const bool comparison_result_1 = (v1 < v2);
    const bool comparison_result_2 = (v2 < v2);
    const bool comparison_result_3 = (v3 < v2);
    EXPECT_EQ(true, comparison_result_1);
    EXPECT_EQ(false, comparison_result_2);
    EXPECT_EQ(false, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_greater_than_comparison_operator)
{
    const integer_type v1(1);
    const integer_type v2(2);
    const integer_type v3(3);
    EXPECT_EQ(1, v1.get());
    EXPECT_EQ(2, v2.get());
    EXPECT_EQ(3, v3.get());
    const bool comparison_result_1 = (v1 > v2);
    const bool comparison_result_2 = (v2 > v2);
    const bool comparison_result_3 = (v3 > v2);
    EXPECT_EQ(false, comparison_result_1);
    EXPECT_EQ(false, comparison_result_2);
    EXPECT_EQ(true, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_less_than_or_equal_to_comparison_operator)
{
    const integer_type v1(1);
    const integer_type v2(2);
    const integer_type v3(3);
    EXPECT_EQ(1, v1.get());
    EXPECT_EQ(2, v2.get());
    EXPECT_EQ(3, v3.get());
    const bool comparison_result_1 = (v1 <= v2);
    const bool comparison_result_2 = (v2 <= v2);
    const bool comparison_result_3 = (v3 <= v2);
    EXPECT_EQ(true, comparison_result_1);
    EXPECT_EQ(true, comparison_result_2);
    EXPECT_EQ(false, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_greater_than_or_equal_to_comparison_operator)
{
    const integer_type v1(1);
    const integer_type v2(2);
    const integer_type v3(3);
    EXPECT_EQ(1, v1.get());
    EXPECT_EQ(2, v2.get());
    EXPECT_EQ(3, v3.get());
    const bool comparison_result_1 = (v1 >= v2);
    const bool comparison_result_2 = (v2 >= v2);
    const bool comparison_result_3 = (v3 >= v2);
    EXPECT_EQ(false, comparison_result_1);
    EXPECT_EQ(true, comparison_result_2);
    EXPECT_EQ(true, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_pre_increment_operator)
{
    integer_type v1(10);
    EXPECT_EQ(10, v1.get());
    const integer_type v2(++v1);
    EXPECT_EQ(11, v1.get());
    EXPECT_EQ(11, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_post_increment_operator)
{
    integer_type v1(10);
    EXPECT_EQ(10, v1.get());
    const integer_type v2(v1++);
    EXPECT_EQ(11, v1.get());
    EXPECT_EQ(10, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_pre_decrement_operator)
{
    integer_type v1(10);
    EXPECT_EQ(10, v1.get());
    const integer_type v2(--v1);
    EXPECT_EQ(9, v1.get());
    EXPECT_EQ(9, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_integer_type_specializer_post_decrement_operator)
{
    integer_type v1(10);
    EXPECT_EQ(10, v1.get());
    const integer_type v2(v1--);
    EXPECT_EQ(9, v1.get());
    EXPECT_EQ(10, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_default_value)
{
    const floating_point_type v;
    EXPECT_EQ(0.0, v.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_construction)
{
    {
        const floating_point_type v(0.0);
        EXPECT_EQ(0.0, v.get());
    }
    {
        const floating_point_type v1(1.0);
        EXPECT_EQ(1.0, v1.get());
        const floating_point_type v2(v1);
        EXPECT_EQ(1.0, v1.get());
        EXPECT_EQ(1.0, v2.get());
        EXPECT_EQ(v1, v2);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_get_set)
{
    floating_point_type v1(47.0);
    EXPECT_EQ(47.0, v1.get());
    floating_point_type v2(42.0);
    EXPECT_EQ(42.0, v2.get());
    v1.set(v2);
    EXPECT_EQ(42.0, v1.get());
    EXPECT_EQ(42.0, v2.get());
    v1.set(74.0);
    EXPECT_EQ(74.0, v1.get());
    EXPECT_EQ(42.0, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_simple_assignment_operator)
{
    const floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1.get());
    floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2.get());
    v2 = v1;
    EXPECT_EQ(100.0, v1.get());
    EXPECT_EQ(100.0, v2.get());
    EXPECT_EQ(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_addition_assignment_operator)
{
    const floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1.get());
    floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2.get());
    v2 += v1;
    EXPECT_EQ(100.0, v1.get());
    EXPECT_EQ(147.0, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_subtraction_assignment_operator)
{
    const floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1.get());
    floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2.get());
    v2 -= v1;
    EXPECT_EQ(100.0, v1.get());
    EXPECT_EQ(-53.0, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_multiplication_assignment_operator)
{
    const floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1.get());
    floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2.get());
    v2 *= v1;
    EXPECT_EQ(10.0, v1.get());
    EXPECT_EQ(470.0, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_division_assignment_operator)
{
    const floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1.get());
    floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2.get());
    v2 /= v1;
    EXPECT_EQ(10.0, v1.get());
    EXPECT_EQ(4.7, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_modulo_assignment_operator)
{
    const floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1.get());
    floating_point_type v2(42.0);
    EXPECT_EQ(42.0, v2.get());
    v2 %= v1;
    EXPECT_EQ(10.0, v1.get());
    EXPECT_EQ(2.0, v2.get());
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_unary_plus_arithmetic_operator)
{
    {
        const floating_point_type v1(47.0);
        EXPECT_EQ(47.0, v1.get());
        const floating_point_type v2 = +v1;
        EXPECT_EQ(47.0, v1.get());
        EXPECT_EQ(47.0, v2.get());
    }
    {
        const floating_point_type v1(-74.0);
        EXPECT_EQ(-74.0, v1.get());
        const floating_point_type v2 = +v1;
        EXPECT_EQ(-74.0, v1.get());
        EXPECT_EQ(-74.0, v2.get());
    }
}

#if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_unary_minus_arithmetic_operator)
{
    {
        const floating_point_type v1(47.0);
        EXPECT_EQ(47.0, v1.get());
        const floating_point_type v2 = -v1;
        EXPECT_EQ(47.0, v1.get());
        EXPECT_EQ(-47.0, v2.get());
    }
    {
        const floating_point_type v1(-74.0);
        EXPECT_EQ(-74.0, v1.get());
        const floating_point_type v2 = -v1;
        EXPECT_EQ(-74.0, v1.get());
        EXPECT_EQ(74.0, v2.get());
    }
}

#endif  // #if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_addition_arithmetic_operator)
{
    const floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1.get());
    const floating_point_type v2(42.0);
    EXPECT_EQ(42.0, v2.get());
    const floating_point_type v3 = v1 + v2;
    EXPECT_EQ(100.0, v1.get());
    EXPECT_EQ(42.0, v2.get());
    EXPECT_EQ(142.0, v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_subtraction_arithmetic_operator)
{
    const floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1.get());
    const floating_point_type v2(42.0);
    EXPECT_EQ(42.0, v2.get());
    const floating_point_type v3 = v1 - v2;
    EXPECT_EQ(100.0, v1.get());
    EXPECT_EQ(42.0, v2.get());
    EXPECT_EQ(58.0, v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_multiplication_arithmetic_operator)
{
    const floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1.get());
    const floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2.get());
    const floating_point_type v3 = v1 * v2;
    EXPECT_EQ(10.0, v1.get());
    EXPECT_EQ(47.0, v2.get());
    EXPECT_EQ(470.0, v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_division_arithmetic_operator)
{
    const floating_point_type v1(5.0);
    EXPECT_EQ(5.0, v1.get());
    const floating_point_type v2(10500.0);
    EXPECT_EQ(10500.0, v2.get());
    const floating_point_type v3 = v2 / v1;
    EXPECT_EQ(5.0, v1.get());
    EXPECT_EQ(10500.0, v2.get());
    EXPECT_EQ(2100.0, v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_modulo_arithmetic_operator)
{
    const floating_point_type v1(8472.0);
    EXPECT_EQ(8472.0, v1.get());
    const floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2.get());
    const floating_point_type v3 = v1 % v2;
    EXPECT_EQ(8472.0, v1.get());
    EXPECT_EQ(47.0, v2.get());
    EXPECT_EQ(12.0, v3.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_equal_to_comparison_operator)
{
    const floating_point_type v1(1.0);
    const floating_point_type v2(2.0);
    const floating_point_type v3(3.0);
    EXPECT_EQ(1.0, v1.get());
    EXPECT_EQ(2.0, v2.get());
    EXPECT_EQ(3.0, v3.get());
    const bool comparison_result_1 = (v1 == v2);
    const bool comparison_result_2 = (v2 == v2);
    const bool comparison_result_3 = (v3 == v2);
    EXPECT_EQ(false, comparison_result_1);
    EXPECT_EQ(true, comparison_result_2);
    EXPECT_EQ(false, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_not_equal_to_comparison_operator)
{
    const floating_point_type v1(1.0);
    const floating_point_type v2(2.0);
    const floating_point_type v3(3.0);
    EXPECT_EQ(1.0, v1.get());
    EXPECT_EQ(2.0, v2.get());
    EXPECT_EQ(3.0, v3.get());
    const bool comparison_result_1 = (v1 != v2);
    const bool comparison_result_2 = (v2 != v2);
    const bool comparison_result_3 = (v3 != v2);
    EXPECT_EQ(true, comparison_result_1);
    EXPECT_EQ(false, comparison_result_2);
    EXPECT_EQ(true, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_less_than_to_comparison_operator)
{
    const floating_point_type v1(1.0);
    const floating_point_type v2(2.0);
    const floating_point_type v3(3.0);
    EXPECT_EQ(1.0, v1.get());
    EXPECT_EQ(2.0, v2.get());
    EXPECT_EQ(3.0, v3.get());
    const bool comparison_result_1 = (v1 < v2);
    const bool comparison_result_2 = (v2 < v2);
    const bool comparison_result_3 = (v3 < v2);
    EXPECT_EQ(true, comparison_result_1);
    EXPECT_EQ(false, comparison_result_2);
    EXPECT_EQ(false, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_greater_than_comparison_operator)
{
    const floating_point_type v1(1.0);
    const floating_point_type v2(2.0);
    const floating_point_type v3(3.0);
    EXPECT_EQ(1.0, v1.get());
    EXPECT_EQ(2.0, v2.get());
    EXPECT_EQ(3.0, v3.get());
    const bool comparison_result_1 = (v1 > v2);
    const bool comparison_result_2 = (v2 > v2);
    const bool comparison_result_3 = (v3 > v2);
    EXPECT_EQ(false, comparison_result_1);
    EXPECT_EQ(false, comparison_result_2);
    EXPECT_EQ(true, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_less_than_or_equal_to_to_comparison_operator)
{
    const floating_point_type v1(1.0);
    const floating_point_type v2(2.0);
    const floating_point_type v3(3.0);
    EXPECT_EQ(1.0, v1.get());
    EXPECT_EQ(2.0, v2.get());
    EXPECT_EQ(3.0, v3.get());
    const bool comparison_result_1 = (v1 <= v2);
    const bool comparison_result_2 = (v2 <= v2);
    const bool comparison_result_3 = (v3 <= v2);
    EXPECT_EQ(true, comparison_result_1);
    EXPECT_EQ(true, comparison_result_2);
    EXPECT_EQ(false, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_greater_than_or_equal_to_comparison_operator)
{
    const floating_point_type v1(1.0);
    const floating_point_type v2(2.0);
    const floating_point_type v3(3.0);
    EXPECT_EQ(1.0, v1.get());
    EXPECT_EQ(2.0, v2.get());
    EXPECT_EQ(3.0, v3.get());
    const bool comparison_result_1 = (v1 >= v2);
    const bool comparison_result_2 = (v2 >= v2);
    const bool comparison_result_3 = (v3 >= v2);
    EXPECT_EQ(false, comparison_result_1);
    EXPECT_EQ(true, comparison_result_2);
    EXPECT_EQ(true, comparison_result_3);
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_pre_increment_operator)
{
    floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1.get());
    const floating_point_type v2(++v1);
    EXPECT_EQ(11.0, v1.get());
    EXPECT_EQ(11.0, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_post_increment_operator)
{
    floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1.get());
    const floating_point_type v2(v1++);
    EXPECT_EQ(11.0, v1.get());
    EXPECT_EQ(10.0, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_pre_decrement_operator)
{
    floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1.get());
    const floating_point_type v2(--v1);
    EXPECT_EQ(9.0, v1.get());
    EXPECT_EQ(9.0, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_floating_point_type_specializer_post_decrement_operator)
{
    floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1.get());
    const floating_point_type v2(v1--);
    EXPECT_EQ(9.0, v1.get());
    EXPECT_EQ(10.0, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer)
{
    implicit_integer_type v1;
    EXPECT_EQ(0, v1);
    v1 = 42;
    EXPECT_EQ(42, v1);
    another_implicit_integer_type v2;
    EXPECT_EQ(0, v2);
    v1 = v2;
    EXPECT_EQ(0, v1);
    EXPECT_EQ(0, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_default_value)
{
    const implicit_integer_type v;
    EXPECT_EQ(0u, v);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_construction)
{
    {
        const implicit_integer_type v(0);
        EXPECT_EQ(0u, v);
    }
    {
        const implicit_integer_type v1(1);
        EXPECT_EQ(1, v1);
        const implicit_integer_type v2(v1);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(1, v2);
        EXPECT_EQ(v1, v2);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_get_set)
{
    implicit_integer_type v1;
    EXPECT_EQ(0, v1);
    v1 = 42;
    EXPECT_EQ(42, v1);
    EXPECT_EQ(42, v1.get());
    implicit_integer_type v2(47);
    EXPECT_EQ(47, v2);
    EXPECT_EQ(47, v2.get());
    v1.set(v2);
    EXPECT_EQ(47, v1);
    EXPECT_EQ(47, v1.get());
    EXPECT_EQ(47, v2);
    EXPECT_EQ(47, v2.get());
    v1.set(74);
    EXPECT_EQ(74, v1);
    EXPECT_EQ(74, v1.get());
    EXPECT_EQ(47, v2);
    EXPECT_EQ(47, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_simple_assignment_operator)
{
    const implicit_integer_type v1(100);
    EXPECT_EQ(100, v1);
    implicit_integer_type v2;
    EXPECT_EQ(0, v2);
    v2 = 42;
    EXPECT_EQ(42, v2);
    v2 = v1;
    EXPECT_EQ(100, v1);
    EXPECT_EQ(100, v2);
    EXPECT_EQ(v1, v2);
    v2 = 200;
    EXPECT_EQ(200, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_addition_assignment_operator)
{
    const implicit_integer_type v1(100);
    EXPECT_EQ(100, v1);
    implicit_integer_type v2;
    EXPECT_EQ(0, v2);
    v2 = 42;
    EXPECT_EQ(42, v2);
    v2 += v1;
    EXPECT_EQ(100, v1);
    EXPECT_EQ(142, v2);
    EXPECT_NE(v1, v2);
    v2 += 50;
    EXPECT_EQ(192, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_subtraction_assignment_operator)
{
    const implicit_integer_type v1(10);
    EXPECT_EQ(10, v1);
    implicit_integer_type v2;
    EXPECT_EQ(0, v2);
    v2 = 42;
    EXPECT_EQ(42, v2);
    v2 -= v1;
    EXPECT_EQ(10, v1);
    EXPECT_EQ(32, v2);
    EXPECT_NE(v1, v2);
    v2 -= 7;
    EXPECT_EQ(25, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_multiplication_assignment_operator)
{
    const implicit_integer_type v1(10);
    EXPECT_EQ(10, v1);
    implicit_integer_type v2;
    EXPECT_EQ(0, v2);
    v2 = 42;
    EXPECT_EQ(42, v2);
    v2 *= v1;
    EXPECT_EQ(10, v1);
    EXPECT_EQ(420, v2);
    EXPECT_NE(v1, v2);
    v2 *= 2;
    EXPECT_EQ(840, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_division_assignment_operator)
{
    const implicit_integer_type v1(7);
    EXPECT_EQ(7, v1);
    implicit_integer_type v2;
    EXPECT_EQ(0, v2);
    v2 = 42;
    EXPECT_EQ(42, v2);
    v2 /= v1;
    EXPECT_EQ(7, v1);
    EXPECT_EQ(6, v2);
    EXPECT_NE(v1, v2);
    v2 /= 2;
    EXPECT_EQ(3, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_modulo_assignment_operator)
{
    {
        const implicit_integer_type v1(10);
        EXPECT_EQ(10, v1);
        implicit_integer_type v2(42);
        EXPECT_EQ(42, v2);
        v2 %= v1;
        EXPECT_EQ(10, v1);
        EXPECT_EQ(2, v2);
        EXPECT_NE(v1, v2);
    }
    {
        implicit_integer_type v(42);
        EXPECT_EQ(42u, v);
        v %= 10;
        EXPECT_EQ(2u, v);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_and_assignment_operator)
{
    const implicit_integer_type v1(74); // == 0x4A == 01001010
    EXPECT_EQ(74, v1);
    implicit_integer_type v2(42);       // == 0x2A == 00101010
    EXPECT_EQ(42, v2);
    v2 &= v1;                  // == 0x0A == 00001010
    EXPECT_EQ(74, v1);
    EXPECT_EQ(10, v2);
    EXPECT_NE(v1, v2);
    v2 &= 9;                   // == 0x08 == 00001000
    EXPECT_EQ(8, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_or_assignment_operator)
{
    const implicit_integer_type v1(74); // == 0x4A == 01001010
    EXPECT_EQ(74, v1);
    implicit_integer_type v2(42);       // == 0x2A == 00101010
    EXPECT_EQ(42, v2);
    v2 |= v1;                  // == 0x6A == 01101010
    EXPECT_EQ(74, v1);
    EXPECT_EQ(106, v2);
    EXPECT_NE(v1, v2);
    v2 |= 9;                   // == 0x6B == 01101011
    EXPECT_EQ(107, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_xor_assignment_operator)
{
    const implicit_integer_type v1(74); // == 0x4A == 01001010
    EXPECT_EQ(74, v1);
    implicit_integer_type v2(42);       // == 0x2A == 00101010
    EXPECT_EQ(42, v2);
    v2 ^= v1;                  // == 0x60 == 01100000
    EXPECT_EQ(74, v1);
    EXPECT_EQ(96, v2);
    EXPECT_NE(v1, v2);
    v2 ^= 9;                   // == 0x69 == 01101001
    EXPECT_EQ(105, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_left_shift_assignment_operator)
{
    const implicit_integer_type v1(2);  // == 0x02 == 00000010
    EXPECT_EQ(2, v1);
    implicit_integer_type v2(27);       // == 0x1B == 00011011
    EXPECT_EQ(27, v2);
    v2 <<= v1;                 // == 0x6C == 01101100
    EXPECT_EQ(2, v1);
    EXPECT_EQ(108, v2);
    EXPECT_NE(v1, v2);
    v2 <<= 1;                   // == 0xD8 == 11011000
    EXPECT_EQ(216, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_right_shift_assignment_operator)
{
    const implicit_integer_type v1(2);  // == 0x02 == 00000010
    EXPECT_EQ(2, v1);
    implicit_integer_type v2(216);      // == 0xD8 == 11011000
    EXPECT_EQ(216, v2);
    v2 >>= v1;                 // == 0x36 == 00110110
    EXPECT_EQ(2, v1);
    EXPECT_EQ(54, v2);
    EXPECT_NE(v1, v2);
    v2 >>= 1;                   // == 0x1B == 00011011
    EXPECT_EQ(27, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_unary_plus_arithmetic_operator)
{
    {
        const implicit_integer_type v1(42);
        EXPECT_EQ(42, v1);
        const implicit_integer_type v2 = +v1;
        EXPECT_EQ(42, v1);
        EXPECT_EQ(42, v2);
    }
    {
        const implicit_integer_type v1(-47);
        EXPECT_EQ(-47, v1);
        const implicit_integer_type v2 = +v1;
        EXPECT_EQ(-47, v1);
        EXPECT_EQ(-47, v2);
    }
}

#if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_unary_minus_arithmetic_operator)
{
    {
        const implicit_integer_type v1(42);
        EXPECT_EQ(42, v1);
        const implicit_integer_type v2 = -v1;
        EXPECT_EQ(42, v1);
        EXPECT_EQ(-42, v2);
    }
    {
        const implicit_integer_type v1(-47);
        EXPECT_EQ(-47, v1);
        const implicit_integer_type v2 = -v1;
        EXPECT_EQ(-47, v1);
        EXPECT_EQ(47, v2);
    }
}

#endif  // #if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_addition_arithmetic_operator)
{
    const implicit_integer_type v1(100);
    EXPECT_EQ(100, v1);
    const implicit_integer_type v2(42);
    EXPECT_EQ(42, v2);
    const implicit_integer_type v3 = v1 + v2;
    EXPECT_EQ(100, v1);
    EXPECT_EQ(42, v2);
    EXPECT_EQ(142, v3);
    const implicit_integer_type v4 = v3 + 50;
    EXPECT_EQ(142, v3);
    EXPECT_EQ(192u, v4);
    const implicit_integer_type v5 = 50 + v4;
    EXPECT_EQ(192u, v4);
    EXPECT_EQ(242u, v5);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_subtraction_arithmetic_operator)
{
    const implicit_integer_type v1(100);
    EXPECT_EQ(100, v1);
    const implicit_integer_type v2(42);
    EXPECT_EQ(42, v2);
    const implicit_integer_type v3 = v1 - v2;
    EXPECT_EQ(100, v1);
    EXPECT_EQ(42, v2);
    EXPECT_EQ(58, v3);
    const implicit_integer_type v4 = v3 - 50;
    EXPECT_EQ(58, v3);
    EXPECT_EQ(8u, v4);
    const implicit_integer_type v5 = 50 - v4;
    EXPECT_EQ(8u, v4);
    EXPECT_EQ(42u, v5);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_multiplication_arithmetic_operator)
{
    const implicit_integer_type v1(10);
    EXPECT_EQ(10, v1);
    const implicit_integer_type v2(42);
    EXPECT_EQ(42, v2);
    const implicit_integer_type v3 = v1 * v2;
    EXPECT_EQ(10, v1);
    EXPECT_EQ(42, v2);
    EXPECT_EQ(420, v3);
    const implicit_integer_type v4 = v3 * 5;
    EXPECT_EQ(420, v3);
    EXPECT_EQ(2100u, v4);
    const implicit_integer_type v5 = 5 * v4;
    EXPECT_EQ(2100u, v4);
    EXPECT_EQ(10500u, v5);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_division_arithmetic_operator)
{
    const implicit_integer_type v1(5);
    EXPECT_EQ(5, v1);
    const implicit_integer_type v2(10500);
    EXPECT_EQ(10500, v2);
    const implicit_integer_type v3 = v2 / v1;
    EXPECT_EQ(5, v1);
    EXPECT_EQ(10500, v2);
    EXPECT_EQ(2100, v3);
    const implicit_integer_type v4 = v3 / 5;
    EXPECT_EQ(2100, v3);
    EXPECT_EQ(420u, v4);
    const implicit_integer_type v5 = 4200 / v4;
    EXPECT_EQ(420u, v4);
    EXPECT_EQ(10u, v5);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_modulo_arithmetic_operator)
{
    const implicit_integer_type v1(8472);
    EXPECT_EQ(8472, v1);
    const implicit_integer_type v2(42);
    EXPECT_EQ(42, v2);
    const implicit_integer_type v3 = v1 % v2;
    EXPECT_EQ(8472, v1);
    EXPECT_EQ(42, v2);
    EXPECT_EQ(30, v3);
    const implicit_integer_type v4 = v2 % 5;
    EXPECT_EQ(42, v2);
    EXPECT_EQ(2u, v4);
    const implicit_integer_type v5 = 100 % v3;
    EXPECT_EQ(30, v3);
    EXPECT_EQ(10u, v5);
}

#if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_not_arithmetic_operator)
{
    const implicit_integer_type v1(0xA0B3E7F9); //        10100000 10110011 11100111 11111001
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
    const implicit_integer_type v2 = ~v1; // 0x5F4C1806 = 01011111 01001100 00011000 00000110
    EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
    EXPECT_EQ(static_cast<int>(0x5F4C1806), v2);
}

#endif  // #if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_and_arithmetic_operator)
{
    {
        const implicit_integer_type v1(0xA0B3E7F9); // 10100000 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        const implicit_integer_type v2(0xB3A0F9E7); // 10110011 10100000 11111001 11100111
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        const implicit_integer_type v3 = v1 & v2;   // 10100000 10100000 11100001 11100001 = 0xA0A0E1E1
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        EXPECT_EQ(static_cast<int>(0xA0A0E1E1), v3);
    }
    {
        const int i1 = 0xA0B3E7F9;         // 10100000 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), i1);
        const implicit_integer_type v2(0xB3A0F9E7); // 10110011 10100000 11111001 11100111
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        const implicit_integer_type v3 = i1 & v2;   // 10100000 10100000 11100001 11100001 = 0xA0A0E1E1
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), i1);
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        EXPECT_EQ(static_cast<int>(0xA0A0E1E1), v3);
    }
    {
        const implicit_integer_type v1(0xA0B3E7F9); // 10100000 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        const int i2 = 0xB3A0F9E7;         // 10110011 10100000 11111001 11100111
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), i2);
        const implicit_integer_type v3 = v1 & i2;   // 10100000 10100000 11100001 11100001 = 0xA0A0E1E1
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), i2);
        EXPECT_EQ(static_cast<int>(0xA0A0E1E1), v3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_or_arithmetic_operator)
{
    {
        const implicit_integer_type v1(0xA0B3E7F9); // 10100000 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        const implicit_integer_type v2(0xB3A0F9E7); // 10110011 10100000 11111001 11100111
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        const implicit_integer_type v3 = v1 | v2;   // 10110011 10110011 11111111 11111111 = 0xB3B3FFFF
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        EXPECT_EQ(static_cast<int>(0xB3B3FFFF), v3);
    }
    {
        const int i1 = 0xA0B3E7F9;         // 10100000 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), i1);
        const implicit_integer_type v2(0xB3A0F9E7); // 10110011 10100000 11111001 11100111
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        const implicit_integer_type v3 = i1 | v2;   // 10110011 10110011 11111111 11111111 = 0xB3B3FFFF
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), i1);
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        EXPECT_EQ(static_cast<int>(0xB3B3FFFF), v3);
    }
    {
        const implicit_integer_type v1(0xA0B3E7F9); // 10100000 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        const int i2 = 0xB3A0F9E7;         // 10110011 10100000 11111001 11100111
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), i2);
        const implicit_integer_type v3 = v1 | i2;   // 10110011 10110011 11111111 11111111 = 0xB3B3FFFF
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), i2);
        EXPECT_EQ(static_cast<int>(0xB3B3FFFF), v3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_xor_arithmetic_operator)
{
    {
        const implicit_integer_type v1(0xA0B3E7F9); // 10100000 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        const implicit_integer_type v2(0xB3A0F9E7); // 10110011 10100000 11111001 11100111
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        const implicit_integer_type v3 = v1 ^ v2;   // 00010011 00010011 00011110 00011110 = 0x13131E1E
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        EXPECT_EQ(static_cast<int>(0x13131E1E), v3);
    }
    {
        const int i1 = 0xA0B3E7F9;         // 10100000 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), i1);
        const implicit_integer_type v2(0xB3A0F9E7); // 10110011 10100000 11111001 11100111
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        const implicit_integer_type v3 = i1 ^ v2;   // 00010011 00010011 00011110 00011110 = 0x13131E1E
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), i1);
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), v2);
        EXPECT_EQ(static_cast<int>(0x13131E1E), v3);
    }
    {
        const implicit_integer_type v1(0xA0B3E7F9); // 10100000 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        const int i2 = 0xB3A0F9E7;         // 10110011 10100000 11111001 11100111
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), i2);
        const implicit_integer_type v3 = v1 ^ i2;   // 00010011 00010011 00011110 00011110 = 0x13131E1E
        EXPECT_EQ(static_cast<int>(0xA0B3E7F9), v1);
        EXPECT_EQ(static_cast<int>(0xB3A0F9E7), i2);
        EXPECT_EQ(static_cast<int>(0x13131E1E), v3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_left_shift_arithmetic_operator)
{
    {
        const implicit_integer_type v1(0x0AB3E7F9); // 00001010 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0x0AB3E7F9), v1);
        const implicit_integer_type v2(3);
        EXPECT_EQ(3, v2);
        const implicit_integer_type v3 = v1 << v2;  // 01010101 10011111 00111111 11001000 = 0x559F3FC8
        EXPECT_EQ(static_cast<int>(0x0AB3E7F9), v1);
        EXPECT_EQ(3, v2);
        EXPECT_EQ(static_cast<int>(0x559F3FC8), v3);
    }
    {
        const int i1 = 0x0AB3E7F9;         // 00001010 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0x0AB3E7F9), i1);
        const implicit_integer_type v2(3);
        EXPECT_EQ(3, v2);
        const implicit_integer_type v3 = i1 << v2;  // 01010101 10011111 00111111 11001000 = 0x559F3FC8
        EXPECT_EQ(static_cast<int>(0x0AB3E7F9), i1);
        EXPECT_EQ(3, v2);
        EXPECT_EQ(static_cast<int>(0x559F3FC8), v3);
    }
    {
        const implicit_integer_type v1(0x0AB3E7F9); // 00001010 10110011 11100111 11111001
        EXPECT_EQ(static_cast<int>(0x0AB3E7F9), v1);
        const int i2 = 3;
        EXPECT_EQ(3, i2);
        const implicit_integer_type v3 = v1 << i2;  // 01010101 10011111 00111111 11001000 = 0x559F3FC8
        EXPECT_EQ(static_cast<int>(0x0AB3E7F9), v1);
        EXPECT_EQ(3, i2);
        EXPECT_EQ(static_cast<int>(0x559F3FC8), v3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_bitwise_right_shift_arithmetic_operator)
{
    {
        const implicit_integer_type v1(0x0AB3E7F0); // 00001010 10110011 11100111 11111000
        EXPECT_EQ(static_cast<int>(0x0AB3E7F0), v1);
        const implicit_integer_type v2(3);
        EXPECT_EQ(3, v2);
        const implicit_integer_type v3 = v1 >> v2;  // 00000001 01010110 01111100 11111110 = 0x01567CFE
        EXPECT_EQ(static_cast<int>(0x0AB3E7F0), v1);
        EXPECT_EQ(3, v2);
        EXPECT_EQ(static_cast<int>(0x01567CFE), v3);
    }
    {
        const int i1 = 0x0AB3E7F0;         // 00001010 10110011 11100111 11111000
        EXPECT_EQ(static_cast<int>(0x0AB3E7F0), i1);
        const implicit_integer_type v2(3);
        EXPECT_EQ(3, v2);
        const implicit_integer_type v3 = i1 >> v2;  // 00000001 01010110 01111100 11111110 = 0x01567CFE
        EXPECT_EQ(static_cast<int>(0x0AB3E7F0), i1);
        EXPECT_EQ(3, v2);
        EXPECT_EQ(static_cast<int>(0x01567CFE), v3);
    }
    {
        const implicit_integer_type v1(0x0AB3E7F0); // 00001010 10110011 11100111 11111000
        EXPECT_EQ(static_cast<int>(0x0AB3E7F0), v1);
        const int i2 = 3;
        EXPECT_EQ(3, i2);
        const implicit_integer_type v3 = v1 >> i2;  // 00000001 01010110 01111100 11111110 = 0x01567CFE
        EXPECT_EQ(static_cast<int>(0x0AB3E7F0), v1);
        EXPECT_EQ(3, i2);
        EXPECT_EQ(static_cast<int>(0x01567CFE), v3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_equal_to_comparison_operator)
{
    {
        const implicit_integer_type v1(1);
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 == v2);
        const bool comparison_result_2 = (v2 == v2);
        const bool comparison_result_3 = (v3 == v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const int i1 = 1;
        const implicit_integer_type v2(2);
        const int i3 = 3;
        EXPECT_EQ(1, i1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, i3);
        const bool comparison_result_1 = (i1 == v2);
        const bool comparison_result_2 = (v2 == v2);
        const bool comparison_result_3 = (i3 == v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const implicit_integer_type v1(1);
        const int i2 = 2;
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, i2);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 == i2);
        const bool comparison_result_2 = (v2 == i2);
        const bool comparison_result_3 = (v3 == i2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_not_equal_to_comparison_operator)
{
    {
        const implicit_integer_type v1(1);
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 != v2);
        const bool comparison_result_2 = (v2 != v2);
        const bool comparison_result_3 = (v3 != v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const int i1 = 1;
        const implicit_integer_type v2(2);
        const int i3 = 3;
        EXPECT_EQ(1, i1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, i3);
        const bool comparison_result_1 = (i1 != v2);
        const bool comparison_result_2 = (v2 != v2);
        const bool comparison_result_3 = (i3 != v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const implicit_integer_type v1(1);
        const int i2 = 2;
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, i2);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 != i2);
        const bool comparison_result_2 = (v2 != i2);
        const bool comparison_result_3 = (v3 != i2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_less_than_comparison_operator)
{
    {
        const implicit_integer_type v1(1);
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 < v2);
        const bool comparison_result_2 = (v2 < v2);
        const bool comparison_result_3 = (v3 < v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const int i1 = 1;
        const implicit_integer_type v2(2);
        const int i3 = 3;
        EXPECT_EQ(1, i1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, i3);
        const bool comparison_result_1 = (i1 < v2);
        const bool comparison_result_2 = (v2 < v2);
        const bool comparison_result_3 = (i3 < v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const implicit_integer_type v1(1);
        const int i2 = 2;
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, i2);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 < i2);
        const bool comparison_result_2 = (v2 < i2);
        const bool comparison_result_3 = (v3 < i2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_greater_than_comparison_operator)
{
    {
        const implicit_integer_type v1(1);
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 > v2);
        const bool comparison_result_2 = (v2 > v2);
        const bool comparison_result_3 = (v3 > v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const int i1 = 1;
        const implicit_integer_type v2(2);
        const int i3 = 3;
        EXPECT_EQ(1, i1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, i3);
        const bool comparison_result_1 = (i1 > v2);
        const bool comparison_result_2 = (v2 > v2);
        const bool comparison_result_3 = (i3 > v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const implicit_integer_type v1(1);
        const int i2 = 2;
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, i2);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 > i2);
        const bool comparison_result_2 = (v2 > i2);
        const bool comparison_result_3 = (v3 > i2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_less_than_or_equal_to_comparison_operator)
{
    {
        const implicit_integer_type v1(1);
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 <= v2);
        const bool comparison_result_2 = (v2 <= v2);
        const bool comparison_result_3 = (v3 <= v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const int i1 = 1;
        const implicit_integer_type v2(2);
        const int i3 = 3;
        EXPECT_EQ(1, i1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, i3);
        const bool comparison_result_1 = (i1 <= v2);
        const bool comparison_result_2 = (v2 <= v2);
        const bool comparison_result_3 = (i3 <= v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const implicit_integer_type v1(1);
        const int i2 = 2;
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, i2);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 <= i2);
        const bool comparison_result_2 = (v2 <= i2);
        const bool comparison_result_3 = (v3 <= i2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_greater_than_or_equal_to_comparison_operator)
{
    {
        const implicit_integer_type v1(1);
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 >= v2);
        const bool comparison_result_2 = (v2 >= v2);
        const bool comparison_result_3 = (v3 >= v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const int i1 = 1;
        const implicit_integer_type v2(2);
        const int i3 = 3;
        EXPECT_EQ(1, i1);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, i3);
        const bool comparison_result_1 = (i1 >= v2);
        const bool comparison_result_2 = (v2 >= v2);
        const bool comparison_result_3 = (i3 >= v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const implicit_integer_type v1(1);
        const int i2 = 2;
        const implicit_integer_type v2(2);
        const implicit_integer_type v3(3);
        EXPECT_EQ(1, v1);
        EXPECT_EQ(2, i2);
        EXPECT_EQ(2, v2);
        EXPECT_EQ(3, v3);
        const bool comparison_result_1 = (v1 >= i2);
        const bool comparison_result_2 = (v2 >= i2);
        const bool comparison_result_3 = (v3 >= i2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_pre_increment_operator)
{
    implicit_integer_type v1(10);
    EXPECT_EQ(10, v1);
    const implicit_integer_type v2(++v1);
    EXPECT_EQ(11, v1);
    EXPECT_EQ(11, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_post_increment_operator)
{
    implicit_integer_type v1(10);
    EXPECT_EQ(10, v1);
    const implicit_integer_type v2(v1++);
    EXPECT_EQ(11, v1);
    EXPECT_EQ(10, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_pre_decrement_operator)
{
    implicit_integer_type v1(10);
    EXPECT_EQ(10, v1);
    const implicit_integer_type v2(--v1);
    EXPECT_EQ(9, v1);
    EXPECT_EQ(9, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_integer_type_specializer_post_decrement_operator)
{
    implicit_integer_type v1(10);
    EXPECT_EQ(10, v1);
    const implicit_integer_type v2(v1--);
    EXPECT_EQ(9, v1);
    EXPECT_EQ(10, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_default_value)
{
    const implicit_floating_point_type v(47.0);
    EXPECT_EQ(47.0, v);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_construction)
{
    {
        const implicit_floating_point_type v(0.0);
        EXPECT_EQ(0.0, v);
    }
    {
        const implicit_floating_point_type v1(1.0);
        EXPECT_EQ(1.0, v1);
        const implicit_floating_point_type v2(v1);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(1.0, v2);
        EXPECT_EQ(v1, v2);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_get_set)
{
    implicit_floating_point_type v1(47.0);
    EXPECT_EQ(47.0, v1);
    EXPECT_EQ(47.0, v1.get());
    implicit_floating_point_type v2(42.0);
    EXPECT_EQ(42.0, v2);
    EXPECT_EQ(42.0, v2.get());
    v1.set(v2);
    EXPECT_EQ(42.0, v1);
    EXPECT_EQ(42.0, v1.get());
    EXPECT_EQ(42.0, v2);
    EXPECT_EQ(42.0, v2.get());
    v1.set(74.0);
    EXPECT_EQ(74.0, v1);
    EXPECT_EQ(74.0, v1.get());
    EXPECT_EQ(42.0, v2);
    EXPECT_EQ(42.0, v2.get());
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_simple_assignment_operator)
{
    const implicit_floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1);
    implicit_floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2);
    v2 = v1;
    EXPECT_EQ(100.0, v1);
    EXPECT_EQ(100.0, v2);
    EXPECT_EQ(v1, v2);
    v2 = 200.0;
    EXPECT_EQ(200.0, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_addition_assignment_operator)
{
    const implicit_floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1);
    implicit_floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2);
    v2 += v1;
    EXPECT_EQ(100.0, v1);
    EXPECT_EQ(147.0, v2);
    EXPECT_NE(v1, v2);
    v2 += 50.0;
    EXPECT_EQ(197.0, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_subtraction_assignment_operator)
{
    const implicit_floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1);
    implicit_floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2);
    v2 -= v1;
    EXPECT_EQ(100.0, v1);
    EXPECT_EQ(-53.0, v2);
    EXPECT_NE(v1, v2);
    v2 -= 7.0;
    EXPECT_EQ(-60.0, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_multiplication_assignment_operator)
{
    const implicit_floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1);
    implicit_floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2);
    v2 *= v1;
    EXPECT_EQ(10.0, v1);
    EXPECT_EQ(470.0, v2);
    EXPECT_NE(v1, v2);
    v2 *= 2.0;
    EXPECT_EQ(940.0, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_division_assignment_operator)
{
    const implicit_floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1);
    implicit_floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2);
    v2 /= v1;
    EXPECT_EQ(10.0, v1);
    EXPECT_EQ(4.7, v2);
    EXPECT_NE(v1, v2);
    v2 /= 2.0;
    EXPECT_EQ(2.35, v2);
    EXPECT_NE(v1, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_modulo_assignment_operator)
{
    {
        const implicit_floating_point_type v1(10.0);
        EXPECT_EQ(10.0, v1);
        implicit_floating_point_type v2(42.0);
        EXPECT_EQ(42.0, v2);
        v2 %= v1;
        EXPECT_EQ(10.0, v1);
        EXPECT_EQ(2.0, v2);
        EXPECT_NE(v1, v2);
    }
    {
        implicit_floating_point_type v(42.0);
        EXPECT_EQ(42.0, v);
        v %= 10.0;
        EXPECT_EQ(2.0, v);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_unary_plus_arithmetic_operator)
{
    {
        const implicit_floating_point_type v1(47.0);
        EXPECT_EQ(47.0, v1);
        const implicit_floating_point_type v2 = +v1;
        EXPECT_EQ(47.0, v1);
        EXPECT_EQ(47.0, v2);
    }
    {
        const implicit_floating_point_type v1(-74.0);
        EXPECT_EQ(-74.0, v1);
        const implicit_floating_point_type v2 = +v1;
        EXPECT_EQ(-74.0, v1);
        EXPECT_EQ(-74.0, v2);
    }
}

#if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_unary_minus_arithmetic_operator)
{
    {
        const implicit_floating_point_type v1(47.0);
        EXPECT_EQ(47.0, v1);
        const implicit_floating_point_type v2 = -v1;
        EXPECT_EQ(47.0, v1);
        EXPECT_EQ(-47.0, v2);
    }
    {
        const implicit_floating_point_type v1(-74.0);
        EXPECT_EQ(-74.0, v1);
        const implicit_floating_point_type v2 = -v1;
        EXPECT_EQ(-74.0, v1);
        EXPECT_EQ(74.0, v2);
    }
}

#endif  // #if !defined(GO_BOOST_COMP_MSVC_VC120)

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_addition_arithmetic_operator)
{
    const implicit_floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1);
    const implicit_floating_point_type v2(42.0);
    EXPECT_EQ(42.0, v2);
    const implicit_floating_point_type v3 = v1 + v2;
    EXPECT_EQ(100.0, v1);
    EXPECT_EQ(42.0, v2);
    EXPECT_EQ(142.0, v3);
    const implicit_floating_point_type v4 = v3 + 50.0;
    EXPECT_EQ(142.0, v3);
    EXPECT_EQ(192.0, v4);
    const implicit_floating_point_type v5 = 50.0 + v4;
    EXPECT_EQ(192.0, v4);
    EXPECT_EQ(242.0, v5);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_subtraction_arithmetic_operator)
{
    const implicit_floating_point_type v1(100.0);
    EXPECT_EQ(100.0, v1);
    const implicit_floating_point_type v2(42.0);
    EXPECT_EQ(42.0, v2);
    const implicit_floating_point_type v3 = v1 - v2;
    EXPECT_EQ(100.0, v1);
    EXPECT_EQ(42.0, v2);
    EXPECT_EQ(58.0, v3);
    const implicit_floating_point_type v4 = v3 - 50.0;
    EXPECT_EQ(58.0, v3);
    EXPECT_EQ(8.0, v4);
    const implicit_floating_point_type v5 = 50.0 - v4;
    EXPECT_EQ(8.0, v4);
    EXPECT_EQ(42.0, v5);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_multiplication_arithmetic_operator)
{
    const implicit_floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1);
    const implicit_floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2);
    const implicit_floating_point_type v3 = v1 * v2;
    EXPECT_EQ(10.0, v1);
    EXPECT_EQ(47.0, v2);
    EXPECT_EQ(470.0, v3);
    const implicit_floating_point_type v4 = v3 * 5.0;
    EXPECT_EQ(470.0, v3);
    EXPECT_EQ(2350.0, v4);
    const implicit_floating_point_type v5 = 5.0 * v4;
    EXPECT_EQ(2350.0, v4);
    EXPECT_EQ(11750.0, v5);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_division_arithmetic_operator)
{
    const implicit_floating_point_type v1(5.0);
    EXPECT_EQ(5.0, v1);
    const implicit_floating_point_type v2(10500.0);
    EXPECT_EQ(10500.0, v2);
    const implicit_floating_point_type v3 = v2 / v1;
    EXPECT_EQ(5.0, v1);
    EXPECT_EQ(10500.0, v2);
    EXPECT_EQ(2100.0, v3);
    const implicit_floating_point_type v4 = v3 / 5.0;
    EXPECT_EQ(2100.0, v3);
    EXPECT_EQ(420.0, v4);
    const implicit_floating_point_type v5 = 4200.0 / v4;
    EXPECT_EQ(420.0, v4);
    EXPECT_EQ(10.0, v5);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_modulo_arithmetic_operator)
{
    const implicit_floating_point_type v1(8472.0);
    EXPECT_EQ(8472.0, v1);
    const implicit_floating_point_type v2(47.0);
    EXPECT_EQ(47.0, v2);
    const implicit_floating_point_type v3 = v1 % v2;
    EXPECT_EQ(8472.0, v1);
    EXPECT_EQ(47.0, v2);
    EXPECT_EQ(12.0, v3);
    const implicit_floating_point_type v4 = v2 % 5;
    EXPECT_EQ(47.0, v2);
    EXPECT_EQ(2u, v4);
    const implicit_floating_point_type v5 = 100.0 % v3;
    EXPECT_EQ(12, v3);
    EXPECT_EQ(4u, v5);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_equal_to_comparison_operator)
{
    {
        const implicit_floating_point_type v1(1.0);
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 == v2);
        const bool comparison_result_2 = (v2 == v2);
        const bool comparison_result_3 = (v3 == v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const double i1 = 1.0;
        const implicit_floating_point_type v2(2.0);
        const double i3 = 3.0;
        EXPECT_EQ(1.0, i1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, i3);
        const bool comparison_result_1 = (i1 == v2);
        const bool comparison_result_2 = (v2 == v2);
        const bool comparison_result_3 = (i3 == v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const implicit_floating_point_type v1(1.0);
        const double i2 = 2.0;
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, i2);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 == i2);
        const bool comparison_result_2 = (v2 == i2);
        const bool comparison_result_3 = (v3 == i2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_not_equal_to_comparison_operator)
{
    {
        const implicit_floating_point_type v1(1.0);
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 != v2);
        const bool comparison_result_2 = (v2 != v2);
        const bool comparison_result_3 = (v3 != v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const double i1 = 1.0;
        const implicit_floating_point_type v2(2.0);
        const double i3 = 3.0;
        EXPECT_EQ(1.0, i1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, i3);
        const bool comparison_result_1 = (i1 != v2);
        const bool comparison_result_2 = (v2 != v2);
        const bool comparison_result_3 = (i3 != v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const implicit_floating_point_type v1(1.0);
        const double i2 = 2.0;
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, i2);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 != i2);
        const bool comparison_result_2 = (v2 != i2);
        const bool comparison_result_3 = (v3 != i2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_less_than_to_comparison_operator)
{
    {
        const implicit_floating_point_type v1(1.0);
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 < v2);
        const bool comparison_result_2 = (v2 < v2);
        const bool comparison_result_3 = (v3 < v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const double i1 = 1.0;
        const implicit_floating_point_type v2(2.0);
        const double i3 = 3.0;
        EXPECT_EQ(1.0, i1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, i3);
        const bool comparison_result_1 = (i1 < v2);
        const bool comparison_result_2 = (v2 < v2);
        const bool comparison_result_3 = (i3 < v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const implicit_floating_point_type v1(1.0);
        const double i2 = 2.0;
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, i2);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 < i2);
        const bool comparison_result_2 = (v2 < i2);
        const bool comparison_result_3 = (v3 < i2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_greater_than_comparison_operator)
{
    {
        const implicit_floating_point_type v1(1.0);
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 > v2);
        const bool comparison_result_2 = (v2 > v2);
        const bool comparison_result_3 = (v3 > v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const double i1 = 1.0;
        const implicit_floating_point_type v2(2.0);
        const double i3 = 3.0;
        EXPECT_EQ(1.0, i1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, i3);
        const bool comparison_result_1 = (i1 > v2);
        const bool comparison_result_2 = (v2 > v2);
        const bool comparison_result_3 = (i3 > v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const implicit_floating_point_type v1(1.0);
        const double i2 = 2.0;
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, i2);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 > i2);
        const bool comparison_result_2 = (v2 > i2);
        const bool comparison_result_3 = (v3 > i2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(false, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_less_than_or_equal_to_to_comparison_operator)
{
    {
        const implicit_floating_point_type v1(1.0);
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 <= v2);
        const bool comparison_result_2 = (v2 <= v2);
        const bool comparison_result_3 = (v3 <= v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const double i1 = 1.0;
        const implicit_floating_point_type v2(2.0);
        const double i3 = 3.0;
        EXPECT_EQ(1.0, i1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, i3);
        const bool comparison_result_1 = (i1 <= v2);
        const bool comparison_result_2 = (v2 <= v2);
        const bool comparison_result_3 = (i3 <= v2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
    {
        const implicit_floating_point_type v1(1.0);
        const double i2 = 2.0;
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, i2);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 <= i2);
        const bool comparison_result_2 = (v2 <= i2);
        const bool comparison_result_3 = (v3 <= i2);
        EXPECT_EQ(true, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(false, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_greater_than_or_equal_to_comparison_operator)
{
    {
        const implicit_floating_point_type v1(1.0);
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 >= v2);
        const bool comparison_result_2 = (v2 >= v2);
        const bool comparison_result_3 = (v3 >= v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const double i1 = 1.0;
        const implicit_floating_point_type v2(2.0);
        const double i3 = 3.0;
        EXPECT_EQ(1.0, i1);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, i3);
        const bool comparison_result_1 = (i1 >= v2);
        const bool comparison_result_2 = (v2 >= v2);
        const bool comparison_result_3 = (i3 >= v2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
    {
        const implicit_floating_point_type v1(1.0);
        const double i2 = 2.0;
        const implicit_floating_point_type v2(2.0);
        const implicit_floating_point_type v3(3.0);
        EXPECT_EQ(1.0, v1);
        EXPECT_EQ(2.0, i2);
        EXPECT_EQ(2.0, v2);
        EXPECT_EQ(3.0, v3);
        const bool comparison_result_1 = (v1 >= i2);
        const bool comparison_result_2 = (v2 >= i2);
        const bool comparison_result_3 = (v3 >= i2);
        EXPECT_EQ(false, comparison_result_1);
        EXPECT_EQ(true, comparison_result_2);
        EXPECT_EQ(true, comparison_result_3);
    }
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_pre_increment_operator)
{
    implicit_floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1);
    const implicit_floating_point_type v2(++v1);
    EXPECT_EQ(11.0, v1);
    EXPECT_EQ(11.0, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_post_increment_operator)
{
    implicit_floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1);
    const implicit_floating_point_type v2(v1++);
    EXPECT_EQ(11.0, v1);
    EXPECT_EQ(10.0, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_pre_decrement_operator)
{
    implicit_floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1);
    const implicit_floating_point_type v2(--v1);
    EXPECT_EQ(9.0, v1);
    EXPECT_EQ(9.0, v2);
}

TEST(boost_primitive_type_specializer_test_suite, test_implicit_floating_point_type_specializer_post_decrement_operator)
{
    implicit_floating_point_type v1(10.0);
    EXPECT_EQ(10.0, v1);
    const implicit_floating_point_type v2(v1--);
    EXPECT_EQ(9.0, v1);
    EXPECT_EQ(10.0, v2);
}

}
