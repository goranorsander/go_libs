#ifndef GO_BOOST_SELECT_FLEET_ORGANIZATION_EVENT_HPP_INCLUDED
#define GO_BOOST_SELECT_FLEET_ORGANIZATION_EVENT_HPP_INCLUDED

//
//  select_fleet_organization_event.hpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go_boost/mvvm/event.hpp>
#include <go_boost/property/nameless/read_only_value_property.hpp>
#include "fleet_organization_id_type.hpp"

class select_fleet_organization_event
    : public m::wevent
{
public:
    typedef select_fleet_organization_event this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~select_fleet_organization_event();

protected:
    select_fleet_organization_event(const fleet_organization_id_type& id_, const std::wstring& selected_by_);

private:
    select_fleet_organization_event();

public:
    pnro::value_property<fleet_organization_id_type> id;
    pnro::value_property<std::wstring> selected_by;

public:
    static ptr create(const fleet_organization_id_type& id_, const std::wstring& selected_by_);
};

#endif  // #ifndef GO_BOOST_SELECT_FLEET_ORGANIZATION_EVENT_HPP_INCLUDED
