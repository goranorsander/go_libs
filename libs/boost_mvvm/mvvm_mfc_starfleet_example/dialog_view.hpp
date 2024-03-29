#ifndef GO_BOOST_MVVM_MFC_STARFLEET_EXAMPLE_DIALOG_VIEW_HPP_INCLUDED
#define GO_BOOST_MVVM_MFC_STARFLEET_EXAMPLE_DIALOG_VIEW_HPP_INCLUDED

//
//  dialog_view.hpp
//
//  Copyright 2017-2022 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#include <go_boost/signals.hpp>

class dialog_view
    : public CDialogEx
{
    DECLARE_DYNAMIC(dialog_view)

public:
    typedef dialog_view this_type;
    typedef this_type* pointer;
    typedef boost::shared_ptr<this_type> ptr;
    typedef boost::signals2::signal<void(const pointer)> on_close_signal;

public:
    virtual ~dialog_view() = 0;

protected:
    dialog_view();
    dialog_view(UINT nIDTemplate, CWnd* pParent = NULL);
    dialog_view(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);

protected:
    virtual void OnOK() GO_BOOST_OVERRIDE;
    virtual void OnCancel() GO_BOOST_OVERRIDE;

    DECLARE_MESSAGE_MAP()

public:
    on_close_signal on_close;
};

#endif  // #ifndef GO_BOOST_MVVM_MFC_STARFLEET_EXAMPLE_DIALOG_VIEW_HPP_INCLUDED
