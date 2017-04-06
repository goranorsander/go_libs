//
//  product_view.cpp
//
//  Copyright 2016-2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "boost_mvvm_mfc_example_2.hpp"
#include "product_view.hpp"

#include <go_boost/mvvm/utility/mfc_dlgdata.hpp>

namespace mu = go_boost::mvvm::utility;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

product_view::~product_view()
{
    m_product_view_model->data_context_changed.disconnect(boost::bind(&product_view::on_data_context_changed, this));
}

product_view::product_view(const m::wcommand_manager::ptr& command_manager, CWnd* pParent)
    : CDialogEx(IDD_PRODUCT_VIEW, pParent)
    , m_hIcon(0)
    , m_command_manager(command_manager)
    , m_product_view_model(product_view_model::create())
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_product_view_model->data_context_changed.connect(boost::bind(&product_view::on_data_context_changed, this));
}

void product_view::on_data_context_changed()
{
    if(m_product_view_model)
    {
        UpdateData(false);
    }
}

void product_view::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    if(m_product_view_model)
    {
        mu::DDX_Text(pDX, IDC_EDIT_PRODUCT_ID, m_product_view_model->product_id);
        DDV_MinMaxInt(pDX, m_product_view_model->product_id, 0, 10000);
        if(m_product_view_model)
        {
            mu::DDX_Text(pDX, IDC_EDIT_ID, m_product_view_model->current_product_id);
            DDV_MinMaxInt(pDX, m_product_view_model->current_product_id, 0, 10000);
            mu::DDX_Text(pDX, IDC_EDIT_NAME, m_product_view_model->current_product_name);
            mu::DDX_Text(pDX, IDC_EDIT_UNIT_PRICE, m_product_view_model->current_unit_price);
        }
    }
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
        command_manager->post(m_product_view_model->get_product_command);
    }
}

void product_view::OnBnClickedButtonSaveProduct()
{
    UpdateData();
    m::wcommand_manager::ptr command_manager = m_command_manager.lock();
    if(command_manager && m_product_view_model)
    {
        command_manager->post(m_product_view_model->save_product_command);
    }
}
