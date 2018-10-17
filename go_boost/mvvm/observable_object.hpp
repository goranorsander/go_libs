#ifndef GO_BOOST_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED

//
//  observable_object.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/notify_property_changed_interface.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S>
class basic_observable_object;
typedef basic_observable_object<std::string> observable_object;
typedef basic_observable_object<std::wstring> wobservable_object;

template<class S>
class basic_observable_object
    : public basic_notify_property_changed_interface<S>
    , public object
{
public:
    typedef S string_type;
    typedef basic_observable_object<string_type> this_type;

public:
    virtual ~basic_observable_object() = 0;

protected:
    basic_observable_object() GO_BOOST_DEFAULT_CONSTRUCTOR
};

template<class S>
inline basic_observable_object<S>::~basic_observable_object()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
