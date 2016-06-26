#ifndef GO_BOOST_MVVM_OBSERVABLE_UNORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_UNORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

//
//  observable_unordered_associative_container.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <go_boost/mvvm/notify_container_changed.hpp>
#include <go_boost/mvvm/observable_associative_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class C> class basic_observable_unordered_associative_container
    : public basic_observable_associative_container<S, C>
{
public:
    typedef S string_type;
    typedef C container_type;
    typedef basic_observable_unordered_associative_container<string_type, container_type> this_type;
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
        : basic_observable_associative_container<string_type, container_type>()
    {
    }

public:
    key_equal key_eq() const
    {
        return _container.key_eq();
    }

    hasher hash_function() const
    {
        return _container.hash_function();
    }

    size_type bucket(const key_type& k) const
    {
        return _container.bucket(k);
    }

    size_type bucket_count() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.bucket_count();
    }

    size_type bucket_size(size_type n) const
    {
        return _container.bucket_size(n);
    }

    size_type max_bucket_count() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.max_bucket_count();
    }

    void rehash(size_type n)
    {
        _container.rehash(n);
    }

    float load_factor() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.load_factor();
    }

    float max_load_factor() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.max_load_factor();
    }

    void max_load_factor(float z)
    {
        _container.max_load_factor(z);
    }
};

template<class S, class C>
inline basic_observable_unordered_associative_container<S, C>::~basic_observable_unordered_associative_container()
{
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_UNORDERED_ASSOCIATIVE_CONTAINER_HPP_INCLUDED