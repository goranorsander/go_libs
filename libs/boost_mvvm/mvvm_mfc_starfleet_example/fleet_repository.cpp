//
//  fleet_repository.cpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "fleet_repository.hpp"
#include "fleet_organization_model.hpp"

namespace
{

fleet_organization_interface::ptr find_fleet_organization(const fleet_organization_interface::ptr& fleet_org, const std::wstring& name)
{
    if(fleet_org)
    {
        if(fleet_org->name() == name) { return fleet_org; }
        fleet_organization_interface::ptr found_org = find_fleet_organization(fleet_org->first_child(), name);
        if(found_org) { return found_org; }
        found_org = find_fleet_organization(fleet_org->next_sibling(), name);
        if(found_org) { return found_org; }
    }
    return fleet_organization_interface::ptr();
}

fleet_organization_interface::ptr find_fleet_organization(const fleet_organization_interface::ptr& fleet_org, const spaceship_interface::ptr& spaceship_model)
{
    if(fleet_org)
    {
        if(fleet_org->spaceship_model() == spaceship_model) { return fleet_org; }
        fleet_organization_interface::ptr found_org = find_fleet_organization(fleet_org->first_child(), spaceship_model);
        if(found_org) { return found_org; }
        found_org = find_fleet_organization(fleet_org->next_sibling(), spaceship_model);
        if(found_org) { return found_org; }
    }
    return fleet_organization_interface::ptr();
}

fleet_organization_interface::ptr find_fleet_organization(const fleet_organization_interface::ptr& fleet_org, const fleet_organization_id_type id)
{
    fleet_organization_model::ptr fleet_org_ = boost::dynamic_pointer_cast<fleet_organization_model>(fleet_org);
    if(fleet_org_)
    {
        if(fleet_org_->id() == id) { return fleet_org; }
        fleet_organization_interface::ptr found_org = find_fleet_organization(fleet_org->first_child(), id);
        if(found_org) { return found_org; }
        found_org = find_fleet_organization(fleet_org->next_sibling(), id);
        if(found_org) { return found_org; }
    }
    return fleet_organization_interface::ptr();
}

spaceship_interface::ptr find_spaceship(const fleet_organization_interface::ptr& fleet_org, const std::wstring& name)
{
    if(fleet_org)
    {
        if(fleet_org->spaceship_model() && fleet_org->spaceship_model()->name() == name) { return fleet_org->spaceship_model(); }
        spaceship_interface::ptr found_spaceship = find_spaceship(fleet_org->first_child(), name);
        if(found_spaceship) { return found_spaceship; }
        found_spaceship = find_spaceship(fleet_org->next_sibling(), name);
        if(found_spaceship) { return found_spaceship; }
    }
    return spaceship_interface::ptr();
}

}

fleet_repository::~fleet_repository()
{
}

fleet_repository::fleet_repository()
    : fleet_repository_interface()
    , _fleet_organization(fleet_organization_model::create(L"The Fleets", spaceship_interface::ptr()))
{
}

fleet_repository::ptr fleet_repository::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler() GO_BOOST_DEFAULT_CONSTRUCTOR
    };

    return boost::make_shared<make_shared_enabler>();
}

fleet_organization_interface::ptr fleet_repository::fleet_organization_model() const
{
    return _fleet_organization;
}

fleet_organization_interface::ptr fleet_repository::fleet_organization_model(const std::wstring& name) const
{
    return find_fleet_organization(_fleet_organization, name);
}

fleet_organization_interface::ptr fleet_repository::fleet_organization_model(const spaceship_interface::ptr& spaceship_model) const
{
    return find_fleet_organization(_fleet_organization, spaceship_model);
}

fleet_organization_interface::ptr fleet_repository::fleet_organization_model(const fleet_organization_id_type id) const
{
    return find_fleet_organization(_fleet_organization, id);
}

spaceship_interface::ptr fleet_repository::spaceship_model(const std::wstring& name) const
{
    return find_spaceship(_fleet_organization, name);
}

bool operator==(const fleet_repository::wptr& lhs, const fleet_repository::wptr& rhs)
{
    return lhs.lock() == rhs.lock();
}

bool operator!=(const fleet_repository::wptr& lhs, const fleet_repository::wptr& rhs)
{
    return !operator==(lhs, rhs);
}
