// This header intentionally has no include guards.
//
//  deleted_assignment_operator.hpp
//
//  Copyright 2017 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

private:

    this_type& operator=(const this_type& v)
    {
        throw std::logic_error(std::string("deleted assignment operator : assignment operator should not be used"));
    }

    this_type& operator=(const value_type& v)
    {
        throw std::logic_error(std::string("deleted assignment operator : assignment operator should not be used"));
    }