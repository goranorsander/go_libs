#ifndef GO_FLEET_REPOSITORY_HPP_INCLUDED
#define GO_FLEET_REPOSITORY_HPP_INCLUDED

//
//  fleet_repository.hpp
//
//  Copyright 2016-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "fleet_organization_id_type.hpp"
#include "fleet_repository_interface.hpp"

class fleet_repository
    : public fleet_repository_interface
    , private tt::noncopyable_nonmovable
{
public:
    using this_type = fleet_repository;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

public:
    virtual ~fleet_repository() GO_DEFAULT_DESTRUCTOR

protected:
    fleet_repository();

public:
    static ptr create();

public:
    virtual fleet_organization_interface::ptr fleet_organization_model() const override;
    virtual fleet_organization_interface::ptr fleet_organization_model(const std::wstring& name) const override;
    virtual fleet_organization_interface::ptr fleet_organization_model(const spaceship_interface::ptr& spaceship_model) const override;
    virtual fleet_organization_interface::ptr fleet_organization_model(const fleet_organization_id_type id) const;
    virtual spaceship_interface::ptr spaceship_model(const std::wstring& name) const override;

private:
    fleet_organization_interface::ptr _fleet_organization;
};

bool operator==(const fleet_repository::wptr& lhs, const fleet_repository::wptr& rhs);
bool operator!=(const fleet_repository::wptr& lhs, const fleet_repository::wptr& rhs);

#endif  // #ifndef GO_FLEET_REPOSITORY_HPP_INCLUDED
