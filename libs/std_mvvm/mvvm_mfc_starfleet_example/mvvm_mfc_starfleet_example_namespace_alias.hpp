#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_NAMESPACE_ALIAS_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_NAMESPACE_ALIAS_HPP_INCLUDED

//
//  mvvm_mfc_starfleet_example_namespace_alias.hpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

namespace go
{
namespace mvvm
{
namespace single_threaded {}
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

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_NAMESPACE_ALIAS_HPP_INCLUDED
