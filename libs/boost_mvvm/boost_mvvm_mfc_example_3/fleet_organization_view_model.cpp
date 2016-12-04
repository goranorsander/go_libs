//
//  fleet_organization_view_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "fleet_organization_view_model.hpp"
#include "fleet_organization_command_parameters.hpp"
#include "fleet_organization_model.hpp"

#include <functional>

namespace
{

bool is_spaceship(const fleet_organization_interface::ptr fleet_org, const fleet_organization_id_type id)
{
    fleet_organization_model::ptr fleet_org_ = boost::dynamic_pointer_cast<fleet_organization_model>(fleet_org);
    if(fleet_org_)
    {
        if(fleet_org_->id == id)
        {
            return fleet_org_->spaceship_model() != NULL;
        }
        bool is_spaceship_ = is_spaceship(fleet_org->first_child(), id);
        if(is_spaceship_) { return true; }
        is_spaceship_ = is_spaceship(fleet_org->next_sibling(), id);
        if(is_spaceship_) { return true; }
    }
    return false;
}

}

fleet_organization_view_model::fleet_organization_view_model()
    : m::view_model_interface()
    , m::wobservable_object()
    , m::data_context_interface<fleet_organization_interface::ptr>(fleet_organization_model::create())
    , boost::noncopyable()
    , main_frame_view_model(L"fleet_organization_view_model::main_frame_view_model")
    , fleet_organization_root(L"fleet_organization_view_model::fleet_organization_root")
    , selected_fleet_organization_id(L"fleet_organization_view_model::selected_fleet_organization_id")
    , on_left_double_click_command(L"fleet_organization_view_model::on_left_double_click_command")
    , _main_frame_view_model()
    , _selected_fleet_organization_id(0)
    , _on_left_double_click_command()
{
    bind_properties();
}

fleet_organization_view_model::ptr fleet_organization_view_model::create()
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler() : this_type() {}
    };

    return boost::make_shared<make_shared_enabler>();
}

void fleet_organization_view_model::set_data_context(const fleet_organization_interface::ptr& context)
{
    data_context = context;
}

void fleet_organization_view_model::on_data_context_changing()
{
    m::data_context_interface<fleet_organization_interface::ptr>::on_data_context_changing();
    on_view_model_changing();
}

void fleet_organization_view_model::on_data_context_changed()
{
    m::data_context_interface<fleet_organization_interface::ptr>::on_data_context_changed();
    on_view_model_changed();
}

void fleet_organization_view_model::bind_properties()
{
    main_frame_view_model.getter([this]() -> main_frame_view_model::ptr { return _main_frame_view_model.lock(); });
    main_frame_view_model.setter([this](const main_frame_view_model::ptr& v) { if(_main_frame_view_model.lock() != v) { _main_frame_view_model = v; on_property_changed(main_frame_view_model.name()); } });
    fleet_organization_root.getter([this]() -> fleet_organization_interface::ptr { if(*data_context) { return data_context; } return NULL; });
    fleet_organization_root.setter([this](const fleet_organization_interface::ptr& v) { if(*data_context) { data_context.set(v); on_property_changed(fleet_organization_root.name()); } });
    selected_fleet_organization_id.getter([this]() -> fleet_organization_id_type { return _selected_fleet_organization_id; });
    selected_fleet_organization_id.setter([this](const fleet_organization_id_type& v) { if(_selected_fleet_organization_id != v) { _selected_fleet_organization_id = v; on_property_changed(selected_fleet_organization_id.name()); } });
    on_left_double_click_command.getter(
        [this]()
        {
            _on_left_double_click_command = m::relay_wcommand::create(L"fleet_organization_view_model::on_left_double_click",
                [this](const m::command_parameters::ptr& p)
                {
                    if(is_spaceship(*data_context, _selected_fleet_organization_id))
                    {
                        main_frame_view_model::ptr main_frame_view_model = _main_frame_view_model.lock();
                        if(main_frame_view_model)
                        {
                            m::wcommand_manager::ptr command_manager = main_frame_view_model->command_manager();
                            if(command_manager)
                            {
                                m::wcommand_interface::ptr show_spaceship = main_frame_view_model->show_spaceship_command;
                                if(show_spaceship)
                                {
                                    fleet_organization_command_parameters::ptr this_cmd_params = boost::dynamic_pointer_cast<fleet_organization_command_parameters>(p);
                                    fleet_organization_command_parameters::ptr show_spaceship_params = boost::dynamic_pointer_cast<fleet_organization_command_parameters>(show_spaceship->parameters());
                                    if(this_cmd_params && show_spaceship_params)
                                    {
                                        show_spaceship_params->id = this_cmd_params->id;
                                        command_manager->issue_command(show_spaceship);
                                    }
                                }
                            }
                        }
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    fleet_organization_command_parameters::ptr params = boost::dynamic_pointer_cast<fleet_organization_command_parameters>(p);
                    if(params)
                    {
                        return params->id > 0;
                    }
                    return false;
                },
                fleet_organization_command_parameters::create(_selected_fleet_organization_id));
            return _on_left_double_click_command;
        });
}
