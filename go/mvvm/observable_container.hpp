#ifndef GO_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED

//
//  observable_container.hpp
//
//  Copyright 2015-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/notify_container_changed_interface.hpp>
#include <go/mvvm/observable_object.hpp>

namespace go
{
namespace mvvm
{

template<class S, class C, class L = std::recursive_mutex>
class basic_observable_container
    : public notify_container_changed_interface<L>
    , public basic_observable_object<S, L>
{
public:
    using string_type = S;
    using container_type = C;
    using lockable_type = L;
    using this_type = basic_observable_container<string_type, container_type, lockable_type>;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

public:
    virtual ~basic_observable_container() = 0;

protected:
    basic_observable_container()
        : notify_container_changed_interface<lockable_type>()
        , basic_observable_object<string_type, lockable_type>()
    {
    }

protected:
    virtual void notify_container_changed(const notify_container_changed_action& action, const std::size_t& added_elements, const std::size_t& removed_elements, const std::size_t& new_size) override
    {
        if(!this_type::container_changed.empty())
        {
            this_type::container_changed(this->shared_from_this(), container_changed_arguments::create(action, added_elements, removed_elements, new_size));
        }
    }

    virtual container_type& container() = 0;

    virtual const container_type& container() const = 0;
};

template<class S, class C, class L>
inline basic_observable_container<S, C, L>::~basic_observable_container()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_CONTAINER_HPP_INCLUDED
