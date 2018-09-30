#ifndef GO_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED

//
//  observable_container.hpp
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

#include <go/mvvm/notify_container_changed_interface.hpp>
#include <go/mvvm/observable_object.hpp>

namespace go
{
namespace mvvm
{

template<class S, class C> class basic_observable_container
    : public notify_container_changed_interface
    , public basic_observable_object<S>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef basic_observable_container<string_type, container_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~basic_observable_container() = 0;

protected:
    basic_observable_container()
        : notify_container_changed_interface()
        , basic_observable_object<string_type>()
    {
    }

protected:
    virtual void notify_container_changed(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size)
    {
        if(!this_type::container_changed.empty())
        {
            this_type::container_changed(this_type::shared_from_this(), container_changed_arguments::create(action, added_elements, removed_elements, new_size));
        }
    }

    virtual void notify_property_changed(const string_type& property_name)
    {
        basic_observable_object<string_type>::notify_property_changed(property_name);
    }

    virtual container_type& container() = 0;

    virtual const container_type& container() const = 0;
};

template<class S, class C>
inline basic_observable_container<S, C>::~basic_observable_container()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED
