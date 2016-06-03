#ifndef GO_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

//
//  observable_associative_container.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/notify_container_changed.hpp>
#include <go/mvvm/observable_container.hpp>

namespace go
{
namespace mvvm
{

template<class S, class C> class basic_observable_associative_container
    : public basic_observable_container<S, C>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef basic_observable_associative_container<string_type, container_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::allocator_type allocator_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::pointer pointer;
    typedef typename container_type::const_pointer const_pointer;
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
    typedef typename container_type::difference_type difference_type;
    typedef typename container_type::size_type size_type;

public:
    virtual ~basic_observable_associative_container() = 0;

protected:
    basic_observable_associative_container()
        : basic_observable_container<string_type, container_type>()
    {
    }

public:
    iterator begin() noexcept
    {
        return container().begin();
    }

    const_iterator begin() const noexcept
    {
        return container().begin();
    }

    iterator end() noexcept
    {
        return container().end();
    }

    const_iterator end() const noexcept
    {
        return container().end();
    }

    const_iterator cbegin() const noexcept
    {
        return container().cbegin();
    }

    const_iterator cend() const noexcept
    {
        return container().cend();
    }

    size_type size() const noexcept
    {
        return container().size();
    }

    size_type max_size() const noexcept
    {
        return container().max_size();
    }

    bool empty() const noexcept
    {
        return container().empty();
    }

    template <class... Args>
    iterator emplace_hint(const_iterator position, Args&&... args)
    {
        const std::size_t before = container().size();
        const iterator it = container().emplace_hint(position, args...);
        const std::size_t after = container().size();
        notify_insert(before, after);
        return it;
    }

    void clear() noexcept
    {
        const std::size_t before = container().size();
        container().clear();
        on_container_changed(notify_container_changed_action_reset, 0, before, container().size());
    }

    template<class t, class s>
    void swap(basic_observable_associative_container<t, s>& x)
    {
        const std::size_t this_before = container().size();
        const std::size_t x_before = x.container().size();
        container().swap(x.container());
        x.on_container_changed(notify_container_changed_action_swap, this_before, x_before, x.container().size());
        on_container_changed(notify_container_changed_action_swap, x_before, this_before, container().size());
    }

    size_type count(const value_type& val) const
    {
        return container().count(val);
    }
	
    const_iterator find(const value_type& val) const
    {
        return container().find(val);
    }

    iterator find(const value_type& val)
    {
        return container().find(val);
    }

    std::pair<const_iterator, const_iterator> equal_range(const value_type& val) const
    {
        return container().equal_range(val);
    }

    std::pair<iterator, iterator> equal_range(const value_type& val)
    {
        return container().equal_range(val);
    }

    allocator_type get_allocator() const noexcept
    {
        return container().get_allocator();
    }

protected:
    void notify_insert(const std::size_t& before, const std::size_t& after)
    {
        if(after - before > 0)
        {
            on_container_changed(notify_container_changed_action_add, after - before, 0, after);
        }
    }

    void notify_erase(const std::size_t& before, const std::size_t& after)
    {
        if(before - after > 0)
        {
            on_container_changed(notify_container_changed_action_remove, 0, before - after, after);
        }
    }
};

template<class S, class C>
inline basic_observable_associative_container<S, C>::~basic_observable_associative_container()
{
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
