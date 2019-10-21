//
//  add_equipment_view.cpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include "stdafx.h"
#include "Resource.h"
#include "add_equipment_view.hpp"

#include <go_boost/mvvm/utility/mfc_dlgdata.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(add_equipment_view, dialog_view)

add_equipment_view::~add_equipment_view()
{
}

add_equipment_view::add_equipment_view(const add_equipment_view_model::ptr& vm, CWnd* pParent)
    : dialog_view(IDD_ADD_EQUIPMENT, pParent)
    , _add_equipment_view_model(vm)
{
}

void add_equipment_view::DoDataExchange(CDataExchange* pDX)
{
    dialog_view::DoDataExchange(pDX);
    if (_add_equipment_view_model)
    {
        mu::DDX_Text(pDX, IDC_EDIT_CATEGORY, _add_equipment_view_model->category);
        mu::DDX_Text(pDX, IDC_EDIT_NAME, _add_equipment_view_model->name);
        mu::DDX_Text(pDX, IDC_EDIT_QUANTITY, _add_equipment_view_model->quantity);
        DDV_MinMaxInt(pDX, _add_equipment_view_model->quantity().get(), 0, 1000000000);
    }
}

BEGIN_MESSAGE_MAP(add_equipment_view, dialog_view)
END_MESSAGE_MAP()

BOOL add_equipment_view::OnInitDialog()
{
    dialog_view::OnInitDialog();
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void add_equipment_view::OnOK()
{
    UpdateData();
    if (_add_equipment_view_model)
    {
        _add_equipment_view_model->on_add_equipment();
    }
    dialog_view::OnOK();
}

void add_equipment_view::OnCancel()
{
    UpdateData();
    if (_add_equipment_view_model)
    {
        _add_equipment_view_model->on_cancel();
    }
    dialog_view::OnCancel();
}
