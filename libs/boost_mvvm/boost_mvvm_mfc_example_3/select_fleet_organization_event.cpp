//
//  select_fleet_organization_event.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "select_fleet_organization_event.hpp"
#include <boost/make_shared.hpp>

select_fleet_organization_event::~select_fleet_organization_event()
{
}

select_fleet_organization_event::select_fleet_organization_event(const fleet_organization_id_type& id_, const std::wstring& selected_by_)
    : m::wevent(L"select fleet organization event")
    , id(id_)
    , selected_by(selected_by_)
{
}

select_fleet_organization_event::select_fleet_organization_event()
    : m::wevent(L"")
    , id(0)
    , selected_by(L"")
{
}

select_fleet_organization_event::ptr select_fleet_organization_event::create(const fleet_organization_id_type& id_, const std::wstring& selected_by_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const fleet_organization_id_type& id_, const std::wstring& selected_by_) : this_type(id_, selected_by_) {}
    };

    return boost::make_shared<make_shared_enabler, const fleet_organization_id_type&, const std::wstring&>(id_, selected_by_);
}
