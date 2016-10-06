#ifndef GO_PROPERTIES_VIEW_MODEL_HPP_INCLUDED
#define GO_PROPERTIES_VIEW_MODEL_HPP_INCLUDED

//
//  properties_view_model.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go/mvvm.hpp>

#include "fleet_organization_model.hpp"
#include "fleet_repository_interface.hpp"

namespace m = go::mvvm;

class properties_view_model
    : public m::data_context_interface<fleet_organization_model::ptr>
    , public u::noncopyable_nonmovable
{
public:
    typedef properties_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~properties_view_model() = default;

private:
    properties_view_model(const fleet_repository_interface::ptr& fleet_repository_);

public:
    static ptr create(const fleet_repository_interface::ptr& fleet_repository_);

private:
    fleet_repository_interface::wptr _fleet_repository;
};

#endif  // #ifndef GO_PROPERTIES_VIEW_MODEL_HPP_INCLUDED
