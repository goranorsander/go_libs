#ifndef GO_SIGNALS_SLOTS_HPP_INCLUDED
#define GO_SIGNALS_SLOTS_HPP_INCLUDED

//
//  slots.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
#else

#include <map>
#include <go/signals/return_value_collector_invoker.hpp>
#include <go/signals/slots_fwd.hpp>
#include <go/signals/slot_key.hpp>
#include <go/utility/noncopyable_nonmovable.hpp>

namespace go
{
namespace signals
{

template<class Collector, class ReturnValueType, class... Args>
class slots<ReturnValueType(Args...), Collector>
    : private return_value_collector_invoker<Collector, ReturnValueType (Args...)>
    , go::utility::noncopyable_nonmovable
{
protected:
    using signal_function_type = std::function<ReturnValueType (Args...)>;
    using signal_return_value_type = typename signal_function_type::result_type;

private:
    using slot_type = std::shared_ptr<signal_function_type>;
    using slot_sequence_type = std::map<slot_key, slot_type>;

public:
    virtual ~slots() = default;

protected:
    explicit slots(const signal_function_type& signal_function)
        : _next_slot_key()
        , _slots()
    {
        if (signal_function)
        {
            add_slot(signal_function);
        }
    }

    template <typename R>
    typename std::enable_if<std::is_void<R>::value && std::is_same<R, signal_return_value_type>::value, R>::type emit(Args... args) const
    {
        Collector collector;
        slot_sequence_type::const_iterator it = this->_slots.cbegin();
        while (it != this->_slots.cend())
        {
            if (it->second)
            {
                signal_function_type f = *(it->second);
                const bool continue_emission = this->invoke(collector, f, args...);
                if (!continue_emission)
                {
                    break;
                }
            }
            ++it;
        }
    }

    template <typename R>
    typename std::enable_if<!std::is_void<R>::value && std::is_same<R, signal_return_value_type>::value, R>::type emit(Args... args) const
    {
        Collector collector;
        slot_sequence_type::const_iterator it = this->_slots.cbegin();
        while (it != this->_slots.cend())
        {
            if (it->second)
            {
                signal_function_type f = *(it->second);
                const bool continue_emission = this->invoke(collector, f, args...);
                if (!continue_emission)
                {
                    break;
                }
            }
            ++it;
        }
        return collector.return_value();
    }

    std::size_t connections() const
    {
        return this->_slots.size();
    }

    slot_key add_slot(const signal_function_type& signal_function)
    {
        const slot_key key = ++_next_slot_key;
        slot_type slot = std::make_shared<signal_function_type>(signal_function);
        this->_slots[key] = slot;
        return key;
    }

    bool remove_slot(const slot_key& key)
    {
        auto it = _slots.find(key);
        if (it != this->_slots.end())
        {
            this->_slots.erase(it);
            return true;
        }
        return false;
    }

    void remove_all_slots()
    {
        this->_slots.clear();
    }

private:
    slot_key _next_slot_key;
    slot_sequence_type _slots;
};

} // namespace signals
} // namespace go

#endif  // Required C++11 feature is not supported by this compiler

#endif  // #ifndef GO_SIGNALS_SLOTS_HPP_INCLUDED
