//
//  boost_primitive_type_implicit_specializer_example.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <iostream>
#include <go_boost/utility.hpp>

namespace u = go_boost::utility;

GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(radian_type, double, 0.0)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(degree_type, double, 0.0)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(meter_type, double, 0.0)
GO_BOOST_IMPLEMENT_FLOATING_POINT_TYPE_IMPLICIT_SPECIALIZER(square_meter_type, double, 0.0)

namespace bad
{

double circular_sector_area(const double& central_angle, const double& radius)
{
    return radius*radius*central_angle/2.0;
}

}

namespace better
{

square_meter_type circular_sector_area(const radian_type& central_angle, const meter_type& radius)
{
    return square_meter_type(((radius*radius)*central_angle.get())/2.0);
}

square_meter_type circular_sector_area(const degree_type& central_angle, const meter_type& radius)
{
    static const double pi = std::acos(-1.0);
    return square_meter_type(((radius*radius)*central_angle.get())*pi/360.0);
}

}

int main()
{
    {
        // Bad, but right
        const double central_angle_rad = std::acos(-1.0)/3.0;
        const double radius = 1.0;
        const double area_1 = bad::circular_sector_area(central_angle_rad, radius);
        std::cout << "Area 1 = " << area_1 << std::endl;
        // Bad, and wrong (parameter order)
        const double area_2 = bad::circular_sector_area(radius, central_angle_rad);
        std::cout << "Area 2 = " << area_2 << " (wrong)" << std::endl;
        // Bad, and wrong again (unit of measurment)
        const double central_angle_deg = 60.0;
        const double area_3 = bad::circular_sector_area(central_angle_deg, radius);
        std::cout << "Area 3 = " << area_3 << " (wrong)" << std::endl;
    }
    {
        // Better, and right
        const radian_type central_angle_rad(std::acos(-1.0)/3.0);
        const meter_type radius(1.0);
        const square_meter_type area_4 = better::circular_sector_area(central_angle_rad, radius);
        std::cout << "Area 4 = " << area_4 << " square meter" << std::endl;
        // Also better and right
        const degree_type central_angle_deg(60.0);
        const square_meter_type area_5 = better::circular_sector_area(central_angle_deg, radius);
        std::cout << "Area 5 = " << area_5 << " square meter" << std::endl;
    }
    return 0;
}
