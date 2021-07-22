//
//  container_benchmark.cpp
//
//  Copyright 2019-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if (defined(GO_COMP_MSVC) && (GO_MSVC_VER < 1900))
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
int main() { return -1; }
#else

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>

#include <go/diagnostics/benchmark.hpp>
#include <go/namespace_alias.hpp>
#include <go/utility/exchange.hpp>
#include <go/utility/range/sequentially_increasing.hpp>

#if !defined(GO_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS)
#define GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS( _class_name_ ) \
public: \
    ~_class_name_() = default; \
    _class_name_() = default; \
    GO_CONSTEXPR bool operator==(const _class_name_& other) const { return _key == other._key; } \
    GO_CONSTEXPR bool operator!=(const _class_name_& other) const { return !operator==(other); } \
    GO_CONSTEXPR bool operator<(const _class_name_& other) const { return _key < other._key; } \
    GO_CONSTEXPR bool operator<=(const _class_name_& other) const { return _key <= other._key; } \
    GO_CONSTEXPR bool operator>(const _class_name_& other) const { return _key > other._key; } \
    GO_CONSTEXPR bool operator>=(const _class_name_& other) const { return _key >= other._key; } \
    uint64_t _key = 0;
#else
#define GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS( _class_name_ ) \
public: \
    ~_class_name_() = default; \
    _class_name_() : _key(0) {} \
    GO_CONSTEXPR bool operator==(const _class_name_& other) const { return _key == other._key; } \
    GO_CONSTEXPR bool operator!=(const _class_name_& other) const { return !operator==(other); } \
    GO_CONSTEXPR bool operator<(const _class_name_& other) const { return _key < other._key; } \
    GO_CONSTEXPR bool operator<=(const _class_name_& other) const { return _key <= other._key; } \
    GO_CONSTEXPR bool operator>(const _class_name_& other) const { return _key > other._key; } \
    GO_CONSTEXPR bool operator>=(const _class_name_& other) const { return _key >= other._key; } \
    uint64_t _key;
#endif  // #if !defined(GO_NO_CXX11_NON_STATIC_DATA_MEMBER_INITIALIZERS)

#define GO_IMPLEMENT_CONTAINER_ELEMENT_DATA( _element_size_in_bytes_ ) \
public: \
    std::array<char, _element_size_in_bytes_ - sizeof(uint64_t)> _data;

#define GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_COPY_FUNCTIONS( _class_name_ ) \
public: \
    _class_name_(const _class_name_& other) : _key(other._key) {} \
    explicit _class_name_(const uint64_t key) : _key(key) {} \
    _class_name_& operator=(const _class_name_& other) noexcept { if (&other != this) { _key = other._key; } return *this; }

#define GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_COPY_FUNCTIONS( _class_name_ ) \
public: \
    _class_name_(const _class_name_& other) : _key(other._key), _data(other._data) {} \
    explicit _class_name_(const uint64_t key) : _key(key), _data() {} \
    _class_name_& operator=(const _class_name_& other) noexcept { if (&other != this) { _key = other._key; _data = other._data; } return *this; }

#if !defined(GO_NO_CXX14_STD_EXCHANGE)
#define GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_MOVE_FUNCTIONS( _class_name_ ) \
public: \
    explicit _class_name_(_class_name_&& other) : _key(std::exchange(other._key, 0)) {} \
    _class_name_& operator=(_class_name_&& other) noexcept { if (&other != this) { _key = std::exchange(other._key, 0); } return *this; }
#else
#define GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_MOVE_FUNCTIONS( _class_name_ ) \
public: \
    explicit _class_name_(_class_name_&& other) : _key(u::exchange(other._key, 0)) {} \
    _class_name_& operator=(_class_name_&& other) noexcept { if (&other != this) { _key = u::exchange(other._key, 0); } return *this; }
#endif  // #if !defined(GO_NO_CXX14_STD_EXCHANGE)

#if !defined(GO_NO_CXX14_STD_EXCHANGE)
#define GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_MOVE_FUNCTIONS( _class_name_ ) \
public: \
    explicit _class_name_(_class_name_&& other) : _key(std::exchange(other._key, 0)), _data(std::move(other._data)) {} \
    _class_name_& operator=(_class_name_&& other) noexcept { if (&other != this) { _key = std::exchange(other._key, 0); _data = std::move(other._data); } return *this; }
#else
#define GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_MOVE_FUNCTIONS( _class_name_ ) \
public: \
    explicit _class_name_(_class_name_&& other) : _key(u::exchange(other._key, 0)), _data(std::move(other._data)) {} \
    _class_name_& operator=(_class_name_&& other) noexcept { if (&other != this) { _key = u::exchange(other._key, 0); _data = std::move(other._data); } return *this; }
#endif  // #if !defined(GO_NO_CXX14_STD_EXCHANGE)

#define GO_IMPLEMENT_CONTAINER_ELEMENT_DELETE_MOVE_FUNCTIONS( _class_name_ ) \
private: \
    explicit _class_name_(_class_name_&&) = delete; \
    _class_name_& operator=(_class_name_&&) = delete;

#define GO_IMPLEMENT_CONTAINER_ELEMENT_STD_HASH_FUNCTIONS( _class_name_ ) \
template<> struct hash<_class_name_> \
{ \
    typedef _class_name_ argument_type; \
    typedef std::size_t result_type; \
    result_type operator()(const argument_type& e) const GO_NOEXCEPT \
    { \
        return std::hash<uint64_t>{}(e._key); \
    } \
};

namespace benchmark
{
namespace movable
{

class element_8_byte;
class element_64_byte;
class element_512_byte;
class element_4096_byte;

}
namespace nonmovable
{

class element_8_byte;
class element_64_byte;
class element_512_byte;
class element_4096_byte;

}
}

namespace std
{

template<> struct hash<benchmark::movable::element_8_byte>;
template<> struct hash<benchmark::movable::element_64_byte>;
template<> struct hash<benchmark::movable::element_512_byte>;
template<> struct hash<benchmark::movable::element_4096_byte>;

template<> struct hash<benchmark::nonmovable::element_8_byte>;
template<> struct hash<benchmark::nonmovable::element_64_byte>;
template<> struct hash<benchmark::nonmovable::element_512_byte>;
template<> struct hash<benchmark::nonmovable::element_4096_byte>;

}

namespace benchmark
{
namespace movable
{

class element_8_byte
{
    GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS(element_8_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_COPY_FUNCTIONS(element_8_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_MOVE_FUNCTIONS(element_8_byte)
};

class element_64_byte
{
    GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS(element_64_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DATA(64)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_COPY_FUNCTIONS(element_64_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_MOVE_FUNCTIONS(element_64_byte)
};

class element_512_byte
{
    GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS(element_512_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DATA(512)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_COPY_FUNCTIONS(element_512_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_MOVE_FUNCTIONS(element_512_byte)
};

class element_4096_byte
{
    GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS(element_4096_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DATA(4096)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_COPY_FUNCTIONS(element_4096_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_MOVE_FUNCTIONS(element_4096_byte)
};

}

namespace nonmovable
{

class element_8_byte
{
    GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS(element_8_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_COPY_FUNCTIONS(element_8_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DELETE_MOVE_FUNCTIONS(element_8_byte)
};

class element_64_byte
{
    GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS(element_64_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DATA(64)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_COPY_FUNCTIONS(element_64_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DELETE_MOVE_FUNCTIONS(element_64_byte)
};

class element_512_byte
{
    GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS(element_512_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DATA(512)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_COPY_FUNCTIONS(element_512_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DELETE_MOVE_FUNCTIONS(element_512_byte)
};

class element_4096_byte
{
    GO_IMPLEMENT_CONTAINER_ELEMENT_COMMON_FUNCTIONS(element_4096_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DATA(4096)
    GO_IMPLEMENT_CONTAINER_ELEMENT_KEY_DATA_COPY_FUNCTIONS(element_4096_byte)
    GO_IMPLEMENT_CONTAINER_ELEMENT_DELETE_MOVE_FUNCTIONS(element_4096_byte)
};

}

using test_case_number_of_elements_type = std::array<uint64_t, 10>;

const test_case_number_of_elements_type tiny_test_case_number_of_elements = { 2500, 5000, 7500, 10000, 12500, 15000, 17500, 20000, 22500, 25000 };
//const test_case_number_of_elements_type small_test_case_number_of_elements = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };
const test_case_number_of_elements_type standard_test_case_number_of_elements = { 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000 };

const std::vector<uint64_t>& key_sequence(const uint64_t number_of_keys)
{
    using key_sequence_type = std::vector<uint64_t>;
    using key_sequences_type = std::map<uint64_t, key_sequence_type>;

    static std::map<uint64_t, std::vector<uint64_t>> test_case_key_sequences = std::map<uint64_t, std::vector<uint64_t>>();
    static auto randomizer = std::default_random_engine{};

    auto ks = test_case_key_sequences.find(number_of_keys);
    if (ks == test_case_key_sequences.end())
    {
        key_sequence_type keys(number_of_keys);
        std::iota(keys.begin(), keys.end(), 0);
        std::shuffle(keys.begin(), keys.end(), randomizer);
        auto ret = test_case_key_sequences.insert(key_sequences_type::value_type(number_of_keys, keys));
        ks = ret.first;
    }
    return ks->second;
}

const std::vector<uint64_t>& key_sequence_at(const uint64_t number_of_keys)
{
    using key_sequence_type = std::vector<uint64_t>;
    using key_sequences_type = std::map<uint64_t, key_sequence_type>;

    static std::map<uint64_t, std::vector<uint64_t>> test_case_key_sequences = std::map<uint64_t, std::vector<uint64_t>>();

    auto ks = test_case_key_sequences.find(number_of_keys);
    if (ks == test_case_key_sequences.end())
    {
        key_sequence_type keys(number_of_keys);
        ur::sequentially_increasing<uint64_t> g(1, 2);
        std::generate(keys.begin(), keys.end(), g);
        auto ret = test_case_key_sequences.insert(key_sequences_type::value_type(number_of_keys, keys));
        ks = ret.first;
    }
    return ks->second;
}

namespace movable
{

template <class C>
void add_elements(const uint64_t number_of_elements, std::function<void(typename C::value_type&&)> add, db::stopwatch& duration)
{
    using container_type = C;
    using element_type = typename container_type::value_type;

    auto keys = key_sequence(number_of_elements);
    duration.start();
    for (const uint64_t key : keys)
    {
        element_type e(key);
        add(std::move(e));
    }
    duration.stop();
}

template <class C>
void add_keyed_elements(const uint64_t number_of_elements, std::function<void(typename C::value_type&&)> add, db::stopwatch& duration)
{
    using container_type = C;
    using value_type = typename container_type::value_type;
    using mapped_type = typename container_type::mapped_type;
    using element_type = value_type;

    auto keys = key_sequence(number_of_elements);
    duration.start();
    for (const uint64_t key : keys)
    {
        element_type e(key, mapped_type(key));
        add(std::move(e));
    }
    duration.stop();
}

template <class C>
void emplace_elements(const uint64_t number_of_elements, std::function<void(typename C::value_type&&)> emplace, db::stopwatch& duration)
{
    using container_type = C;
    using element_type = typename container_type::value_type;

    auto keys = key_sequence(number_of_elements);
    duration.start();
    for (const uint64_t key : keys)
    {
        element_type e(key);
        emplace(std::move(e));
    }
    duration.stop();
}

template <class C>
void emplace_elements_at(const uint64_t number_of_elements, std::function<typename C::iterator(typename C::const_iterator, typename C::value_type&&)> emplace, std::function<typename C::const_iterator()> begin, std::function<typename C::const_iterator()> end, db::stopwatch& duration)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using const_iterator = typename container_type::const_iterator;

    auto keys = key_sequence_at(number_of_elements);
    {
        for (const uint64_t key : keys)
        {
            element_type e(key);
            emplace(end(), std::move(e));
        }
    }
    {
        duration.start();
        const_iterator it = begin();
        for (const uint64_t key : keys)
        {
            element_type e(key - 1);
            it = emplace(it, std::move(e));
            std::advance(it, 2);
        }
        duration.stop();
    }
}

template <class C>
void emplace_keyed_elements_at(const uint64_t number_of_elements, std::function<std::pair<typename C::iterator, bool>(typename C::value_type&&)> emplace, db::stopwatch& duration)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using const_iterator = typename container_type::const_iterator;
    using return_type = std::pair<typename container_type::iterator, bool>;

    auto keys = key_sequence_at(number_of_elements);
    {
        for (const uint64_t key : keys)
        {
            element_type e(key);
            emplace(std::move(e));
        }
    }
    {
        duration.start();
        for (const uint64_t key : keys)
        {
            element_type e(key - 1);
            emplace(std::move(e));
        }
        duration.stop();
    }
}

template <class C>
void emplace_mapped_elements_at(const uint64_t number_of_elements, std::function<std::pair<typename C::iterator, bool>(typename C::value_type&&)> emplace, db::stopwatch& duration)
{
    using container_type = C;
    using value_type = typename container_type::value_type;
    using mapped_type = typename container_type::mapped_type;
    using element_type = value_type;
    using const_iterator = typename container_type::const_iterator;
    using return_type = std::pair<typename container_type::iterator, bool>;

    auto keys = key_sequence_at(number_of_elements);
    {
        for (const uint64_t key : keys)
        {
            element_type e(key, mapped_type(key));
            emplace(std::move(e));
        }
    }
    {
        duration.start();
        for (const uint64_t key : keys)
        {
            const uint64_t k = key - 1;
            element_type e(k, mapped_type(k));
            emplace(std::move(e));
        }
        duration.stop();
    }
}

template <class C>
void std_container_push_back(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using add_function = std::function<void(element_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "push_back\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        add_function add = std::bind(static_cast<void(container_type::*)(element_type&&)>(&container_type::push_back), &c, ph::_1);
        db::stopwatch duration;
        add_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_reserved_push_back(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using add_function = std::function<void(element_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "push_back\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        c.reserve(number_of_elements);
        add_function add = std::bind(static_cast<void(container_type::*)(element_type&&)>(&container_type::push_back), &c, ph::_1);
        db::stopwatch duration;
        add_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_push_front(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using add_function = std::function<void(element_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "push_front\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        add_function add = std::bind(static_cast<void(container_type::*)(element_type&&)>(&container_type::push_front), &c, ph::_1);
        db::stopwatch duration;
        add_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_insert(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using return_type = std::pair<typename container_type::iterator, bool>;
    using add_function = std::function<return_type(element_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "insert\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        add_function add = std::bind(static_cast<return_type(container_type::*)(element_type&&)>(&container_type::insert), &c, ph::_1);
        db::stopwatch duration;
        add_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_keyed_insert(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using key_type = typename container_type::key_type;
    using value_type = typename container_type::value_type;
    using mapped_type = typename container_type::mapped_type;
    using element_type = value_type;
    using return_type = std::pair<typename container_type::iterator, bool>;
    using add_function = std::function<return_type(element_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "insert\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        add_function add = std::bind(static_cast<return_type(container_type::*)(element_type&&)>(&container_type::insert), &c, ph::_1);
        db::stopwatch duration;
        add_keyed_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_emplace_back(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using emplace_function = std::function<void(element_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "emplace_back\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        emplace_function emplace = std::bind(&container_type::template emplace_back<element_type>, &c, ph::_1);
        db::stopwatch duration;
        emplace_elements<container_type>(number_of_elements, emplace, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_reserved_emplace_back(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using emplace_function = std::function<void(element_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "emplace_back\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        c.reserve(number_of_elements);
        emplace_function emplace = std::bind(&container_type::template emplace_back<element_type>, &c, ph::_1);
        db::stopwatch duration;
        emplace_elements<container_type>(number_of_elements, emplace, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_emplace_front(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using emplace_function = std::function<void(element_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "emplace_front\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        emplace_function emplace = std::bind(&container_type::template emplace_front<element_type>, &c, ph::_1);
        db::stopwatch duration;
        emplace_elements<container_type>(number_of_elements, emplace, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_emplace(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using emplace_function = std::function<typename container_type::iterator(typename container_type::const_iterator, element_type&&)>;
    using iterator_function = std::function<typename container_type::const_iterator()>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "emplace\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        emplace_function emplace = std::bind(&container_type::template emplace<element_type>, &c, ph::_1, ph::_2);
        iterator_function begin = std::bind(&container_type::cbegin, &c);
        iterator_function end = std::bind(&container_type::cend, &c);
        db::stopwatch duration;
        emplace_elements_at<container_type>(number_of_elements, emplace, begin, end, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_reserved_emplace(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using emplace_function = std::function<typename container_type::iterator(typename container_type::const_iterator, element_type&&)>;
    using iterator_function = std::function<typename container_type::const_iterator()>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "emplace\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        c.reserve(number_of_elements);
        emplace_function emplace = std::bind(&container_type::template emplace<element_type>, &c, ph::_1, ph::_2);
        iterator_function begin = std::bind(&container_type::cbegin, &c);
        iterator_function end = std::bind(&container_type::cend, &c);
        db::stopwatch duration;
        emplace_elements_at<container_type>(number_of_elements, emplace, begin, end, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_emplace_keyed(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using return_type = std::pair<typename container_type::iterator, bool>;
    using emplace_function = std::function<return_type(element_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "emplace\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        emplace_function emplace = std::bind(&container_type::template emplace<element_type>, &c, ph::_1);
        db::stopwatch duration;
        emplace_keyed_elements_at<container_type>(number_of_elements, emplace, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_emplace_mapped(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using value_type = typename container_type::value_type;
    using mapped_type = typename container_type::mapped_type;
    using element_type = value_type;
    using return_type = std::pair<typename container_type::iterator, bool>;
    using emplace_function = std::function<return_type(value_type&&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "emplace\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        emplace_function emplace = std::bind(&container_type::template emplace<value_type>, &c, ph::_1);
        db::stopwatch duration;
        emplace_mapped_elements_at<container_type>(number_of_elements, emplace, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

}

namespace nonmovable
{

template <class T>
class allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_swap = std::false_type;
    using is_always_equal = std::true_type;

    template <class U>
    struct rebind
    {
        using other = allocator<U>;
    };

public:
    ~allocator() = default;
    allocator() GO_NOEXCEPT = default;
    allocator(const allocator& /*other*/) GO_NOEXCEPT = default;
    template<class U>
    explicit allocator(const allocator<U>& /*other*/) GO_NOEXCEPT {}

    static pointer allocate(std::size_t n, const void* /*hint*/)
    {
        return allocate(n);
    }

    static pointer allocate(std::size_t n)
    {
        return reinterpret_cast<pointer>(::operator new(n*sizeof(value_type)));
    }

    static void deallocate(pointer p, std::size_t /*n*/)
    {
        ::operator delete(reinterpret_cast<void*>(p));
    }
};

template <class T1, class T2>
bool operator==(const allocator<T1>&, const allocator<T2>&) GO_NOEXCEPT
{
    return true;
}

template <class T1, class T2>
bool operator!=(const allocator<T1>&, const allocator<T2>&) GO_NOEXCEPT
{
    return false;
}

template <class C>
void add_elements(const uint64_t number_of_elements, std::function<void(const typename C::value_type&)> add, db::stopwatch& duration)
{
    using container_type = C;
    using element_type = typename container_type::value_type;

    auto keys = key_sequence(number_of_elements);
    duration.start();
    for (const uint64_t key : keys)
    {
        const element_type e(key);
        add(e);
    }
    duration.stop();
}

template <class C>
void add_keyed_elements(const uint64_t number_of_elements, std::function<void(const typename C::value_type&)> add, db::stopwatch& duration)
{
    using container_type = C;
    using value_type = typename container_type::value_type;
    using mapped_type = typename container_type::mapped_type;
    using element_type = value_type;

    auto keys = key_sequence(number_of_elements);
    duration.start();
    for (const uint64_t key : keys)
    {
        element_type e(key, mapped_type(key));
        add(e);
    }
    duration.stop();
}

template <class C>
void std_container_push_back(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using add_function = std::function<void(const element_type&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "push_back\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        add_function add = std::bind(static_cast<void(container_type::*)(const element_type&)>(&container_type::push_back), &c, ph::_1);
        db::stopwatch duration;
        add_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_reserved_push_back(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using add_function = std::function<void(const element_type&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "push_back\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        c.reserve(number_of_elements);
        add_function add = std::bind(static_cast<void(container_type::*)(const element_type&)>(&container_type::push_back), &c, ph::_1);
        db::stopwatch duration;
        add_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_push_front(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using add_function = std::function<void(const element_type&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "push_front\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        add_function add = std::bind(static_cast<void(container_type::*)(const element_type&)>(&container_type::push_front), &c, ph::_1);
        db::stopwatch duration;
        add_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_insert(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using element_type = typename container_type::value_type;
    using return_type = std::pair<typename container_type::iterator, bool>;
    using add_function = std::function<return_type(const element_type&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "insert\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        add_function add = std::bind(static_cast<return_type(container_type::*)(const element_type&)>(&container_type::insert), &c, ph::_1);
        db::stopwatch duration;
        add_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

template <class C>
void std_container_keyed_insert(const std::string& container, const std::string& element, const test_case_number_of_elements_type& test_case_number_of_elements)
{
    using container_type = C;
    using key_type = typename container_type::key_type;
    using value_type = typename container_type::value_type;
    using mapped_type = typename container_type::mapped_type;
    using element_type = value_type;
    using return_type = std::pair<typename container_type::iterator, bool>;
    using add_function = std::function<return_type(const value_type&)>;

    std::cout
        << element.c_str() << ": " << "size: " << sizeof(element_type) << " bytes" << std::endl
        << "insert\t" << container.c_str() << std::endl
        << "elements\ttime (microseconds)" << std::endl;
    for (const uint64_t number_of_elements : test_case_number_of_elements)
    {
        container_type c;
        add_function add = std::bind(static_cast<return_type(container_type::*)(const value_type&)>(&container_type::insert), &c, ph::_1);
        db::stopwatch duration;
        add_keyed_elements<container_type>(number_of_elements, add, duration);
        std::cout << number_of_elements << "\t" << duration.total_duration().count() << std::endl;
    }
    std::cout << std::endl;
}

}

void push_back()
{
    movable::std_container_push_back<std::deque<movable::element_8_byte>>("std::deque", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_push_back<std::deque<movable::element_64_byte>>("std::deque", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_push_back<std::deque<movable::element_512_byte>>("std::deque", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_push_back<std::deque<movable::element_4096_byte>>("std::deque", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_push_back<std::list<movable::element_8_byte>>("std::list", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_push_back<std::list<movable::element_64_byte>>("std::list", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_push_back<std::list<movable::element_512_byte>>("std::list", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_push_back<std::list<movable::element_4096_byte>>("std::list", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_push_back<std::vector<movable::element_8_byte>>("std::vector", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_push_back<std::vector<movable::element_64_byte>>("std::vector", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_push_back<std::vector<movable::element_512_byte>>("std::vector", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_push_back<std::vector<movable::element_4096_byte>>("std::vector", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_reserved_push_back<std::vector<movable::element_8_byte>>("std::vector+reserve", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_reserved_push_back<std::vector<movable::element_64_byte>>("std::vector+reserve", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_reserved_push_back<std::vector<movable::element_512_byte>>("std::vector+reserve", "movable::element_521_byte", standard_test_case_number_of_elements);
    movable::std_container_reserved_push_back<std::vector<movable::element_4096_byte>>("std::vector+reserve", "movable::element_4096_byte", standard_test_case_number_of_elements);

    nonmovable::std_container_push_back<std::deque<nonmovable::element_8_byte, nonmovable::allocator<nonmovable::element_8_byte>>>("std::deque", "nonmovable::element_8_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_back<std::deque<nonmovable::element_64_byte, nonmovable::allocator<nonmovable::element_64_byte>>>("std::deque", "nonmovable::element_64_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_back<std::deque<nonmovable::element_512_byte, nonmovable::allocator<nonmovable::element_512_byte>>>("std::deque", "nonmovable::element_512_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_back<std::deque<nonmovable::element_4096_byte, nonmovable::allocator<nonmovable::element_4096_byte>>>("std::deque", "nonmovable::element_4096_byte", standard_test_case_number_of_elements);

    nonmovable::std_container_push_back<std::list<nonmovable::element_8_byte, nonmovable::allocator<nonmovable::element_8_byte>>>("std::list", "nonmovable::element_8_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_back<std::list<nonmovable::element_64_byte, nonmovable::allocator<nonmovable::element_64_byte>>>("std::list", "nonmovable::element_64_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_back<std::list<nonmovable::element_512_byte, nonmovable::allocator<nonmovable::element_512_byte>>>("std::list", "nonmovable::element_512_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_back<std::list<nonmovable::element_4096_byte, nonmovable::allocator<nonmovable::element_4096_byte>>>("std::list", "nonmovable::element_4096_byte", standard_test_case_number_of_elements);

    //nonmovable::std_container_push_back<std::vector<nonmovable::element_8_byte, nonmovable::allocator<nonmovable::element_8_byte>>>("std::vector", "nonmovable::element_8_byte", standard_test_case_number_of_elements);
    //nonmovable::std_container_push_back<std::vector<nonmovable::element_64_byte>>("std::vector", "nonmovable::element_64_byte", standard_test_case_number_of_elements);
    //nonmovable::std_container_push_back<std::vector<nonmovable::element_512_byte>>("std::vector", "nonmovable::element_512_byte", standard_test_case_number_of_elements);
    //nonmovable::std_container_push_back<std::vector<nonmovable::element_4096_byte>>("std::vector", "nonmovable::element_4096_byte", standard_test_case_number_of_elements);

    //nonmovable::std_container_reserved_push_back<std::vector<nonmovable::element_8_byte>>("std::vector+reserve", "nonmovable::element_8_byte", standard_test_case_number_of_elements);
    //nonmovable::std_container_reserved_push_back<std::vector<nonmovable::element_64_byte>>("std::vector+reserve", "nonmovable::element_64_byte", standard_test_case_number_of_elements);
    //nonmovable::std_container_reserved_push_back<std::vector<nonmovable::element_512_byte>>("std::vector+reserve", "nonmovable::element_521_byte", standard_test_case_number_of_elements);
    //nonmovable::std_container_reserved_push_back<std::vector<nonmovable::element_4096_byte>>("std::vector+reserve", "nonmovable::element_4096_byte", standard_test_case_number_of_elements);
}

void push_front()
{
    movable::std_container_push_front<std::deque<movable::element_8_byte>>("std::deque", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_push_front<std::deque<movable::element_64_byte>>("std::deque", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_push_front<std::deque<movable::element_512_byte>>("std::deque", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_push_front<std::deque<movable::element_4096_byte>>("std::deque", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_push_front<std::forward_list<movable::element_8_byte>>("std::forward_list", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_push_front<std::forward_list<movable::element_64_byte>>("std::forward_list", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_push_front<std::forward_list<movable::element_512_byte>>("std::forward_list", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_push_front<std::forward_list<movable::element_4096_byte>>("std::forward_list", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_push_front<std::list<movable::element_8_byte>>("std::list", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_push_front<std::list<movable::element_64_byte>>("std::list", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_push_front<std::list<movable::element_512_byte>>("std::list", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_push_front<std::list<movable::element_4096_byte>>("std::list", "movable::element_4096_byte", standard_test_case_number_of_elements);

    nonmovable::std_container_push_front<std::deque<nonmovable::element_8_byte>>("std::deque", "nonmovable::element_8_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_front<std::deque<nonmovable::element_64_byte>>("std::deque", "nonmovable::element_64_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_front<std::deque<nonmovable::element_512_byte>>("std::deque", "nonmovable::element_512_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_front<std::deque<nonmovable::element_4096_byte>>("std::deque", "nonmovable::element_4096_byte", standard_test_case_number_of_elements);

    nonmovable::std_container_push_front<std::forward_list<nonmovable::element_8_byte>>("std::forward_list", "nonmovable::element_8_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_front<std::forward_list<nonmovable::element_64_byte>>("std::forward_list", "nonmovable::element_64_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_front<std::forward_list<nonmovable::element_512_byte>>("std::forward_list", "nonmovable::element_512_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_front<std::forward_list<nonmovable::element_4096_byte>>("std::forward_list", "nonmovable::element_4096_byte", standard_test_case_number_of_elements);

    nonmovable::std_container_push_front<std::list<nonmovable::element_8_byte>>("std::list", "nonmovable::element_8_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_front<std::list<nonmovable::element_64_byte>>("std::list", "nonmovable::element_64_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_front<std::list<nonmovable::element_512_byte>>("std::list", "nonmovable::element_512_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_push_front<std::list<nonmovable::element_4096_byte>>("std::list", "nonmovable::element_4096_byte", standard_test_case_number_of_elements);
}

void insert()
{
    movable::std_container_keyed_insert<std::map<uint64_t, movable::element_8_byte>>("std::map", "uint64_t, movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_keyed_insert<std::map<uint64_t, movable::element_64_byte>>("std::map", "uint64_t, movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_keyed_insert<std::map<uint64_t, movable::element_512_byte>>("std::map", "uint64_t, movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_keyed_insert<std::map<uint64_t, movable::element_4096_byte>>("std::map", "uint64_t, movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_insert<std::set<movable::element_8_byte>>("std::set", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_insert<std::set<movable::element_64_byte>>("std::set", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_insert<std::set<movable::element_512_byte>>("std::set", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_insert<std::set<movable::element_4096_byte>>("std::set", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_keyed_insert<std::unordered_map<uint64_t, movable::element_8_byte>>("std::unordered_map", "uint64_t, movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_keyed_insert<std::unordered_map<uint64_t, movable::element_64_byte>>("std::unordered_map", "uint64_t, movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_keyed_insert<std::unordered_map<uint64_t, movable::element_512_byte>>("std::unordered_map", "uint64_t, movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_keyed_insert<std::unordered_map<uint64_t, movable::element_4096_byte>>("std::unordered_map", "uint64_t, movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_insert<std::unordered_set<movable::element_8_byte>>("std::unordered_set", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_insert<std::unordered_set<movable::element_64_byte>>("std::unordered_set", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_insert<std::unordered_set<movable::element_512_byte>>("std::unordered_set", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_insert<std::unordered_set<movable::element_4096_byte>>("std::unordered_set", "movable::element_4096_byte", standard_test_case_number_of_elements);

    nonmovable::std_container_keyed_insert<std::map<uint64_t, nonmovable::element_8_byte>>("std::map", "uint64_t, nonmovable::element_8_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_keyed_insert<std::map<uint64_t, nonmovable::element_64_byte>>("std::map", "uint64_t, nonmovable::element_64_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_keyed_insert<std::map<uint64_t, nonmovable::element_512_byte>>("std::map", "uint64_t, nonmovable::element_512_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_keyed_insert<std::map<uint64_t, nonmovable::element_4096_byte>>("std::map", "uint64_t, nonmovable::element_4096_byte", standard_test_case_number_of_elements);

    nonmovable::std_container_insert<std::set<nonmovable::element_8_byte>>("std::set", "nonmovable::element_8_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_insert<std::set<nonmovable::element_64_byte>>("std::set", "nonmovable::element_64_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_insert<std::set<nonmovable::element_512_byte>>("std::set", "nonmovable::element_512_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_insert<std::set<nonmovable::element_4096_byte>>("std::set", "nonmovable::element_4096_byte", standard_test_case_number_of_elements);

    nonmovable::std_container_keyed_insert<std::unordered_map<uint64_t, nonmovable::element_8_byte>>("std::unordered_map", "uint64_t, nonmovable::element_8_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_keyed_insert<std::unordered_map<uint64_t, nonmovable::element_64_byte>>("std::unordered_map", "uint64_t, nonmovable::element_64_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_keyed_insert<std::unordered_map<uint64_t, nonmovable::element_512_byte>>("std::unordered_map", "uint64_t, nonmovable::element_512_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_keyed_insert<std::unordered_map<uint64_t, nonmovable::element_4096_byte>>("std::unordered_map", "uint64_t, nonmovable::element_4096_byte", standard_test_case_number_of_elements);

    nonmovable::std_container_insert<std::unordered_set<nonmovable::element_8_byte>>("std::unordered_set", "nonmovable::element_8_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_insert<std::unordered_set<nonmovable::element_64_byte>>("std::unordered_set", "nonmovable::element_64_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_insert<std::unordered_set<nonmovable::element_512_byte>>("std::unordered_set", "nonmovable::element_512_byte", standard_test_case_number_of_elements);
    nonmovable::std_container_insert<std::unordered_set<nonmovable::element_4096_byte>>("std::unordered_set", "nonmovable::element_4096_byte", standard_test_case_number_of_elements);
}

void emplace_back()
{
    movable::std_container_emplace_back<std::deque<movable::element_8_byte>>("std::deque", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_back<std::deque<movable::element_64_byte>>("std::deque", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_back<std::deque<movable::element_512_byte>>("std::deque", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_back<std::deque<movable::element_4096_byte>>("std::deque", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_emplace_back<std::list<movable::element_8_byte>>("std::list", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_back<std::list<movable::element_64_byte>>("std::list", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_back<std::list<movable::element_512_byte>>("std::list", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_back<std::list<movable::element_4096_byte>>("std::list", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_emplace_back<std::vector<movable::element_8_byte>>("std::vector", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_back<std::vector<movable::element_64_byte>>("std::vector", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_back<std::vector<movable::element_512_byte>>("std::vector", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_back<std::vector<movable::element_4096_byte>>("std::vector", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_reserved_emplace_back<std::vector<movable::element_8_byte>>("std::vector+reserve", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_reserved_emplace_back<std::vector<movable::element_64_byte>>("std::vector+reserve", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_reserved_emplace_back<std::vector<movable::element_512_byte>>("std::vector+reserve", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_reserved_emplace_back<std::vector<movable::element_4096_byte>>("std::vector+reserve", "movable::element_4096_byte", standard_test_case_number_of_elements);
}

void emplace_front()
{
    movable::std_container_emplace_front<std::deque<movable::element_8_byte>>("std::deque", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_front<std::deque<movable::element_64_byte>>("std::deque", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_front<std::deque<movable::element_512_byte>>("std::deque", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_front<std::deque<movable::element_4096_byte>>("std::deque", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_emplace_front<std::list<movable::element_8_byte>>("std::list", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_front<std::list<movable::element_64_byte>>("std::list", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_front<std::list<movable::element_512_byte>>("std::list", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_front<std::list<movable::element_4096_byte>>("std::list", "movable::element_4096_byte", standard_test_case_number_of_elements);

    movable::std_container_emplace_front<std::forward_list<movable::element_8_byte>>("std::forward_list", "movable::element_8_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_front<std::forward_list<movable::element_64_byte>>("std::forward_list", "movable::element_64_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_front<std::forward_list<movable::element_512_byte>>("std::forward_list", "movable::element_512_byte", standard_test_case_number_of_elements);
    movable::std_container_emplace_front<std::forward_list<movable::element_4096_byte>>("std::forward_list", "movable::element_4096_byte", standard_test_case_number_of_elements);
}

void emplace()
{
    movable::std_container_emplace<std::deque<movable::element_8_byte>>("std::deque", "movable::element_8_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace<std::deque<movable::element_64_byte>>("std::deque", "movable::element_64_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace<std::deque<movable::element_512_byte>>("std::deque", "movable::element_512_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace<std::deque<movable::element_4096_byte>>("std::deque", "movable::element_4096_byte", tiny_test_case_number_of_elements);

    movable::std_container_emplace<std::list<movable::element_8_byte>>("std::list", "movable::element_8_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace<std::list<movable::element_64_byte>>("std::list", "movable::element_64_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace<std::list<movable::element_512_byte>>("std::list", "movable::element_512_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace<std::list<movable::element_4096_byte>>("std::list", "movable::element_4096_byte", tiny_test_case_number_of_elements);

    movable::std_container_emplace<std::vector<movable::element_8_byte>>("std::vector", "movable::element_8_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace<std::vector<movable::element_64_byte>>("std::vector", "movable::element_64_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace<std::vector<movable::element_512_byte>>("std::vector", "movable::element_512_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace<std::vector<movable::element_4096_byte>>("std::vector", "movable::element_4096_byte", tiny_test_case_number_of_elements);

    movable::std_container_reserved_emplace<std::vector<movable::element_8_byte>>("std::vector+reserve", "movable::element_8_byte", tiny_test_case_number_of_elements);
    movable::std_container_reserved_emplace<std::vector<movable::element_64_byte>>("std::vector+reserve", "movable::element_64_byte", tiny_test_case_number_of_elements);
    movable::std_container_reserved_emplace<std::vector<movable::element_512_byte>>("std::vector+reserve", "movable::element_512_byte", tiny_test_case_number_of_elements);
    movable::std_container_reserved_emplace<std::vector<movable::element_4096_byte>>("std::vector+reserve", "movable::element_4096_byte", tiny_test_case_number_of_elements);

    movable::std_container_emplace_mapped<std::map<uint64_t, movable::element_8_byte>>("std::map", "uint64_t, movable::element_8_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_mapped<std::map<uint64_t, movable::element_64_byte>>("std::map", "uint64_t, movable::element_64_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_mapped<std::map<uint64_t, movable::element_512_byte>>("std::map", "uint64_t, movable::element_512_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_mapped<std::map<uint64_t, movable::element_4096_byte>>("std::map", "uint64_t, movable::element_4096_byte", tiny_test_case_number_of_elements);

    movable::std_container_emplace_keyed<std::set<movable::element_8_byte>>("std::set", "movable::element_8_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_keyed<std::set<movable::element_64_byte>>("std::set", "movable::element_64_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_keyed<std::set<movable::element_512_byte>>("std::set", "movable::element_512_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_keyed<std::set<movable::element_4096_byte>>("std::set", "movable::element_4096_byte", tiny_test_case_number_of_elements);

    movable::std_container_emplace_mapped<std::unordered_map<uint64_t, movable::element_8_byte>>("std::unordered_map", "uint64_t, movable::element_8_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_mapped<std::unordered_map<uint64_t, movable::element_64_byte>>("std::unordered_map", "uint64_t, movable::element_64_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_mapped<std::unordered_map<uint64_t, movable::element_512_byte>>("std::unordered_map", "uint64_t, movable::element_512_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_mapped<std::unordered_map<uint64_t, movable::element_4096_byte>>("std::unordered_map", "uint64_t, movable::element_4096_byte", tiny_test_case_number_of_elements);

    movable::std_container_emplace_keyed<std::unordered_set<movable::element_8_byte>>("std::unordered_set", "movable::element_8_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_keyed<std::unordered_set<movable::element_64_byte>>("std::unordered_set", "movable::element_64_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_keyed<std::unordered_set<movable::element_512_byte>>("std::unordered_set", "movable::element_512_byte", tiny_test_case_number_of_elements);
    movable::std_container_emplace_keyed<std::unordered_set<movable::element_4096_byte>>("std::unordered_set", "movable::element_4096_byte", tiny_test_case_number_of_elements);
}

}

namespace std
{

GO_IMPLEMENT_CONTAINER_ELEMENT_STD_HASH_FUNCTIONS(benchmark::movable::element_8_byte)
GO_IMPLEMENT_CONTAINER_ELEMENT_STD_HASH_FUNCTIONS(benchmark::movable::element_64_byte)
GO_IMPLEMENT_CONTAINER_ELEMENT_STD_HASH_FUNCTIONS(benchmark::movable::element_512_byte)
GO_IMPLEMENT_CONTAINER_ELEMENT_STD_HASH_FUNCTIONS(benchmark::movable::element_4096_byte)

GO_IMPLEMENT_CONTAINER_ELEMENT_STD_HASH_FUNCTIONS(benchmark::nonmovable::element_8_byte)
GO_IMPLEMENT_CONTAINER_ELEMENT_STD_HASH_FUNCTIONS(benchmark::nonmovable::element_64_byte)
GO_IMPLEMENT_CONTAINER_ELEMENT_STD_HASH_FUNCTIONS(benchmark::nonmovable::element_512_byte)
GO_IMPLEMENT_CONTAINER_ELEMENT_STD_HASH_FUNCTIONS(benchmark::nonmovable::element_4096_byte)

}

int main()
{
    db::stopwatch duration;

    duration.start();
    benchmark::push_back();
    benchmark::push_front();
    benchmark::insert();
    benchmark::emplace_back();
    benchmark::emplace_front();
    benchmark::emplace();
    duration.stop();

    std::cout << std::endl << "Total test time " << duration.total_duration().count() << std::endl;

    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
