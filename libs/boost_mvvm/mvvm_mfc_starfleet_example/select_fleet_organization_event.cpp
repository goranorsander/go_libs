//
//  select_fleet_organization_event.cpp
//
//  Copyright 2016-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
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
    , id(fleet_organization_id_type(0ull))
    , selected_by(L"")
{
}

select_fleet_organization_event::ptr select_fleet_organization_event::create(const fleet_organization_id_type& id_, const std::wstring& selected_by_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler(const fleet_organization_id_type& id_, const std::wstring& selected_by_) : this_type(id_, selected_by_) {}
    };

    return boost::make_shared<make_shared_enabler, const fleet_organization_id_type&, const std::wstring&>(id_, selected_by_);
#else
    return boost::shared_ptr<this_type>(new this_type(id_, selected_by_));
#endif // BOOST_MSVC > 1500
}
