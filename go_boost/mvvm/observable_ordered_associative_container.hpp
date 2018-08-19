#ifndef GO_BOOST_MVVM_OBSERVABLE_ORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_ORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

//
//  observable_ordered_associative_container.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/notify_container_changed_interface.hpp>
#include <go_boost/mvvm/observable_associative_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class C> class basic_observable_ordered_associative_container
    : public basic_observable_associative_container<S, C>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef basic_observable_ordered_associative_container<string_type, container_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::key_compare key_compare;
    typedef typename container_type::value_compare value_compare;
    typedef typename container_type::allocator_type allocator_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::pointer pointer;
    typedef typename container_type::const_pointer const_pointer;
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
    typedef typename container_type::reverse_iterator reverse_iterator;
    typedef typename container_type::const_reverse_iterator const_reverse_iterator;
    typedef typename container_type::difference_type difference_type;
    typedef typename container_type::size_type size_type;

public:
    virtual ~basic_observable_ordered_associative_container() = 0;

protected:
    basic_observable_ordered_associative_container()
        : basic_observable_associative_container<string_type, container_type>()
    {
    }

public:
    reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().rbegin();
    }

    GO_BOOST_CONSTEXPR const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().rbegin();
    }

    reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().rend();
    }

    GO_BOOST_CONSTEXPR const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().rend();
    }

    GO_BOOST_CONSTEXPR const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().crbegin();
    }

    GO_BOOST_CONSTEXPR const_reverse_iterator crend() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().crend();
    }

    iterator lower_bound(const value_type& val)
    {
        return this->container().lower_bound(val);
    }

    GO_BOOST_CONSTEXPR const_iterator lower_bound(const value_type& val) const
    {
        return this->container().lower_bound(val);
    }

    iterator upper_bound(const value_type& val)
    {
        return this->container().upper_bound(val);
    }

    GO_BOOST_CONSTEXPR const_iterator upper_bound(const value_type& val) const
    {
        return this->container().upper_bound(val);
    }

    GO_BOOST_CONSTEXPR key_compare key_comp() const
    {
        return this->container().key_comp();
    }

    GO_BOOST_CONSTEXPR value_compare value_comp() const
    {
        return this->container().key_comp();
    }
};

template<class S, class C>
inline basic_observable_ordered_associative_container<S, C>::~basic_observable_ordered_associative_container()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_ORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
