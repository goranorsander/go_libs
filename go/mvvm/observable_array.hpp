#ifndef GO_MVVM_OBSERVABLE_ARRAY_HPP_INCLUDED
#define GO_MVVM_OBSERVABLE_ARRAY_HPP_INCLUDED

//
//  observable_array.hpp
//
//  Copyright 2015-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_NOEXCEPT) || defined(GO_NO_CXX11_MUTEX)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <array>

#include <go/mvvm/observable_sequence_container.hpp>

namespace go
{
namespace mvvm
{

template<class T, class S, size_t N, class L = std::recursive_mutex>
class basic_observable_array
    : public basic_observable_sequence_container<S, std::array<T, N>, L>
{
public:
    using string_type = S;
    using lockable_type = L;
    using container_type = typename std::array<T, N>;
    using this_type = basic_observable_array<T, S, N, L>;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

    using value_type = typename container_type::value_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator = typename container_type::const_reverse_iterator;
    using difference_type = typename container_type::difference_type;
    using size_type = typename container_type::size_type;

public:
    virtual ~basic_observable_array() GO_DEFAULT_DESTRUCTOR

protected:
    basic_observable_array()
        : basic_observable_sequence_container<string_type, container_type, lockable_type>()
        , _container()
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

public:
    GO_CONSTEXPR const_reference operator[](size_type n) const
    {
        return _container.operator[](n);
    }

    reference operator[](size_type n)
    {
        return _container.operator[](n);
    }

protected:
    virtual container_type& container()
    {
        return _container;
    }

    virtual const container_type& container() const
    {
        return _container;
    }

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

    GO_CONSTEXPR size_type size() const noexcept
    {
        return _container.size();
    }

    GO_CONSTEXPR const_reference at(size_type n) const
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

    GO_CONSTEXPR const_reference back() const
    {
        return _container.back();
    }

    pointer data() noexcept
    {
        return _container.data();
    }

    GO_CONSTEXPR const_pointer data() const noexcept
    {
        return _container.data();
    }

private:
    container_type _container;
};

template<class T, size_t N, class L = std::recursive_mutex> class observable_array
    : public basic_observable_array<T, std::string, N, L>
{
public:
    using string_type = std::string;
    using lockable_type = L;
    using container_type = typename std::array<T, N>;
    using this_type = observable_array<T, N, L>;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

    using value_type = typename container_type::value_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator = typename container_type::const_reverse_iterator;
    using difference_type = typename container_type::difference_type;
    using size_type = typename container_type::size_type;

public:
    virtual ~observable_array() GO_DEFAULT_DESTRUCTOR

protected:
     observable_array()
        : basic_observable_array<T, string_type, N, lockable_type>()
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
};

template<class T, size_t N, class L = std::recursive_mutex> class wobservable_array
    : public basic_observable_array<T, std::wstring, N, L>
{
public:
    using string_type = std::wstring;
    using lockable_type = L;
    using container_type = typename std::array<T, N>;
    using this_type = wobservable_array<T, N, L>;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

    using value_type = typename container_type::value_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator = typename container_type::const_reverse_iterator;
    using difference_type = typename container_type::difference_type;
    using size_type = typename container_type::size_type;

public:
    virtual ~wobservable_array() GO_DEFAULT_DESTRUCTOR

protected:
     wobservable_array()
        : basic_observable_array<T, string_type, N, lockable_type>()
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
};

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_OBSERVABLE_ARRAY_HPP_INCLUDED
