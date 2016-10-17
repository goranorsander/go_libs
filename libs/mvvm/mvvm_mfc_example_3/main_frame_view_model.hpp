#ifndef GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED
#define GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED

//
//  main_frame_view_model.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go/property.hpp>
#include <go/mvvm/object_observer_interface.hpp>

#include "fleet_repository.hpp"
#include "properties_view_model.hpp"

namespace m = go::mvvm;
namespace p = go::property;
namespace u = go::utility;

class main_frame_view_model
    : public m::object_wobserver_interface
    , public u::noncopyable_nonmovable
{
public:
    typedef main_frame_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~main_frame_view_model() = default;

private:
    main_frame_view_model(const fleet_repository::ptr& fleet_repository_, const properties_view_model::ptr& properties_view_model_);

public:
    static ptr create(const fleet_repository::ptr& fleet_repository_, const properties_view_model::ptr& properties_view_model_);

public:
    virtual void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a);
    virtual void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a);

private:
    void bind_properties();

public:
    rop::wproperty<m::wcommand::ptr> show_spaceship_command;

private:
    fleet_repository::wptr _fleet_repository;
    m::wcommand::ptr _show_spaceship_command;
    properties_view_model::wptr _properties_view_model;
};

#endif  // #ifndef GO_APPLICATION_VIEW_MODEL_HPP_INCLUDED
