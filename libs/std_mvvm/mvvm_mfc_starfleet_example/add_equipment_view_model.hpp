#ifndef GO_ADD_EQUIPMENT_VIEW_MODEL_HPP_INCLUDED
#define GO_ADD_EQUIPMENT_VIEW_MODEL_HPP_INCLUDED

//
//  add_equipment_view_model.hpp
//
//  Copyright 2017-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/mvvm.hpp>
#include <go/property.hpp>

#include "equipment_interface.hpp"

class add_equipment_view_model
    : public m::wobservable_object
    , public tt::noncopyable_nonmovable
{
public:
    typedef add_equipment_view_model this_type;
    typedef typename std::shared_ptr<this_type> ptr;
    typedef typename std::weak_ptr<this_type> wptr;

public:
    virtual ~add_equipment_view_model() GO_DEFAULT_DESTRUCTOR

private:
    explicit add_equipment_view_model(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment);

public:
    static ptr create(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment);

    void on_add_equipment() const;
    void on_cancel() const;

private:
    void on_close() const;

    void bind_properties();

public:
    p::wproperty<std::wstring> category;
    p::wproperty<std::wstring> name;
    p::wproperty<unsigned int> quantity;

private:
    m::wobservable_deque<equipment_interface::ptr>::wptr _equipment;

    std::wstring _category;
    std::wstring _name;
    unsigned int _quantity;
};

#endif  // #ifndef GO_ADD_EQUIPMENT_VIEW_MODEL_HPP_INCLUDED
