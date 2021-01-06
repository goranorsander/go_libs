//
//  erase_example.cpp
//
//  Copyright 2018-2021 Göran Orsander
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

#include <deque>
#include <iostream>
#include <go/namespace_alias.hpp>
#include <go/utility/iterator/erase.hpp>

int main()
{
    std::deque<int> container = { 1, 2, 3, 4, 5 };
    std::deque<int>::iterator it = container.begin();
    ++it;
    it = ui::erase(container, it, 3);
    std::cout << *container.begin() << std::endl;
    std::cout << *it << std::endl;
    std::cout << container.size() << std::endl;
    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
