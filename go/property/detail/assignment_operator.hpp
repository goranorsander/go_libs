// This header intentionally has no include guards.
//
//  assignment_operator.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

public:
    this_type& operator=(const this_type& v)
    {
        set(v.get());
        return *this;
    }

    this_type& operator=(const value_type& v)
    {
        set(v);
        return *this;
    }
