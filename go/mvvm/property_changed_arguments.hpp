#ifndef GO_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED

//
//  property_changed_arguments.hpp
//
//  Copyright 2015-2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/signals/slot_arguments.hpp>

namespace go
{
namespace mvvm
{

template<class S> class basic_property_changed_arguments;
typedef basic_property_changed_arguments<std::string> property_changed_arguments;
typedef basic_property_changed_arguments<std::wstring> wproperty_changed_arguments;

template<class S>
class basic_property_changed_arguments
    : public go::signals::slot_arguments
{
public:
    typedef S string_type;
    typedef basic_property_changed_arguments<string_type> this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~basic_property_changed_arguments() GO_DEFAULT_DESTRUCTOR

protected:
    basic_property_changed_arguments(const string_type& property_name)
        : go::signals::slot_arguments()
        , _property_name(property_name)
    {
    }

public:
    static std::shared_ptr<basic_property_changed_arguments<S>> create(const string_type& property_name);

    string_type property_name() const;

private:
    const string_type _property_name;
};

template<>
inline std::shared_ptr<basic_property_changed_arguments<std::string>> basic_property_changed_arguments<std::string>::create(const std::string& property_name)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::string& property_name)
            : this_type(property_name)
        {
        }
    };

    return std::make_shared<make_shared_enabler, const std::string&>(property_name);
}

template<>
inline std::shared_ptr<basic_property_changed_arguments<std::wstring>> basic_property_changed_arguments<std::wstring>::create(const std::wstring& property_name)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& property_name)
            : this_type(property_name)
        {
        }
    };

    return std::make_shared<make_shared_enabler, const std::wstring&>(property_name);
}

template<class S>
inline std::shared_ptr<basic_property_changed_arguments<S>> basic_property_changed_arguments<S>::create(const S& property_name)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const S& property_name)
            : this_type(property_name)
        {
        }
    };

    return std::make_shared<make_shared_enabler, const S&>(property_name);
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
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_PROPERTY_CHANGED_ARGUMENTS_HPP_INCLUDED
