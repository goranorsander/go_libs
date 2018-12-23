#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_DIALOG_VIEW_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_DIALOG_VIEW_HPP_INCLUDED

//
//  dialog_view.hpp
//
//  Copyright 2017-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/signals.hpp>
#include <go/utility/placebo_lockable.hpp>

class dialog_view
    : public CDialogEx
{
    DECLARE_DYNAMIC(dialog_view)

public:
    typedef dialog_view this_type;
    typedef this_type* pointer;
    typedef std::shared_ptr<this_type> ptr;
    typedef go::signals::signal<std::function<void(const pointer)>> on_close_signal;

public:
    virtual ~dialog_view() = 0;

protected:
    dialog_view();
    dialog_view(UINT nIDTemplate, CWnd* pParent = nullptr);
    dialog_view(LPCTSTR lpszTemplateName, CWnd* pParentWnd = nullptr);

protected:
    virtual void OnOK();
    virtual void OnCancel();

    DECLARE_MESSAGE_MAP()

public:
    on_close_signal on_close;
};

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_DIALOG_VIEW_HPP_INCLUDED
