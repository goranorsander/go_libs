#ifndef GO_BOOST_MVVM_OBSERVABLE_UNORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_UNORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

//
//  observable_unordered_associative_container.hpp
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

#include <go_boost/mvvm/observable_associative_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class C, class L = boost::recursive_mutex>
class basic_observable_unordered_associative_container
    : public basic_observable_associative_container<S, C, L>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef L lockable_type;
    typedef basic_observable_unordered_associative_container<S, C, L> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::hasher hasher;
    typedef typename container_type::key_equal key_equal;
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
    virtual ~basic_observable_unordered_associative_container() = 0;

protected:
    basic_observable_unordered_associative_container()
        : basic_observable_associative_container<string_type, container_type, lockable_type>()
    {
    }

public:
    GO_BOOST_CONSTEXPR key_equal key_eq() const
    {
        return this->container().key_eq();
    }

    GO_BOOST_CONSTEXPR hasher hash_function() const
    {
        return this->container().hash_function();
    }

    GO_BOOST_CONSTEXPR size_type bucket(const key_type& k) const
    {
        return this->container().bucket(k);
    }

    GO_BOOST_CONSTEXPR size_type bucket_count() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().bucket_count();
    }

    GO_BOOST_CONSTEXPR size_type bucket_size(size_type n) const
    {
        return this->container().bucket_size(n);
    }

    GO_BOOST_CONSTEXPR size_type max_bucket_count() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().max_bucket_count();
    }

    void rehash(size_type n)
    {
        this->container().rehash(n);
    }

    GO_BOOST_CONSTEXPR float load_factor() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().load_factor();
    }

    GO_BOOST_CONSTEXPR float max_load_factor() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return this->container().max_load_factor();
    }

    void max_load_factor(float z)
    {
        this->container().max_load_factor(z);
    }
};

template<class S, class C, class L>
inline basic_observable_unordered_associative_container<S, C, L>::~basic_observable_unordered_associative_container()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_UNORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
