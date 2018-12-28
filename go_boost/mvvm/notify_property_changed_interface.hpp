#ifndef GO_BOOST_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
#define GO_BOOST_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED

//
//  notify_property_changed_interface.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif  // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <go_boost/mvvm/object.hpp>
#include <go_boost/mvvm/property_changed_arguments.hpp>
#include <go_boost/signals.hpp>
#include <go_boost/utility/u8string.hpp>
#include <go_boost/utility/u16string.hpp>
#include <go_boost/utility/u32string.hpp>

namespace go_boost
{
namespace mvvm
{

template<class S, class L> class basic_notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::string, boost::recursive_mutex> notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::wstring, boost::recursive_mutex> notify_wproperty_changed_interface;

namespace single_threaded
{

typedef basic_notify_property_changed_interface<std::string, go_boost::utility::placebo_lockable> notify_property_changed_interface;
typedef basic_notify_property_changed_interface<std::wstring, go_boost::utility::placebo_lockable> notify_wproperty_changed_interface;

}

template<class S, class L = boost::recursive_mutex>
class basic_notify_property_changed_interface
    : public go_boost::signals::slot
{
public:
    typedef S string_type;
    typedef L lockable_type;
    typedef basic_notify_property_changed_interface<S, L> this_type;
    typedef typename boost::signals2::signal<void(const boost::shared_ptr<object>&, const boost::shared_ptr<basic_property_changed_arguments<S>>&)> property_changed_signal;

public:
    virtual ~basic_notify_property_changed_interface() = 0;

protected:
    basic_notify_property_changed_interface();

public:
    property_changed_signal property_changed;

protected:
    virtual void notify_property_changed(const boost::shared_ptr<object>& object, const string_type& property_name);
};

template<>
inline basic_notify_property_changed_interface<std::string, boost::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::wstring, boost::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u8string, boost::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u16string, boost::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u32string, boost::recursive_mutex>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::string, go_boost::utility::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::wstring, go_boost::utility::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u8string, go_boost::utility::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u16string, go_boost::utility::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u32string, go_boost::utility::placebo_lockable>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<class S, class L>
inline basic_notify_property_changed_interface<S, L>::~basic_notify_property_changed_interface()
{
    this->property_changed.disconnect_all_slots();
}

template<>
inline basic_notify_property_changed_interface<std::string, boost::recursive_mutex>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<std::wstring, boost::recursive_mutex>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u8string, boost::recursive_mutex>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u16string, boost::recursive_mutex>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u32string, boost::recursive_mutex>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<std::string, go_boost::utility::placebo_lockable>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<std::wstring, go_boost::utility::placebo_lockable>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u8string, go_boost::utility::placebo_lockable>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u16string, go_boost::utility::placebo_lockable>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline basic_notify_property_changed_interface<go_boost::utility::u32string, go_boost::utility::placebo_lockable>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<class S, class L>
inline basic_notify_property_changed_interface<S, L>::basic_notify_property_changed_interface()
    : go_boost::signals::slot()
{
}

template<>
inline void basic_notify_property_changed_interface<std::string, boost::recursive_mutex>::notify_property_changed(const boost::shared_ptr<object>& object, const std::string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::wstring, boost::recursive_mutex>::notify_property_changed(const boost::shared_ptr<object>& object, const std::wstring& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<go_boost::utility::u8string, boost::recursive_mutex>::notify_property_changed(const boost::shared_ptr<object>& object, const go_boost::utility::u8string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<go_boost::utility::u16string, boost::recursive_mutex>::notify_property_changed(const boost::shared_ptr<object>& object, const go_boost::utility::u16string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<go_boost::utility::u32string, boost::recursive_mutex>::notify_property_changed(const boost::shared_ptr<object>& object, const go_boost::utility::u32string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::string, go_boost::utility::placebo_lockable>::notify_property_changed(const boost::shared_ptr<object>& object, const std::string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<std::wstring, go_boost::utility::placebo_lockable>::notify_property_changed(const boost::shared_ptr<object>& object, const std::wstring& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<go_boost::utility::u8string, go_boost::utility::placebo_lockable>::notify_property_changed(const boost::shared_ptr<object>& object, const go_boost::utility::u8string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<go_boost::utility::u16string, go_boost::utility::placebo_lockable>::notify_property_changed(const boost::shared_ptr<object>& object, const go_boost::utility::u16string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<>
inline void basic_notify_property_changed_interface<go_boost::utility::u32string, go_boost::utility::placebo_lockable>::notify_property_changed(const boost::shared_ptr<object>& object, const go_boost::utility::u32string& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(object, basic_property_changed_arguments<string_type>::create(property_name));
    }
}

template<class S, class L>
inline void basic_notify_property_changed_interface<S, L>::notify_property_changed(const boost::shared_ptr<object>&, const string_type& property_name)
{
    if (!this->property_changed.empty())
    {
        this->property_changed(this->shared_from_this(), basic_property_changed_arguments<string_type>::create(property_name));
    }
}

} // namespace mvvm
} // namespace go_boost

#endif  // #ifndef GO_BOOST_MVVM_NOTIFY_PROPERTY_CHANGED_INTERFACE_HPP_INCLUDED
