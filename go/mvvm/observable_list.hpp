#ifndef GO_MVVM_OBSERVABLE_LIST_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_LIST_HPP_INCLUDED

//
//  observable_list.hpp
//
//  Copyright 2015-2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <list>

#include <go/mvvm/observable_sequence_container.hpp>

namespace go
{
namespace mvvm
{

template<class T, class S, typename M = std::recursive_mutex>
class basic_observable_list
    : public basic_observable_sequence_container<S, std::list<T>, M>
{
public:
    typedef S string_type;
    typedef M mutex_type;
    typedef typename std::list<T> container_type;
    typedef basic_observable_list<T, S, M> this_type;
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
    virtual ~basic_observable_list() GO_DEFAULT_DESTRUCTOR

protected:
    basic_observable_list()
        : basic_observable_sequence_container<string_type, container_type, mutex_type>()
        , _container()
    {
    }

    explicit basic_observable_list(size_type n)
        : basic_observable_sequence_container<string_type, container_type, mutex_type>()
        , _container(n)
    {
    }

    basic_observable_list(size_type n, const value_type& val)
        : basic_observable_sequence_container<string_type, container_type, mutex_type>()
        , _container(n, val)
    {
    }

    template <class InputIterator>
    basic_observable_list(InputIterator first, InputIterator last)
        : basic_observable_sequence_container<string_type, container_type, mutex_type>()
        , _container(first, last)
    {
    }

    explicit basic_observable_list(const this_type& x)
        : basic_observable_sequence_container<string_type, container_type, mutex_type>()
        , _container(x._container)
    {
    }

    explicit basic_observable_list(this_type&& x)
        : basic_observable_sequence_container<string_type, container_type, mutex_type>()
        , _container(x._container)
    {
    }

    explicit basic_observable_list(const std::initializer_list<value_type>& il)
        : basic_observable_sequence_container<string_type, container_type, mutex_type>()
        , _container(il)
    {
    }

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
        };

        return std::make_shared<make_shared_enabler>();
    }

    static ptr create(size_type n)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(size_type n) : this_type(n) {}
        };

        return std::make_shared<make_shared_enabler, size_type>(n);
    }

    static ptr create(size_type n, const value_type& val)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                make_shared_enabler(size_type n, const value_type& val) : this_type(n, val) {}
        };

        return std::make_shared<make_shared_enabler, size_type, const value_type&>(n, val);
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                make_shared_enabler(InputIterator first, InputIterator last) : this_type(first, last) {}
        };

        return std::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
    }

    static ptr create(const this_type& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(const this_type& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, const this_type&>(x);
    }

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(this_type&& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, this_type&&>(x);
    }

    static ptr create(const std::initializer_list<value_type>& il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
                explicit make_shared_enabler(const std::initializer_list<value_type>& il) : this_type(il) {}
        };

        return std::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
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

    this_type& operator=(const std::initializer_list<value_type>& il)
    {
        _container.operator=(il);
        return *this;
    }

protected:
    virtual container_type& container();

    virtual const container_type& container() const;

public:
    reverse_iterator rbegin() noexcept
    {
        return _container.rbegin();
    }

    GO_CONSTEXPR const_reverse_iterator rbegin() const noexcept
    {
        return _container.rbegin();
    }

    reverse_iterator rend() noexcept
    {
        return _container.rend();
    }

    GO_CONSTEXPR const_reverse_iterator rend() const noexcept
    {
        return _container.rend();
    }

    GO_CONSTEXPR const_reverse_iterator crbegin() const noexcept
    {
        return _container.crbegin();
    }

    GO_CONSTEXPR const_reverse_iterator crend() const noexcept
    {
        return _container.crend();
    }

    GO_CONSTEXPR size_type size() const noexcept;

    reference back()
    {
        return _container.back();
    }

    GO_CONSTEXPR const_reference back() const
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

    void assign(const std::initializer_list<value_type>& il)
    {
        const std::size_t before = _container.size();
        _container.assign(il);
        const std::size_t after = _container.size();
        this->notify_assign(before, after);
    }

    void push_back(const value_type& val)
    {
        _container.push_back(val);
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, _container.size());
    }

    void push_back(value_type&& val)
    {
        _container.push_back(val);
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, _container.size());
    }

    void push_front(const value_type& val)
    {
        _container.push_front(val);
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, _container.size());
    }

    void push_front(value_type&& val)
    {
        _container.push_front(val);
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, _container.size());
    }

    void pop_back()
    {
        const std::size_t before = _container.size();
        _container.pop_back();
        const std::size_t after = _container.size();
        if(before > after)
        {
            this->notify_container_changed(notify_container_changed_action::remove, 0, before - after, _container.size());
        }
    }

    void pop_front()
    {
        const std::size_t before = _container.size();
        _container.pop_front();
        const std::size_t after = _container.size();
        if(before > after)
        {
            this->notify_container_changed(notify_container_changed_action::remove, 0, before - after, _container.size());
        }
    }

    iterator insert(const_iterator position, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    iterator insert(const_iterator position, size_type n, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, n, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    template <class InputIterator>
    iterator insert(const_iterator position, InputIterator first, InputIterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, first, last);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    iterator insert(const_iterator position, value_type&& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    iterator insert(const_iterator position, std::initializer_list<value_type> il)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, il);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

    iterator erase(const_iterator position)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(position);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
        return it;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(first, last);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
        return it;
    }

    template<class t, class s, typename m>
    void swap(basic_observable_list<t, s, m>& x)
    {
        const std::size_t this_before = _container.size();
        const std::size_t x_before = x._container.size();
        _container.swap(x._container);
        x.notify_container_changed(notify_container_changed_action::swap, this_before, x_before, x._container.size());
        this->notify_container_changed(notify_container_changed_action::swap, x_before, this_before, _container.size());
    }

    void clear() noexcept
    {
        const std::size_t before = _container.size();
        _container.clear();
        this->notify_container_changed(notify_container_changed_action::reset, 0, before, 0);
    }

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

    GO_CONSTEXPR allocator_type get_allocator() const noexcept
    {
        return _container.get_allocator();
    }

    template<class t, class s, typename m>
    void splice(const_iterator position, basic_observable_list<t, s, m>& x)
    {
        const std::size_t x_before = x._container.size();
        _container.splice(position, x._container);
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, x_before, 0, _container.size());
    }

    template<class t, class s, typename m>
    void splice(const_iterator position, basic_observable_list<t, s, m>&& x)
    {
        const std::size_t x_before = x._container.size();
        _container.splice(position, x._container);
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, x_before, 0, _container.size());
    }

    template<class t, class s, typename m>
    void splice(const_iterator position, basic_observable_list<t, s, m>& x, const_iterator i)
    {
        _container.splice(position, x._container, i);
        x.notify_container_changed(notify_container_changed_action::remove, 0, 1, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, _container.size());
    }

    template<class t, class s, typename m>
    void splice(const_iterator position, basic_observable_list<t, s, m>&& x, const_iterator i)
    {
        _container.splice(position, x._container, i);
        x.notify_container_changed(notify_container_changed_action::remove, 0, 1, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, 1, 0, _container.size());
    }

    template<class t, class s, typename m>
    void splice(const_iterator position, basic_observable_list<t, s, m>& x, const_iterator first, const_iterator last)
    {
        const std::size_t this_before = _container.size();
        _container.splice(position, x._container, first, last);
        const std::size_t transfer_count = _container.size() - this_before;
        x.notify_container_changed(notify_container_changed_action::remove, 0, transfer_count, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, transfer_count, 0, _container.size());
    }

    template<class t, class s, typename m>
    void splice(const_iterator position, basic_observable_list<t, s, m>&& x, const_iterator first, const_iterator last)
    {
        const std::size_t this_before = _container.size();
        _container.splice(position, x._container, first, last);
        const std::size_t transfer_count = _container.size() - this_before;
        x.notify_container_changed(notify_container_changed_action::remove, 0, transfer_count, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, transfer_count, 0, _container.size());
    }

    void remove(const value_type& val)
    {
        const std::size_t before = _container.size();
        _container.remove(val);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
    }

    template <class Predicate>
    void remove_if(Predicate pred)
    {
        const std::size_t before = _container.size();
        _container.remove_if(pred);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
    }

    void unique()
    {
        const std::size_t before = _container.size();
        _container.unique();
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
    }

    template <class BinaryPredicate>
    void unique(BinaryPredicate binary_pred)
    {
        const std::size_t before = _container.size();
        _container.unique(binary_pred);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
    }

    template<class t, class s, typename m>
    void merge(basic_observable_list<t, s, m>& x)
    {
        const std::size_t this_before = _container.size();
        const std::size_t x_before = x._container.size();
        _container.merge(x._container);
        const std::size_t this_after = _container.size();
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, this_after - this_before, 0, this_after);
    }

    template<class t, class s, typename m>
    void merge(basic_observable_list<t, s, m>&& x)
    {
        const std::size_t this_before = _container.size();
        const std::size_t x_before = x._container.size();
        _container.merge(x._container);
        const std::size_t this_after = _container.size();
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, this_after - this_before, 0, this_after);
    }

    template<class t, class s, typename m, class Compare>
    void merge(basic_observable_list<t, s, m>& x, Compare comp)
    {
        const std::size_t this_before = _container.size();
        const std::size_t x_before = x._container.size();
        _container.merge(x._container, comp);
        const std::size_t this_after = _container.size();
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, this_after - this_before, 0, this_after);
    }

    template<class t, class s, typename m, class Compare>
    void merge(basic_observable_list<t, s, m>&& x, Compare comp)
    {
        const std::size_t this_before = _container.size();
        const std::size_t x_before = x._container.size();
        _container.merge(x._container, comp);
        const std::size_t this_after = _container.size();
        x.notify_container_changed(notify_container_changed_action::remove, 0, x_before, x._container.size());
        this->notify_container_changed(notify_container_changed_action::add, this_after - this_before, 0, this_after);
    }

    void sort()
    {
        _container.sort();
    }

    template <class Compare>
    void sort(Compare comp)
    {
        _container.sort(comp);
    }

    void reverse()
    {
        _container.reverse();
    }

private:
    container_type _container;
};

template<class T, class S, typename M>
inline GO_CONSTEXPR typename basic_observable_list<T, S, M>::size_type basic_observable_list<T, S, M>::size() const noexcept
{
    return _container.size();
}

template<class T, class S, typename M>
inline typename basic_observable_list<T, S, M>::container_type& basic_observable_list<T, S, M>::container()
{
    return _container;
}

template<class T, class S, typename M>
inline const typename basic_observable_list<T, S, M>::container_type& basic_observable_list<T, S, M>::container() const
{
    return _container;
}

template<class T, typename M = std::recursive_mutex>
class observable_list
    : public basic_observable_list<T, std::string, M>
{
public:
    typedef std::string string_type;
    typedef M mutex_type;
    typedef typename std::list<T> container_type;
    typedef observable_list<T, M> this_type;
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
    virtual ~observable_list() GO_DEFAULT_DESTRUCTOR

protected:
     observable_list()
        : basic_observable_list<value_type, string_type, mutex_type>()
    {
    }

    explicit observable_list(size_type n)
        : basic_observable_list<value_type, string_type, mutex_type>(n)
    {
    }

    observable_list(size_type n, const value_type& val)
        : basic_observable_list<value_type, string_type, mutex_type>(n, val)
    {
    }

    template <class InputIterator>
    observable_list(InputIterator first, InputIterator last)
        : basic_observable_list<value_type, string_type, mutex_type>(first, last)
    {
    }

    explicit observable_list(const this_type& x)
        : basic_observable_list<value_type, string_type, mutex_type>(x)
    {
    }

    explicit observable_list(this_type&& x)
        : basic_observable_list<value_type, string_type, mutex_type>(x)
    {
    }

    explicit observable_list(const std::initializer_list<value_type>& il)
        : basic_observable_list<value_type, string_type, mutex_type>(il)
    {
    }

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
        };

        return std::make_shared<make_shared_enabler>();
    }

    static ptr create(size_type n)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(size_type n) : this_type(n) {}
        };

        return std::make_shared<make_shared_enabler, size_type>(n);
    }

    static ptr create(size_type n, const value_type& val)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(size_type n, const value_type& val) : this_type(n, val) {}
        };

        return std::make_shared<make_shared_enabler, size_type, const value_type&>(n, val);
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(InputIterator first, InputIterator last) : this_type(first, last) {}
        };

        return std::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
    }

    static ptr create(const this_type& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const this_type& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, const this_type&>(x);
    }

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(this_type&& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, this_type&&>(x);
    }

    static ptr create(const std::initializer_list<value_type>& il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const std::initializer_list<value_type>& il) : this_type(il) {}
        };

        return std::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            basic_observable_list<value_type, string_type, mutex_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            basic_observable_list<value_type, string_type, mutex_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(const std::initializer_list<value_type>& il)
    {
        basic_observable_list<value_type, string_type, mutex_type>::operator=(il);
        return *this;
    }

public:
    template<class t, typename m>
    void swap(observable_list<t, m>& x)
    {
        basic_observable_list<t, string_type, m>::swap(dynamic_cast<basic_observable_list<t, string_type, m>&>(x));
    }
};

template<class T, typename M = std::recursive_mutex>
class wobservable_list
    : public basic_observable_list<T, std::wstring, M>
{
public:
    typedef std::wstring string_type;
    typedef M mutex_type;
    typedef typename std::list<T> container_type;
    typedef wobservable_list<T, M> this_type;
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
    virtual ~wobservable_list() GO_DEFAULT_DESTRUCTOR

protected:
     wobservable_list()
        : basic_observable_list<value_type, string_type, mutex_type>()
    {
    }

    explicit wobservable_list(size_type n)
        : basic_observable_list<value_type, string_type, mutex_type>(n)
    {
    }

    wobservable_list(size_type n, const value_type& val)
        : basic_observable_list<value_type, string_type, mutex_type>(n, val)
    {
    }

    template <class InputIterator>
    wobservable_list(InputIterator first, InputIterator last)
        : basic_observable_list<value_type, string_type, mutex_type>(first, last)
    {
    }

    explicit wobservable_list(const this_type& x)
        : basic_observable_list<value_type, string_type, mutex_type>(x)
    {
    }

    explicit wobservable_list(this_type&& x)
        : basic_observable_list<value_type, string_type, mutex_type>(x)
    {
    }

    explicit wobservable_list(const std::initializer_list<value_type>& il)
        : basic_observable_list<value_type, string_type, mutex_type>(il)
    {
    }

public:
    static ptr create()
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler() GO_DEFAULT_CONSTRUCTOR
        };

        return std::make_shared<make_shared_enabler>();
    }

    static ptr create(size_type n)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(size_type n) : this_type(n) {}
        };

        return std::make_shared<make_shared_enabler, size_type>(n);
    }

    static ptr create(size_type n, const value_type& val)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(size_type n, const value_type& val) : this_type(n, val) {}
        };

        return std::make_shared<make_shared_enabler, size_type, const value_type&>(n, val);
    }

    template <class InputIterator>
    static ptr create(InputIterator first, InputIterator last)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            make_shared_enabler(InputIterator first, InputIterator last) : this_type(first, last) {}
        };

        return std::make_shared<make_shared_enabler, InputIterator, InputIterator>(first, last);
    }

    static ptr create(const this_type& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const this_type& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, const this_type&>(x);
    }

    static ptr create(this_type&& x)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(this_type&& x) : this_type(x) {}
        };

        return std::make_shared<make_shared_enabler, this_type&&>(x);
    }

    static ptr create(const std::initializer_list<value_type>& il)
    {
        struct make_shared_enabler
            : public this_type
        {
            virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
            explicit make_shared_enabler(const std::initializer_list<value_type>& il) : this_type(il) {}
        };

        return std::make_shared<make_shared_enabler, std::initializer_list<value_type>>(il);
    }

public:
    this_type& operator=(const this_type& x)
    {
        if(this != &x)
        {
            basic_observable_list<value_type, string_type, mutex_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(this_type&& x)
    {
        if(this != &x)
        {
            basic_observable_list<value_type, string_type, mutex_type>::operator=(x);
        }
        return *this;
    }

    this_type& operator=(const std::initializer_list<value_type>& il)
    {
        basic_observable_list<value_type, string_type, mutex_type>::operator=(il);
        return *this;
    }

public:
    template<class t, typename m>
    void swap(wobservable_list<t, m>& x)
    {
        basic_observable_list<t, string_type, m>::swap(dynamic_cast<basic_observable_list<t, string_type, m>&>(x));
    }
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_LIST_HPP_INCLUDED
