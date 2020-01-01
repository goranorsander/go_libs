#ifndef GO_BOOST_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_BOOST_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  property_changed_arguments.hpp
//
//  Copyright 2015-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <boost/make_shared.hpp>

#include <go_boost/mvvm/arguments.hpp>
#include <go_boost/mvvm/container_changed_arguments.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S> class basic_property_changed_arguments;
typedef basic_property_changed_arguments<std::string> property_changed_arguments;
typedef basic_property_changed_arguments<std::wstring> wproperty_changed_arguments;

template<class S>
class basic_property_changed_arguments
    : public go_boost::mvvm::arguments
{
public:
    typedef S string_type;
    typedef basic_property_changed_arguments<string_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~basic_property_changed_arguments() GO_BOOST_DEFAULT_DESTRUCTOR

protected:
    explicit basic_property_changed_arguments(const string_type& property_name_);

public:
    static boost::shared_ptr<basic_property_changed_arguments<S>> create(const string_type& property_name_);

public:
    go_boost::property::nameless::read_only::value_property<string_type> property_name;
};

template<>
inline basic_property_changed_arguments<std::string>::basic_property_changed_arguments(const std::string& property_name_)
    : go_boost::mvvm::arguments()
    , property_name(property_name_)
{
}

template<>
inline basic_property_changed_arguments<std::wstring>::basic_property_changed_arguments(const std::wstring& property_name_)
    : go_boost::mvvm::arguments()
    , property_name(property_name_)
{
}

template<class S>
inline basic_property_changed_arguments<S>::basic_property_changed_arguments(const S& property_name_)
    : go_boost::mvvm::arguments()
    , property_name(property_name_)
{
}

template<>
inline boost::shared_ptr<basic_property_changed_arguments<std::string>> basic_property_changed_arguments<std::string>::create(const std::string& property_name_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const std::string& property_name_) : this_type(property_name_) {}
    };

    return boost::make_shared<make_shared_enabler, const std::string&>(property_name_);
#else
    return boost::shared_ptr<this_type>(new this_type(property_name_));
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_property_changed_arguments<std::wstring>> basic_property_changed_arguments<std::wstring>::create(const std::wstring& property_name_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const std::wstring& property_name_) : this_type(property_name_) {}
    };

    return boost::make_shared<make_shared_enabler, const std::wstring&>(property_name_);
#else
    return boost::shared_ptr<this_type>(new this_type(property_name_));
#endif // BOOST_MSVC > 1500
}

template<class S>
inline boost::shared_ptr<basic_property_changed_arguments<S>> basic_property_changed_arguments<S>::create(const S& property_name_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        explicit make_shared_enabler(const S& property_name_) : this_type(property_name_) {}
    };

    return boost::make_shared<make_shared_enabler, const S&>(property_name_);
#else
    return boost::shared_ptr<this_type>(new this_type(property_name_));
#endif // BOOST_MSVC > 1500
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
