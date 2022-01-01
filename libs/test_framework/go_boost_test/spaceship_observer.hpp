#ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_SPACESHIP_OBSERVER_HPP_INCLUDED
#define GO_TEST_FRAMEWORK_GO_BOOST_TEST_SPACESHIP_OBSERVER_HPP_INCLUDED

//
//  spaceship_observer.hpp
//
//  Copyright 2021-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#include <go_boost/signals/connections.hpp>
#include <go_boost_test/observable_spaceship.hpp>

namespace go_boost_test
{

template <class Spaceship>
class spaceship_observer
{
public:
    typedef spaceship_observer<Spaceship> this_type;
    typedef Spaceship spaceship_type;
    typedef typename Spaceship::ptr spaceship_ptr;

    typedef typename spaceship_type::traits_type traits_type;
    typedef typename traits_type::string_value_type string_value_type;
    typedef typename traits_type::lockable_type lockable_type;
    typedef typename traits_type::string_identifier_type string_identifier_type;
    typedef typename traits_type::property_changed_arguments_type property_changed_arguments_type;
    typedef typename traits_type::property_changed_arguments_ptr property_changed_arguments_ptr;

public:
    virtual ~spaceship_observer() GO_BOOST_DEFAULT_DESTRUCTOR

     spaceship_observer()
        : _property_changed_connections()
        , _property_changed_count()
    {
    }

    bool try_connect(const spaceship_ptr& ship)
    {
        if (ship)
            return this->_property_changed_connections.connect(ship, ship->property_changed, boost::bind(&this_type::on_property_changed, this, boost::placeholders::_1, boost::placeholders::_2));
        return false;
    }

    bool try_disconnect(const spaceship_ptr& ship)
    {
        if (ship)
            return this->_property_changed_connections.disconnect(ship, ship->property_changed);
        return false;
    }

    void on_property_changed(const m::object::ptr& o, const property_changed_arguments_ptr& a)
    {
        if(o && a)
        {
            spaceship_ptr ship = boost::dynamic_pointer_cast<spaceship_type>(o);
            if(ship)
            {
                const ship_and_property_type ship_and_property(ship->name(), a->property_name());
                const typename on_property_changed_counter_type::iterator it = this->_property_changed_count.find(ship_and_property);
                if(it == this->_property_changed_count.end())
                {
                    this->_property_changed_count[ship_and_property] = 1;
                }
                else
                {
                    ++(it->second);
                }
            }
        }
    }

    unsigned int get_property_changed_count(const string_identifier_type& ship_name, const string_identifier_type& property_name) const
    {
        const ship_and_property_type ship_and_property(ship_name, property_name);
        const typename on_property_changed_counter_type::const_iterator it = this->_property_changed_count.find(ship_and_property);
        if(it == this->_property_changed_count.end())
        {
            return 0;
        }
        return it->second;
    }

private:
    typedef si::connections<spaceship_ptr, void(const m::object::ptr&, const property_changed_arguments_ptr&)> property_changed_connections_type;
    typedef std::pair<string_identifier_type, string_identifier_type> ship_and_property_type;
    typedef std::map<ship_and_property_type, unsigned int> on_property_changed_counter_type;

    property_changed_connections_type _property_changed_connections;
    on_property_changed_counter_type _property_changed_count;
};

}

#endif  // #ifndef GO_TEST_FRAMEWORK_GO_BOOST_TEST_SPACESHIP_OBSERVER_HPP_INCLUDED
