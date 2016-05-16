#ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED

//
//  observable_object.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/mvvm/notify_property_changed.hpp>

namespace go
{
namespace mvvm
{

template<class S>
class basic_observable_object
    : public basic_notify_property_changed<S>
    , public object
{
public:
    typedef typename S string_type;
    typedef typename basic_observable_object<string_type> this_type;

public:
    virtual ~basic_observable_object()
    {
    }

protected:
    basic_observable_object()
        : basic_notify_property_changed<string_type>()
        , object()
    {
    }

protected:
    virtual void on_property_changed(const string_type& property_name)
    {
        if(!basic_notify_property_changed<string_type>::property_changed.empty())
        {
            basic_notify_property_changed<string_type>::property_changed(shared_from_this(), basic_property_changed_arguments<string_type>::create(property_name));
        }
    }
};

class observable_object
    : public basic_observable_object<std::string>
{
public:
    typedef typename observable_object this_type;

public:
    virtual ~observable_object()
    {
    }

protected:
    observable_object()
        : basic_observable_object<string_type>()
    {
    }
};

class wobservable_object
    : public basic_observable_object<std::wstring>
{
public:
    typedef typename wobservable_object this_type;

public:
    virtual ~wobservable_object()
    {
    }

protected:
    wobservable_object()
        : basic_observable_object<string_type>()
    {
    }
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
