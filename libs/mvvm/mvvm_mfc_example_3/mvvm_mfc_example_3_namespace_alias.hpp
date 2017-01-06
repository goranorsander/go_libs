#ifndef GO_MVVM_MFC_EXAMPLE_3_NAMESPACE_ALIAS_HPP_INCLUDED
#define GO_MVVM_MFC_EXAMPLE_3_NAMESPACE_ALIAS_HPP_INCLUDED

//
//  mvvm_mfc_example_3_namespace_alias.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

namespace go
{
namespace mvvm
{
namespace utility {}
}
namespace property
{
namespace nameless
{
namespace read_only {}
}
namespace read_only {}
}
namespace signals {}
namespace utility 
{
namespace string {}
}
}

namespace m = go::mvvm;
namespace mu = go::mvvm::utility;
namespace p = go::property;
namespace np = go::property::nameless;
namespace rop = go::property::read_only;
namespace nrop = go::property::nameless::read_only;
namespace s = go::signals;
namespace u = go::utility;
namespace us = go::utility::string;

namespace std
{
namespace placeholders {}
}

namespace ph = std::placeholders;

#endif  // #ifndef GO_MVVM_MFC_EXAMPLE_3_NAMESPACE_ALIAS_HPP_INCLUDED
