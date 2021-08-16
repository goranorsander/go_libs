#ifndef GO_MVVM_EVENT_HPP_INCLUDED
#define GO_MVVM_EVENT_HPP_INCLUDED

//
//  event.hpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <string>
#include <go/property/nameless/read_only_property.hpp>
#include <go/type_traits/noncopyable_nonmovable.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_event;
using event = basic_event<std::string>;
using wevent = basic_event<std::wstring>;

template<class S>
class basic_event
    : public std::enable_shared_from_this<basic_event<S>>
    , public go::type_traits::noncopyable_nonmovable
{
public:
    using string_type = S;
    using this_type = basic_event<S>;
    using ptr = typename std::shared_ptr<basic_event<S>>;
    using wptr = typename std::weak_ptr<basic_event<S>>;
    using event_type_type = typename go::property::nameless::read_only::property<S>;

public:
    virtual ~basic_event() GO_DEFAULT_DESTRUCTOR

protected:
    explicit basic_event(const S& event_type_);

public:
    event_type_type event_type;

public:
    static ptr create(const S& event_type_);

private:
    const S _event_type;
};

template<class S>
inline basic_event<S>::basic_event(const S& event_type_)
    : std::enable_shared_from_this<basic_event<S>>()
    , go::type_traits::noncopyable_nonmovable()
    , event_type(nullptr)
    , _event_type(event_type_)
{
    event_type.getter([this]() -> S { return _event_type; });
}

template<class S>
inline std::shared_ptr<basic_event<S>> basic_event<S>::create(const S& event_type_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const S& event_type_) : this_type(event_type_) {}
    };

    return std::make_shared<make_shared_enabler, const S&>(event_type_);
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_EVENT_HPP_INCLUDED
