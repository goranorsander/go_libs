#ifndef GO_PRODUCT_VIEW_HPP_INCLUDED
#define GO_PRODUCT_VIEW_HPP_INCLUDED

//
//  add_equipment_view.h
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include "add_equipment_view_model.hpp"
#include "dialog_view.hpp"

class add_equipment_view
    : public dialog_view
{
    DECLARE_DYNAMIC(add_equipment_view)

public:
    virtual ~add_equipment_view() = default;

    add_equipment_view(const add_equipment_view_model::ptr& vm, CWnd* pParent = NULL);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ADD_EQUIPMENT };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();

    DECLARE_MESSAGE_MAP()

private:
    add_equipment_view_model::ptr _add_equipment_view_model;
};

#endif  // #ifndef GO_PRODUCT_VIEW_HPP_INCLUDED
