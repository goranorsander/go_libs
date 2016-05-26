#ifndef GO_BOOST_MVVM_OBSERVABLE_DEQUE_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_DEQUE_HPP_INCLUDED

//
//  observable_deque.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/container/deque.hpp>

#include <go_boost/mvvm/notify_container_changed.hpp>
#include <go_boost/mvvm/observable_sequence_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class T, class S> class basic_observable_deque
    : public basic_observable_sequence_container<S, boost::container::deque<T>>
{
public:
    typedef S string_type;
    typedef typename boost::container::deque<T> container_type;
    typedef basic_observable_deque<string_type, container_type> this_type;
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
    virtual ~basic_observable_deque()
    {
    }

protected:
    basic_observable_deque()
        : basic_observable_sequence_container<string_type, container_type>()
        , _container()
    {
    }

    explicit basic_observable_deque(size_type n)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(n)
    {
    }

    basic_observable_deque(size_type n, const value_type& val)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(n, val)
    {
    }

    template <class InputIterator>
    basic_observable_deque(InputIterator first, InputIterator last)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(first, last)
    {
    }

    basic_observable_deque(const basic_observable_deque& x)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(x._container)
    {
    }

public:
    basic_observable_deque& operator=(const basic_observable_deque& x)
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

    const_reference operator[](size_type n) const
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

    size_type size() const;

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
        notify_assign(before, after);
    }

    void assign(size_type n, const value_type& val)
    {
        const std::size_t before = _container.size();
        _container.assign(n, val);
        const std::size_t after = _container.size();
        notify_assign(before, after);
    }

    void push_back(const value_type& val)
    {
        _container.push_back(val);
        on_container_changed(notify_container_changed_action_add, 1, 0, _container.size());
    }

    void push_front(const value_type& val)
    {
        _container.push_front(val);
        on_container_changed(notify_container_changed_action_add, 1, 0, _container.size());
    }

    void pop_back()
    {
        const std::size_t before = _container.size();
        _container.pop_back();
        const std::size_t after = _container.size();
        if(before > after)
        {
            on_container_changed(notify_container_changed_action_remove, 0, before - after, _container.size());
        }
    }

    void pop_front()
    {
        const std::size_t before = _container.size();
        _container.pop_front();
        const std::size_t after = _container.size();
        if(before > after)
        {
            on_container_changed(notify_container_changed_action_remove, 0, before - after, _container.size());
        }
    }

    iterator insert(iterator position, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

    iterator insert(iterator position, size_type n, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, n, val);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

    template <class InputIterator>
    iterator insert(iterator position, InputIterator first, InputIterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, first, last);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

    iterator erase(iterator position)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(position);
        const std::size_t after = _container.size();
        notify_erase(before, after);
        return it;
    }

    iterator erase(iterator first, iterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(first, last);
        const std::size_t after = _container.size();
        notify_erase(before, after);
        return it;
    }

    template<class t, class s>
    void swap(basic_observable_deque<t, s>& x)
    {
        const std::size_t this_before = _container.size();
        const std::size_t x_before = x._container.size();
        _container.swap(x._container);
        x.on_container_changed(notify_container_changed_action_swap, this_before, x_before, x._container.size());
        on_container_changed(notify_container_changed_action_swap, x_before, this_before, _container.size());
    }

    void clear()
    {
        const std::size_t before = _container.size();
        _container.clear();
        on_container_changed(notify_container_changed_action_reset, 0, before, _container.size());
    }

    allocator_type get_allocator() const
    {
        return _container.get_allocator();
    }

private:
    container_type _container;
};

template<class T, class S>
inline typename basic_observable_deque<T, S>::size_type basic_observable_deque<T, S>::size() const
{
    return _container.size();
}

template<class T, class S>
inline typename basic_observable_deque<T, S>::container_type& basic_observable_deque<T, S>::container()
{
    return _container;
}

template<class T, class S>
inline const typename basic_observable_deque<T, S>::container_type& basic_observable_deque<T, S>::container() const
{
    return _container;
}

template<class T> class observable_deque
    : public basic_observable_deque<T, std::string>
{
public:
    typedef typename std::string string_type;
    typedef typename boost::container::deque<T> container_type;
    typedef observable_deque<T> this_type;
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
    virtual ~observable_deque()
    {
    }

protected:
    observable_deque()
        : basic_observable_deque<value_type, string_type>()
    {
    }

    explicit observable_deque(size_type n)
        : basic_observable_deque<value_type, string_type>(n)
    {
    }

    observable_deque(size_type n, const value_type& val)
        : basic_observable_deque<value_type, string_type>(n, val)
    {
    }

    template <class InputIterator>
    observable_deque(InputIterator first, InputIterator last)
        : basic_observable_deque<value_type, string_type>(first, last)
    {
    }

    observable_deque(const observable_deque& x)
        : basic_observable_deque<value_type, string_type>(x)
    {
    }

public:
    static ptr create()
    {
        return ptr(new observable_deque);
    }

    static ptr create(size_type n)
    {
        return ptr(new observable_deque(n));
    }

    static ptr create(size_type n, const value_type& val)
    {
        return ptr(new observable_deque(n, val));
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        return ptr(new observable_deque(first, last));
    }

    static ptr create(const observable_deque& x)
    {
        return ptr(new observable_deque(x));
    }

public:
    observable_deque& operator=(const observable_deque& x)
    {
        if(this != &x)
        {
            basic_observable_deque<value_type, string_type>::operator=(x);
        }
        return *this;
    }

public:
    template<class t>
    void swap(observable_deque<t>& x)
    {
        basic_observable_deque<t, string_type>::swap(dynamic_cast<basic_observable_deque<t, string_type>&>(x));
    }
};

template<class T> class wobservable_deque
    : public basic_observable_deque<T, std::wstring>
{
public:
    typedef typename std::wstring string_type;
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
    virtual ~wobservable_deque()
    {
    }

protected:
    wobservable_deque()
        : basic_observable_deque<value_type, string_type>()
    {
    }

    explicit wobservable_deque(size_type n)
        : basic_observable_deque<value_type, string_type>(n)
    {
    }

    wobservable_deque(size_type n, const value_type& val)
        : basic_observable_deque<value_type, string_type>(n, val)
    {
    }

    template <class InputIterator>
    wobservable_deque(InputIterator first, InputIterator last)
        : basic_observable_deque<value_type, string_type>(first, last)
    {
    }

    wobservable_deque(const wobservable_deque& x)
        : basic_observable_deque<value_type, string_type>(x)
    {
    }

public:
    static ptr create()
    {
        return ptr(new wobservable_deque);
    }

    static ptr create(size_type n)
    {
        return ptr(new wobservable_deque(n));
    }

    static ptr create(size_type n, const value_type& val)
    {
        return ptr(new wobservable_deque(n, val));
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        return ptr(new wobservable_deque(first, last));
    }

    static ptr create(const wobservable_deque& x)
    {
        return ptr(new wobservable_deque(x));
    }

public:
    wobservable_deque& operator=(const wobservable_deque& x)
    {
        if(this != &x)
        {
            basic_observable_deque<value_type, string_type>::operator=(x);
        }
        return *this;
    }

public:
    template<class t>
    void swap(wobservable_deque<t>& x)
    {
        basic_observable_deque<t, string_type>::swap(dynamic_cast<basic_observable_deque<t, string_type>&>(x));
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_DEQUE_HPP_INCLUDED
