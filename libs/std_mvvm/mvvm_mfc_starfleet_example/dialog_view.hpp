#ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_DIALOG_VIEW_HPP_INCLUDED
#define GO_MVVM_MFC_STARFLEET_EXAMPLE_DIALOG_VIEW_HPP_INCLUDED

//
//  dialog_view.hpp
//
//  Copyright 2017-2021 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go/async/placebo_lockable.hpp>
#include <go/signals.hpp>

class dialog_view
    : public CDialogEx
{
    DECLARE_DYNAMIC(dialog_view)

public:
    using this_type = dialog_view;
    using pointer = this_type*;
    using ptr = std::shared_ptr<this_type>;
    using on_close_signal = si::signal<void(const pointer)>;

public:
    virtual ~dialog_view() = 0;

protected:
    dialog_view();
    dialog_view(UINT nIDTemplate, CWnd* pParent = nullptr);
    dialog_view(LPCTSTR lpszTemplateName, CWnd* pParentWnd = nullptr);

protected:
    virtual void OnOK() override;
    virtual void OnCancel() override;

    DECLARE_MESSAGE_MAP()

public:
    on_close_signal on_close;
};

#endif  // #ifndef GO_MVVM_MFC_STARFLEET_EXAMPLE_DIALOG_VIEW_HPP_INCLUDED
