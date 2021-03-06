#ifndef GO_BOOST_SPACESHIP_VIEW_HPP_INCLUDED
#define GO_BOOST_SPACESHIP_VIEW_HPP_INCLUDED
#include "afxwin.h"

//
//  spaceship_view.hpp
//
//  Copyright 2016-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

// spaceship_view.hpp : interface of the spaceship_view class
//

#pragma once

#include "equipment_model.hpp"
#include "spaceship_view_model.hpp"

class spaceship_view
    : public CFormView
    , public m::data_context_interface<spaceship_view_model::ptr>
    , public m::object_wobserver_interface
{
public:
    virtual ~spaceship_view();

    spaceship_view();

protected:
    DECLARE_DYNCREATE(spaceship_view)

public:
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SPACESHIP_VIEW };
#endif

public:
    virtual BOOL DestroyWindow() GO_BOOST_OVERRIDE;
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs) GO_BOOST_OVERRIDE;
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL) GO_BOOST_OVERRIDE;
    virtual BOOL PreTranslateMessage(MSG* pMsg) GO_BOOST_OVERRIDE;

protected:
    virtual void DoDataExchange(CDataExchange* pDX) GO_BOOST_OVERRIDE;
    virtual void OnInitialUpdate() GO_BOOST_OVERRIDE;

public:
#ifdef _DEBUG
    virtual void AssertValid() const GO_BOOST_OVERRIDE;
    virtual void Dump(CDumpContext& dc) const GO_BOOST_OVERRIDE;
#endif

protected:
    virtual void PostNcDestroy() GO_BOOST_OVERRIDE;

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonRemove();
    afx_msg void OnLvnItemchangedListEquipment(NMHDR *pNMHDR, LRESULT *pResult);

public:
    void initialization_complete();

    void on_close() const;
    void on_activate() const;
    void on_deactivate() const;

    virtual void on_view_model_will_change(const m::view_model_will_change_arguments::ptr& a);
    virtual void on_view_model_changed(const m::view_model_changed_arguments::ptr& a);

protected:
    virtual void on_data_context_will_change() GO_BOOST_OVERRIDE;
    virtual void on_data_context_changed() GO_BOOST_OVERRIDE;
    virtual void on_container_changed(const m::object::ptr& o, const m::container_changed_arguments::ptr& a) GO_BOOST_OVERRIDE;
    virtual void on_property_changed(const m::object::ptr& o, const m::wproperty_changed_arguments::ptr& a) GO_BOOST_OVERRIDE;

private:
    void on_initial_update_spaceship_name();
    void on_initial_update_equipment_list();
    void on_view_model_changed();

    void populate_equipment_list();
    void clear_equipment_list();

private:
    typedef std::map<equipment_id_type, equipment_interface::ptr> equipment_list_item_data_type;

    bool _initialization_complete;
    CStatic _spaceship_class_static;
    CStatic _spaceship_name_static;
    CListCtrl _equipment_list_ctrl;
    equipment_id_type _selected_equipment_id;
    equipment_list_item_data_type _equipment_list_data;
    boost::signals2::connection _on_data_context_equipment_container_changed_connection;
    boost::signals2::connection _on_data_context_property_changed_connection;
};

#endif  // #ifndef GO_BOOST_SPACESHIP_VIEW_HPP_INCLUDED
