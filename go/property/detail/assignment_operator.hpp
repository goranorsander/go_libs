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
    // cppcheck-suppress operatorEqVarError
    this_type& operator=(const this_type& v) GO_NOEXCEPT_OR_NOTHROW
    {
        try
        {
            this_type::set(v.get());
        }
        catch (const std::exception&) {}
        return *this;
    }

    // cppcheck-suppress operatorEqVarError
    this_type& operator=(const value_type& v) GO_NOEXCEPT_OR_NOTHROW
    {
        try
        {
            this_type::set(v);
        }
        catch (const std::exception&) {}
        return *this;
    }
