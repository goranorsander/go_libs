//
//  dialog_view.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt.
//

#include "stdafx.h"
#include "dialog_view.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(dialog_view, CDialogEx)

dialog_view::~dialog_view()
{
}

dialog_view::dialog_view()
    : CDialogEx()
    , on_close()
{
}

dialog_view::dialog_view(UINT nIDTemplate, CWnd *pParent)
    : CDialogEx(nIDTemplate, pParent)
    , on_close()
{
}

dialog_view::dialog_view(LPCTSTR lpszTemplateName, CWnd *pParentWnd)
    : CDialogEx(lpszTemplateName, pParentWnd)
    , on_close()
{
}

void dialog_view::OnOK()
{
    CDialogEx::OnOK();
    on_close(this);
}

void dialog_view::OnCancel()
{
    CDialogEx::OnCancel();
    on_close(this);
}

BEGIN_MESSAGE_MAP(dialog_view, CDialogEx)
END_MESSAGE_MAP()
