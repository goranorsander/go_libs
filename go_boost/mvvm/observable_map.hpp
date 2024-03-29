#ifndef GO_BOOST_MVVM_OBSERVABLE_MAP_HPP_INCLUDED
#define GO_BOOST_MVVM_OBSERVABLE_MAP_HPP_INCLUDED

//
//  observable_map.hpp
//
//  Copyright 2015-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/container/map.hpp>

#include <go_boost/mvvm/observable_ordered_associative_container.hpp>

namespace go_boost
{
namespace mvvm
{

template<class K, class T, class S, class L = boost::recursive_mutex>
class basic_observable_map
    : public basic_observable_ordered_associative_container<S, boost::container::map<K, T>, L>
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef typename boost::container::map<K, T> container_type;
    typedef basic_observable_map<K, T, S, L> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::mapped_type mapped_type;
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
    virtual ~basic_observable_map() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    basic_observable_map()
        : basic_observable_ordered_associative_container<string_type, container_type, lockable_type>()
        , _container()
    {
    }

    template <class InputIterator>
    basic_observable_map(InputIterator first, InputIterator last)
        : basic_observable_ordered_associative_container<string_type, container_type, lockable_type>()
        , _container(first, last)
    {
    }

    explicit basic_observable_map(const this_type& x)
        : basic_observable_ordered_associative_container<string_type, container_type, lockable_type>()
        , _container(x._container)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit basic_observable_map(this_type&& x)
        : basic_observable_ordered_associative_container<string_type, container_type, lockable_type>()
        , _container(x._container)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    explicit basic_observable_map(const std::initializer_list<value_type>& il)
        : basic_observable_ordered_associative_container<string_type, container_type, lockable_type>()
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
        this->container().operator=(il);
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    mapped_type& operator[](const key_type& k)
    {
        return _container.operator[](k);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    mapped_type& operator[](key_type&& k)
    {
        return _container.operator[](k);
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

public:
    mapped_type& at(const key_type& k)
    {
        return _container.at(k);
    }

    GO_BOOST_CONSTEXPR const mapped_type& at(const key_type& k) const
    {
        return _container.at(k);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

    template <class... Args>
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        const std::size_t before = this->container().size();
        const std::pair<iterator, bool> p = this->container().emplace(args...);
        if(p.second)
        {
            const std::size_t after = this->container().size();
            this->notify_insert(before, after);
        }
        return p;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

    std::pair<iterator, bool> insert(const value_type& val)
    {
        const std::size_t before = this->container().size();
        const std::pair<iterator, bool> p = this->container().insert(val);
        if(p.second)
        {
            const std::size_t after = this->container().size();
            this->notify_insert(before, after);
        }
        return p;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template <class P> std::pair<iterator, bool> insert(P&& val)
    {
        const std::size_t before = this->container().size();
        const std::pair<iterator, bool> p = this->container().insert(val);
        if(p.second)
        {
            const std::size_t after = this->container().size();
            this->notify_insert(before, after);
        }
        return p;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    iterator insert(const_iterator position, const value_type& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    iterator insert(const_iterator position, value_type&& val)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.insert(position, val);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
        return it;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        const std::size_t before = _container.size();
        _container.insert(first, last);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
    }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    void insert(const std::initializer_list<value_type>& il)
    {
        const std::size_t before = _container.size();
        _container.insert(il);
        const std::size_t after = _container.size();
        this->notify_insert(before, after);
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    iterator erase(const_iterator position)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(position);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
        return it;
    }

    size_type erase(const key_type& k)
    {
        const std::size_t before = this->container().size();
        const size_type s = this->container().erase(k);
        if(s > 0)
        {
            const std::size_t after = this->container().size();
            this->notify_erase(before, after);
        }
        return s;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        const std::size_t before = _container.size();
        const iterator it = _container.erase(first, last);
        const std::size_t after = _container.size();
        this->notify_erase(before, after);
        return it;
    }

protected:
    virtual container_type& container();

    virtual const container_type& container() const;

private:
    container_type _container;
};

template<class K, class T, class S, class L>
inline typename basic_observable_map<K, T, S, L>::container_type& basic_observable_map<K, T, S, L>::container()
{
    return _container;
}

template<class K, class T, class S, class L>
inline const typename basic_observable_map<K, T, S, L>::container_type& basic_observable_map<K, T, S, L>::container() const
{
    return _container;
}

template<class K, class T, class L = boost::recursive_mutex>
class observable_map
    : public basic_observable_map<K, T, std::string, L>
{
public:
    typedef std::string string_type;
    typedef L lockable_type;
    typedef typename boost::container::map<K, T> container_type;
    typedef observable_map<K, T, L> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::mapped_type mapped_type;
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
    virtual ~observable_map() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
     observable_map()
        //: basic_observable_map<key_type, value_type, string_type, lockable_type>()
    {
    }

    template <class InputIterator>
    observable_map(InputIterator first, InputIterator last)
        : basic_observable_map<key_type, value_type, string_type, lockable_type>(first, last)
    {
    }

    explicit observable_map(const this_type& x)
        : basic_observable_map<key_type, value_type, string_type, lockable_type>(x)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit observable_map(this_type&& x)
        : basic_observable_map<key_type, value_type, string_type, lockable_type>(x)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    explicit observable_map(const std::initializer_list<value_type>& il)
        : basic_observable_map<key_type, value_type, string_type, lockable_type>(il)
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
            basic_observable_map<key_type, value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_type& operator=(this_type&& x) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &x)
        {
            basic_observable_map<key_type, value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    this_type& operator=(const std::initializer_list<value_type>& il) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->container().operator=(il);
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    template<class k, class t, typename m>
    void swap(observable_map<k, t, m>& x)
    {
        basic_observable_map<k, t, string_type, m>::swap(dynamic_cast<basic_observable_map<k, t, string_type, m>&>(x));
    }
};

template<class K, class T, class L = boost::recursive_mutex>
class wobservable_map
    : public basic_observable_map<K, T, std::wstring, L>
{
public:
    typedef std::wstring string_type;
    typedef L lockable_type;
    typedef typename boost::container::map<K, T> container_type;
    typedef wobservable_map<K, T, L> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

    typedef typename container_type::key_type key_type;
    typedef typename container_type::mapped_type mapped_type;
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
    virtual ~wobservable_map() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
     wobservable_map()
        //: basic_observable_map<key_type, value_type, string_type, lockable_type>()
    {
    }

    template <class InputIterator>
    wobservable_map(InputIterator first, InputIterator last)
        : basic_observable_map<key_type, value_type, string_type, lockable_type>(first, last)
    {
    }

    explicit wobservable_map(const this_type& x)
        : basic_observable_map<key_type, value_type, string_type, lockable_type>(x)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    explicit wobservable_map(this_type&& x)
        : basic_observable_map<key_type, value_type, string_type, lockable_type>(x)
    {
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    explicit wobservable_map(const std::initializer_list<value_type>& il)
        : basic_observable_map<key_type, value_type, string_type, lockable_type>(il)
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
            basic_observable_map<key_type, value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    this_type& operator=(this_type&& x) BOOST_NOEXCEPT_OR_NOTHROW
    {
        if(this != &x)
        {
            basic_observable_map<key_type, value_type, string_type, lockable_type>::operator=(x);
        }
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    this_type& operator=(const std::initializer_list<value_type>& il) BOOST_NOEXCEPT_OR_NOTHROW
    {
        this->container().operator=(il);
        return *this;
    }

#endif  // #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

public:
    template<class k, class t, typename m>
    void swap(wobservable_map<k, t, m>& x)
    {
        basic_observable_map<k, t, string_type, m>::swap(dynamic_cast<basic_observable_map<k, t, string_type, m>&>(x));
    }
};

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_OBSERVABLE_MAP_HPP_INCLUDED
