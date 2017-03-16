//
//  equipment_model.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "equipment_model.hpp"

equipment_model::~equipment_model()
{
}

equipment_model::equipment_model(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_)
    : equipment_interface()
    , m::wobservable_object()
    , u::noncopyable_nonmovable()
    , _category(category_)
    , _name(name_)
    , _quantity(quantity_)
{
    bind_properties();
}

equipment_model::ptr equipment_model::create(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_) : this_type(category_, name_, quantity_) {}
    };

    return std::make_shared<make_shared_enabler, const std::wstring&, const std::wstring&, const unsigned int&>(category_, name_, quantity_);
}

void equipment_model::bind_properties()
{
    category.getter([this]() { return _category; });
    name.getter([this]() { return _name; });
    quantity.getter([this]() { return _quantity; });
    quantity.setter([this](const unsigned int& v) { if(v != _quantity) { _quantity = v; on_property_changed(quantity.name()); } });
}
