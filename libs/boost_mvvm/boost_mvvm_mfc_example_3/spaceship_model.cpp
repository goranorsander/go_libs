//
//  spaceship_model.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
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
    , u::noncopyable_nonmovable()
    , _spaceship_class(spaceship_class_)
    , _name(name_)
    , _equipment(m::wobservable_list<equipment_interface::ptr>::create())
    , _captain()
    , _crew_complement(0)
{
    bind_properties();
}

spaceship_model::spaceship_model()
    : spaceship_interface()
    , m::wobservable_object()
    , u::noncopyable_nonmovable()
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
        virtual ~make_shared_enabler() {}
        make_shared_enabler(const std::wstring& spaceship_class_, const std::wstring& name_) : this_type(spaceship_class_, name_) {}
    };

    return boost::make_shared<make_shared_enabler, const std::wstring&, const std::wstring&>(spaceship_class_, name_);
#else
    return boost::shared_ptr<this_type>(new this_type(spaceship_class_, name_));
#endif // BOOST_MSVC > 1500
}

void spaceship_model::bind_properties()
{
    spaceship_class.getter(boost::bind(&this_type::get_spaceship_class, this));
    name.getter(boost::bind(&this_type::get_name, this));
    captain.getter(boost::bind(&this_type::get_captain, this));
    captain.setter(boost::bind(&this_type::set_captain, this, _1));
    crew_complement.getter(boost::bind(&this_type::get_crew_complement, this));
    crew_complement.setter(boost::bind(&this_type::set_crew_complement, this, _1));
    equipment.getter(boost::bind(&this_type::get_equipment, this));
    equipment.setter(boost::bind(&this_type::set_equipment, this, _1));
    _equipment->container_changed.connect(boost::bind(&this_type::on_equipment_list_changed, this, _1, _2));
}

void spaceship_model::on_equipment_list_changed(const m::object::ptr& /*o*/, const m::container_changed_arguments::ptr& /*a*/)
{
    on_property_changed(equipment.name());
}

std::wstring spaceship_model::get_spaceship_class() const
{
    return _spaceship_class;
}

std::wstring spaceship_model::get_name() const
{
    return _name;
}

m::wobservable_list<equipment_interface::ptr>::ptr spaceship_model::get_equipment() const
{
    return _equipment;
}

void spaceship_model::set_equipment(const m::wobservable_list<equipment_interface::ptr>::ptr& v)
{
    if(v != _equipment)
    {
        _equipment = v;
        on_property_changed(equipment.name());
    }
}

std::wstring spaceship_model::get_captain() const
{
    return _captain;
}

void spaceship_model::set_captain(const std::wstring& v)
{
    if(v != _captain)
    {
        _captain = v;
        on_property_changed(captain.name());
    }
}

unsigned int spaceship_model::get_crew_complement() const
{
    return _crew_complement;
}

void spaceship_model::set_crew_complement(const unsigned int& v)
{
    if(v != _crew_complement)
    {
        _crew_complement = v;
        on_property_changed(crew_complement.name());
    }
}
