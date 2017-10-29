#ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED

//
//  observable_object.hpp
//
//  Copyright 2015-2017 Göran Orsander
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
    basic_observable_object() GO_DEFAULT_CONSTRUCTOR

protected:
    virtual void on_property_changed(const string_type& property_name)
    {
        if(!basic_notify_property_changed_interface<string_type>::property_changed.empty())
        {
            basic_notify_property_changed_interface<string_type>::property_changed(shared_from_this(), basic_property_changed_arguments<string_type>::create(property_name));
        }
    }
};

template<class S>
inline basic_observable_object<S>::~basic_observable_object()
{
}

class observable_object
    : public basic_observable_object<std::string>
{
public:
    typedef observable_object this_type;

public:
    virtual ~observable_object() = 0;

protected:
    observable_object() GO_DEFAULT_CONSTRUCTOR
};

inline observable_object::~observable_object()
{
}

class wobservable_object
    : public basic_observable_object<std::wstring>
{
public:
    typedef wobservable_object this_type;

public:
    virtual ~wobservable_object() = 0;

protected:
    wobservable_object() GO_DEFAULT_CONSTRUCTOR
};

inline wobservable_object::~wobservable_object()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
