//
//  product_view.cpp
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "mvvm_example_2.h"
#include "product_view.hpp"

#include <go/mvvm/utility/mfc_dlgdata.hpp>

namespace mu = go::mvvm::utility;
namespace ph = std::placeholders;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

product_view::~product_view()
{
    m_product_view_model->property_changed.disconnect(m_on_property_changed_slot_key);
}

product_view::product_view(const m::wcommand_manager::ptr& command_manager, CWnd* pParent)
	: CDialogEx(IDD_PRODUCT_VIEW, pParent)
    , m_hIcon(0)
    , m_command_manager(command_manager)
    , m_product_view_model()
    , m_on_property_changed_slot_key(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_product_view_model = product_view_model::create();
    m_on_property_changed_slot_key = m_product_view_model->property_changed.connect(std::bind(&product_view::on_property_changed, this, ph::_1, ph::_2));
}

void product_view::on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a)
{
    if(o && a)
    {
        product_view_model::ptr vm = std::dynamic_pointer_cast<product_view_model>(o);
        if(vm)
        {
            if(a->property_name() == L"current_product")
            {
                UpdateData(false);
            }
        }
    }
}

void product_view::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    if(m_product_view_model)
    {
        mu::DDX_Text(pDX, IDC_EDIT_PRODUCT_ID, m_product_view_model->product_id);
        DDV_MinMaxInt(pDX, m_product_view_model->product_id, 0, 10000);
        if(m_product_view_model->current_product.get())
        {
            mu::DDX_Text(pDX, IDC_EDIT_ID, m_product_view_model->current_product.get()->product_id);
            DDV_MinMaxInt(pDX, m_product_view_model->current_product.get()->product_id, 0, 10000);
            mu::DDX_Text(pDX, IDC_EDIT_NAME, m_product_view_model->current_product.get()->product_name);
            mu::DDX_Text(pDX, IDC_EDIT_UNIT_PRICE, m_product_view_model->current_product.get()->unit_price);
        }
    }
    DDX_Control(pDX, IDC_BUTTON_GET_PRODUCT, m_get_product_button);
    DDX_Control(pDX, IDC_BUTTON_SAVE_PRODUCT, m_save_product_button);
}

BEGIN_MESSAGE_MAP(product_view, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET_PRODUCT, &product_view::OnBnClickedButtonGetProduct)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_PRODUCT, &product_view::OnBnClickedButtonSaveProduct)
END_MESSAGE_MAP()

BOOL product_view::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void product_view::OnBnClickedButtonGetProduct()
{
    UpdateData();
    m::wcommand_manager::ptr command_manager = m_command_manager.lock();
    if(command_manager && m_product_view_model)
    {
        command_manager->add_command(m_product_view_model->get_product_command);
    }
}

void product_view::OnBnClickedButtonSaveProduct()
{
    UpdateData();
    m::wcommand_manager::ptr command_manager = m_command_manager.lock();
    if(command_manager && m_product_view_model)
    {
        command_manager->add_command(m_product_view_model->save_product_command);
    }
}
