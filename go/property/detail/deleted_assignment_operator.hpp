// This header intentionally has no include guards.
//
//  deleted_assignment_operator.hpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

private:

#if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)

    this_type& operator=(const this_type& v) GO_NOEXCEPT_OR_NOTHROW; // = delete;

    this_type& operator=(const value_type& v) GO_NOEXCEPT_OR_NOTHROW; // = delete;

#else

    this_type& operator=(const this_type& v) = delete;

    this_type& operator=(const value_type& v) = delete;

#endif  // #if defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
