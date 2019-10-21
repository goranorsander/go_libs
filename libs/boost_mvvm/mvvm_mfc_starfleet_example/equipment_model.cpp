//
//  equipment_model.cpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "equipment_model.hpp"

#include <boost/bind.hpp>

equipment_id_type equipment_model::_next_id = equipment_id_type(0);

equipment_model::~equipment_model()
{
}

equipment_model::equipment_model(const std::wstring& category_, const std::wstring& name_, const quantity_type& quantity_)
    : equipment_interface()
    , m::wobservable_object()
    , u::noncopyable_nonmovable()
    , id(L"equipment_model::id")
    , _id(_next_id++)
    , _category(category_)
    , _name(name_)
    , _quantity(quantity_)
{
}

equipment_model::equipment_model()
    : equipment_interface()
    , m::wobservable_object()
    , u::noncopyable_nonmovable()
    , id(L"equipment_model::id")
    , _id(_next_id++)
    , _category(L"")
    , _name(L"")
    , _quantity(quantity_type(0))
{
}

equipment_model::ptr equipment_model::create(const std::wstring& category_, const std::wstring& name_, const quantity_type& quantity_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& category_, const std::wstring& name_, const quantity_type& quantity_) : this_type(category_, name_, quantity_) {}
    };

    equipment_model::ptr model = boost::make_shared<make_shared_enabler, const std::wstring&, const std::wstring&, const quantity_type&>(category_, name_, quantity_);
#else
    equipment_model::ptr model = boost::shared_ptr<this_type>(new this_type(category_, name_, quantity_));
#endif // BOOST_MSVC > 1500
    model->bind_properties();
    return model;
}

void equipment_model::bind_properties()
{
    id.getter(boost::bind(&this_type::get_property_value<equipment_id_type>, this, boost::cref(_id)));
    category.getter(boost::bind(&this_type::get_property_value<std::wstring>, this, boost::cref(_category)));
    name.getter(boost::bind(&this_type::get_property_value<std::wstring>, this, boost::cref(_name)));
    quantity.getter(boost::bind(&this_type::get_property_value<quantity_type>, this, boost::cref(_quantity)));
    quantity.setter(boost::bind(&this_type::set_property_value<p::wproperty<quantity_type>>, this, boost::cref(quantity), boost::ref(_quantity), _1));
}
