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

#include <go/diagnostics/log.hpp>

equipment_id_type equipment_model::_next_id = equipment_id_type(0);

equipment_model::equipment_model(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_)
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

equipment_model::ptr equipment_model::create(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_)
{
    GO_LOG_TRACE << "equipment_model::create: " << category_ << ", " << name_ << ", " << quantity_;

    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& category_, const std::wstring& name_, const unsigned int& quantity_) : this_type(category_, name_, quantity_) {}
    };

    equipment_model::ptr model = std::make_shared<make_shared_enabler, const std::wstring&, const std::wstring&, const unsigned int&>(category_, name_, quantity_);
    model->bind_properties();

    GO_LOG_TRACE << "equipment_model::create: done";

    return model;
}

void equipment_model::bind_properties()
{
    id.getter([this]() -> equipment_id_type { return _id; });
    category.getter([this]() -> std::wstring { return _category; });
    name.getter([this]() -> std::wstring { return _name; });
    quantity.getter([this]() -> unsigned int { return _quantity; });
    quantity.setter(std::bind(&this_type::set_property_value<p::wproperty<unsigned int>>, this, std::cref(quantity), std::ref(_quantity), ph::_1));
}
