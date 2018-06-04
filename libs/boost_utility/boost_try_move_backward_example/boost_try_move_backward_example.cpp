//
//  boost_scope_guard_example.cpp
//
//  Copyright 2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/utility.hpp>
#include <iostream>
#include <boost/assign.hpp>
#include <boost/container/slist.hpp>

namespace u = go_boost::utility;
namespace ui = go_boost::utility::iterator;

int main()
{
    boost::container::slist<int> container = boost::assign::list_of<int>(1)(2)(3)(4)(5);
    boost::container::slist<int>::iterator it = container.end();
    while (ui::try_move_backward(container, it))
    {
        std::cout << *it << std::endl;
    }
    return 0;
}
