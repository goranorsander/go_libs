#ifndef GO_BOOST_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

//
//  observable_associative_container.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/observable_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class C, class L = boost::recursive_mutex>
class basic_observable_associative_container
    : public basic_observable_container<S, C, L>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef L lockable_type;
    typedef basic_observable_associative_container<string_type, container_type, lockable_type> this_type;
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
        : basic_observable_container<string_type, container_type, lockable_type>()
    {
    }

public:
    iterator begin() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().begin();
    }

    GO_BOOST_CONSTEXPR const_iterator begin() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().begin();
    }

    iterator end() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().end();
    }

    GO_BOOST_CONSTEXPR const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().end();
    }

    GO_BOOST_CONSTEXPR const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().cbegin();
    }

    GO_BOOST_CONSTEXPR const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().cend();
    }

    GO_BOOST_CONSTEXPR size_type size() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().size();
    }

    GO_BOOST_CONSTEXPR size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().max_size();
    }

    GO_BOOST_CONSTEXPR bool empty() const BOOST_NOEXCEPT_OR_NOTHROW
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
        this->notify_container_changed(notify_container_changed_action_reset, 0, before, 0);
    }

    template<class t, class s, typename m>
    void swap(basic_observable_associative_container<t, s, m>& x)
    {
        const std::size_t this_before = this->container().size();
        const std::size_t x_before = x.container().size();
        this->container().swap(x.container());
        x.notify_container_changed(notify_container_changed_action_swap, this_before, x_before, x.container().size());
        this->notify_container_changed(notify_container_changed_action_swap, x_before, this_before, this->container().size());
    }

    GO_BOOST_CONSTEXPR size_type count(const value_type& val) const
    {
        return this->container().count(val);
    }

    GO_BOOST_CONSTEXPR const_iterator find(const value_type& val) const
    {
        return this->container().find(val);
    }

    iterator find(const value_type& val)
    {
        return this->container().find(val);
    }

    GO_BOOST_CONSTEXPR std::pair<const_iterator, const_iterator> equal_range(const value_type& val) const
    {
        return this->container().equal_range(val);
    }

    std::pair<iterator, iterator> equal_range(const value_type& val)
    {
        return this->container().equal_range(val);
    }

    GO_BOOST_CONSTEXPR allocator_type get_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().get_allocator();
    }

protected:
    void notify_insert(const std::size_t& before, const std::size_t& after)
    {
        if(after - before > 0)
        {
            this->notify_container_changed(notify_container_changed_action_add, after - before, 0, after);
        }
    }

    void notify_erase(const std::size_t& before, const std::size_t& after)
    {
        if(before - after > 0)
        {
            this->notify_container_changed(notify_container_changed_action_remove, 0, before - after, after);
        }
    }
};

template<class S, class C, class L>
inline basic_observable_associative_container<S, C, L>::~basic_observable_associative_container()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
