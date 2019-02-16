#ifndef GO_PRODUCT_VIEW_HPP_INCLUDED
#define GO_PRODUCT_VIEW_HPP_INCLUDED

//
//  add_equipment_view.h
//
//  Copyright 2017-2019 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include "add_equipment_view_model.hpp"
#include "dialog_view.hpp"

class add_equipment_view
    : public dialog_view
{
    DECLARE_DYNAMIC(add_equipment_view)

public:
    virtual ~add_equipment_view() GO_DEFAULT_DESTRUCTOR

    add_equipment_view(const add_equipment_view_model::ptr& vm, CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ADD_EQUIPMENT };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

    virtual BOOL OnInitDialog() override;
    virtual void OnOK() override;
    virtual void OnCancel() override;

    DECLARE_MESSAGE_MAP()

private:
    add_equipment_view_model::ptr _add_equipment_view_model;
};

#endif  // #ifndef GO_PRODUCT_VIEW_HPP_INCLUDED
