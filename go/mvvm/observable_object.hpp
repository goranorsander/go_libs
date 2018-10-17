#ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED

//
//  observable_object.hpp
//
//  Copyright 2015-2018 Göran Orsander
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
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~basic_observable_object() = 0;

protected:
    basic_observable_object() GO_DEFAULT_CONSTRUCTOR
};

template<class S>
inline basic_observable_object<S>::~basic_observable_object()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
