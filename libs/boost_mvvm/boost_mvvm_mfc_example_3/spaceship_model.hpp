#ifndef GO_BOOST_SPACESHIP_MODEL_HPP_INCLUDED
#define GO_BOOST_SPACESHIP_MODEL_HPP_INCLUDED

//
//  spaceship_model.hpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "spaceship_interface.hpp"

class spaceship_model
    : public spaceship_interface
    , public m::wobservable_object
    , private u::noncopyable_nonmovable
{
public:
    typedef spaceship_model this_type;
    typedef GO_BOOST_TYPENAME boost::shared_ptr<this_type> ptr;
    typedef GO_BOOST_TYPENAME boost::weak_ptr<this_type> wptr;

public:
    virtual ~spaceship_model();

protected:
    spaceship_model(const std::wstring& spaceship_class_, const std::wstring& name_);

private:
    explicit spaceship_model();

public:
    static ptr create(const std::wstring& spaceship_class_, const std::wstring& name_);

protected:
    virtual void bind_properties();

private:
    void on_equipment_list_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a);

    std::wstring get_spaceship_class() const;
    std::wstring get_name() const;
    m::wobservable_list<equipment_interface::ptr>::ptr get_equipment() const;
    void set_equipment(const m::wobservable_list<equipment_interface::ptr>::ptr& v);
    std::wstring get_captain() const;
    void set_captain(const std::wstring& v);
    unsigned int get_crew_complement() const;
    void set_crew_complement(const unsigned int& v);

private:
    const std::wstring _spaceship_class;
    const std::wstring _name;
    m::wobservable_list<equipment_interface::ptr>::ptr _equipment;
    std::wstring _captain;
    unsigned int _crew_complement;
};

#endif  // #ifndef GO_BOOST_SPACESHIP_MODEL_HPP_INCLUDED
