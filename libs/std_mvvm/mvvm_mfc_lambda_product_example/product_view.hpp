#ifndef GO_PRODUCT_VIEW_HPP_INCLUDED
#define GO_PRODUCT_VIEW_HPP_INCLUDED

//
//  product_view.h
//
//  Copyright 2016-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/namespace_alias.hpp>
#include "product_view_model.hpp"

class product_view
    : public CDialogEx
{
public:
    virtual ~product_view();
    explicit product_view(const m::wcommand_manager::ptr& command_manager, CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PRODUCT_VIEW };
#endif

protected:
    virtual void on_data_context_changed();

    virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

    virtual BOOL OnInitDialog() override;

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedButtonGetProduct();
    afx_msg void OnBnClickedButtonSaveProduct();

protected:
    HICON m_hIcon;

private:
    m::wcommand_manager::wptr m_command_manager;
    product_view_model::ptr m_product_view_model;
    si::connection m_on_data_context_changed_connection;
};

#endif  // #ifndef GO_PRODUCT_VIEW_HPP_INCLUDED
