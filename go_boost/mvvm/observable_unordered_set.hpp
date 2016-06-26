#ifndef GO_BOOST_MVVM_OBSERVABLE_UNORDERED_SET_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_UNORDERED_SET_HPP_INCLUDED

//
//  observable_unordered_set.hpp
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

#include <boost/unordered_set.hpp>

#include <go_boost/mvvm/notify_container_changed.hpp>
#include <go_boost/mvvm/observable_unordered_associative_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class K, class S> class basic_observable_unordered_set
    : public basic_observable_unordered_associative_container<S, boost::unordered_set<K>>
{
public:
    typedef S string_type;
    typedef typename boost::unordered_set<K> container_type;
    typedef basic_observable_unordered_set<string_type, container_type> this_type;
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
    virtual ~basic_observable_unordered_set()
    {
    }

protected:
    basic_observable_unordered_set()
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container()
    {
    }

    template <class InputIterator>
    basic_observable_unordered_set(InputIterator first, InputIterator last)
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container(first, last)
    {
    }

    basic_observable_unordered_set(const this_type& x)
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container(x._container)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    basic_observable_unordered_set(this_type&& x)
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container(x._container)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    basic_observable_unordered_set(std::initializer_list<value_type> il)
        : basic_observable_unordered_associative_container<string_type, container_type>()
        , _container(il)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

public:

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

    template <class... Args>
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        const std::size_t before = _container.size();
        const std::pair<iterator, bool> p = _container.emplace(args...);
        if(p.second)
        {
            const std::size_t after = _container.size();
            notify_insert(before, after);
        }
        return p;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

    std::pair<iterator, bool> insert(const value_type& val)
    {
        const std::size_t before = _container.size();
        const std::pair<iterator, bool> p = _container.insert(val);
        if(p.second)
        {
            const std::size_t after = _container.size();
            notify_insert(before, after);
        }
        return p;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    std::pair<iterator, bool> insert(value_type&& val)
    {
        const std::size_t before = _container.size();
        const std::pair<iterator, bool> p = _container.insert(val);
        if(p.second)
        {
            const std::size_t after = _container.size();
            notify_insert(before, after);
        }
        return p;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    iterator insert(const_iterator position, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    iterator insert(const_iterator position, value_type&& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        const std::size_t before = _container.size();
        _container.insert(first, last);
        const std::size_t after = _container.size();
        notify_insert(before, after);
    }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    void insert(std::initializer_list<value_type> il)
    {
        const std::size_t before = _container.size();
        _container.insert(il);
        const std::size_t after = _container.size();
        notify_insert(before, after);
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    iterator erase(const_iterator position)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(position);
        const std::size_t after = _container.size();
        notify_erase(before, after);
        return it;
    }

    size_type erase(const value_type& val)
    {
        const std::size_t before = _container.size();
        const size_type s = _container.erase(val);
        if(s > 0)
        {
            const std::size_t after = _container.size();
            notify_erase(before, after);
        }
        return s;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(first, last);
        const std::size_t after = _container.size();
        notify_erase(before, after);
        return it;
    }

protected:
    virtual container_type& container();

    virtual const container_type& container() const;

private:
    container_type _container;
};

template<class K, class S>
inline typename basic_observable_unordered_set<K, S>::container_type& basic_observable_unordered_set<K, S>::container()
{
    return _container;
}

template<class K, class S>
inline const typename basic_observable_unordered_set<K, S>::container_type& basic_observable_unordered_set<K, S>::container() const
{
    return _container;
}

template<class K> class observable_unordered_set
    : public basic_observable_unordered_set<K, std::string>
{
public:
    typedef std::string string_type;
    typedef typename boost::unordered_set<K> container_type;
    typedef observable_unordered_set<K> this_type;
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
    virtual ~observable_unordered_set()
    {
    }

protected:
    observable_unordered_set()
        : basic_observable_unordered_set<value_type, string_type>()
    {
    }

    template <class InputIterator>
    observable_unordered_set(InputIterator first, InputIterator last)
        : basic_observable_unordered_set<value_type, string_type>(first, last)
    {
    }

    observable_unordered_set(const this_type& x)
        : basic_observable_unordered_set<value_type, string_type>(x)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    observable_unordered_set(this_type&& x)
        : basic_observable_unordered_set<value_type, string_type>(x)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    observable_unordered_set(std::initializer_list<value_type> il)
        : basic_observable_unordered_set<value_type, string_type>(il)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    static ptr create()
    {
        return ptr(new this_type);
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        return ptr(new this_type(first, last));
    }

    static ptr create(const this_type& x)
    {
        return ptr(new this_type(x));
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    static ptr create(this_type&& x)
    {
        return ptr(new this_type(x));
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    static ptr create(std::initializer_list<value_type> il)
    {
        return ptr(new this_type(il));
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            basic_observable_unordered_set<value_type, string_type>::operator=(x);
        }
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            basic_observable_unordered_set<value_type, string_type>::operator=(x);
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    this_type& operator=(std::initializer_list<value_type> il)
    {
        container().operator=(il);
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    template<class k>
    void swap(observable_unordered_set<k>& x)
    {
        basic_observable_unordered_set<k, string_type>::swap(dynamic_cast<basic_observable_unordered_set<k, string_type>&>(x));
    }
};

template<class K> class wobservable_unordered_set
    : public basic_observable_unordered_set<K, std::wstring>
{
public:
    typedef std::wstring string_type;
    typedef typename boost::unordered_set<K> container_type;
    typedef wobservable_unordered_set<K> this_type;
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
    virtual ~wobservable_unordered_set()
    {
    }

protected:
    wobservable_unordered_set()
        : basic_observable_unordered_set<value_type, string_type>()
    {
    }

    template <class InputIterator>
    wobservable_unordered_set(InputIterator first, InputIterator last)
        : basic_observable_unordered_set<value_type, string_type>(first, last)
    {
    }

    wobservable_unordered_set(const this_type& x)
        : basic_observable_unordered_set<value_type, string_type>(x)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    wobservable_unordered_set(this_type&& x)
        : basic_observable_unordered_set<value_type, string_type>(x)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    wobservable_unordered_set(std::initializer_list<value_type> il)
        : basic_observable_unordered_set<value_type, string_type>(il)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    static ptr create()
    {
        return ptr(new this_type);
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        return ptr(new this_type(first, last));
    }

    static ptr create(const this_type& x)
    {
        return ptr(new this_type(x));
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    static ptr create(this_type&& x)
    {
        return ptr(new this_type(x));
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    static ptr create(std::initializer_list<value_type> il)
    {
        return ptr(new this_type(il));
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            basic_observable_unordered_set<value_type, string_type>::operator=(x);
        }
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            basic_observable_unordered_set<value_type, string_type>::operator=(x);
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    this_type& operator=(std::initializer_list<value_type> il)
    {
        container().operator=(il);
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    template<class k>
    void swap(wobservable_unordered_set<k>& x)
    {
        basic_observable_unordered_set<k, string_type>::swap(dynamic_cast<basic_observable_unordered_set<k, string_type>&>(x));
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_UNORDERED_SET_HPP_INCLUDED