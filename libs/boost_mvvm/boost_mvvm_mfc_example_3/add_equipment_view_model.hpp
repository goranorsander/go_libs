#ifndef GO_BOOST_ADD_EQUIPMENT_VIEW_MODEL_HPP_INCLUDED
#define GO_BOOST_ADD_EQUIPMENT_VIEW_MODEL_HPP_INCLUDED

//
//  add_equipment_view_model.hpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go_boost/mvvm.hpp>
#include <go_boost/property.hpp>

#include "equipment_interface.hpp"

class add_equipment_view_model
    : public m::wobservable_object
    , public u::noncopyable_nonmovable
{
public:
    typedef add_equipment_view_model this_type;
    typedef typename boost::shared_ptr<this_type> ptr;
    typedef typename boost::weak_ptr<this_type> wptr;

public:
    virtual ~add_equipment_view_model();

private:
    add_equipment_view_model(const m::wobservable_deque<equipment_interface::ptr>::ptr& equipment);

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
    std::wstring get_category() const;
    void set_category(const std::wstring& v);
    std::wstring get_name() const;
    void set_name(const std::wstring& v);
    unsigned int get_quantity() const;
    void set_quantity(const unsigned int& v);

private:
    m::wobservable_deque<equipment_interface::ptr>::wptr _equipment;

    std::wstring _category;
    std::wstring _name;
    unsigned int _quantity;
};

#endif  // #ifndef GO_BOOST_ADD_EQUIPMENT_VIEW_MODEL_HPP_INCLUDED
