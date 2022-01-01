#ifndef GO_FLEET_REPOSITORY_POPULATOR_HPP_INCLUDED
#define GO_FLEET_REPOSITORY_POPULATOR_HPP_INCLUDED

//
//  fleet_repository_populator.hpp
//
//  Copyright 2016-2022 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "fleet_repository_interface.hpp"

class output_view;

class fleet_repository_populator
    : private tt::noncopyable_nonmovable
{
public:
    using this_type = fleet_repository_populator;
    using ptr = typename std::shared_ptr<this_type>;
    using wptr = typename std::weak_ptr<this_type>;

public:
    virtual ~fleet_repository_populator() GO_DEFAULT_DESTRUCTOR

protected:
    fleet_repository_populator() GO_DEFAULT_CONSTRUCTOR

public:
    static ptr create();

public:
    void populate(const fleet_repository_interface::ptr& fleet_repo, output_view* object_observer) const;
};

#endif  // #ifndef GO_FLEET_REPOSITORY_POPULATOR_HPP_INCLUDED
