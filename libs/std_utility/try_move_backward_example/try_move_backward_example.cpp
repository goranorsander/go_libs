//
//  try_move_backward_example.cpp
//
//  Copyright 2018-2019 Göran Orsander
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

#include <forward_list>
#include <iostream>
#include <go/utility.hpp>

namespace u = go::utility;
namespace ui = go::utility::iterator;

int main()
{
    std::forward_list<int> container = { 1, 2, 3, 4, 5 };
    std::forward_list<int>::iterator it = container.end();
    while (ui::try_move_backward(container, it))
    {
        std::cout << *it << std::endl;
    }
    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
