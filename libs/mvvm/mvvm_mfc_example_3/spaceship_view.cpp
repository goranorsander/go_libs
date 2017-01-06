//
//  spaceship_view.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "spaceship_view.hpp"
#include <go/mvvm/utility/mfc_dlgdata.hpp>
#include <go/utility/scope_guard_new.hpp>

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mvvm_mfc_example_3.hpp"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(spaceship_view, CFormView)

spaceship_view::spaceship_view()
    : CFormView(IDD_SPACESHIP_VIEW)
    , m::data_context_interface<spaceship_view_model::ptr>()
    , _initialization_complete(false)
    , _spaceship_class_static()
    , _spaceship_name_static()
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

    u::scope_guard_new<CFont> font(new CFont());
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 36;
    lf.lfWeight = FW_BOLD;
    wcscpy_s(lf.lfFaceName, _T("Segeo UI"));
    font->CreateFontIndirect(&lf);
    _spaceship_name_static.SetFont(font.detach());
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
END_MESSAGE_MAP()

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
        UpdateData();
    }
    m::data_context_interface<spaceship_view_model::ptr>::on_data_context_will_change();
}

void spaceship_view::on_data_context_changed()
{
    m::data_context_interface<spaceship_view_model::ptr>::on_data_context_changed();
    on_view_model_changed();
}

void spaceship_view::on_view_model_changed()
{
    if(data_context())
    {
        _spaceship_class_static.SetWindowText(data_context()->spaceship_class().c_str());
        _spaceship_name_static.SetWindowText(data_context()->name().c_str());
    }
    else
    {
        _spaceship_class_static.SetWindowText(_T("-"));
        _spaceship_name_static.SetWindowText(_T("-"));
    }
    UpdateData(false);
}
