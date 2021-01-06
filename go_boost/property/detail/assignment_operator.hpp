// This header intentionally has no include guards.
//
//  assignment_operator.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

public:
    this_type& operator=(const this_type& v) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this_type::set(v.get());
        return *this;
    }

    this_type& operator=(const value_type& v) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this_type::set(v);
        return *this;
    }
