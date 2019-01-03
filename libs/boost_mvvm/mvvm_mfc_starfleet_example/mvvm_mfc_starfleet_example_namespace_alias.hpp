#ifndef GO_BOOST_MVVM_MFC_STARFLEET_EXAMPLE_NAMESPACE_ALIAS_HPP_INCLUDED
#define GO_BOOST_MVVM_MFC_STARFLEET_EXAMPLE_NAMESPACE_ALIAS_HPP_INCLUDED

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

namespace go_boost
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
namespace utility {}
}

namespace m = go_boost::mvvm;
namespace mu = go_boost::mvvm::utility;
namespace p = go_boost::property;
namespace np = go_boost::property::nameless;
namespace rop = go_boost::property::read_only;
namespace nrop = go_boost::property::nameless::read_only;
namespace s = go_boost::signals;
namespace u = go_boost::utility;

#endif  // #ifndef GO_BOOST_MVVM_MFC_STARFLEET_EXAMPLE_NAMESPACE_ALIAS_HPP_INCLUDED
