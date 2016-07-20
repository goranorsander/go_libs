#ifndef GO_MVVM_EXAMPLE_3_OUTPUTWND_H_INCLUDED
#define GO_MVVM_EXAMPLE_3_OUTPUTWND_H_INCLUDED

//
//  OutputWnd.h
//
//  Copyright 2016 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#pragma once

#include <go/mvvm/command_execution_observer_interface.hpp>
#include <go/mvvm/object_observer_interface.hpp>

namespace m = go::mvvm;

/////////////////////////////////////////////////////////////////////////////

class COutputList
    : public CListBox
{
public:
    virtual ~COutputList();
    COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

class COutputWnd
    : public CDockablePane
    , public m::wcommand_execution_wobserver_interface
    , public m::object_wobserver_interface
{
public:
    virtual ~COutputWnd();
    COutputWnd();

	void UpdateFonts();

    virtual void on_command_executed(const m::wcommand::ptr& c);
    virtual void on_command_not_executed(const m::wcommand::ptr& c);

    virtual void on_container_changed(const m::object::ptr& o, const std::shared_ptr<m::container_changed_arguments>& a);
    virtual void on_property_changed(const m::object::ptr& o, const std::shared_ptr<m::wproperty_changed_arguments>& a);

protected:
	CMFCTabCtrl	m_wndTabs;

	COutputList m_wndOutputAllMvvmEvents;
	COutputList m_wndOutputCommandEvents;
	COutputList m_wndOutputObservableObjectEvents;

protected:
	void AdjustHorzScroll(CListBox& wndListBox);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

#endif  // #ifndef GO_MVVM_EXAMPLE_3_OUTPUTWND_H_INCLUDED
