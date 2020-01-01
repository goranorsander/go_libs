#ifndef GO_BOOST_MVVM_MFC_PRODUCT_EXAMPLE_STDAFX_H_INCLUDED
#define GO_BOOST_MVVM_MFC_PRODUCT_EXAMPLE_STDAFX_H_INCLUDED

//
//  stdafx.h
//
//  Copyright 2016-2020 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

#include <go_boost/config.hpp>

#if defined(GO_BOOST_NO_BOOST_PHOENIX)
#error Boost.Phoenix is not supported by this compiler
#endif  // #if defined(GO_BOOST_NO_BOOST_PHOENIX)

#endif  // #ifndef GO_BOOST_MVVM_MFC_PRODUCT_EXAMPLE_STDAFX_H_INCLUDED
