#ifndef GO_UTILITY_CONTAINER_CIRCULAR_BUFFER_HPP_INCLUDED
#define GO_UTILITY_CONTAINER_CIRCULAR_BUFFER_HPP_INCLUDED

//
//  circular_buffer.hpp
//
//  Copyright 2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11_RANGE_FOR_LOOP) || defined(GO_NO_CXX11_STATIC_CONST_DATA_MEMBER_INSIDE_CLASS_DEFINITION)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <vector>

#if defined(max)
#define GO_UTILITY_CONTAINER_CIRCULAR_BUFFER_RESTORE_MAX 1
#pragma push_macro("max")
#undef max
#endif  // #if defined(max)

namespace go
{
namespace utility
{
namespace container
{

template<class T, class A = std::allocator<T>> class circular_buffer
{
public:
    using this_type = circular_buffer<T, A>;
    using element_type = T;
    using allocator_type = A;
    using buffer_container_type = typename std::vector<T, A>;
    using value_type = typename buffer_container_type::value_type;
    using capacity_type = typename buffer_container_type::size_type;
    using reference = typename buffer_container_type::reference;
    using const_reference = typename buffer_container_type::const_reference;
    using pointer = typename buffer_container_type::pointer;
    using const_pointer = typename buffer_container_type::const_pointer;
    using difference_type = typename buffer_container_type::difference_type;
    using size_type = typename buffer_container_type::size_type;
    using param_value_type = typename buffer_container_type::const_reference;
    using rvalue_type = typename buffer_container_type::value_type&&;

protected:
    class iterator_base
        : public std::iterator<std::random_access_iterator_tag, value_type>
    {
        friend class circular_buffer<element_type, allocator_type>;

    protected:
        using base_type = std::iterator<std::random_access_iterator_tag, value_type>;
        using iterator_category = typename base_type::iterator_category;
        using difference_type = typename base_type::difference_type;
        using reference = typename base_type::reference;
        using const_reference = const typename base_type::reference;
        using pointer = typename base_type::pointer;
        using const_pointer = const typename base_type::pointer;

        virtual ~iterator_base() = default;
        iterator_base() = default;
        iterator_base(const iterator_base&) = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        iterator_base(iterator_base&&) = default;

#else

        iterator_base(iterator_base&& other)
            : base_type(std::move(other))
            , _pos(std::move(other._pos))
            , _container(std::move(other._container))
        {
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        explicit iterator_base(circular_buffer<element_type, allocator_type>* container, size_t pos = 0)
            : base_type()
            , _pos(pos)
            , _container(container)
        {
        }

        iterator_base& operator=(const iterator_base&) noexcept = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        iterator_base& operator=(iterator_base&&) noexcept = default;

#else

        iterator_base& operator=(iterator_base&& other) noexcept
        {
            if(this != &other)
            {
                base_type::operator=(std::move(other));
                this->_pos = std::move(other._pos);
                this->_container = std::move(other._container);
            }
            return *this;
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        bool operator==(const iterator_base& other) const
        {
            if ((this->_container == nullptr) || (this->_container != other._container))
            {
                throw std::logic_error("operator== : Invalid container reference");
            }
            return this->_pos == other._pos;
        }

        bool operator!=(const iterator_base& other) const
        {
            if ((this->_container == nullptr) || (this->_container != other._container))
            {
                throw std::logic_error("operator!= : Invalid container reference");
            }
            return this->_pos != other._pos;
        }

        bool operator<(const iterator_base& other) const
        {
            if ((this->_container == nullptr) || (this->_container != other._container))
            {
                throw std::logic_error("operator< : Invalid container reference");
            }
            return this->_pos < other._pos;
        }

        bool operator>(const iterator_base& other) const
        {
            if ((this->_container == nullptr) || (this->_container != other._container))
            {
                throw std::logic_error("operator> : Invalid container reference");
            }
            return this->_pos > other._pos;
        }

        bool operator<=(const iterator_base& other) const
        {
            if ((this->_container == nullptr) || (this->_container != other._container))
            {
                throw std::logic_error("operator<= : Invalid container reference");
            }
            return this->_pos <= other._pos;
        }

        bool operator>=(const iterator_base& other) const
        {
            if ((this->_container == nullptr) || (this->_container != other._container))
            {
                throw std::logic_error("operator>= : Invalid container reference");
            }
            return this->_pos >= other._pos;
        }

        reference operator*()
        {
            if (!this->is_in_valid_range())
            {
                throw std::out_of_range("operator* : Out of range");
            }
            return this->_container->_buffer.at(this->_pos);
        }

        const_reference operator*() const
        {
            if (!this->is_in_valid_range())
            {
                throw std::out_of_range("operator* : Out of range");
            }
            return this->_container->_buffer.at(this->_pos);
        }

        pointer operator->()
        {
            if (!this->is_in_valid_range())
            {
                throw std::out_of_range("operator-> : Out of range");
            }
            return std::addressof(this->_container->_buffer.at(this->_pos));
        }

        const_pointer operator->() const
        {
            if (!this->is_in_valid_range())
            {
                throw std::out_of_range("operator-> : Out of range");
            }
            return std::addressof(this->_container->_buffer.at(this->_pos));
        }

    public:
        GO_CONSTEXPR bool is_at_end() const
        {
            return (this->_container != nullptr)
                && (this->_pos == circular_buffer<element_type, allocator_type>::_end_pos);
        }

        GO_CONSTEXPR bool is_in_valid_range() const
        {
            return (this->_container != nullptr)
                && (!this->_container->empty())
                && (this->_pos != circular_buffer<element_type, allocator_type>::_end_pos)
                && (this->_pos < this->_container->capacity())
                && ((this->_container->_front_pos < this->_container->_back_pos)
                    ? ((this->_pos >= this->_container->_front_pos) && (this->_pos <= this->_container->_back_pos))
                    : ((this->_pos >= this->_container->_front_pos) || (this->_pos <= this->_container->_back_pos)));
        }

        GO_CONSTEXPR bool is_valid() const
        {
            return (this->is_at_end())
                || (!this->is_in_valid_range());
        }

    protected:
        void increment()
        {
            if (this->_container == nullptr)
            {
                throw std::logic_error("increment : Invalid container reference");
            }
            if (this->_pos != circular_buffer<element_type, allocator_type>::_end_pos)
            {
                if (this->_container->empty())
                {
                    this->_pos = circular_buffer<element_type, allocator_type>::_end_pos;
                }
                else
                {
                    if (this->_pos == this->_container->_back_pos)
                    {
                        this->_pos = circular_buffer<element_type, allocator_type>::_end_pos;
                    }
                    else if (this->_pos == this->_container->max_pos())
                    {
                        this->_pos = 0;
                    }
                    else
                    {
                        ++(this->_pos);
                    }
                }
            }
        }

        void decrement()
        {
            if (this->_container == nullptr)
            {
                throw std::logic_error("decrement : Invalid container reference");
            }
            if (this->_pos == circular_buffer<element_type, allocator_type>::_end_pos)
            {
                if (!this->_container->empty())
                {
                    this->_pos = this->_container->_back_pos;
                }
            }
            else
            {
                if (this->_container->empty())
                {
                    this->_pos = circular_buffer<element_type, allocator_type>::_end_pos;
                }
                else
                {
                    if (this->_pos == this->_container->_front_pos)
                    {
                        this->_pos = circular_buffer<element_type, allocator_type>::_end_pos;
                    }
                    else if (this->_pos == 0)
                    {
                        this->_pos = this->_container->max_pos();
                    }
                    else
                    {
                        --(this->_pos);
                    }
                }
            }
        }

    private:
        size_t _pos = 0;
        circular_buffer<element_type, allocator_type>* _container = nullptr;
    };

public:
    class iterator
        : public iterator_base
    {
        friend class circular_buffer<element_type, allocator_type>;

    public:
        using base_type = iterator_base;
        using iterator_category = typename base_type::iterator_category;
        using difference_type = typename base_type::difference_type;
        using reference = typename base_type::reference;
        using const_reference = const typename base_type::reference;
        using pointer = typename base_type::pointer;
        using const_pointer = const typename base_type::pointer;

    public:
        virtual ~iterator() = default;
        iterator() = default;
        iterator(const iterator&) = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        iterator(iterator&&) = default;

#else

        iterator(iterator&& other)
            : base_type(std::move(other))
        {
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        explicit iterator(circular_buffer<element_type, allocator_type>* container, size_t pos = 0)
            : base_type(container, pos)
        {
        }

        iterator& operator=(const iterator&) noexcept = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        iterator& operator=(iterator&&) noexcept = default;

#else

        iterator& operator=(iterator&& other) noexcept
        {
            if(this != &other)
            {
                base_type::operator=(std::move(other));
            }
            return *this;
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        bool operator==(const iterator& other) const
        {
            return base_type::operator==(other);
        }

        bool operator!=(const iterator& other) const
        {
            return base_type::operator!=(other);
        }

        bool operator<(const iterator& other) const
        {
            return base_type::operator<(other);
        }

        bool operator>(const iterator& other) const
        {
            return base_type::operator>(other);
        }

        bool operator<=(const iterator& other) const
        {
            return base_type::operator<=(other);
        }

        bool operator>=(const iterator& other) const
        {
            return base_type::operator>=(other);
        }

        reference operator*()
        {
            return base_type::operator*();
        }

        const_reference operator*() const
        {
            return base_type::operator*();
        }

        pointer operator->()
        {
            return base_type::operator->();
        }

        const_pointer operator->() const
        {
            return base_type::operator->();
        }

        iterator& operator++()
        {
            this->increment();
            return *this;
        }

        iterator operator++(int)
        {
            iterator it(*this);
            return ++it;
        }

        iterator& operator--()
        {
            this->decrement();
            return *this;
        }

        iterator operator--(int)
        {
            iterator it(*this);
            return --it;
        }
    };

    class const_iterator
        : public iterator_base
    {
        friend class circular_buffer<element_type, allocator_type>;

    public:
        using base_type = iterator_base;
        using iterator_category = typename base_type::iterator_category;
        using difference_type = typename base_type::difference_type;
        using reference = typename base_type::reference;
        using const_reference = const typename base_type::reference;
        using pointer = typename base_type::pointer;
        using const_pointer = const typename base_type::pointer;

    public:
        virtual ~const_iterator() = default;
        const_iterator() = default;
        const_iterator(const const_iterator&) = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        const_iterator(const_iterator&&) = default;

#else

        const_iterator(const_iterator&& other)
            : base_type(std::move(other))
        {
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        explicit const_iterator(circular_buffer<element_type, allocator_type>* container, size_t pos = 0)
            : base_type(container, pos)
        {
        }

        const_iterator& operator=(const const_iterator&) noexcept = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        const_iterator& operator=(const_iterator&&) noexcept = default;

#else

        const_iterator& operator=(const_iterator&& other) noexcept
        {
            if(this != &other)
            {
                base_type::operator=(std::move(other));
            }
            return *this;
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        bool operator==(const const_iterator& other) const
        {
            return base_type::operator==(other);
        }

        bool operator!=(const const_iterator& other) const
        {
            return base_type::operator!=(other);
        }

        bool operator<(const const_iterator& other) const
        {
            return base_type::operator<(other);
        }

        bool operator>(const const_iterator& other) const
        {
            return base_type::operator>(other);
        }

        bool operator<=(const const_iterator& other) const
        {
            return base_type::operator<=(other);
        }

        bool operator>=(const const_iterator& other) const
        {
            return base_type::operator>=(other);
        }

        const_reference operator*() const
        {
            return base_type::operator*();
        }

        const_pointer operator->() const
        {
            return base_type::operator->();
        }

        const_iterator& operator++()
        {
            this->increment();
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator it(*this);
            return ++it;
        }

        const_iterator& operator--()
        {
            this->decrement();
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator it(*this);
            return --it;
        }
    };

    class reverse_iterator
        : public iterator_base
    {
        friend class circular_buffer<element_type, allocator_type>;

    public:
        using base_type = iterator_base;
        using iterator_category = typename base_type::iterator_category;
        using difference_type = typename base_type::difference_type;
        using reference = typename base_type::reference;
        using const_reference = const typename base_type::reference;
        using pointer = typename base_type::pointer;
        using const_pointer = const typename base_type::pointer;

    public:
        virtual ~reverse_iterator() = default;
        reverse_iterator() = default;
        reverse_iterator(const reverse_iterator&) = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        reverse_iterator(reverse_iterator&&) = default;

#else

        reverse_iterator(reverse_iterator&& other)
            : base_type(std::move(other))
        {
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        explicit reverse_iterator(circular_buffer<element_type, allocator_type>* container, size_t pos = 0)
            : base_type(container, pos)
        {
        }

        reverse_iterator& operator=(const reverse_iterator&) noexcept = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        reverse_iterator& operator=(reverse_iterator&&) noexcept = default;

#else

        reverse_iterator& operator=(reverse_iterator&& other) noexcept
        {
            if(this != &other)
            {
                base_type::operator=(std::move(other));
            }
            return *this;
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        bool operator==(const reverse_iterator& other) const
        {
            return base_type::operator==(other);
        }

        bool operator!=(const reverse_iterator& other) const
        {
            return base_type::operator!=(other);
        }

        bool operator<(const reverse_iterator& other) const
        {
            return base_type::operator<(other);
        }

        bool operator>(const reverse_iterator& other) const
        {
            return base_type::operator>(other);
        }

        bool operator<=(const reverse_iterator& other) const
        {
            return base_type::operator<=(other);
        }

        bool operator>=(const reverse_iterator& other) const
        {
            return base_type::operator>=(other);
        }

        reference operator*()
        {
            return base_type::operator*();
        }

        const_reference operator*() const
        {
            return base_type::operator*();
        }

        pointer operator->()
        {
            return base_type::operator->();
        }

        const_pointer operator->() const
        {
            return base_type::operator->();
        }

        reverse_iterator& operator++()
        {
            this->decrement();
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator it(*this);
            return ++it;
        }

        reverse_iterator& operator--()
        {
            this->increment();
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator it(*this);
            return --it;
        }
    };

    class const_reverse_iterator
        : public iterator_base
    {
        friend class circular_buffer<element_type, allocator_type>;

    public:
        using base_type = iterator_base;
        using iterator_category = typename base_type::iterator_category;
        using difference_type = typename base_type::difference_type;
        using reference = typename base_type::reference;
        using const_reference = const typename base_type::reference;
        using pointer = typename base_type::pointer;
        using const_pointer = const typename base_type::pointer;

    public:
        virtual ~const_reverse_iterator() = default;
        const_reverse_iterator() = default;
        const_reverse_iterator(const const_reverse_iterator&) = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        const_reverse_iterator(const_reverse_iterator&&) = default;

#else

        const_reverse_iterator(const_reverse_iterator&& other)
            : base_type(std::move(other))
        {
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

        explicit const_reverse_iterator(circular_buffer<element_type, allocator_type>* container, size_t pos = 0)
            : base_type(container, pos)
        {
        }

        const_reverse_iterator& operator=(const const_reverse_iterator&) noexcept = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        const_reverse_iterator& operator=(const_reverse_iterator&&) noexcept = default;

#else

        const_reverse_iterator& operator=(const_reverse_iterator&& other) noexcept
        {
            if(this != &other)
            {
                base_type::operator=(std::move(other));
            }
            return *this;
        }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR)

        bool operator==(const const_reverse_iterator& other) const
        {
            return base_type::operator==(other);
        }

        bool operator!=(const const_reverse_iterator& other) const
        {
            return base_type::operator!=(other);
        }

        bool operator<(const const_reverse_iterator& other) const
        {
            return base_type::operator<(other);
        }

        bool operator>(const const_reverse_iterator& other) const
        {
            return base_type::operator>(other);
        }

        bool operator<=(const const_reverse_iterator& other) const
        {
            return base_type::operator<=(other);
        }

        bool operator>=(const const_reverse_iterator& other) const
        {
            return base_type::operator>=(other);
        }

        const_reference operator*() const
        {
            return base_type::operator*();
        }

        const_pointer operator->() const
        {
            return base_type::operator->();
        }

        const_reverse_iterator& operator++()
        {
            this->decrement();
            return *this;
        }

        const_reverse_iterator operator++(int)
        {
            const_reverse_iterator it(*this);
            return ++it;
        }

        const_reverse_iterator& operator--()
        {
            this->increment();
            return *this;
        }

        const_reverse_iterator operator--(int)
        {
            const_reverse_iterator it(*this);
            return --it;
        }
    };

public:
	virtual ~circular_buffer() = default;

    explicit circular_buffer(const allocator_type& alloc = allocator_type()) GO_NOEXCEPT_OR_NOTHROW
        : _buffer(alloc)
        , _front_pos(0)
        , _back_pos(this_type::_end_pos)
    {
        this->fill_buffer_to_capacity();
    }

    explicit circular_buffer(capacity_type cap, const allocator_type& alloc = allocator_type())
        : _buffer(alloc)
        , _front_pos(0)
        , _back_pos(this_type::_end_pos)
    {
        this->_buffer.reserve(cap);
        this->fill_buffer_to_capacity();
    }

    circular_buffer(size_type count, param_value_type value, const allocator_type& alloc = allocator_type())
        : _buffer(count, value, alloc)
        , _front_pos(0)
        , _back_pos(this_type::_end_pos)
    {
        const size_type count_cap = (count < this->_buffer.capacity()) ? count : this->_buffer.capacity();
        this->_back_pos = (count_cap > 0) ? (count_cap - 1) : this_type::_end_pos;
        this->fill_buffer_to_capacity();
    }

    circular_buffer(capacity_type cap, size_type count, param_value_type value, const allocator_type& alloc = allocator_type())
        : _buffer(count, value, alloc)
        , _front_pos(0)
        , _back_pos(this_type::_end_pos)
    {
        this->_buffer.reserve(cap);
        const size_type count_cap = (count < this->_buffer.capacity()) ? count : this->_buffer.capacity();
        this->_back_pos = (count_cap > 0) ? (count_cap - 1) : this_type::_end_pos;
        this->fill_buffer_to_capacity();
    }

    circular_buffer(const this_type&) = default;

#if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

    circular_buffer(this_type&&) GO_NOEXCEPT = default;

#else

    circular_buffer(this_type&& other) GO_NOEXCEPT
        : _buffer(std::move(other._buffer))
        , _front_pos(std::move(other._front_pos))
        , _back_pos(std::move(other._back_pos))
    {
    }

#endif  // #if !defined(GO_NO_CXX11_DEFAULTED_MOVE_CONSTRUCTOR)

    template<typename InputIt>
    circular_buffer(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
        : _buffer(first, last, alloc)
        , _front_pos(0)
        , _back_pos(this_type::_end_pos)
    {
        const size_type count = std::distance(first, last);
        const size_type count_cap = (count < this->_buffer.capacity()) ? count : this->_buffer.capacity();
        this->_back_pos = (count_cap > 0) ? (count_cap - 1) : this_type::_end_pos;
        this->fill_buffer_to_capacity();
    }

    template<typename InputIt>
    circular_buffer(capacity_type cap, InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
        : _buffer(first, last, alloc)
        , _front_pos(0)
        , _back_pos(this_type::_end_pos)
    {
        this->_buffer.reserve(cap);
        const size_type count = std::distance(first, last);
        const size_type count_cap = (count < this->_buffer.capacity()) ? count : this->_buffer.capacity();
        this->_back_pos = (count_cap > 0) ? (count_cap - 1) : this_type::_end_pos;
        this->fill_buffer_to_capacity();
    }

    circular_buffer(const std::initializer_list<T>& il, const allocator_type& alloc = allocator_type())
        : _buffer(il, alloc)
        , _front_pos(0)
        , _back_pos(this_type::_end_pos)
    {
        const size_type count = il.size();
        const size_type count_cap = (count < this->_buffer.capacity()) ? count : this->_buffer.capacity();
        this->_back_pos = (count_cap > 0) ? (count_cap - 1) : this_type::_end_pos;
        this->fill_buffer_to_capacity();
    }

    circular_buffer(capacity_type cap, const std::initializer_list<T>& il, const allocator_type& alloc = allocator_type())
        : _buffer(il, alloc)
        , _front_pos(0)
        , _back_pos(this_type::_end_pos)
    {
        this->_buffer.reserve(cap);
        const size_type count = il.size();
        const size_type count_cap = (count < this->_buffer.capacity()) ? count : this->_buffer.capacity();
        this->_back_pos = (count_cap > 0) ? (count_cap - 1) : this_type::_end_pos;
        this->fill_buffer_to_capacity();
    }

#if !defined(GO_COMP_CLANG)

    this_type& operator=(const this_type&) noexcept = default;

#else

    this_type& operator=(const this_type& other) noexcept
    {
        if(this != &other)
        {
            _buffer = other._buffer;
            _front_pos = other._front_pos;
            _back_pos = other._back_pos;
        }
        return *this;
    }

#endif  // #if !defined(GO_COMP_CLANG)

#if !(defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR) || defined(GO_COMP_CLANG))

    this_type& operator=(this_type&&) GO_NOEXCEPT = default;

#else

    this_type& operator=(this_type&& other) GO_NOEXCEPT
    {
        if(this != &other)
        {
            _buffer = std::move(other._buffer);
            _front_pos = std::move(other._front_pos);
            _back_pos = std::move(other._back_pos);
        }
        return *this;
    }

#endif  // #if !(defined(GO_NO_CXX11_DEFAULTED_MOVE_ASSIGN_OPERATOR) || defined(GO_COMP_CLANG))

    reference operator[](size_type pos)
    {
        return this->at(pos);
    }

    const_reference operator[](size_type pos) const
    {
        return this->at(pos);
    }

    allocator_type get_allocator() const GO_NOEXCEPT
    {
        return this->_buffer.get_allocator();
    }

    iterator begin() GO_NOEXCEPT
    {
        return iterator(this, (this->_back_pos != this_type::_end_pos) ? this->_front_pos : this->_end_pos);
    }

    iterator end() GO_NOEXCEPT
    {
        return iterator(this, this_type::_end_pos);
    }

    const_iterator begin() const GO_NOEXCEPT
    {
        return const_iterator(const_cast<this_type*>(this), (this->_back_pos != this_type::_end_pos) ? this->_front_pos : this->_end_pos);
    }

    const_iterator end() const GO_NOEXCEPT
    {
        return const_iterator(const_cast<this_type*>(this), this_type::_end_pos);
    }

    reverse_iterator rbegin() GO_NOEXCEPT
    {
        return reverse_iterator(this, this->_back_pos);
    }

    reverse_iterator rend() GO_NOEXCEPT
    {
        return reverse_iterator(this, this_type::_end_pos);
    }

    const_reverse_iterator rbegin() const GO_NOEXCEPT
    {
        return const_reverse_iterator(const_cast<this_type*>(this), this->_back_pos);
    }

    const_reverse_iterator rend() const GO_NOEXCEPT
    {
        return const_reverse_iterator(const_cast<this_type*>(this), this_type::_end_pos);
    }

    reference at(size_type pos)
    {
        if (pos >= this->size())
        {
            throw std::out_of_range("pos out of range");
        }
        const size_type buffer_size = this->_buffer.size();
        size_type buffer_pos = this->_front_pos + pos;
        if (buffer_pos >= buffer_size)
        {
            buffer_pos -= buffer_size;
        }
        return this->_buffer.at(buffer_pos);
    }

    const_reference at(size_type pos) const
    {
        if (pos >= this->size())
        {
            throw std::out_of_range("pos out of range");
        }
        const size_type buffer_size = this->_buffer.size();
        size_type buffer_pos = this->_front_pos + pos;
        if (buffer_pos >= buffer_size)
        {
            buffer_pos -= buffer_size;
        }
        return this->_buffer.at(buffer_pos);
    }

    reference front()
    {
        if (this->empty())
        {
            throw std::out_of_range("out of range");
        }
        return this->_buffer.at(this->_front_pos);
    }

    reference back()
    {
        if (this->empty())
        {
            throw std::out_of_range("out of range");
        }
        return this->_buffer.at(this->_back_pos);
    }

    const_reference front() const
    {
        if (this->empty())
        {
            throw std::out_of_range("out of range");
        }
        return this->_buffer.at(this->_front_pos);
    }

    const_reference back() const
    {
        if (this->empty())
        {
            throw std::out_of_range("out of range");
        }
        return this->_buffer.at(this->_back_pos);
    }

    size_type size() const GO_NOEXCEPT
    {
        if (this->_back_pos != this_type::_end_pos)
        {
            return ((this->_front_pos <= this->_back_pos) ? 0 : this->_buffer.capacity()) + this->_back_pos - this->_front_pos + 1;
        }
        return 0;
    }

    size_type max_size() const GO_NOEXCEPT
    {
        static const size_type maxsize = (this->_buffer.max_size() < std::numeric_limits<size_type>::max()) ? this->_buffer.max_size() : (std::numeric_limits<size_type>::max() - 1);
        return maxsize;
    }

    bool empty() const GO_NOEXCEPT
    {
        return this->_back_pos == this_type::_end_pos;
    }

    bool full() const GO_NOEXCEPT
    {
        return this->_buffer.capacity() == this->size();
    }

    capacity_type capacity() const GO_NOEXCEPT
    {
        return this->_buffer.capacity();
    }

    void resize(capacity_type new_cap)
    {
        if (new_cap == this->_buffer.capacity())
        {
            return;
        }
        if (new_cap == 0)
        {
            buffer_container_type new_buffer(this->_buffer.get_allocator());
            this->_buffer.swap(new_buffer);
            this->_buffer.reserve(new_cap);
            this->_front_pos = 0;
            this->_back_pos = this_type::_end_pos;
            this->fill_buffer_to_capacity();
            return;
        }
        if (this->empty())
        {
            buffer_container_type new_buffer(this->_buffer.get_allocator());
            this->_buffer.swap(new_buffer);
            this->_buffer.reserve(new_cap);
        }
        else
        {
            buffer_container_type new_buffer(this->_buffer.get_allocator());
            new_buffer.reserve(new_cap);
            size_type back_pos = this->size() - 1;
            const_iterator it = const_cast<const this_type*>(this)->begin();
            if (new_cap < this->size())
            {
                const difference_type diff = this->size() - new_cap;
                back_pos = new_cap - 1;
                for (difference_type i = 0; i < diff; i++)
                {
                    ++it;
                }
            }
            while (it != const_cast<const this_type*>(this)->end())
            {
                new_buffer.push_back(*it);
                ++it;
            }
            this->_buffer.swap(new_buffer);
            this->_front_pos = 0;
            this->_back_pos = back_pos;
        }
        this->fill_buffer_to_capacity();
    }

    void assign(size_type count, param_value_type value)
    {
        this->_buffer.clear();
        const size_type count_cap = (count < this->_buffer.capacity()) ? count : this->_buffer.capacity();
        for (size_type i = 0; i < count_cap; ++i)
        {
            this->_buffer.push_back(value);
        }
        this->_front_pos = 0;
        this->_back_pos = count_cap - 1;
        this->fill_buffer_to_capacity();
    }

    void assign(capacity_type cap, size_type count, param_value_type value)
    {
        this->_buffer.reserve(cap);
        this->assign(count, value);
    }

    template<typename InputIt> void assign(InputIt first, InputIt last)
    {
        this->_buffer.clear();
        const size_type count = std::distance(first, last);
        const size_type count_cap = (count < this->_buffer.capacity()) ? count : this->_buffer.capacity();
        InputIt it = first;
        if (count > count_cap)
        {
            std::advance(it, count - count_cap);
        }
        while (it != last)
        {
            this->_buffer.push_back(*it);
            ++it;
        }
        this->fill_buffer_to_capacity();
    }

    template<typename InputIt> void assign(capacity_type cap, InputIt first, InputIt last)
    {
        this->_buffer.reserve(cap);
        this->assign(first, last);
    }

    void assign(const std::initializer_list<T>& il)
    {
        this->_buffer.clear();
        const size_type count = il.size();
        const size_type count_cap = (count < this->_buffer.capacity()) ? count : this->_buffer.capacity();
        GO_TYPENAME std::initializer_list<T>::iterator it = il.begin();
        if (count > count_cap)
        {
            std::advance(it, count - count_cap);
        }
        while (it != il.end())
        {
            this->_buffer.push_back(*it);
            ++it;
        }
        this->fill_buffer_to_capacity();
    }

    void assign(capacity_type cap, const std::initializer_list<T>& il)
    {
        this->_buffer.reserve(cap);
        this->assign(il);
    }

    void swap(this_type& other) GO_NOEXCEPT
    {
        std::swap(this->_buffer, other._buffer);
        std::swap(this->_front_pos, other._front_pos);
        std::swap(this->_back_pos, other._back_pos);
    }

    void push_back(param_value_type value)
    {
        this->update_pos_for_push_back();
        this->_buffer[this->_back_pos] = value;
    }

    void push_back(rvalue_type value)
    {
        this->update_pos_for_push_back();
        this->_buffer[this->_back_pos] = std::move(value);
    }

    void push_front(param_value_type value)
    {
        this->update_pos_for_push_front();
        this->_buffer[this->_front_pos] = value;
    }

    void push_front(rvalue_type value)
    {
        this->update_pos_for_push_front();
        this->_buffer[this->_front_pos] = std::move(value);
    }

    void pop_back()
    {
        if (this->empty())
        {
            return;
        }
        const bool make_empty = this->size() == 1;
        this->_buffer[this->_back_pos] = value_type();
        if (this->_back_pos == 0)
        {
            this->_back_pos = this->max_pos();
        }
        else
        {
            --(this->_back_pos);
        }
        if (make_empty)
        {
            this->clear();
        }
    }

    void pop_front()
    {
        if (this->empty())
        {
            return;
        }
        const bool make_empty = this->size() == 1;
        this->_buffer[this->_front_pos] = value_type();
        if (this->_front_pos == this->max_pos())
        {
            this->_front_pos = 0;
        }
        else
        {
            ++(this->_front_pos);
        }
        if (make_empty)
        {
            this->clear();
        }
    }

    iterator insert(iterator it, param_value_type value)
    {
        value_type v = value;
        return insert(it, std::forward<value_type>(v));
    }

    iterator insert(iterator it, rvalue_type value)
    {
        if (!is_valid_iterator_associated_to_this(it))
        {
            throw std::logic_error("invalid iterator");
        }
        if (this->_buffer.capacity() == 0)
        {
            throw std::out_of_range("out of range");
        }
        if (this->empty())
        {
            this->push_back(value);
            return this->begin();
        }
        else
        {
            if (it._pos == this_type::_end_pos)
            {
                it._pos = this->_back_pos;
            }
            const bool it_is_front = it._pos == this->_front_pos;
            const bool it_is_back = it._pos == this->_back_pos;
            if (this->full())
            {
                this->pop_front();
            }
            if (it_is_front)
            {
                this->push_front(value);
                return this->begin();
            }
            else
            {
                this->push_back(value);
                if (it_is_back)
                {
                    return iterator(this, this->_back_pos);
                }
                else
                {
                    iterator it1(this, this->_back_pos);
                    iterator it0 = it1--;
                    while (it1 != it)
                    {
                        std::swap(*it0, *it1);
                        --it0;
                        --it1;
                    }
                }
                return it;
            }
        }
    }

    iterator insert(iterator it)
    {
        return insert(it, element_type());
    }

    iterator erase(iterator it)
    {
        if (!is_valid_iterator_associated_to_this(it))
        {
            throw std::logic_error("invalid iterator");
        }
        if (this->_buffer.capacity() == 0)
        {
            throw std::out_of_range("out of range");
        }
        if (this->empty() || (it._pos == this_type::_end_pos))
        {
            return this->end();
        }
        else
        {
            if (it._pos == this->_front_pos)
            {
                this->pop_front();
                return this->begin();
            }
            if (it._pos == this->_back_pos)
            {
                this->pop_back();
                return this->end();
            }
            iterator it1(this, this->_back_pos);
            iterator it0 = it1--;
            while (it1 != it)
            {
                std::swap(*it0, *it1);
                --it0;
                --it1;
            }
            this->pop_back();
            return it;
        }
    }

    void clear() GO_NOEXCEPT
    {
        this->_front_pos = 0;
        this->_back_pos = this_type::_end_pos;
        this->_buffer.clear();
        this->fill_buffer_to_capacity();
    }

private:
    GO_CONSTEXPR size_type max_pos() const GO_NOEXCEPT
    {
        return this->_buffer.capacity() - 1;
    }

    void fill_buffer_to_capacity()
    {
        while (this->_buffer.size() < this->_buffer.capacity())
        {
            this->_buffer.push_back(value_type());
        }
    }

    void update_pos_for_push_back()
    {
        if (this->empty())
        {
            this->_front_pos = this->_back_pos = 0;
        }
        else if (this->full())
        {
            if (this->_back_pos == this->max_pos())
            {
                this->_back_pos = 0;
                this->_front_pos = 1;
            }
            else
            {
                this->_back_pos = this->_front_pos;
                this->_front_pos = (this->_front_pos == this->max_pos()) ? 0 : (this->_front_pos + 1);
            }
        }
        else
        {
            if (this->_back_pos == this->max_pos())
            {
                this->_back_pos = 0;
            }
            else
            {
                ++(this->_back_pos);
            }
        }
    }

    void update_pos_for_push_front()
    {
        if (this->empty())
        {
            this->_front_pos = this->_back_pos = this->max_pos();
        }
        else if (this->full())
        {
            if (this->_front_pos == 0)
            {
                this->_front_pos = this->_back_pos;
                --(this->_back_pos);
            }
            else
            {
                --(this->_front_pos);
                this->_back_pos = (this->_back_pos == 0) ? this->max_pos() : (this->_back_pos - 1);
            }
        }
        else
        {
            if (this->_front_pos == 0)
            {
                this->_front_pos = this->max_pos();
            }
            else
            {
                --(this->_front_pos);
            }
        }
    }

    template <class I>
    bool is_valid_iterator_associated_to_this(const I& it)
    {
        if (it._container == this)
        {
            return ((this->_front_pos <= this->_back_pos)
                ? ((it._pos >= this->_front_pos) && (it._pos <= this->_back_pos))
                : ((it._pos <= this->_back_pos) || ((it._pos >= this->_front_pos) && (it._pos < this->size()))))
                || (it._pos == this_type::_end_pos);
        }
        return false;
    }

private:
    static GO_CONSTEXPR size_type _end_pos = std::numeric_limits<size_type>::max();
    buffer_container_type _buffer;
    size_type _front_pos;
    size_type _back_pos;
};

}
}
}

#if defined(GO_UTILITY_CONTAINER_CIRCULAR_BUFFER_RESTORE_MAX)
#undef GO_UTILITY_CONTAINER_CIRCULAR_BUFFER_RESTORE_MAX
#pragma pop_macro("max")
#endif  // #if defined(GO_UTILITY_CONTAINER_CIRCULAR_BUFFER_RESTORE_MAX)

#endif  // #if defined(GO_NO_CXX11_RANGE_FOR_LOOP)

#endif  // #ifndef GO_UTILITY_CONTAINER_CIRCULAR_BUFFER_HPP_INCLUDED
