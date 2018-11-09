#ifndef GO_SPACESHIP_MODEL_HPP_INCLUDED
#define GO_SPACESHIP_MODEL_HPP_INCLUDED

//
//  spaceship_model.hpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "spaceship_interface.hpp"

class spaceship_model
    : public spaceship_interface
    , public mst::wobservable_object
    , private u::noncopyable_nonmovable
{
public:
    typedef spaceship_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~spaceship_model();

protected:
    spaceship_model(const std::wstring& spaceship_class_, const std::wstring& name_);

private:
     spaceship_model() = delete;

public:
    static ptr create(const std::wstring& spaceship_class_, const std::wstring& name_);

protected:
    virtual void bind_properties();

private:
    const std::wstring _spaceship_class;
    const std::wstring _name;
    m::wobservable_deque<equipment_interface::ptr>::ptr _equipment;
    std::wstring _captain;
    unsigned int _crew_complement;
    s::slot_key _on_equipment_list_changed_slot_key;
};

#endif  // #ifndef GO_SPACESHIP_MODEL_HPP_INCLUDED
