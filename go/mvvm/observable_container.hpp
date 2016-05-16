#ifndef GO_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED

//
//  observable_container.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/mvvm/notify_container_changed.hpp>
#include <go/mvvm/observable_object.hpp>

namespace go
{
namespace mvvm
{

template<class S, class C> class basic_observable_container
    : public notify_container_changed
    , public basic_observable_object<S>
{
public:
    typedef typename S string_type;
    typedef typename C container_type;
    typedef typename basic_observable_container<string_type, container_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~basic_observable_container() = 0;

protected:
    basic_observable_container()
        : notify_container_changed()
        , basic_observable_object<string_type>()
    {
    }

protected:
    virtual void on_container_changed(const notify_container_changed_action& /*action*/, const std::size_t& /*added_elements*/, const std::size_t& /*removed_elements*/, const std::size_t& /*new_size*/) = 0;

    virtual container_type& container() = 0;

    virtual const container_type& container() const = 0;
};

template<class S, class C>
inline basic_observable_container<S, C>::~basic_observable_container()
{
}

template<class S, class C>
inline void basic_observable_container<S, C>::on_container_changed(const notify_container_changed_action& /*action*/, const std::size_t& /*added_elements*/, const std::size_t& /*removed_elements*/, const std::size_t& /*new_size*/)
{
}

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED
