#ifndef GO_BOOST_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED

//
//  observable_object.hpp
//
//  Copyright 2015-2019 G�ran Orsander
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

template<class S, class L>
class basic_observable_object;
typedef basic_observable_object<std::string, boost::recursive_mutex> observable_object;
typedef basic_observable_object<std::wstring, boost::recursive_mutex> wobservable_object;

namespace single_threaded
{

typedef basic_observable_object<std::string, go_boost::utility::placebo_lockable> observable_object;
typedef basic_observable_object<std::wstring, go_boost::utility::placebo_lockable> wobservable_object;

}

template<class S, class L = boost::recursive_mutex>
class basic_observable_object
    : public basic_notify_property_changed_interface<S, L>
    , public object
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_observable_object<S, L> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~basic_observable_object() = 0;

protected:
    basic_observable_object() GO_BOOST_DEFAULT_CONSTRUCTOR
};

template<class S, class L>
inline basic_observable_object<S, L>::~basic_observable_object()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
