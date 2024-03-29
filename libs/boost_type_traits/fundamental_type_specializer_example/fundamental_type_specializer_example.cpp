//
//  fundamental_type_specializer_example.cpp
//
//  Copyright 2018-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <iostream>
#include <go_boost/namespace_alias.hpp>
#include <go_boost/type_traits.hpp>

#if !defined(GO_BOOST_NO_CXX11_FUNDAMENTAL_TYPE_SPECIALIZER)

GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(radian_type, double)
GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(degree_type, double)
GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(meter_type, double)
GO_BOOST_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(square_meter_type, double)

#else

GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(radian_type, double)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(degree_type, double)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(meter_type, double)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_SPECIALIZER(square_meter_type, double)

#endif  // #if !defined(GO_BOOST_NO_CXX11_FUNDAMENTAL_TYPE_SPECIALIZER)

namespace bad
{

double circular_sector_area(const double& central_angle, const double& radius)
{
    return radius*radius*central_angle/2.0;
}

}

namespace less_bad
{

typedef double meter;
typedef double radian;
typedef double square_meter;

square_meter circular_sector_area(const radian& central_angle, const meter& radius)
{
    return radius*radius*central_angle/2.0;
}

}

namespace better
{

square_meter_type circular_sector_area(const radian_type& central_angle, const meter_type& radius)
{
    return square_meter_type(((radius*radius).get()*central_angle.get())/2.0);
}

square_meter_type circular_sector_area(const degree_type& central_angle, const meter_type& radius)
{
    static const double pi = std::acos(-1.0);
    return square_meter_type(((radius*radius).get()*central_angle.get())*pi/360.0);
}

}

int main()
{
    {
        // Bad, but correct
        const double central_angle_rad = std::acos(-1.0)/3.0;
        const double radius = 1.0;
        const double area_1 = bad::circular_sector_area(central_angle_rad, radius);
        std::cout << "Bad:" << std::endl << "  Area 1 = " << area_1 << std::endl;
        // Bad, and wrong (parameter order)
        const double area_2 = bad::circular_sector_area(radius, central_angle_rad);
        std::cout << "  Area 2 = " << area_2 << " (wrong)" << std::endl;
        // Bad, and wrong again (unit of measurment)
        const double central_angle_deg = 60.0;
        const double area_3 = bad::circular_sector_area(central_angle_deg, radius);
        std::cout << "  Area 3 = " << area_3 << " (wrong)" << std::endl;
    }
    {
        // Less bad, but correct
        const less_bad::radian central_angle_rad = std::acos(-1.0)/3.0;
        const less_bad::meter radius = 1.0;
        const less_bad::square_meter area_4 = less_bad::circular_sector_area(central_angle_rad, radius);
        std::cout << "Less bad:" << std::endl << "  Area 4 = " << area_4 << std::endl;
        // Less bad, but wrong (parameter order)
        const less_bad::square_meter area_5 = less_bad::circular_sector_area(radius, central_angle_rad);
        std::cout << "  Area 5 = " << area_5 << " (wrong)" << std::endl;
        // Less bad, but wrong again (unit of measurment)
        const double central_angle_deg = 60.0;
        const double area_6 = less_bad::circular_sector_area(central_angle_deg, radius);
        std::cout << "  Area 6 = " << area_6 << " (wrong)" << std::endl;
    }
    {
        // Better, and correct
        const radian_type central_angle_rad(std::acos(-1.0)/3.0);
        const meter_type radius(1.0);
        const square_meter_type area_7 = better::circular_sector_area(central_angle_rad, radius);
        std::cout << "Better:" << std::endl << "  Area 7 = " << area_7.get() << " square meter" << std::endl;
        // Also better and correct
        const degree_type central_angle_deg(60.0);
        const square_meter_type area_8 = better::circular_sector_area(central_angle_deg, radius);
        std::cout << "  Area 8 = " << area_8.get() << " square meter" << std::endl;
    }
    return 0;
}
