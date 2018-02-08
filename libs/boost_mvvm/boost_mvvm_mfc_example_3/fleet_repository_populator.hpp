#ifndef GO_BOOST_FLEET_REPOSITORY_POPULATOR_HPP_INCLUDED
#define GO_BOOST_FLEET_REPOSITORY_POPULATOR_HPP_INCLUDED

//
//  fleet_repository_populator.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "fleet_repository_interface.hpp"

class output_view;

class fleet_repository_populator
    : private u::noncopyable_nonmovable
{
public:
    typedef fleet_repository_populator this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~fleet_repository_populator();

protected:
    fleet_repository_populator();

public:
    static ptr create();

public:
    void populate(const fleet_repository_interface::ptr& fleet_repo, output_view* object_observer) const;
};

#endif  // #ifndef GO_BOOST_FLEET_REPOSITORY_POPULATOR_HPP_INCLUDED
