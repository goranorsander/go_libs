#ifndef GO_BOOST_MVVM_UTILITY_MFC_DLGDATA_HPP_INCLUDED
#define GO_BOOST_MVVM_UTILITY_MFC_DLGDATA_HPP_INCLUDED

//
//  mfc_dlgdata.hpp
//
//  Copyright 2015-2018 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

#if !defined(GO_BOOST_MSVC_MFC)
GO_BOOST_MESSAGE("Required MFC feature is not supported by this compiler or project configuration")
#else

#include <go_boost/property.hpp>

namespace go_boost
{
namespace mvvm
{
namespace utility
{
namespace detail
{

inline void _Afx_DDX_TextWithFormat(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, UINT nIDPrompt, ...)
{
    va_list pData;
    va_start(pData, nIDPrompt);

    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    ASSERT(hWndCtrl != NULL);

    const int SZT_SIZE = 64;
    TCHAR szT[SZT_SIZE];
    if(pDX->m_bSaveAndValidate)
    {
        void* pResult;

        pResult = va_arg(pData, void*);
        // the following works for %d, %u, %ld, %lu
        ::GetWindowText(hWndCtrl, szT, _countof(szT));
        if(_sntscanf_s(szT, _countof(szT), lpszFormat, pResult) != 1)
        {
            AfxMessageBox(nIDPrompt);
            pDX->Fail(); // throws exception
        }
    }
    else
    {

        ATL_CRT_ERRORCHECK_SPRINTF(_vsntprintf_s(szT, _countof(szT), _countof(szT) - 1, lpszFormat, pData));
        AfxSetWindowText(hWndCtrl, szT);
    }

    va_end(pData);
}

inline void AfxTextFloatFormat(CDataExchange* pDX, int nIDC, void* pData, double value, int nSizeGcvt)
{
    ASSERT(pData != NULL);

    pDX->PrepareEditCtrl(nIDC);
    HWND hWndCtrl;
    pDX->m_pDlgWnd->GetDlgItem(nIDC, &hWndCtrl);

    const int TEXT_BUFFER_SIZE = 400;
    TCHAR szBuffer[TEXT_BUFFER_SIZE];
    if(pDX->m_bSaveAndValidate)
    {
        ::GetWindowText(hWndCtrl, szBuffer, _countof(szBuffer));
        double d;
        if(_sntscanf_s(szBuffer, _countof(szBuffer), _T("%lf"), &d) != 1)
        {
            AfxMessageBox(AFX_IDP_PARSE_REAL);
            pDX->Fail(); // throws exception
        }
        if(nSizeGcvt == FLT_DIG)
            *((float*)pData) = (float)d;
        else
            *((double*)pData) = d;
    }
    else
    {
        ATL_CRT_ERRORCHECK_SPRINTF(_sntprintf_s(szBuffer, _countof(szBuffer), _countof(szBuffer) - 1, _T("%.*g"), nSizeGcvt, value));
        AfxSetWindowText(hWndCtrl, szBuffer);
    }
}

}

// go_boost::property::property

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<BYTE>& value)
{
    int n = static_cast<int>(value);
    if(pDX->m_bSaveAndValidate)
    {
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_BYTE, &n);
        if(n > 255)
        {
            AfxMessageBox(AFX_IDP_PARSE_BYTE);
            pDX->Fail();        // throws exception
        }
        value = static_cast<BYTE>(n);
    }
    else
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_BYTE, n);
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<short>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        short v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%hd"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const short v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%hd"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<int>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        int v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const int v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<UINT>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        UINT v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_UINT, &v);
        value = v;
    }
    else
    {
        const UINT v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_UINT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<long>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        long v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%ld"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const long v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%ld"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<DWORD>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        DWORD v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%lu"), AFX_IDP_PARSE_UINT, &v);
        value = v;
    }
    else
    {
        const DWORD v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%lu"), AFX_IDP_PARSE_UINT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<LONGLONG>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        LONGLONG v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64d"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const LONGLONG v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64d"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<ULONGLONG>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        ULONGLONG v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64u"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const ULONGLONG v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64u"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<float>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        float v = 0;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, FLT_DIG);
        value = v;
    }
    else
    {
        float v = value;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, FLT_DIG);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<double>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        double v = 0;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, DBL_DIG);
        value = v;
    }
    else
    {
        double v = value;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, DBL_DIG);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<CString>& value)
{
    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    if(pDX->m_bSaveAndValidate)
    {
        const int nLen = ::GetWindowTextLength(hWndCtrl);
        CString v;
        ::GetWindowText(hWndCtrl, v.GetBufferSetLength(nLen), nLen + 1);
        v.ReleaseBuffer();
        value = v;
    }
    else
    {
        const CString v = value;
        AfxSetWindowText(hWndCtrl, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<std::string>& value)
{
    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    if(pDX->m_bSaveAndValidate)
    {
        const int nLen = ::GetWindowTextLength(hWndCtrl);
        CString v;
        ::GetWindowText(hWndCtrl, v.GetBufferSetLength(nLen), nLen + 1);
        v.ReleaseBuffer();
#if defined(GO_BOOST_MSVC_UNICODE)
        std::string t(nLen, 0);
        ::WideCharToMultiByte(CP_ACP, 0, v.GetBuffer(), nLen, &(t[0]), static_cast<int>(t.capacity()), 0, NULL);
        value = t;
#else
        value = static_cast<const TCHAR*>(v);
#endif  // #if defined(GO_BOOST_MSVC_UNICODE)
    }
    else
    {
        const CString v(value().c_str());
        AfxSetWindowText(hWndCtrl, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<std::wstring>& value)
{
    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    if(pDX->m_bSaveAndValidate)
    {
        const int nLen = ::GetWindowTextLength(hWndCtrl);
        CString v;
        ::GetWindowText(hWndCtrl, v.GetBufferSetLength(nLen), nLen + 1);
        v.ReleaseBuffer();
#if defined(GO_BOOST_MSVC_UNICODE)
        value = static_cast<const TCHAR*>(v);
#else
        std::wstring t(nLen, 0);
        ::MultiByteToWideChar(CP_ACP, 0, v.GetBuffer(), nLen, &(t[0]), static_cast<int>(t.capacity()));
        value = t;
#endif  // #if defined(GO_BOOST_MSVC_UNICODE)
    }
    else
    {
        const CString v(value().c_str());
        AfxSetWindowText(hWndCtrl, v);
    }
}

// go_boost::property::wproperty

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<BYTE>& value)
{
    int n = static_cast<int>(value);
    if(pDX->m_bSaveAndValidate)
    {
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_BYTE, &n);
        if(n > 255)
        {
            AfxMessageBox(AFX_IDP_PARSE_BYTE);
            pDX->Fail();        // throws exception
        }
        value = static_cast<BYTE>(n);
    }
    else
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_BYTE, n);
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<short>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        short v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const short v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<int>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        int v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const int v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<UINT>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        UINT v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_UINT, &v);
        value = v;
    }
    else
    {
        const UINT v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_UINT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<long>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        long v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%ld"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const long v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%ld"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<DWORD>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        DWORD v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%lu"), AFX_IDP_PARSE_UINT, &v);
        value = v;
    }
    else
    {
        const DWORD v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%lu"), AFX_IDP_PARSE_UINT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<LONGLONG>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        LONGLONG v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64d"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const LONGLONG v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64d"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<ULONGLONG>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        ULONGLONG v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64u"), AFX_IDP_PARSE_INT, &v);
        value = v;
    }
    else
    {
        const ULONGLONG v = value;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64u"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<float>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        float v = 0;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, FLT_DIG);
        value = v;
    }
    else
    {
        float v = value;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, FLT_DIG);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<double>& value)
{
    if(pDX->m_bSaveAndValidate)
    {
        double v = 0;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, DBL_DIG);
        value = v;
    }
    else
    {
        double v = value;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, DBL_DIG);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<CString>& value)
{
    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    if(pDX->m_bSaveAndValidate)
    {
        const int nLen = ::GetWindowTextLength(hWndCtrl);
        CString v;
        ::GetWindowText(hWndCtrl, v.GetBufferSetLength(nLen), nLen + 1);
        v.ReleaseBuffer();
        value = v;
    }
    else
    {
        const CString v = value;
        AfxSetWindowText(hWndCtrl, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<std::string>& value)
{
    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    if(pDX->m_bSaveAndValidate)
    {
        const int nLen = ::GetWindowTextLength(hWndCtrl);
        CString v;
        ::GetWindowText(hWndCtrl, v.GetBufferSetLength(nLen), nLen + 1);
        v.ReleaseBuffer();
#if defined(GO_BOOST_MSVC_UNICODE)
        std::string t(nLen, 0);
        ::WideCharToMultiByte(CP_ACP, 0, v.GetBuffer(), nLen, &(t[0]), static_cast<int>(t.capacity()), 0, NULL);
        value = t;
#else
        value = static_cast<const TCHAR*>(v);
#endif  // #if defined(GO_BOOST_MSVC_UNICODE)
    }
    else
    {
        const CString v(value().c_str());
        AfxSetWindowText(hWndCtrl, v);
    }
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<std::wstring>& value)
{
    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    if(pDX->m_bSaveAndValidate)
    {
        const int nLen = ::GetWindowTextLength(hWndCtrl);
        CString v;
        ::GetWindowText(hWndCtrl, v.GetBufferSetLength(nLen), nLen + 1);
        v.ReleaseBuffer();
#if defined(GO_BOOST_MSVC_UNICODE)
        value = static_cast<const TCHAR*>(v);
#else
        std::wstring t(nLen, 0);
        ::MultiByteToWideChar(CP_ACP, 0, v.GetBuffer(), nLen, &(t[0]), static_cast<int>(t.capacity()));
        value = t;
#endif  // #if defined(GO_BOOST_MSVC_UNICODE)
    }
    else
    {
        const CString v(value().c_str());
        AfxSetWindowText(hWndCtrl, v);
    }
}

} // namespace utility
} // namespace mvvm
} // namespace go_boost

#endif  // #if !defined(_MFC_VER)

#endif  // #ifndef GO_BOOST_MVVM_UTILITY_MFC_DLGDATA_HPP_INCLUDED
