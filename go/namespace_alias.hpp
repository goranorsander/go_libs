#ifndef GO_NAMESPACE_ALIAS_HPP_INCLUDED
#define GO_NAMESPACE_ALIAS_HPP_INCLUDED

//
//  namespace_alias.hpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

namespace go
{
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

namespace d = go::diagnostics;
namespace db = go::diagnostics::benchmark;
namespace dl = go::diagnostics::log;
namespace e = go::exception;
namespace m = go::mvvm;
namespace mi = go::mvvm::iterator;
namespace mst = go::mvvm::single_threaded;
namespace mu = go::mvvm::utility;
namespace must = go::mvvm::utility::single_threaded;
namespace p = go::property;
namespace pn = go::property::nameless;
namespace pnro = go::property::nameless::read_only;
namespace pnwo = go::property::nameless::write_only;
namespace pro = go::property::read_only;
namespace pwo = go::property::write_only;
namespace s = go::signals;
namespace tt = go::type_traits;
namespace u = go::utility;
namespace uc = go::utility::container;
namespace ui = go::utility::iterator;
namespace ur = go::utility::range;
namespace us = go::utility::string;

namespace std
{
namespace placeholders {}
}

namespace ph = std::placeholders;

#endif  // #ifndef GO_NAMESPACE_ALIAS_HPP_INCLUDED
