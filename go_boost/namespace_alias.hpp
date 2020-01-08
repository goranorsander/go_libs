#ifndef GO_BOOST_NAMESPACE_ALIAS_HPP_INCLUDED
#define GO_BOOST_NAMESPACE_ALIAS_HPP_INCLUDED

//
//  namespace_alias.hpp
//
//  Copyright 2019-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

namespace go_boost
{
namespace async {}
namespace diagnostics
{
namespace benchmark {}
namespace log {}
}
namespace exception {}
namespace mvvm
{
namespace iterator {}
namespace single_threaded {}
namespace utility
{
namespace single_threaded {}
}
}
namespace property
{
namespace nameless
{
namespace read_only {}
namespace write_only {}
}
namespace policy {}
namespace read_only {}
namespace write_only {}
}
namespace signals {}
namespace type_traits {}
namespace utility
{
namespace container {}
namespace iterator {}
namespace range {}
namespace string {}
}
}

namespace a = go_boost::async;
namespace d = go_boost::diagnostics;
namespace db = go_boost::diagnostics::benchmark;
namespace dl = go_boost::diagnostics::log;
namespace e = go_boost::exception;
namespace m = go_boost::mvvm;
namespace mi = go_boost::mvvm::iterator;
namespace mst = go_boost::mvvm::single_threaded;
namespace mu = go_boost::mvvm::utility;
namespace must = go_boost::mvvm::utility::single_threaded;
namespace p = go_boost::property;
namespace pn = go_boost::property::nameless;
namespace pnro = go_boost::property::nameless::read_only;
namespace pnwo = go_boost::property::nameless::write_only;
namespace pro = go_boost::property::read_only;
namespace pwo = go_boost::property::write_only;
namespace s = go_boost::signals;
namespace tt = go_boost::type_traits;
namespace u = go_boost::utility;
namespace uc = go_boost::utility::container;
namespace ui = go_boost::utility::iterator;
namespace ur = go_boost::utility::range;
namespace us = go_boost::utility::string;

namespace boost
{
namespace phoenix
{
namespace placeholders {}
}
}

namespace bp = boost::phoenix;
namespace bph = boost::phoenix::placeholders;

#endif  // #ifndef GO_BOOST_NAMESPACE_ALIAS_HPP_INCLUDED
