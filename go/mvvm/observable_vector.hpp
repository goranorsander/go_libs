#ifndef GO_MVVM_OBSERVABLE_VECTOR_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_VECTOR_HPP_INCLUDED

//
//  observable_vector.hpp
//
//  Copyright 2015-2016 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
#pragma message("Required C++11 feature is not supported by this compiler")
#else

#include <vector>

#include <go/mvvm/notify_container_changed.hpp>
#include <go/mvvm/observable_sequence_container.hpp>

namespace go
{
namespace mvvm
{

template<class T, class S> class basic_observable_vector
    : public basic_observable_sequence_container<S, std::vector<T>>
{
public:
    typedef S string_type;
    typedef typename std::vector<T> container_type;
    typedef basic_observable_vector<string_type, container_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

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
    virtual ~basic_observable_vector()
    {
    }

protected:
    basic_observable_vector()
        : basic_observable_sequence_container<string_type, container_type>()
        , _container()
    {
    }

    explicit basic_observable_vector(size_type n)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(n)
    {
    }

    basic_observable_vector(size_type n, const value_type& val)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(n, val)
    {
    }

    template <class InputIterator>
    basic_observable_vector(InputIterator first, InputIterator last)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(first, last)
    {
    }

    basic_observable_vector(const this_type& x)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(x._container)
    {
    }

    basic_observable_vector(this_type&& x)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(x._container)
    {
    }

    basic_observable_vector(std::initializer_list<value_type> il)
        : basic_observable_sequence_container<string_type, container_type>()
        , _container(il)
    {
    }

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            _container.operator=(x._container);
        }
        return *this;
    }

    this_type& operator=(std::initializer_list<value_type> il)
    {
        _container.operator=(il);
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
    reverse_iterator rbegin() noexcept
    {
        return _container.rbegin();
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return _container.rbegin();
    }

    reverse_iterator rend() noexcept
    {
        return _container.rend();
    }

    const_reverse_iterator rend() const noexcept
    {
        return _container.rend();
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return _container.crbegin();
    }

    const_reverse_iterator crend() const noexcept
    {
        return _container.crend();
    }

    size_type size() const noexcept;

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

    pointer data() noexcept
    {
        return _container.data();
    }

    const_pointer data() const noexcept
    {
        return _container.data();
    }

    void resize(size_type n)
    {
        _container.resize(n);
    }

    void resize(size_type n, const value_type& val)
    {
        _container.resize(n, val);
    }

    size_type capacity() const noexcept
    {
        return _container.capacity();
    }

    void reserve(size_type n)
    {
        _container.reserve(n);
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

    void assign(std::initializer_list<value_type> il)
    {
        const std::size_t before = _container.size();
        _container.assign(il);
        const std::size_t after = _container.size();
        notify_assign(before, after);
    }

    void push_back(const value_type& val)
    {
        _container.push_back(val);
        on_container_changed(notify_container_changed_action_add, 1, 0, _container.size());
    }

    void push_back(value_type&& val)
    {
        _container.push_back(val);
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

    iterator insert(const_iterator position, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

    iterator insert(const_iterator position, size_type n, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, n, val);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

    template <class InputIterator>
    iterator insert(const_iterator position, InputIterator first, InputIterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, first, last);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

    iterator insert(const_iterator position, value_type&& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

    iterator insert(const_iterator position, std::initializer_list<value_type> il)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, il);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

    iterator erase(const_iterator position)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(position);
        const std::size_t after = _container.size();
        notify_erase(before, after);
        return it;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(first, last);
        const std::size_t after = _container.size();
        notify_erase(before, after);
        return it;
    }

    template<class t, class s>
    void swap(basic_observable_vector<t, s>& x)
    {
        const std::size_t this_before = _container.size();
        const std::size_t x_before = x._container.size();
        _container.swap(x._container);
        x.on_container_changed(notify_container_changed_action_swap, this_before, x_before, x._container.size());
        on_container_changed(notify_container_changed_action_swap, x_before, this_before, _container.size());
    }

    void clear() noexcept
    {
        const std::size_t before = _container.size();
        _container.clear();
        on_container_changed(notify_container_changed_action_reset, 0, before, _container.size());
    }

    template <class... Args>
    iterator emplace(const_iterator position, Args&&... args)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.emplace(position, args...);
        const std::size_t after = _container.size();
        notify_insert(before, after);
        return it;
    }

    template <class... Args>
    void emplace_back(Args&&... args)
    {
        const std::size_t before = _container.size();
        _container.emplace_back(args...);
        const std::size_t after = _container.size();
        notify_insert(before, after);
    }

    allocator_type get_allocator() const noexcept
    {
        return _container.get_allocator();
    }

private:
    container_type _container;
};

template<class T, class S>
inline typename basic_observable_vector<T, S>::size_type basic_observable_vector<T, S>::size() const noexcept
{
    return _container.size();
}

template<class T, class S>
inline typename basic_observable_vector<T, S>::container_type& basic_observable_vector<T, S>::container()
{
    return _container;
}

template<class T, class S>
inline const typename basic_observable_vector<T, S>::container_type& basic_observable_vector<T, S>::container() const
{
    return _container;
}

template<class T> class observable_vector
    : public basic_observable_vector<T, std::string>
{
public:
    typedef std::string string_type;
    typedef typename std::vector<T> container_type;
    typedef observable_vector<T> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

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
    virtual ~observable_vector()
    {
    }

protected:
    observable_vector()
        : basic_observable_vector<value_type, string_type>()
    {
    }

    explicit observable_vector(size_type n)
        : basic_observable_vector<value_type, string_type>(n)
    {
    }

    observable_vector(size_type n, const value_type& val)
        : basic_observable_vector<value_type, string_type>(n, val)
    {
    }

    template <class InputIterator>
    observable_vector(InputIterator first, InputIterator last)
        : basic_observable_vector<value_type, string_type>(first, last)
    {
    }

    observable_vector(const this_type& x)
        : basic_observable_vector<value_type, string_type>(x)
    {
    }

    observable_vector(this_type&& x)
        : basic_observable_vector<value_type, string_type>(x)
    {
    }

    observable_vector(std::initializer_list<value_type> il)
        : basic_observable_vector<value_type, string_type>(il)
    {
    }

public:
    static ptr create()
    {
        return ptr(new this_type);
    }

    static ptr create(size_type n)
    {
        return ptr(new this_type(n));
    }

    static ptr create(size_type n, const value_type& val)
    {
        return ptr(new this_type(n, val));
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

    static ptr create(this_type&& x)
    {
        return ptr(new this_type(x));
    }

    static ptr create(std::initializer_list<value_type> il)
    {
        return ptr(new this_type(il));
    }

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            basic_observable_vector<value_type, string_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            basic_observable_vector<value_type, string_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(std::initializer_list<value_type> il)
    {
        basic_observable_vector<value_type, string_type>::operator=(il);
        return *this;
    }

public:
    template<class t>
    void swap(observable_vector<t>& x)
    {
        basic_observable_vector<t, string_type>::swap(dynamic_cast<basic_observable_vector<t, string_type>&>(x));
    }
};

template<class T> class wobservable_vector
    : public basic_observable_vector<T, std::wstring>
{
public:
    typedef std::wstring string_type;
    typedef typename std::vector<T> container_type;
    typedef wobservable_vector<T> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

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
    virtual ~wobservable_vector()
    {
    }

protected:
    wobservable_vector()
        : basic_observable_vector<value_type, string_type>()
    {
    }

    explicit wobservable_vector(size_type n)
        : basic_observable_vector<value_type, string_type>(n)
    {
    }

    wobservable_vector(size_type n, const value_type& val)
        : basic_observable_vector<value_type, string_type>(n, val)
    {
    }

    template <class InputIterator>
    wobservable_vector(InputIterator first, InputIterator last)
        : basic_observable_vector<value_type, string_type>(first, last)
    {
    }

    wobservable_vector(const this_type& x)
        : basic_observable_vector<value_type, string_type>(x)
    {
    }

    wobservable_vector(this_type&& x)
        : basic_observable_vector<value_type, string_type>(x)
    {
    }

    wobservable_vector(std::initializer_list<value_type> il)
        : basic_observable_vector<value_type, string_type>(il)
    {
    }

public:
    static ptr create()
    {
        return ptr(new this_type);
    }

    static ptr create(size_type n)
    {
        return ptr(new this_type(n));
    }

    static ptr create(size_type n, const value_type& val)
    {
        return ptr(new this_type(n, val));
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

    static ptr create(this_type&& x)
    {
        return ptr(new this_type(x));
    }

    static ptr create(std::initializer_list<value_type> il)
    {
        return ptr(new this_type(il));
    }

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            basic_observable_vector<value_type, string_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            basic_observable_vector<value_type, string_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(std::initializer_list<value_type> il)
    {
        basic_observable_vector<value_type, string_type>::operator=(il);
        return *this;
    }

public:
    template<class t>
    void swap(wobservable_vector<t>& x)
    {
        basic_observable_vector<t, string_type>::swap(dynamic_cast<basic_observable_vector<t, string_type>&>(x));
    }
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_VECTOR_HPP_INCLUDED