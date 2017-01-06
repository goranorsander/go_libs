#ifndef GO_BOOST_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_BOOST_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  property_changed_arguments.hpp
//
//  Copyright 2015-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/make_shared.hpp>

#include <go_boost/signals/slot_arguments.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S> class basic_property_changed_arguments;
typedef basic_property_changed_arguments<std::string> property_changed_arguments;
typedef basic_property_changed_arguments<std::wstring> wproperty_changed_arguments;

template<class S>
class basic_property_changed_arguments
    : public go_boost::signals::slot_arguments
{
public:
    typedef S string_type;
    typedef basic_property_changed_arguments<string_type> this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~basic_property_changed_arguments();

protected:
    basic_property_changed_arguments(const string_type& property_name);

public:
    static boost::shared_ptr<basic_property_changed_arguments<S>> create(const string_type& property_name);

    string_type property_name() const;

private:
    const string_type _property_name;
};

template<>
inline basic_property_changed_arguments<std::string>::~basic_property_changed_arguments()
{
}

template<>
inline basic_property_changed_arguments<std::wstring>::~basic_property_changed_arguments()
{
}

template<class S>
inline basic_property_changed_arguments<S>::~basic_property_changed_arguments()
{
}

template<>
inline basic_property_changed_arguments<std::string>::basic_property_changed_arguments(const std::string& property_name)
    : go_boost::signals::slot_arguments()
    , _property_name(property_name)
{
}

template<>
inline basic_property_changed_arguments<std::wstring>::basic_property_changed_arguments(const std::wstring& property_name)
    : go_boost::signals::slot_arguments()
    , _property_name(property_name)
{
}

template<class S>
inline basic_property_changed_arguments<S>::basic_property_changed_arguments(const S& property_name)
    : go_boost::signals::slot_arguments()
    , _property_name(property_name)
{
}

template<>
inline boost::shared_ptr<basic_property_changed_arguments<std::string>> basic_property_changed_arguments<std::string>::create(const std::string& property_name)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const std::string& property_name)
            : this_type(property_name)
        {
        }
    };

    return boost::make_shared<make_shared_enabler, const std::string&>(property_name);
#else
    return boost::shared_ptr<this_type>(new this_type(property_name));
#endif // BOOST_MSVC > 1500
}

template<>
inline boost::shared_ptr<basic_property_changed_arguments<std::wstring>> basic_property_changed_arguments<std::wstring>::create(const std::wstring& property_name)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const std::wstring& property_name)
            : this_type(property_name)
        {
        }
    };

    return boost::make_shared<make_shared_enabler, const std::wstring&>(property_name);
#else
    return boost::shared_ptr<this_type>(new this_type(property_name));
#endif // BOOST_MSVC > 1500
}

template<class S>
inline boost::shared_ptr<basic_property_changed_arguments<S>> basic_property_changed_arguments<S>::create(const S& property_name)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const S& property_name)
            : this_type(property_name)
        {
        }
    };

    return boost::make_shared<make_shared_enabler, const S&>(property_name);
#else
    return boost::shared_ptr<this_type>(new this_type(property_name));
#endif // BOOST_MSVC > 1500
}

template<>
inline std::string basic_property_changed_arguments<std::string>::property_name() const
{
    return _property_name;
}

template<>
inline std::wstring basic_property_changed_arguments<std::wstring>::property_name() const
{
    return _property_name;
}

template<class S>
inline S basic_property_changed_arguments<S>::property_name() const
{
    return _property_name;
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
