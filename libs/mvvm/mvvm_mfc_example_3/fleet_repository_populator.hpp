#ifndef GO_FLEET_REPOSITORY_POPULATOR_HPP_INCLUDED
#define GO_FLEET_REPOSITORY_POPULATOR_HPP_INCLUDED

//
//  fleet_repository_populator.hpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "fleet_repository_interface.hpp"

namespace m = go::mvvm;

class COutputWnd;

class fleet_repository_populator
{
public:
    typedef fleet_repository_populator this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_repository_populator();

protected:
    fleet_repository_populator();

private:
    fleet_repository_populator(const fleet_repository_populator&) = delete;
    fleet_repository_populator(fleet_repository_populator&&) = delete;

public:
    static ptr create();

private:
    fleet_repository_populator& operator=(const fleet_repository_populator&) = delete;
    fleet_repository_populator& operator=(fleet_repository_populator&&) = delete;

public:
    void populate(const fleet_repository_interface::ptr& fleet_repo, COutputWnd* object_observer) const;
};

#endif  // #ifndef GO_FLEET_REPOSITORY_POPULATOR_HPP_INCLUDED
