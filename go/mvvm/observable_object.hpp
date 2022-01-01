#ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED

//
//  observable_object.hpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_CONCURRENCY_SUPPORT) || defined(GO_NO_CXX11_MUTEX) || defined(GO_NO_CXX11_VARIADIC_TEMPLATES)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <mutex>
#include <go/async/placebo_lockable.hpp>
#include <go/mvvm/notify_property_changed_interface.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_observable_object;
#if defined(GO_NO_CXX11_TYPE_ALIASES)
typedef basic_observable_object<std::string, std::recursive_mutex> observable_object;
typedef basic_observable_object<std::wstring, std::recursive_mutex> wobservable_object;
#else
using observable_object = basic_observable_object<std::string, std::recursive_mutex>;
using wobservable_object = basic_observable_object<std::wstring, std::recursive_mutex>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

namespace single_threaded
{

#if defined(GO_NO_CXX11_TYPE_ALIASES)
typedef basic_observable_object<std::string, go::async::placebo_lockable> observable_object;
typedef basic_observable_object<std::wstring, go::async::placebo_lockable> wobservable_object;
#else
using observable_object = basic_observable_object<std::string, go::async::placebo_lockable>;
using wobservable_object = basic_observable_object<std::wstring, go::async::placebo_lockable>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)

}

template<class S, class L = std::recursive_mutex>
class basic_observable_object
    : public basic_notify_property_changed_interface<S, L>
    , public object
{
public:
    GO_USING(string_type, S);
    GO_USING(lockable_type, L);
#if defined(GO_NO_CXX11_TYPE_ALIASES)
    typedef this_type basic_observable_object<S, L>;
#else
    using this_type = basic_observable_object<S, L>;
#endif  // #if defined(GO_NO_CXX11_TYPE_ALIASES)
    GO_USING(ptr, typename std::shared_ptr<this_type>);
    GO_USING(wptr, typename std::shared_ptr<this_type>);

public:
    virtual ~basic_observable_object() = 0;

protected:
    basic_observable_object() GO_DEFAULT_CONSTRUCTOR

    template<class T>
    T get_property_value(const T& value)
    {
        return value;
    }

    template<class P>
    void set_property_value(const P& prop, typename P::value_type& value, const typename P::value_type& new_value)
    {
        if (value != new_value)
        {
            value = new_value;
            this->notify_property_changed(this->shared_from_this(), prop.name());
        }
    }
};

template<class S, class L>
inline basic_observable_object<S, L>::~basic_observable_object()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_OBJECT_HPP_INCLUDED
