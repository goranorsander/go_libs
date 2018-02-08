//
//  output_view.cpp
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"

#include <cstdio>
#include <locale>
#include <time.h>

#include <go/utility/string/format.hpp>

#include "output_view.hpp"
#include "Resource.h"
#include "main_frame_view.hpp"

#include "activate_spaceship_command_parameters.hpp"
#include "add_equipment_command_parameters.hpp"
#include "close_spaceship_command_parameters.hpp"
#include "close_spaceship_event.hpp"
#include "delete_dialog_view_command_parameters.hpp"
#include "fleet_organization_command_parameters.hpp"
#include "open_add_equipment_view_command_parameters.hpp"
#include "remove_equipment_command_parameters.hpp"
#include "select_fleet_organization_event.hpp"
#include "show_spaceship_event.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{

std::wstring current_date_and_time()
{
    const std::time_t t = std::time(nullptr);
    std::tm lt;
    localtime_s(&lt, &t);
    std::wstring dt(100, 0);
    std::wcsftime(&(dt[0]), 100, _T("%F %T"), &lt);
    return dt;
}

std::wstring command_information(const m::wcommand_interface::ptr& c)
{
    const m::relay_wcommand::ptr r = std::dynamic_pointer_cast<m::relay_wcommand>(c);
    if(r)
    {
        const m::command_parameters::ptr p = c->parameters();
        const activate_spaceship_command_parameters::ptr asp = std::dynamic_pointer_cast<activate_spaceship_command_parameters>(p);
        if(asp)
        {
            return us::format(L"class go::mvvm::relay_wcommand[parameters={class activate_spaceship_command_parameters[id=%d]}]",
                *asp->id);
        }
        const add_equipment_command_parameters::ptr aep = std::dynamic_pointer_cast<add_equipment_command_parameters>(p);
        if (aep)
        {
            return us::format(L"class go::mvvm::relay_wcommand[parameters={class add_equipment_command_parameters[spaceship_id=%d]}]",
                *aep->spaceship_id);
        }
        const close_spaceship_command_parameters::ptr csp = std::dynamic_pointer_cast<close_spaceship_command_parameters>(p);
        if(csp)
        {
            return us::format(L"class go::mvvm::relay_wcommand[parameters={class close_spaceship_command_parameters[spaceship_vm->(id=%d)]}]",
                (csp->spaceship_vm() ? *csp->spaceship_vm()->spaceship_id : 0));
        }
        const delete_dialog_view_command_parameters::ptr dvp = std::dynamic_pointer_cast<delete_dialog_view_command_parameters>(p);
        if (dvp)
        {
            return us::format(L"class go::mvvm::relay_wcommand[parameters={class delete_dialog_view_command_parameters[dialog=0x%X]}]",
                reinterpret_cast<unsigned __int3264>(dvp->dialog().get()));
        }
        const fleet_organization_command_parameters::ptr fop = std::dynamic_pointer_cast<fleet_organization_command_parameters>(p);
        if(fop)
        {
            return us::format(L"class go::mvvm::relay_wcommand[parameters={class fleet_organization_command_parameters[id=%d]}]",
                *fop->id);
        }
        const open_add_equipment_view_command_parameters::ptr oep = std::dynamic_pointer_cast<open_add_equipment_view_command_parameters>(p);
        if (oep)
        {
            return us::format(L"class go::mvvm::relay_wcommand[parameters={class open_add_equipment_view_command_parameters[spaceship=0x%X]}]",
                reinterpret_cast<unsigned __int3264>(oep->spaceship().get()));
        }
        const remove_equipment_command_parameters::ptr rep = std::dynamic_pointer_cast<remove_equipment_command_parameters>(p);
        if (rep)
        {
            return us::format(L"class go::mvvm::relay_wcommand[parameters={class remove_equipment_command_parameters[spaceship_id=%d, equipment_id=%d]}]",
                rep->spaceship_id, rep->equipment_id);
        }
    }
    return L"class go::mvvm::wcommand_interface";
}

std::wstring event_information(const m::wevent::ptr& e)
{
    const close_spaceship_event::ptr cs = std::dynamic_pointer_cast<close_spaceship_event>(e);
    if(cs)
    {
        return us::format(L"class close_spaceship_event[spaceship_vm=0x%08X, spaceship_vm->id=%d]",
            (cs->spaceship_vm() ? reinterpret_cast<unsigned __int3264>(cs->spaceship_vm().get()) : 0),
            (cs->spaceship_vm() ? *cs->spaceship_vm()->spaceship_id : 0));
    }
    const select_fleet_organization_event::ptr sfo = std::dynamic_pointer_cast<select_fleet_organization_event>(e);
    if(sfo)
    {
        return us::format(L"class select_fleet_organization_event[id=%d, selected_by=%s]",
            *sfo->id,
            (*sfo->selected_by).c_str());
    }
    const show_spaceship_event::ptr ss = std::dynamic_pointer_cast<show_spaceship_event>(e);
    if(ss)
    {
        return us::format(L"class show_spaceship_event[id=%d]",
            *ss->id);
    }
    return L"class go::mvvm::wevent";
}

std::wstring object_information(const m::object::ptr& o)
{
    const equipment_interface::ptr e = std::dynamic_pointer_cast<equipment_interface>(o);
    if(e)
    {
        return us::format(L"class equipment_model[category=%s, name=%s, quantity=%d]",
            (*e->category).c_str(),
            (*e->name).c_str(),
            *e->quantity);
    }
    const m::wobservable_deque<equipment_interface::ptr>::ptr el = std::dynamic_pointer_cast<m::wobservable_deque<equipment_interface::ptr>>(o);
    if(el)
    {
        return us::format(L"class go::mvvm::wobservable_deque<equipment_model>[size=%d]",
            el->size());
    }
    const fleet_organization_interface::ptr f = std::dynamic_pointer_cast<fleet_organization_interface>(o);
    if(f)
    {
        return us::format(L"class fleet_organization_model[name=%s, spaceship_model.name=%s, parent.name=%s, first_child.name=%s, previous_sibling.name=%s, next_sibling.name=%s]",
            (*f->name).c_str(),
            *f->spaceship_model ? (*(*f->spaceship_model)->name).c_str() : L"<null>",
            *f->parent ? (*(*f->parent)->name).c_str() : L"<null>",
            *f->first_child ? (*(*f->first_child)->name).c_str() : L"<null>",
            *f->previous_sibling ? (*(*f->previous_sibling)->name).c_str() : L"<null>",
            *f->next_sibling ? (*(*f->next_sibling)->name).c_str() : L"<null>");
    }
    const spaceship_interface::ptr s = std::dynamic_pointer_cast<spaceship_interface>(o);
    if(s)
    {
        return us::format(L"class fleet_organization_model[spaceship_class=%s, name=%s, equipment_model={size=%d}, captain=%s, crew_complement=%d]",
            (*s->spaceship_class).c_str(),
            (*s->name).c_str(),
            *s->equipment ? (*s->equipment)->size() : 0,
            (*s->captain).c_str(),
            *s->crew_complement);
    }
    const fleet_organization_view_model::ptr fleet_org_vm = std::dynamic_pointer_cast<fleet_organization_view_model>(o);
    if(fleet_org_vm)
    {
        return L"class fleet_organization_view_model";
    }
    const main_frame_view_model::ptr main_frame_vm = std::dynamic_pointer_cast<main_frame_view_model>(o);
    if(main_frame_vm)
    {
        return L"class main_frame_view_model";
    }
    return L"class go::mvvm::object";
}

}

/////////////////////////////////////////////////////////////////////////////
// COutputBar

output_view::output_view()
    : CDockablePane()
    , m::wcommand_execution_wobserver_interface()
    , m::object_wobserver_interface()
    , _wndTabs()
    , _wndOutputAllMvvmEvents()
    , _wndOutputCommandEvents()
    , _wndOutputEventEvents()
    , _wndOutputObservableObjectEvents()
{
}

BEGIN_MESSAGE_MAP(output_view, CDockablePane)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()

int output_view::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rectDummy;
    rectDummy.SetRectEmpty();

    if (!_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
    {
        TRACE0("Failed to create output tab window\n");
        return -1;
    }

    const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

    if (!_wndOutputAllMvvmEvents.Create(dwStyle, rectDummy, &_wndTabs, 2) ||
        !_wndOutputCommandEvents.Create(dwStyle, rectDummy, &_wndTabs, 3) ||
        !_wndOutputEventEvents.Create(dwStyle, rectDummy, &_wndTabs, 4) ||
        !_wndOutputObservableObjectEvents.Create(dwStyle, rectDummy, &_wndTabs, 5))
    {
        TRACE0("Failed to create output windows\n");
        return -1;
    }

    UpdateFonts();

    CString strTabName;
    BOOL bNameValid;

    bNameValid = strTabName.LoadString(IDS_ALL_MVVM_EVENTS_TAB);
    ASSERT(bNameValid);
    _wndTabs.AddTab(&_wndOutputAllMvvmEvents, strTabName, (UINT)0);
    bNameValid = strTabName.LoadString(IDS_COMMAND_EVENTS_TAB);
    ASSERT(bNameValid);
    _wndTabs.AddTab(&_wndOutputCommandEvents, strTabName, (UINT)1);
    bNameValid = strTabName.LoadString(IDS_EVENT_EVENTS_TAB);
    ASSERT(bNameValid);
    _wndTabs.AddTab(&_wndOutputEventEvents, strTabName, (UINT)2);
    bNameValid = strTabName.LoadString(IDS_OBSERVABLE_OBJECT_EVENTS_TAB);
    ASSERT(bNameValid);
    _wndTabs.AddTab(&_wndOutputObservableObjectEvents, strTabName, (UINT)3);

    return 0;
}

void output_view::OnSize(UINT nType, int cx, int cy)
{
    CDockablePane::OnSize(nType, cx, cy);

    _wndTabs.SetWindowPos (nullptr, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void output_view::AdjustHorzScroll(CListBox& wndListBox)
{
    CClientDC dc(this);
    CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

    int cxExtentMax = 0;

    for (int i = 0; i < wndListBox.GetCount(); i ++)
    {
        CString strItem;
        wndListBox.GetText(i, strItem);

        cxExtentMax = max(cxExtentMax, (int)dc.GetTextExtent(strItem).cx);
    }

    wndListBox.SetHorizontalExtent(cxExtentMax);
    dc.SelectObject(pOldFont);
}

void output_view::UpdateFonts()
{
    _wndOutputAllMvvmEvents.SetFont(&afxGlobalData.fontRegular);
    _wndOutputCommandEvents.SetFont(&afxGlobalData.fontRegular);
    _wndOutputEventEvents.SetFont(&afxGlobalData.fontRegular);
    _wndOutputObservableObjectEvents.SetFont(&afxGlobalData.fontRegular);
}

void output_view::on_command_executed(const m::wcommand_interface::ptr& c)
{
    if(c)
    {
        const std::wstring msg = us::format(L"%s: Executed command %s, %s", current_date_and_time().c_str(), c->command_name().c_str(), command_information(c).c_str());
        _wndOutputAllMvvmEvents.AddString(msg.c_str());
        _wndOutputCommandEvents.AddString(msg.c_str());
    }
}

void output_view::on_command_not_executed(const m::wcommand_interface::ptr& c)
{
    if(c)
    {
        const std::wstring msg = us::format(L"%s: Command %s was not executed, %s", current_date_and_time().c_str(), c->command_name().c_str(), command_information(c).c_str());
        _wndOutputAllMvvmEvents.AddString(msg.c_str());
        _wndOutputCommandEvents.AddString(msg.c_str());
    }
}

void output_view::on_event_fired(const m::wevent::ptr& e)
{
    if(e)
    {
        const std::wstring msg = us::format(L"%s: Fired event %s, %s", current_date_and_time().c_str(), e->event_type().c_str(), event_information(e).c_str());
        _wndOutputAllMvvmEvents.AddString(msg.c_str());
        _wndOutputEventEvents.AddString(msg.c_str());
    }
}

void output_view::on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a)
{
    if(o && a)
    {
        std::wstring msg;
        switch(a->action())
        {
        case m::notify_container_changed_action_add:
            msg = us::format(L"%s: Added %zu elements to container, %s", current_date_and_time().c_str(), a->added_elements(), object_information(o).c_str());
            break;
        case m::notify_container_changed_action_remove:
            msg = us::format(L"%s: Removed %zu elements from container, %s", current_date_and_time().c_str(), a->removed_elements(), object_information(o).c_str());
            break;
        case m::notify_container_changed_action_reset:
            msg = us::format(L"%s: Reset container, removed all %zu elements, %s", current_date_and_time().c_str(), a->removed_elements(), object_information(o).c_str());
            break;
        case m::notify_container_changed_action_swap:
            msg = us::format(L"%s: Swapped container elements, had %zu, now got %zu, %s", current_date_and_time().c_str(), a->removed_elements(), a->added_elements(), object_information(o).c_str());
            break;
        default:
            msg = us::format(L"%s: Unknown container action, %s", current_date_and_time().c_str(), object_information(o).c_str());
            break;
        }
        _wndOutputAllMvvmEvents.AddString(msg.c_str());
        _wndOutputObservableObjectEvents.AddString(msg.c_str());
    }
}

void output_view::on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
{
    if(o && a)
    {
        const std::wstring msg = us::format(L"%s: Changed property %s, %s", current_date_and_time().c_str(), a->property_name().c_str(), object_information(o).c_str());
        _wndOutputAllMvvmEvents.AddString(msg.c_str());
        _wndOutputObservableObjectEvents.AddString(msg.c_str());
    }
}
