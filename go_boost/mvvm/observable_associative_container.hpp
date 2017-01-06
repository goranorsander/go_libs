#ifndef GO_BOOST_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

//
//  observable_associative_container.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/mvvm/notify_container_changed_interface.hpp>
#include <go_boost/mvvm/observable_container.hpp>

namespace go_boost
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
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

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
    iterator begin() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().begin();
    }

    const_iterator begin() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().begin();
    }

    iterator end() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().end();
    }

    const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().end();
    }

    const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().cbegin();
    }

    const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().cend();
    }

    size_type size() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().size();
    }

    size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().max_size();
    }

    bool empty() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().empty();
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

    template <class... Args>
    iterator emplace_hint(const_iterator position, Args&&... args)
    {
        const std::size_t before = this->container().size();
        const iterator it = this->container().emplace_hint(position, args...);
        const std::size_t after = this->container().size();
        this->notify_insert(before, after);
        return it;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

    void clear() BOOST_NOEXCEPT_OR_NOTHROW
    {
        const std::size_t before = this->container().size();
        this->container().clear();
        this->on_container_changed(notify_container_changed_action_reset, 0, before, this->container().size());
    }

    template<class t, class s>
    void swap(basic_observable_associative_container<t, s>& x)
    {
        const std::size_t this_before = this->container().size();
        const std::size_t x_before = x.container().size();
        this->container().swap(x.container());
        x.on_container_changed(notify_container_changed_action_swap, this_before, x_before, x.container().size());
        this->on_container_changed(notify_container_changed_action_swap, x_before, this_before, this->container().size());
    }

    size_type count(const value_type& val) const
    {
        return this->container().count(val);
    }

    const_iterator find(const value_type& val) const
    {
        return this->container().find(val);
    }

    iterator find(const value_type& val)
    {
        return this->container().find(val);
    }

    std::pair<const_iterator, const_iterator> equal_range(const value_type& val) const
    {
        return this->container().equal_range(val);
    }

    std::pair<iterator, iterator> equal_range(const value_type& val)
    {
        return this->container().equal_range(val);
    }

    allocator_type get_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().get_allocator();
    }

protected:
    void notify_insert(const std::size_t& before, const std::size_t& after)
    {
        if(after - before > 0)
        {
            this->on_container_changed(notify_container_changed_action_add, after - before, 0, after);
        }
    }

    void notify_erase(const std::size_t& before, const std::size_t& after)
    {
        if(before - after > 0)
        {
            this->on_container_changed(notify_container_changed_action_remove, 0, before - after, after);
        }
    }
};

template<class S, class C>
inline basic_observable_associative_container<S, C>::~basic_observable_associative_container()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
