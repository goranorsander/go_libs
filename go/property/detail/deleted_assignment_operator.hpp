// This header intentionally has no include guards.
//
//  deleted_assignment_operator.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

private:

#if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    this_type& operator=(const this_type& v)
    {
        throw std::logic_error(std::string("deleted assignment operator : assignment operator should not be used"));
    }

    this_type& operator=(const value_type& v)
    {
        throw std::logic_error(std::string("deleted assignment operator : assignment operator should not be used"));
    }

#else

    this_type& operator=(const this_type& v) = delete;

    this_type& operator=(const value_type& v) = delete;

#endif  // #if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
