//
//  spaceship_view.cpp
//
//  Copyright 2016-2020 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "spaceship_view.hpp"
#include <boost/format.hpp>
#include <go_boost/mvvm/utility/mfc_dlgdata.hpp>
#include <go_boost/utility/scope_guard_new.hpp>

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mvvm_mfc_starfleet_example.hpp"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(spaceship_view, CFormView)

spaceship_view::~spaceship_view()
{
}

spaceship_view::spaceship_view()
    : CFormView(IDD_SPACESHIP_VIEW)
    , m::data_context_interface<spaceship_view_model::ptr>()
    , _initialization_complete(false)
    , _spaceship_class_static()
    , _spaceship_name_static()
    , _equipment_list_ctrl()
    , _selected_equipment_id(0)
    , _equipment_list_data()
{
}

void spaceship_view::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_SPACESHIP_CLASS, _spaceship_class_static);
    DDX_Control(pDX, IDC_STATIC_SPACESHIP_NAME, _spaceship_name_static);
    if(data_context())
    {
        mu::DDX_Text(pDX, IDC_EDIT_CAPTAIN, data_context()->captain);
    }
    DDX_Control(pDX, IDC_LIST_EQUIPMENT, _equipment_list_ctrl);
}

BOOL spaceship_view::DestroyWindow()
{
    return CFormView::DestroyWindow();
}

BOOL spaceship_view::PreCreateWindow(CREATESTRUCT& cs)
{
    return CFormView::PreCreateWindow(cs);
}

BOOL spaceship_view::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL spaceship_view::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_KEYUP)
    {
        UpdateData();
    }
    return CFormView::PreTranslateMessage(pMsg);
}

void spaceship_view::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    ResizeParentToFit();
    on_initial_update_spaceship_name();
    on_initial_update_equipment_list();
}

#ifdef _DEBUG
void spaceship_view::AssertValid() const
{
    CFormView::AssertValid();
}

void spaceship_view::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}
#endif //_DEBUG

void spaceship_view::PostNcDestroy()
{
    // Disable CFormView::PostNcDestroy() from doing 'delete this;' causing '~spaceship_view()' to be called twice 
}

BEGIN_MESSAGE_MAP(spaceship_view, CFormView)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &spaceship_view::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_REMOVE, &spaceship_view::OnBnClickedButtonRemove)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EQUIPMENT, OnLvnItemchangedListEquipment)
END_MESSAGE_MAP()

void spaceship_view::OnBnClickedButtonAdd()
{
    UpdateData();
    m::wcommand_manager::ptr command_manager = data_context()->main_frame_vm()->command_manager();
    if (command_manager)
    {
        command_manager->post(data_context()->on_add_equipment_command);
    }
}

void spaceship_view::OnBnClickedButtonRemove()
{
    UpdateData();
    m::wcommand_manager::ptr command_manager = data_context()->main_frame_vm()->command_manager();
    if (command_manager)
    {
        command_manager->post(data_context()->on_remove_equipment_command);
    }
}

void spaceship_view::OnLvnItemchangedListEquipment(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    if ((pNMLV != NULL) && (pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED))
    {
        _selected_equipment_id = static_cast<equipment_id_type>(_equipment_list_ctrl.GetItemData(pNMLV->iItem));
        equipment_list_item_data_type::const_iterator it = _equipment_list_data.find(_selected_equipment_id);
        data_context()->selected_equipment(it != _equipment_list_data.end() ? it->second : equipment_interface::ptr());
    }
    *pResult = 0;
}

void spaceship_view::initialization_complete()
{
    _initialization_complete = true;
}

void spaceship_view::on_close() const
{
    if(data_context())
    {
        main_frame_view_model::ptr vm = data_context()->main_frame_vm();
        if(vm)
        {
            m::wcommand_manager::ptr command_manager = vm->command_manager();
            if(command_manager)
            {
                command_manager->post(data_context()->on_close_spaceship_view_command);
            }
        }
    }
}

void spaceship_view::on_activate() const
{
    if(_initialization_complete && data_context())
    {
        main_frame_view_model::ptr vm = data_context()->main_frame_vm();
        if(vm)
        {
            m::wcommand_manager::ptr command_manager = vm->command_manager();
            if(command_manager)
            {
                command_manager->post(data_context()->on_activate_spaceship_view_command);
            }
        }
    }
}

void spaceship_view::on_deactivate() const
{
}

void spaceship_view::on_view_model_will_change(const m::view_model_will_change_arguments::ptr& /*a*/)
{
    on_data_context_will_change();
}

void spaceship_view::on_view_model_changed(const m::view_model_changed_arguments::ptr& /*a*/)
{
    on_data_context_changed();
}

void spaceship_view::on_data_context_will_change()
{
    if(data_context())
    {
        data_context()->equipment()->container_changed.disconnect(boost::bind(&spaceship_view::on_container_changed, this, _1, _2));
        data_context()->property_changed.disconnect(boost::bind(&spaceship_view::on_property_changed, this, _1, _2));
    }
    m::data_context_interface<spaceship_view_model::ptr>::on_data_context_will_change();
}

void spaceship_view::on_data_context_changed()
{
    if (data_context())
    {
        data_context()->equipment()->container_changed.connect(boost::bind(&spaceship_view::on_container_changed, this, _1, _2));
        data_context()->property_changed.connect(boost::bind(&spaceship_view::on_property_changed, this, _1, _2));
    }
    m::data_context_interface<spaceship_view_model::ptr>::on_data_context_changed();
    on_view_model_changed();
    UpdateData(false);
}

void spaceship_view::on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a)
{
    if (o && a)
    {
        // Not a pretty solution
        on_view_model_changed();
    }
}

void spaceship_view::on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
{
    if (o && a)
    {
        if (a->property_name() != L"spaceship_view_model::selected_equipment")
        {
            // Not a pretty solution
            on_view_model_changed();
        }
    }
}

void spaceship_view::on_initial_update_spaceship_name()
{
    u::scope_guard_new<CFont> font(new CFont());
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 36;
    lf.lfWeight = FW_BOLD;
    wcscpy_s(lf.lfFaceName, _T("Segeo UI"));
    font->CreateFontIndirect(&lf);
    _spaceship_name_static.SetFont(font.detach());
}

void spaceship_view::on_initial_update_equipment_list()
{
    CRect rect;
    _equipment_list_ctrl.GetClientRect(&rect);
    _equipment_list_ctrl.SetExtendedStyle(_equipment_list_ctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    const int column_width = rect.Width() / 3;
    _equipment_list_ctrl.InsertColumn(0, _T("Category"), LVCFMT_LEFT, column_width);
    _equipment_list_ctrl.InsertColumn(1, _T("Name"), LVCFMT_LEFT, column_width);
    _equipment_list_ctrl.InsertColumn(2, _T("Quantity"), LVCFMT_LEFT, column_width);
}

void spaceship_view::on_view_model_changed()
{
    if(data_context())
    {
        _spaceship_class_static.SetWindowText(data_context()->spaceship_class().c_str());
        _spaceship_name_static.SetWindowText(data_context()->name().c_str());
        populate_equipment_list();
    }
    else
    {
        _spaceship_class_static.SetWindowText(_T("-"));
        _spaceship_name_static.SetWindowText(_T("-"));
        clear_equipment_list();
    }
}

void spaceship_view::clear_equipment_list()
{
    _equipment_list_ctrl.DeleteAllItems();
    _equipment_list_data.clear();
    _selected_equipment_id.set(0);
}

void spaceship_view::populate_equipment_list()
{
    clear_equipment_list();
    if (!data_context()) { return; }

    m::wobservable_deque<equipment_interface::ptr>::ptr equipment = data_context()->equipment();
    if (!equipment) { return; }

    typedef std::map<std::wstring, std::deque<equipment_interface::ptr>> equipment_category_map_type;
    equipment_category_map_type equipment_category;
    m::wobservable_deque<equipment_interface::ptr>::const_iterator e = equipment->begin();
    while (e != equipment->end())
    {
        if (*e)
        {
            equipment_category_map_type::iterator it = equipment_category.find((*e)->category().c_str());
            if (it != equipment_category.end())
            {
                it->second.push_back(*e);
            }
            else
            {
                std::deque<equipment_interface::ptr> c;
                c.push_back(*e);
                equipment_category[(*e)->category().c_str()] = c;
            }
        }
        ++e;
    }

    int item_number = 0;
    equipment_category_map_type::const_iterator ec = equipment_category.begin();
    while (ec != equipment_category.end())
    {
        std::deque<equipment_interface::ptr>::const_iterator ei = ec->second.begin();
        while (ei != ec->second.end())
        {
            LVITEM lvi;
            memset(&lvi, 0, sizeof(lvi));

            std::wstring text = ec->first;
            lvi.mask = LVIF_TEXT;
            lvi.iItem = item_number;
            lvi.iSubItem = 0;
            lvi.pszText = const_cast<wchar_t*>(text.c_str());
            const int item_index = _equipment_list_ctrl.InsertItem(&lvi);
            if (item_index > -1)
            {
                const equipment_id_type equipment_id = boost::dynamic_pointer_cast<equipment_model>(*ei)->id;
                _equipment_list_data[equipment_id] = *ei;

                text = (*ei)->name();
                lvi.iSubItem = 1;
                lvi.pszText = const_cast<wchar_t*>(text.c_str());
                _equipment_list_ctrl.SetItem(&lvi);

                text = (boost::wformat(L"%1%") % ((*ei)->quantity().get())).str();
                lvi.iSubItem = 2;
                lvi.pszText = const_cast<wchar_t*>(text.c_str());
                _equipment_list_ctrl.SetItem(&lvi);

                _equipment_list_ctrl.SetItemData(item_number++, equipment_id.get());
            }
            ++ei;
        }
        ++ec;
    }
}
