#ifndef GO_BOOST_MVVM_OBSERVABLE_DEQUE_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_DEQUE_HPP_INCLUDED

//
//  observable_deque.hpp
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

#include <boost/container/deque.hpp>
#include <boost/make_shared.hpp>

#include <go_boost/mvvm/observable_sequence_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class T, class S, class L = go_boost::utility::recursive_spin_lock>
class basic_observable_deque
    : public basic_observable_sequence_container<S, boost::container::deque<T>, L>
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef typename boost::container::deque<T> container_type;
    typedef basic_observable_deque<T, S, L> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
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
    virtual ~basic_observable_deque() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    basic_observable_deque()
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container()
    {
    }

    explicit basic_observable_deque(size_type n)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(n)
    {
    }

    basic_observable_deque(size_type n, const value_type& val)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(n, val)
    {
    }

    template <class InputIterator>
    basic_observable_deque(InputIterator first, InputIterator last)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(first, last)
    {
    }

    explicit basic_observable_deque(const this_type& x)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(x._container)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit basic_observable_deque(this_type&& x)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(x._container)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    explicit basic_observable_deque(const std::initializer_list<value_type>& il)
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container(il)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

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

    static ptr create(size_type n)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(size_type n) : this_type(n) {}
        };

        return boost::make_shared<make_shared_enabler, size_type>(n);
#else
        return boost::shared_ptr<this_type>(new this_type(n));
#endif // BOOST_MSVC > 1500
    }

    static ptr create(size_type n, const value_type& val)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
                make_shared_enabler(size_type n, const value_type& val) : this_type(n, val) {}
        };

        return boost::make_shared<make_shared_enabler, size_type, const value_type&>(n, val);
#else
        return boost::shared_ptr<this_type>(new this_type(n, val));
#endif // BOOST_MSVC > 1500
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
                make_shared_enabler(InputIterator first, InputIterator last) : this_type(first, last) {}
        };

        return boost::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
#else
        return boost::shared_ptr<this_type>(new this_type(first, last));
#endif // BOOST_MSVC > 1500
    }

    static ptr create(const this_type& x)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(const this_type& x) : this_type(x) {}
        };

        return boost::make_shared<make_shared_enabler, const this_type&>(x);
#else
        return boost::shared_ptr<this_type>(new this_type(x));
#endif // BOOST_MSVC > 1500
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(this_type&& x) : this_type(x) {}
        };

        return boost::make_shared<make_shared_enabler, this_type&&>(x);
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    static ptr create(const std::initializer_list<value_type>& il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(const std::initializer_list<value_type>& il) : this_type(il) {}
        };

        return boost::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    this_type& operator=(const this_type& x) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_type& operator=(this_type&& x) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    this_type& operator=(const std::initializer_list<value_type>& il) BOOST_NOEXCEPT_OR_NOTHROW
    {
        _container.operator=(il);
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    GO_BOOST_CONSTEXPR const_reference operator[](size_type n) const
    {
        return _container.operator[](n);
    }

    reference operator[](size_type n)
    {
        return _container.operator[](n);
    }

protected:
    virtual container_type& container();

    virtual const container_type& container() const;

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

    GO_BOOST_CONSTEXPR size_type size() const BOOST_NOEXCEPT_OR_NOTHROW;

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

    void resize(size_type n)
    {
        _container.resize(n);
    }

    void resize(size_type n, const value_type& val)
    {
        _container.resize(n, val);
    }

    void shrink_to_fit()
    {
        _container.shrink_to_fit();
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        const std::size_t before = _container.size();
        _container.assign(first, last);
        const std::size_t after = _container.size();
        this->notify_assign(before, after);
    }

    void assign(size_type n, const value_type& val)
    {
        const std::size_t before = _container.size();
        _container.assign(n, val);
        const std::size_t after = _container.size();
        this->notify_assign(before, after);
    }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    void assign(const std::initializer_list<value_type>& il)
    {
        const std::size_t before = _container.size();
        _container.assign(il);
        const std::size_t after = _container.size();
        this->notify_assign(before, after);
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    void push_back(const value_type& val)
    {
        _container.push_back(val);
        this->notify_container_changed(notify_container_changed_action_add, 1, 0, _container.size());
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    void push_back(value_type&& val)
    {
        _container.push_back(val);
        this->notify_container_changed(notify_container_changed_action_add, 1, 0, _container.size());
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    void push_front(const value_type& val)
    {
        _container.push_front(val);
        this->notify_container_changed(notify_container_changed_action_add, 1, 0, _container.size());
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    void push_front(value_type&& val)
    {
        _container.push_front(val);
        this->notify_container_changed(notify_container_changed_action_add, 1, 0, _container.size());
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    void pop_back()
    {
        const std::size_t before = _container.size();
        _container.pop_back();
        const std::size_t after = _container.size();
        if(before > after)
        {
            this->notify_container_changed(notify_container_changed_action_remove, 0, before - after, _container.size());
        }
    }

    void pop_front()
    {
        const std::size_t before = _container.size();
        _container.pop_front();
        const std::size_t after = _container.size();
        if(before > after)
        {
            this->notify_container_changed(notify_container_changed_action_remove, 0, before - after, _container.size());
        }
    }

    iterator insert(iterator position, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    iterator insert(iterator position, size_type n, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, n, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    template <class InputIterator>
    iterator insert(iterator position, InputIterator first, InputIterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, first, last);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    iterator insert(iterator position, value_type&& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    iterator insert(iterator position, std::initializer_list<value_type> il)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, il);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    iterator erase(iterator position)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(position);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
        return it;
    }

    iterator erase(iterator first, iterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(first, last);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
        return it;
    }

    template<class t, class s, typename m>
    void swap(basic_observable_deque<t, s, m>& x)
    {
        const std::size_t this_before = _container.size();
        const std::size_t x_before = x._container.size();
        _container.swap(x._container);
        x.notify_container_changed(notify_container_changed_action_swap, this_before, x_before, x._container.size());
        this->notify_container_changed(notify_container_changed_action_swap, x_before, this_before, _container.size());
    }

    void clear() BOOST_NOEXCEPT_OR_NOTHROW
    {
        const std::size_t before = _container.size();
        _container.clear();
        this->notify_container_changed(notify_container_changed_action_reset, 0, before, 0);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

    template <class... Args>
    iterator emplace(const_iterator position, Args&&... args)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.emplace(position, args...);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    template <class... Args>
    void emplace_back(Args&&... args)
    {
        const std::size_t before = _container.size();
        _container.emplace_back(args...);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
    }

    template <class... Args>
    void emplace_front(Args&&... args)
    {
        const std::size_t before = _container.size();
        _container.emplace_front(args...);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

    GO_BOOST_CONSTEXPR allocator_type get_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
    {
        return _container.get_allocator();
    }

private:
    container_type _container;
};

template<class T, class S, class L>
inline GO_BOOST_CONSTEXPR typename basic_observable_deque<T, S, L>::size_type basic_observable_deque<T, S, L>::size() const BOOST_NOEXCEPT_OR_NOTHROW
{
    return _container.size();
}

template<class T, class S, class L>
inline typename basic_observable_deque<T, S, L>::container_type& basic_observable_deque<T, S, L>::container()
{
    return _container;
}

template<class T, class S, class L>
inline const typename basic_observable_deque<T, S, L>::container_type& basic_observable_deque<T, S, L>::container() const
{
    return _container;
}

template<class T, class L = go_boost::utility::recursive_spin_lock>
class observable_deque
    : public basic_observable_deque<T, std::string, L>
{
public:
    typedef typename std::string string_type;
    typedef L lockable_type;
    typedef typename boost::container::deque<T> container_type;
    typedef observable_deque<T, L> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
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
    virtual ~observable_deque() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
     observable_deque()
        : basic_observable_deque<value_type, string_type, lockable_type>()
    {
    }

    explicit observable_deque(size_type n)
        : basic_observable_deque<value_type, string_type, lockable_type>(n)
    {
    }

    observable_deque(size_type n, const value_type& val)
        : basic_observable_deque<value_type, string_type, lockable_type>(n, val)
    {
    }

    template <class InputIterator>
    observable_deque(InputIterator first, InputIterator last)
        : basic_observable_deque<value_type, string_type, lockable_type>(first, last)
    {
    }

    explicit observable_deque(const this_type& x)
        : basic_observable_deque<value_type, string_type, lockable_type>(x)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit observable_deque(this_type&& x)
        : basic_observable_deque<value_type, string_type, lockable_type>(x)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    explicit observable_deque(const std::initializer_list<value_type>& il)
        : basic_observable_deque<value_type, string_type, lockable_type>(il)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

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

    static ptr create(size_type n)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(size_type n) : this_type(n) {}
        };

        return boost::make_shared<make_shared_enabler, size_type>(n);
#else
        return boost::shared_ptr<this_type>(new this_type(n));
#endif // BOOST_MSVC > 1500
    }

    static ptr create(size_type n, const value_type& val)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler(size_type n, const value_type& val) : this_type(n, val) {}
        };

        return boost::make_shared<make_shared_enabler, size_type, const value_type&>(n, val);
#else
        return boost::shared_ptr<this_type>(new this_type(n, val));
#endif // BOOST_MSVC > 1500
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler(InputIterator first, InputIterator last) : this_type(first, last) {}
        };

        return boost::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
#else
        return boost::shared_ptr<this_type>(new this_type(first, last));
#endif // BOOST_MSVC > 1500
    }

    static ptr create(const this_type& x)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const this_type& x) : this_type(x) {}
        };

        return boost::make_shared<make_shared_enabler, const this_type&>(x);
#else
        return boost::shared_ptr<this_type>(new this_type(x));
#endif // BOOST_MSVC > 1500
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(this_type&& x) : this_type(x) {}
        };

        return boost::make_shared<make_shared_enabler, this_type&&>(x);
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    static ptr create(const std::initializer_list<value_type>& il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const std::initializer_list<value_type>& il) : this_type(il) {}
        };

        return boost::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    this_type& operator=(const this_type& x) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &x)
        {
            basic_observable_deque<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_type& operator=(this_type&& x) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &x)
        {
            basic_observable_deque<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    this_type& operator=(const std::initializer_list<value_type>& il) BOOST_NOEXCEPT_OR_NOTHROW
    {
        basic_observable_deque<value_type, string_type, lockable_type>::operator=(il);
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    template<class t, typename m>
    void swap(observable_deque<t, m>& x)
    {
        basic_observable_deque<t, string_type, m>::swap(dynamic_cast<basic_observable_deque<t, string_type, m>&>(x));
    }
};

template<class T, class L = go_boost::utility::recursive_spin_lock>
class wobservable_deque
    : public basic_observable_deque<T, std::wstring>
{
public:
    typedef typename std::wstring string_type;
    typedef L lockable_type;
    typedef typename boost::container::deque<T> container_type;
    typedef wobservable_deque<T> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::value_type value_type;
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
    virtual ~wobservable_deque() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
     wobservable_deque()
        : basic_observable_deque<value_type, string_type, lockable_type>()
    {
    }

    explicit wobservable_deque(size_type n)
        : basic_observable_deque<value_type, string_type, lockable_type>(n)
    {
    }

    wobservable_deque(size_type n, const value_type& val)
        : basic_observable_deque<value_type, string_type, lockable_type>(n, val)
    {
    }

    template <class InputIterator>
    wobservable_deque(InputIterator first, InputIterator last)
        : basic_observable_deque<value_type, string_type, lockable_type>(first, last)
    {
    }

    explicit wobservable_deque(const this_type& x)
        : basic_observable_deque<value_type, string_type, lockable_type>(x)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit wobservable_deque(this_type&& x)
        : basic_observable_deque<value_type, string_type, lockable_type>(x)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    explicit wobservable_deque(const std::initializer_list<value_type>& il)
        : basic_observable_deque<value_type, string_type, lockable_type>(il)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

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

    static ptr create(size_type n)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(size_type n) : this_type(n) {}
        };

        return boost::make_shared<make_shared_enabler, size_type>(n);
#else
        return boost::shared_ptr<this_type>(new this_type(n));
#endif // BOOST_MSVC > 1500
    }

    static ptr create(size_type n, const value_type& val)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler(size_type n, const value_type& val) : this_type(n, val) {}
        };

        return boost::make_shared<make_shared_enabler, size_type, const value_type&>(n, val);
#else
        return boost::shared_ptr<this_type>(new this_type(n, val));
#endif // BOOST_MSVC > 1500
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            make_shared_enabler(InputIterator first, InputIterator last) : this_type(first, last) {}
        };

        return boost::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
#else
        return boost::shared_ptr<this_type>(new this_type(first, last));
#endif // BOOST_MSVC > 1500
    }

    static ptr create(const this_type& x)
    {
#if BOOST_MSVC > 1500
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const this_type& x) : this_type(x) {}
        };

        return boost::make_shared<make_shared_enabler, const this_type&>(x);
#else
        return boost::shared_ptr<this_type>(new this_type(x));
#endif // BOOST_MSVC > 1500
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(this_type&& x) : this_type(x) {}
        };

        return boost::make_shared<make_shared_enabler, this_type&&>(x);
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    static ptr create(const std::initializer_list<value_type>& il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const std::initializer_list<value_type>& il) : this_type(il) {}
        };

        return boost::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    this_type& operator=(const this_type& x) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &x)
        {
            basic_observable_deque<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_type& operator=(this_type&& x) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &x)
        {
            basic_observable_deque<value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    this_type& operator=(const std::initializer_list<value_type>& il) BOOST_NOEXCEPT_OR_NOTHROW
    {
        basic_observable_deque<value_type, string_type, lockable_type>::operator=(il);
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    template<class t, typename m>
    void swap(wobservable_deque<t, m>& x)
    {
        basic_observable_deque<t, string_type, m>::swap(dynamic_cast<basic_observable_deque<t, string_type, m>&>(x));
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_DEQUE_HPP_INCLUDED
