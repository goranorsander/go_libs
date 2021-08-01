#ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_HPP_INCLUDED

//
//  test_command.hpp
//
//  Copyright 2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#include <go/mvvm.hpp>
#include <go/namespace_alias.hpp>
#include <go/string.hpp>

namespace go_test
{

template <class Traits>
class test_command
    : public m::basic_command_interface<typename Traits::string_identifier_type, typename Traits::lockable_type>
{
public:
    typedef test_command<Traits> this_type;
    typedef typename m::basic_command_interface<typename Traits::string_identifier_type, typename Traits::lockable_type> base_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

    typedef Traits traits_type;
    typedef typename traits_type::string_value_type string_value_type;
    typedef typename traits_type::lockable_type lockable_type;
    typedef typename traits_type::string_identifier_type string_identifier_type;

public:
    static const string_identifier_type& name()
    {
        static const string_identifier_type n = s::create<string_identifier_type>("test command");
        return n;
    }

public:
    virtual ~test_command() GO_DEFAULT_DESTRUCTOR

    test_command()
        : base_type(this_type::name(), typename base_type::command_parameters_type())
        , _allow_execute(false)
        , _executed(false)
    {
    }

    virtual bool can_execute(const std::shared_ptr<m::command_parameters>& /*params*/) GO_OVERRIDE
    {
        return this->_allow_execute && !this->_executed;
    }

    virtual void execute(const std::shared_ptr<m::command_parameters>& params) GO_OVERRIDE
    {
        if (this->can_execute(params))
        {
            this->_executed = true;
            if (!this->can_execute(params))
            {
                this->can_execute_changed(this->shared_from_this());
            }
        }
    }

    bool allow_execute() const { return this->_allow_execute; }

    void allow_execute(const bool v)
    {
        const bool can_execute_ = this->can_execute(typename base_type::command_parameters_type());
        this->_allow_execute = v;
        if (can_execute_ != this->can_execute(typename base_type::command_parameters_type()))
        {
            this->can_execute_changed(this->shared_from_this());
        }
    }

    bool executed() const { return this->_executed; }

private:
    bool _allow_execute;
    bool _executed;
};

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_TEST_TEST_COMMAND_HPP_INCLUDED
