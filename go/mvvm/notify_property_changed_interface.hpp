#ifndef GO_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_property_changed_interface.hpp
//
//  Copyright 2015-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <go/mvvm/object.hpp>
#include <go/mvvm/property_changed_arguments.hpp>
#include <go/signals/signal.hpp>
#include <go/string/u8string.hpp>

namespace go
{
namespace mvvm
{

template<class S, class L> class basic_notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::string, std::recursive_mutex> notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::wstring, std::recursive_mutex> notify_wproperty_changed_interface;

namespace single_threaded
{

typedef basic_notify_property_changed_interface<std::string, go::async::placebo_lockable> notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::wstring, go::async::placebo_lockable> notify_wproperty_changed_interface;

}

template<class S, class L = std::recursive_mutex>
class basic_notify_property_changed_interface
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_notify_property_changed_interface<S, L> this_type;
    typedef typename go::signals::signal<std::function<void(const std::shared_ptr<object>&, const std::shared_ptr<basic_property_changed_arguments<S>>&)>, L> property_changed_signal;

public:
    virtual ~basic_notify_property_changed_interface() = 0;

protected:
    basic_notify_property_changed_interface() GO_DEFAULT_CONSTRUCTOR

public:
    property_changed_signal property_changed;

protected:
    virtual void notify_property_changed(const std::shared_ptr<object>& object, const string_type& property_name);
};

template<>
inline basic_notify_property_changed_interface<std::string, std::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::wstring, std::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<go::string::u8string, std::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::u16string, std::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::u32string, std::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::string, go::async::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::wstring, go::async::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<go::string::u8string, go::async::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::u16string, go::async::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::u32string, go::async::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<class S, class L>
inline basic_notify_property_changed_interface<S, L>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline void basic_notify_property_changed_interface<std::string, std::recursive_mutex>::notify_property_changed(const std::shared_ptr<object>& object, const std::string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::wstring, std::recursive_mutex>::notify_property_changed(const std::shared_ptr<object>& object, const std::wstring& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<go::string::u8string, std::recursive_mutex>::notify_property_changed(const std::shared_ptr<object>& object, const go::string::u8string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::u16string, std::recursive_mutex>::notify_property_changed(const std::shared_ptr<object>& object, const std::u16string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::u32string, std::recursive_mutex>::notify_property_changed(const std::shared_ptr<object>& object, const std::u32string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::string, go::async::placebo_lockable>::notify_property_changed(const std::shared_ptr<object>& object, const std::string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::wstring, go::async::placebo_lockable>::notify_property_changed(const std::shared_ptr<object>& object, const std::wstring& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<go::string::u8string, go::async::placebo_lockable>::notify_property_changed(const std::shared_ptr<object>& object, const go::string::u8string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::u16string, go::async::placebo_lockable>::notify_property_changed(const std::shared_ptr<object>& object, const std::u16string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::u32string, go::async::placebo_lockable>::notify_property_changed(const std::shared_ptr<object>& object, const std::u32string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<class S, class L>
inline void basic_notify_property_changed_interface<S, L>::notify_property_changed(const std::shared_ptr<object>&, const string_type& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(this->shared_from_this(), basic_property_changed_arguments<string_type>::create(property_name));
    }
}

} // namespace mvvm
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
