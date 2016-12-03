//
//  main_frame_view_model.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "main_frame_view_model.hpp"
#include "close_spaceship_command_parameters.hpp"
#include "fleet_organization_command_parameters.hpp"
#include "fleet_organization_view_model.hpp"
#include "boost_mvvm_mfc_example_3.h"

#include <functional>


main_frame_view_model::main_frame_view_model(const m::wcommand_manager::ptr& command_mgr, const fleet_repository::ptr& fleet_repo, const properties_view_model::ptr& prop_vm)
    : m::view_model_interface()
    , m::wobservable_object()
    , m::object_wobserver_interface()
    , m::data_context_interface<fleet_repository::wptr>(fleet_repository::wptr(fleet_repo))
    , boost::noncopyable()
    , active_spaceship_view_id(L"main_frame_view_model::active_spaceship_view_id")
    , command_manager(L"main_frame_view_model::command_manager")
    , show_spaceship_command(L"main_frame_view_model::show_spaceship_command")
    , close_spaceship_command(L"main_frame_view_model::close_spaceship_command")
    , _active_spaceship_view_id(0)
    , _command_manager(command_mgr)
    , _show_spaceship_command()
    , _close_spaceship_command()
    , _properties_view_model(prop_vm)
{
    bind_properties();
}

main_frame_view_model::ptr main_frame_view_model::create(const m::wcommand_manager::ptr& command_mgr, const fleet_repository::ptr& fleet_repo, const properties_view_model::ptr& prop_vm)
{
    struct make_shared_enabler
        : public this_type
    {
        virtual ~make_shared_enabler() = default;
        make_shared_enabler(const m::wcommand_manager::ptr& command_mgr, const fleet_repository::ptr& fleet_repo, const properties_view_model::ptr& prop_vm) : this_type(command_mgr, fleet_repo, prop_vm) {}
    };

    return boost::make_shared<make_shared_enabler, const m::wcommand_manager::ptr&, const fleet_repository::ptr&, const properties_view_model::ptr&>(command_mgr, fleet_repo, prop_vm);
}

void main_frame_view_model::on_container_changed(const m::object::ptr& /*o*/, const m::container_changed_arguments::ptr& /*a*/)
{
}

void main_frame_view_model::on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
{
    if(o && a)
    {
        if(a->property_name() == L"fleet_organization_view_model::selected_fleet_organization_id")
        {
            fleet_organization_view_model::ptr fleet_org_view_model = boost::dynamic_pointer_cast<fleet_organization_view_model>(o);
            fleet_repository::ptr fleet_repo = data_context().lock();
            properties_view_model::ptr prop_view_model = _properties_view_model.lock();
            if(fleet_org_view_model && fleet_repo && prop_view_model)
            {
                fleet_organization_interface::ptr selected_fleet_org = fleet_repo->fleet_organization_model(fleet_org_view_model->selected_fleet_organization_id());
                prop_view_model->set_data_context(boost::dynamic_pointer_cast<fleet_organization_model>(selected_fleet_org));
            }
        }
        if(a->property_name() == L"main_frame_view_model::active_spaceship_view_id")
        {
            fleet_repository::ptr fleet_repo = data_context().lock();
            properties_view_model::ptr prop_view_model = _properties_view_model.lock();
            if(fleet_repo && prop_view_model)
            {
                fleet_organization_interface::ptr selected_fleet_org = fleet_repo->fleet_organization_model(_active_spaceship_view_id);
                prop_view_model->set_data_context(boost::dynamic_pointer_cast<fleet_organization_model>(selected_fleet_org));
            }
        }
    }
}

void main_frame_view_model::on_data_context_changing()
{
    m::data_context_interface<fleet_repository::wptr>::on_data_context_changing();
    on_view_model_changing();
}

void main_frame_view_model::on_data_context_changed()
{
    m::data_context_interface<fleet_repository::wptr>::on_data_context_changed();
    on_view_model_changed();
}

void main_frame_view_model::bind_properties()
{
    active_spaceship_view_id.getter([this]() -> fleet_organization_id_type { return _active_spaceship_view_id; });
    active_spaceship_view_id.setter([this](const fleet_organization_id_type& v) { if(_active_spaceship_view_id != v) { _active_spaceship_view_id = v; m::wobservable_object::on_property_changed(active_spaceship_view_id.name()); }});
    command_manager.getter([this]() -> m::wcommand_manager::ptr { return _command_manager.lock(); });
    show_spaceship_command.getter(
        [this]()
        {
            _show_spaceship_command = m::relay_wcommand::create(L"main_frame_view_model::show_spaceship",
                [this](const m::command_parameters::ptr& p)
                {
                    fleet_organization_command_parameters::ptr params = boost::dynamic_pointer_cast<fleet_organization_command_parameters>(p);
                    if(params)
                    {
                        dynamic_cast<boost_mvvm_mfc_example_3*>(AfxGetMainWnd())->on_show_spaceship(params->id);
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
                fleet_organization_command_parameters::create(0));
            return _show_spaceship_command;
        });
    close_spaceship_command.getter(
        [this]()
        {
            _close_spaceship_command = m::relay_wcommand::create(L"main_frame_view_model::close_spaceship",
                [this](const m::command_parameters::ptr& p)
                {
                    close_spaceship_command_parameters::ptr params = boost::dynamic_pointer_cast<close_spaceship_command_parameters>(p);
                    if(params && params->spaceship_view_model())
                    {
                        dynamic_cast<boost_mvvm_mfc_example_3*>(AfxGetMainWnd())->on_close_spaceship(params->spaceship_view_model()->spaceship_id);
                    }
                },
                [this](const m::command_parameters::ptr& p)
                {
                    close_spaceship_command_parameters::ptr params = boost::dynamic_pointer_cast<close_spaceship_command_parameters>(p);
                    if(params && params->spaceship_view_model())
                    {
                        return static_cast<bool>(params->spaceship_view_model());
                    }
                    return false;
                },
                close_spaceship_command_parameters::create(NULL));
            return _close_spaceship_command;
        });
    property_changed.connect(boost::bind(&main_frame_view_model::on_property_changed, this, _1, _2));
}
