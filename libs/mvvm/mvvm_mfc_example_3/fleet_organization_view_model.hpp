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

#include "fleet_organization_interface.hpp"
#include "main_frame_view_model.hpp"

class fleet_organization_view_model
    : public m::view_model_interface
    , public m::wobservable_object
    , private m::data_context_interface<fleet_organization_interface::ptr>
    , private u::noncopyable_nonmovable
{
public:
    typedef fleet_organization_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_organization_view_model() = default;

private:
    fleet_organization_view_model();

public:
    p::wproperty<main_frame_view_model::ptr> main_frame_view_model;
    p::wproperty<fleet_organization_interface::ptr> fleet_organization_root;
    p::wproperty<fleet_organization_id_type> selected_fleet_organization_id;

    rop::wproperty<m::wcommand_interface::ptr> on_left_double_click_command;

public:
    static ptr create();

    void set_data_context(const fleet_organization_interface::ptr& context);

protected:
    virtual void on_data_context_changing();
    virtual void on_data_context_changed();

private:
    void bind_properties();

private:
    main_frame_view_model::wptr _main_frame_view_model;
    fleet_organization_id_type _selected_fleet_organization_id;
    m::wcommand_interface::ptr _on_left_double_click_command;
};

#endif  // #ifndef GO_FLEET_ORGANIZATION_VIEW_MODEL_HPP_INCLUDED
