//
//  main_frame_view_model.cpp
//
//  Copyright 2016-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "main_frame_view_model.hpp"
#include "add_equipment_view.hpp"
#include "close_spaceship_event.hpp"
#include "delete_dialog_view_command_parameters.hpp"
#include "fleet_organization_view_model.hpp"
#include "main_frame_view.hpp"
#include "mvvm_mfc_starfleet_example.hpp"
#include "open_add_equipment_view_command_parameters.hpp"
#include "show_spaceship_event.hpp"

#include <functional>

main_frame_view_model::~main_frame_view_model()
{
    unsubscribe_events();
}

main_frame_view_model::main_frame_view_model(mdi_frame_interface::pointer mdi_frame_mgr, const m::wcommand_manager::ptr& command_mgr, const m::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo)
    : m::view_model_interface<std::recursive_mutex>()
    , m::wobservable_object()
    , m::data_context_interface<fleet_repository::wptr>(fleet_repository::wptr(fleet_repo))
    , tt::noncopyable_nonmovable()
    , mdi_frame_manager(mdi_frame_mgr)
    , command_manager(command_mgr)
    , event_manager(event_mgr)
    , fleet_repository(fleet_repo)
    , dialogs(dialog_view_container_type::create())
    , open_add_equipment_view_command(L"main_frame_view_model::open_add_equipment_view_command")
    , delete_dialog_view_command(L"main_frame_view_model::delete_dialog_view_command")
    , _open_add_equipment_view_command()
    , _delete_dialog_view_command()
    , _close_spaceship_event_key(0)
    , _show_spaceship_event_key(0)
{
}

main_frame_view_model::ptr main_frame_view_model::create(mdi_frame_interface::pointer mdi_frame_mgr, const m::wcommand_manager::ptr& command_mgr, const m::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() GO_DEFAULT_DESTRUCTOR
        make_shared_enabler(mdi_frame_interface::pointer mdi_frame_mgr, const m::wcommand_manager::ptr& command_mgr, const m::wevent_manager::ptr& event_mgr, const fleet_repository::ptr& fleet_repo) : this_type(mdi_frame_mgr, command_mgr, event_mgr, fleet_repo) {}
    };

    main_frame_view_model::ptr view_model = std::make_shared<make_shared_enabler, mdi_frame_interface::pointer, const m::wcommand_manager::ptr&, const m::wevent_manager::ptr&, const fleet_repository::ptr&>(std::forward<mdi_frame_interface::pointer>(mdi_frame_mgr), command_mgr, event_mgr, fleet_repo);
    view_model->bind_properties();
    view_model->subscribe_events();
    return view_model;
}

void main_frame_view_model::on_data_context_will_change()
{
    m::data_context_interface<fleet_repository::wptr>::on_data_context_will_change();
    on_view_model_will_change();
}

void main_frame_view_model::on_data_context_changed()
{
    m::data_context_interface<fleet_repository::wptr>::on_data_context_changed();
    on_view_model_changed();
}

void main_frame_view_model::bind_properties()
{
    open_add_equipment_view_command.getter(
        [this]()
        {
            _open_add_equipment_view_command = m::relay_wcommand::create(L"main_frame_view_model::open_add_equipment_view_command",
                [this](const m::command_parameters::ptr& p)
                {
                    mdi_frame_interface::pointer mdi_frame_mgr = mdi_frame_manager;
                    if(mdi_frame_mgr != nullptr)
                    {
                        open_add_equipment_view_command_parameters::ptr cmd_params = std::dynamic_pointer_cast<open_add_equipment_view_command_parameters>(p);
                        if(cmd_params && cmd_params->spaceship() && cmd_params->spaceship()->equipment())
                        {
                            dialog_view::ptr add_equipment(new add_equipment_view(add_equipment_view_model::create(cmd_params->spaceship()->equipment())));
                            mdi_frame_mgr->on_show_dialog(add_equipment, IDD_ADD_EQUIPMENT);
                        }
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    open_add_equipment_view_command_parameters::ptr params = std::dynamic_pointer_cast<open_add_equipment_view_command_parameters>(p);
                    if(params)
                    {
                        return params->spaceship() != nullptr;
                    }
                    return false;
                },
                open_add_equipment_view_command_parameters::create(nullptr));
            return _open_add_equipment_view_command;
        });
    delete_dialog_view_command.getter(
        [this]()
        {
            _delete_dialog_view_command = m::relay_wcommand::create(L"main_frame_view_model::delete_dialog_view_command",
                [this](const m::command_parameters::ptr& p)
                {
                    mdi_frame_interface::pointer mdi_frame_mgr = mdi_frame_manager;
                    if(dialogs() && mdi_frame_mgr != nullptr)
                    {
                        delete_dialog_view_command_parameters::ptr cmd_params = std::dynamic_pointer_cast<delete_dialog_view_command_parameters>(p);
                        if(cmd_params && cmd_params->dialog())
                        {
                            dialog_view_container_type::iterator it = dialogs()->find(cmd_params->dialog());
                            if (it != dialogs()->end())
                            {
                                dialogs()->erase(it);
                            }
                        }
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    delete_dialog_view_command_parameters::ptr params = std::dynamic_pointer_cast<delete_dialog_view_command_parameters>(p);
                    if(params)
                    {
                        return params->dialog() != nullptr;
                    }
                    return false;
                },
                delete_dialog_view_command_parameters::create(nullptr));
            return _delete_dialog_view_command;
        });
}

void main_frame_view_model::subscribe_events()
{
    m::wevent_manager::ptr event_mgr = event_manager();
    if(event_mgr)
    {
        _close_spaceship_event_key = event_mgr->subscribe(L"close spaceship event",
            [this](const m::wevent::ptr& e)
            {
                close_spaceship_event::ptr close_event = std::dynamic_pointer_cast<close_spaceship_event>(e);
                if(close_event && close_event->spaceship_vm())
                {
                    mdi_frame_interface::pointer mdi_frame_mgr = mdi_frame_manager;
                    if(mdi_frame_mgr != nullptr)
                    {
                        mdi_frame_mgr->on_close_spaceship(close_event->spaceship_vm()->spaceship_id());
                    }
                }
            });
        _show_spaceship_event_key = event_mgr->subscribe(L"show spaceship event",
            [this](const m::wevent::ptr& e)
            {
                show_spaceship_event::ptr show_event = std::dynamic_pointer_cast<show_spaceship_event>(e);
                if(show_event && show_event->id() > fleet_organization_id_type(0ull))
                {
                    mdi_frame_interface::pointer mdi_frame_mgr = mdi_frame_manager;
                    if(mdi_frame_mgr != nullptr)
                    {
                        mdi_frame_mgr->on_show_spaceship(show_event->id);
                    }
                }
            });
    }
}

void main_frame_view_model::unsubscribe_events()
{
    m::wevent_manager::ptr event_mgr = event_manager();
    if(event_mgr)
    {
        event_mgr->unsubscribe(L"close spaceship event", _close_spaceship_event_key);
        m::reset(_close_spaceship_event_key);
        event_mgr->unsubscribe(L"show spaceship event", _show_spaceship_event_key);
        m::reset(_show_spaceship_event_key);
    }
}
