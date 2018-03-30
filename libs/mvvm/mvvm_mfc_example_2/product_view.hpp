#ifndef GO_PRODUCT_VIEW_HPP_INCLUDED
#define GO_PRODUCT_VIEW_HPP_INCLUDED

//
//  product_view.h
//
//  Copyright 2016-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "product_view_model.hpp"

namespace s = go::signals;

class product_view
    : public CDialogEx
{
public:
    virtual ~product_view();
    product_view(const m::wcommand_manager::ptr& command_manager, CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PRODUCT_VIEW };
#endif

protected:
    virtual void on_data_context_changed();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedButtonGetProduct();
    afx_msg void OnBnClickedButtonSaveProduct();

protected:
    HICON m_hIcon;

private:
    m::wcommand_manager::wptr m_command_manager;
    product_view_model::ptr m_product_view_model;
    s::slot_key m_on_data_context_changed_slot_key;
};

#endif  // #ifndef GO_PRODUCT_VIEW_HPP_INCLUDED
