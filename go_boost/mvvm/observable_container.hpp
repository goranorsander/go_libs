#ifndef GO_BOOST_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED

//
//  observable_container.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/mvvm/notify_container_changed.hpp>
#include <go_boost/mvvm/observable_object.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class C> class basic_observable_container
    : public notify_container_changed
    , public basic_observable_object<S>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef basic_observable_container<string_type, container_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~basic_observable_container() = 0;

protected:
    basic_observable_container()
        : notify_container_changed()
        , basic_observable_object<string_type>()
    {
    }

protected:
    virtual void on_container_changed(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size)
    {
        if(!basic_observable_container<string_type, container_type>::container_changed.empty())
        {
            basic_observable_container<string_type, container_type>::container_changed(this->shared_from_this(), container_changed_arguments::create(action, added_elements, removed_elements, new_size));
        }
    }

    virtual void on_property_changed(const string_type& property_name)
    {
        basic_observable_object<string_type>::on_property_changed(property_name);
    }

    virtual container_type& container() = 0;

    virtual const container_type& container() const = 0;
};

template<class S, class C>
inline basic_observable_container<S, C>::~basic_observable_container()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED
