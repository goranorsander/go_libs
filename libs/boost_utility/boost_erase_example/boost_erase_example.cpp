//
//  boost_erase_example.cpp
//
//  Copyright 2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/utility.hpp>
#include <deque>
#include <iostream>
#include <boost/assign.hpp>

namespace u = go_boost::utility;
namespace ui = go_boost::utility::iterator;

int main()
{
    std::deque<int> container = boost::assign::list_of<int>(1)(2)(3)(4)(5);
    std::deque<int>::iterator it = container.begin();
    ++it;
    it = ui::erase(container, it, 3);
    std::cout << *container.begin() << std::endl;
    std::cout << *it << std::endl;
    std::cout << container.size() << std::endl;
    return 0;
}