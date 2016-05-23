#ifndef GO_BOOST_MVVM_OBSERVABLE_ARRAY_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_ARRAY_HPP_INCLUDED

//
//  observable_array.hpp
//
//  Copyright 2015-2016 Göran Orsander
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

#include <boost/container/static_vector.hpp>

#include <go_boost/mvvm/notify_container_changed.hpp>
#include <go_boost/mvvm/observable_sequence_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class T, class S, size_t N> class basic_observable_array
    : public basic_observable_sequence_container<S, boost::container::static_vector<T, N>>
{
public:
    typedef S string_type;
    typedef typename boost::container::static_vector<T, N> container_type;
    typedef basic_observable_array<string_type, container_type, N> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
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
    virtual ~basic_observable_array()
    {
    }

protected:
    basic_observable_array()
        : basic_observable_sequence_container<string_type, container_type>()
        , _container()
    {
        initialize_array();
    }

public:
    const_reference operator[](size_type n) const
    {
        return _container.operator[](n);
    }

    reference operator[](size_type n)
    {
        return _container.operator[](n);
    }

protected:
    virtual void on_container_changed(const notify_container_changed_action& /*action*/, const std::size_t& /*added_elements*/, const std::size_t& /*removed_elements*/, const std::size_t& /*new_size*/)
    {
    }

    virtual container_type& container()
    {
        return _container;
    }

    virtual const container_type& container() const
    {
        return _container;
    }

public:
    reverse_iterator rbegin()
    {
        return _container.rbegin();
    }

    const_reverse_iterator rbegin() const
    {
        return _container.rbegin();
    }

    reverse_iterator rend()
    {
        return _container.rend();
    }

    const_reverse_iterator rend() const
    {
        return _container.rend();
    }

    const_reverse_iterator crbegin() const
    {
        return _container.crbegin();
    }

    const_reverse_iterator crend() const
    {
        return _container.crend();
    }

    size_type size() const
    {
        return _container.size();
    }

    const_reference at(size_type n) const
    {
        return _container.at(n);
    }

    reference at(size_type n)
    {
        return _container.at(n);
    }

    reference back()
    {
        return _container.back();
    }

    const_reference back() const
    {
        return _container.back();
    }

    pointer data()
    {
        return _container.data();
    }

    const_pointer data() const
    {
        return _container.data();
    }

protected:
    virtual void initialize_array()
    {
        const std::size_t s = _container.max_size();
        for(size_type i = 0; i < s; i++)
        {
            _container.push_back(value_type());
        }
    }

private:
    container_type _container;
};

template<class T, size_t N> class observable_array
    : public basic_observable_array<T, std::string, N>
{
public:
    typedef typename std::string string_type;
    typedef typename boost::container::static_vector<T, N> container_type;
    typedef observable_array<T, N> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
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
    virtual ~observable_array()
    {
    }

protected:
    observable_array()
        : basic_observable_array<T, string_type, N>()
    {
    }

public:
    static ptr create()
    {
        return ptr(new observable_array);
    }
};

template<class T, size_t N> class wobservable_array
    : public basic_observable_array<T, std::wstring, N>
{
public:
    typedef typename std::wstring string_type;
    typedef typename boost::container::static_vector<T, N> container_type;
    typedef wobservable_array<T, N> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
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
    virtual ~wobservable_array()
    {
    }

protected:
    wobservable_array()
        : basic_observable_array<T, string_type, N>()
    {
    }

public:
    static ptr create()
    {
        return ptr(new wobservable_array);
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_ARRAY_HPP_INCLUDED
