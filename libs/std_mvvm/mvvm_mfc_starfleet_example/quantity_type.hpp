#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_QUANTITY_TYPE_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_QUANTITY_TYPE_HPP_INCLUDED

//
//  quantity_type.hpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/type_traits/fundamental_type_specializer.hpp>

GO_IMPLEMENT_FUNDAMENTAL_TYPE_SPECIALIZER(quantity_type, uint64_t);

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_QUANTITY_TYPE_HPP_INCLUDED
