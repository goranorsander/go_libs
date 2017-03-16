#ifndef GO_SELECT_FLEET_ORGANIZATION_EVENT_HPP_INCLUDED
#define GO_SELECT_FLEET_ORGANIZATION_EVENT_HPP_INCLUDED

//
//  select_fleet_organization_event.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go/mvvm/event.hpp>
#include <go/property/nameless/read_only_value_property.hpp>

typedef unsigned long fleet_organization_id_type;

class select_fleet_organization_event
    : public m::wevent
{
public:
    typedef select_fleet_organization_event this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~select_fleet_organization_event() = default;

protected:
    select_fleet_organization_event(const fleet_organization_id_type& id_, const std::wstring& selected_by_);

private:
    select_fleet_organization_event() = delete;

public:
    nrop::value_property<fleet_organization_id_type> id;
    nrop::value_property<std::wstring> selected_by;

public:
    static ptr create(const fleet_organization_id_type& id_, const std::wstring& selected_by_);
};

#endif  // #ifndef GO_SELECT_FLEET_ORGANIZATION_EVENT_HPP_INCLUDED
