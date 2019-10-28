//
//  spaceship_model.cpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "spaceship_model.hpp"

#include <boost/bind.hpp>

spaceship_model::~spaceship_model()
{
    _equipment->container_changed.disconnect(boost::bind(&this_type::on_equipment_list_changed, this, _1, _2));
}

spaceship_model::spaceship_model(const std::wstring& spaceship_class_, const std::wstring& name_)
    : spaceship_interface()
    , m::wobservable_object()
    , tt::noncopyable_nonmovable()
    , _spaceship_class(spaceship_class_)
    , _name(name_)
    , _equipment(m::wobservable_deque<equipment_interface::ptr>::create())
    , _captain()
    , _crew_complement(0)
{
}

spaceship_model::spaceship_model()
    : spaceship_interface()
    , m::wobservable_object()
    , tt::noncopyable_nonmovable()
    , _spaceship_class(L"")
    , _name(L"")
    , _equipment()
    , _captain()
    , _crew_complement(0)
{
}

spaceship_model::ptr spaceship_model::create(const std::wstring& spaceship_class_, const std::wstring& name_)
{
#if BOOST_MSVC > 1500
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_BOOST_DEFAULT_DESTRUCTOR
        make_shared_enabler(const std::wstring& spaceship_class_, const std::wstring& name_) : this_type(spaceship_class_, name_) {}
    };

    spaceship_model::ptr model = boost::make_shared<make_shared_enabler, const std::wstring&, const std::wstring&>(spaceship_class_, name_);
#else
    spaceship_model::ptr model = boost::shared_ptr<this_type>(new this_type(spaceship_class_, name_));
#endif // BOOST_MSVC > 1500
    model->bind_properties();
    return model;
}

void spaceship_model::bind_properties()
{
    spaceship_class.getter(boost::bind(&this_type::get_property_value<std::wstring>, this, boost::cref(_spaceship_class)));
    name.getter(boost::bind(&this_type::get_property_value<std::wstring>, this, boost::cref(_name)));
    captain.getter(boost::bind(&this_type::get_property_value<std::wstring>, this, boost::cref(_captain)));
    captain.setter(boost::bind(&this_type::set_property_value<p::wproperty<std::wstring>>, this, boost::cref(captain), boost::ref(_captain), _1));
    crew_complement.getter(boost::bind(&this_type::get_property_value<quantity_type>, this, boost::cref(_crew_complement)));
    crew_complement.setter(boost::bind(&this_type::set_property_value<p::wproperty<quantity_type>>, this, boost::cref(crew_complement), boost::ref(_crew_complement), _1));
    equipment.getter(boost::bind(&this_type::get_property_value<m::wobservable_deque<equipment_interface::ptr>::ptr>, this, boost::cref(_equipment)));
    equipment.setter(boost::bind(&this_type::set_property_value<p::wproperty<m::wobservable_deque<equipment_interface::ptr>::ptr>>, this, boost::cref(equipment), boost::ref(_equipment), _1));
    _equipment->container_changed.connect(boost::bind(&this_type::on_equipment_list_changed, this, _1, _2));
}

void spaceship_model::on_equipment_list_changed(const m::object::ptr& /*o*/, const m::container_changed_arguments::ptr& /*a*/)
{
    notify_property_changed(this->shared_from_this(), equipment.name());
}
