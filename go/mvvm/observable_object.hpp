#ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED

//
//  observable_object.hpp
//
//  Copyright 2015-2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/notify_property_changed_interface.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_observable_object;
typedef basic_observable_object<std::string, go::utility::recursive_spin_lock> observable_object;
typedef basic_observable_object<std::wstring, go::utility::recursive_spin_lock> wobservable_object;

namespace single_threaded
{

typedef basic_observable_object<std::string, go::utility::placebo_lockable> observable_object;
typedef basic_observable_object<std::wstring, go::utility::placebo_lockable> wobservable_object;

}

template<class S, class L = go::utility::recursive_spin_lock>
class basic_observable_object
    : public basic_notify_property_changed_interface<S, L>
    , public object
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_observable_object<S, L> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~basic_observable_object() = 0;

protected:
    basic_observable_object() GO_DEFAULT_CONSTRUCTOR
};

template<class S, class L>
inline basic_observable_object<S, L>::~basic_observable_object()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
