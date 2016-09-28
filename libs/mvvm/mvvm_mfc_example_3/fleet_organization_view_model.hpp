#ifndef GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED
#define GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED

//
//  fleet_organization_view_model.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go/mvvm.hpp>
#include <go/property.hpp>

#include "fleet_organization_model.hpp"

namespace m = go::mvvm;
namespace p = go::property;
namespace rop = go::property::read_only;

class fleet_organization_view_model
    : public m::wobservable_object
    , public m::data_context_interface<fleet_organization_model::ptr>
{
public:
    typedef fleet_organization_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_organization_view_model() = default;

private:
    fleet_organization_view_model();
    fleet_organization_view_model(const fleet_organization_view_model&) = delete;
    fleet_organization_view_model(fleet_organization_view_model&&) = delete;

public:
    static ptr create();

private:
    fleet_organization_view_model& operator=(const fleet_organization_view_model&) = delete;
    fleet_organization_view_model& operator=(fleet_organization_view_model&&) = delete;

private:
    void bind_properties();

public:
    p::wproperty<fleet_organization_model::ptr> fleet_organization_root;
    p::wproperty<fleet_organization_id_type> selected_fleet_organization_id;

    //rop::wproperty<m::wcommand::ptr> get_fleet_organization_selected_command;

private:
    fleet_organization_id_type _selected_fleet_organization_id;
    //m::wcommand::ptr _get_fleet_organization_selected_command;
};

#endif  // #ifndef GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED
