#ifndef GO_BOOST_MVVM_OBSERVABLE_ARRAY_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_ARRAY_HPP_INCLUDED

//
//  observable_array.hpp
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

#include <boost/container/static_vector.hpp>

#include <go_boost/mvvm/observable_sequence_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class T, class S, size_t N, class L = go_boost::utility::recursive_spin_lock>
class basic_observable_array
    : public basic_observable_sequence_container<S, boost::container::static_vector<T, N>, L>
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef typename boost::container::static_vector<T, N> container_type;
    typedef basic_observable_array<T, S, N, L> this_type;
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
    virtual ~basic_observable_array() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    basic_observable_array()
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container()
    {
        initialize_array();
    }

public:
    static ptr create()
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
                make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
        };

        return boost::make_shared<make_shared_enabler>();
#else
        return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
    }

public:
    GO_BOOST_CONSTEXPR const_reference operator[](size_type n) const
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
    reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.rbegin();
    }

    GO_BOOST_CONSTEXPR const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.rbegin();
    }

    reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.rend();
    }

    GO_BOOST_CONSTEXPR const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.rend();
    }

    GO_BOOST_CONSTEXPR const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.crbegin();
    }

    GO_BOOST_CONSTEXPR const_reverse_iterator crend() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.crend();
    }

    GO_BOOST_CONSTEXPR size_type size() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.size();
    }

    GO_BOOST_CONSTEXPR const_reference at(size_type n) const
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

    GO_BOOST_CONSTEXPR const_reference back() const
    {
        return _container.back();
    }

    pointer data() BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.data();
    }

    GO_BOOST_CONSTEXPR const_pointer data() const BOOST_NOEXCEPT_OR_NOTHROW
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

template<class T, size_t N, class L = go_boost::utility::recursive_spin_lock> class observable_array
    : public basic_observable_array<T, std::string, N, L>
{
public:
    typedef typename std::string string_type;
    typedef L lockable_type;
    typedef typename boost::container::static_vector<T, N> container_type;
    typedef observable_array<T, N, L> this_type;
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
    virtual ~observable_array() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
     observable_array()
        : basic_observable_array<T, string_type, N, lockable_type>()
    {
    }

public:
    static ptr create()
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
        };

        return boost::make_shared<make_shared_enabler>();
#else
        return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
    }
};

template<class T, size_t N, class L = go_boost::utility::recursive_spin_lock> class wobservable_array
    : public basic_observable_array<T, std::wstring, N, L>
{
public:
    typedef typename std::wstring string_type;
    typedef L lockable_type;
    typedef typename boost::container::static_vector<T, N> container_type;
    typedef wobservable_array<T, N, L> this_type;
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
    virtual ~wobservable_array() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
     wobservable_array()
        : basic_observable_array<T, string_type, N, lockable_type>()
    {
    }

public:
    static ptr create()
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
        };

        return boost::make_shared<make_shared_enabler>();
#else
        return boost::shared_ptr<this_type>(new this_type());
#endif // BOOST_MSVC > 1500
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_ARRAY_HPP_INCLUDED
