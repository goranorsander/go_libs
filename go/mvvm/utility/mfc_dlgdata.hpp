#ifndef GO_MVVM_UTILITY_MFC_DLGDATA_HPP_INCLUDED
#define GO_MVVM_UTILITY_MFC_DLGDATA_HPP_INCLUDED

//
//  mfc_dlgdata.hpp
//
//  Copyright 2015-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if !defined(GO_MSVC_MFC)
GO_MESSAGE("Required MFC feature is not supported by this compiler or project configuration")
#else

#include <go/property.hpp>
#include <go/type_traits/primitive_type_specializer.hpp>

namespace go
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
    ASSERT(hWndCtrl != nullptr);

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
    ASSERT(pData != nullptr);

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

inline void AFXAPI DDX_Text_BYTE(CDataExchange* pDX, int nIDC, std::function<BYTE(void)> get, std::function<void(const BYTE&)> set)
{
    int n = static_cast<int>(get());
    if (pDX->m_bSaveAndValidate)
    {
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_BYTE, &n);
        if (n > 255)
        {
            AfxMessageBox(AFX_IDP_PARSE_BYTE);
            pDX->Fail();        // throws exception
        }
        set(static_cast<BYTE>(n));
    }
    else
    {
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_BYTE, n);
    }
}

inline void AFXAPI DDX_Text_short(CDataExchange* pDX, int nIDC, std::function<short(void)> get, std::function<void(const short&)> set)
{
    if (pDX->m_bSaveAndValidate)
    {
        short v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%hd"), AFX_IDP_PARSE_INT, &v);
        set(v);
    }
    else
    {
        const short v = get();
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%hd"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text_int(CDataExchange* pDX, int nIDC, std::function<int(void)> get, std::function<void(const int&)> set)
{
    if (pDX->m_bSaveAndValidate)
    {
        int v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, &v);
        set(v);
    }
    else
    {
        const int v = get();
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text_UINT(CDataExchange* pDX, int nIDC, std::function<UINT(void)> get, std::function<void(const UINT&)> set)
{
    if (pDX->m_bSaveAndValidate)
    {
        UINT v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_UINT, &v);
        set(v);
    }
    else
    {
        const UINT v = get();
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_UINT, v);
    }
}

inline void AFXAPI DDX_Text_long(CDataExchange* pDX, int nIDC, std::function<long(void)> get, std::function<void(const long&)> set)
{
    if (pDX->m_bSaveAndValidate)
    {
        long v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%ld"), AFX_IDP_PARSE_INT, &v);
        set(v);
    }
    else
    {
        const long v = get();
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%ld"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text_DWORD(CDataExchange* pDX, int nIDC, std::function<DWORD(void)> get, std::function<void(const DWORD&)> set)
{
    if (pDX->m_bSaveAndValidate)
    {
        DWORD v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%lu"), AFX_IDP_PARSE_UINT, &v);
        set(v);
    }
    else
    {
        const DWORD v = get();
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%lu"), AFX_IDP_PARSE_UINT, v);
    }
}

inline void AFXAPI DDX_Text_LONGLONG(CDataExchange* pDX, int nIDC, std::function<LONGLONG(void)> get, std::function<void(const LONGLONG&)> set)
{
    if (pDX->m_bSaveAndValidate)
    {
        LONGLONG v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64d"), AFX_IDP_PARSE_INT, &v);
        set(v);
    }
    else
    {
        const LONGLONG v = get();
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64d"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text_ULONGLONG(CDataExchange* pDX, int nIDC, std::function<ULONGLONG(void)> get, std::function<void(const ULONGLONG&)> set)
{
    if (pDX->m_bSaveAndValidate)
    {
        ULONGLONG v = 0;
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64u"), AFX_IDP_PARSE_INT, &v);
        set(v);
    }
    else
    {
        const ULONGLONG v = get();
        detail::_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%I64u"), AFX_IDP_PARSE_INT, v);
    }
}

inline void AFXAPI DDX_Text_float(CDataExchange* pDX, int nIDC, std::function<float(void)> get, std::function<void(const float&)> set)
{
    if (pDX->m_bSaveAndValidate)
    {
        float v = 0;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, FLT_DIG);
        set(v);
    }
    else
    {
        float v = get();
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, FLT_DIG);
    }
}

inline void AFXAPI DDX_Text_double(CDataExchange* pDX, int nIDC, std::function<double(void)> get, std::function<void(const double&)> set)
{
    if (pDX->m_bSaveAndValidate)
    {
        double v = 0;
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, DBL_DIG);
        set(v);
    }
    else
    {
        double v = get();
        detail::AfxTextFloatFormat(pDX, nIDC, &v, v, DBL_DIG);
    }
}

inline void AFXAPI DDX_Text_CString(CDataExchange* pDX, int nIDC, std::function<CString(void)> get, std::function<void(const CString&)> set)
{
    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    if (pDX->m_bSaveAndValidate)
    {
        const int nLen = ::GetWindowTextLength(hWndCtrl);
        CString v;
        ::GetWindowText(hWndCtrl, v.GetBufferSetLength(nLen), nLen + 1);
        v.ReleaseBuffer();
        set(v);
    }
    else
    {
        const CString v = get();
        AfxSetWindowText(hWndCtrl, v);
    }
}

inline void AFXAPI DDX_Text_std_string(CDataExchange* pDX, int nIDC, std::function<std::string(void)> get, std::function<void(const std::string&)> set)
{
    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    if (pDX->m_bSaveAndValidate)
    {
        const int nLen = ::GetWindowTextLength(hWndCtrl);
        CString v;
        ::GetWindowText(hWndCtrl, v.GetBufferSetLength(nLen), nLen + 1);
        v.ReleaseBuffer();
#if defined(_UNICODE) || defined(UNICODE)
        std::string t(nLen, 0);
        ::WideCharToMultiByte(CP_ACP, 0, v.GetBuffer(), nLen, &(t[0]), static_cast<int>(t.capacity()), 0, NULL);
        set(t);
#else
        const std::string t(static_cast<const char*>(v));
        set(t);
#endif  // #if defined(_UNICODE) || defined(UNICODE)
    }
    else
    {
        const CString v(get().c_str());
        AfxSetWindowText(hWndCtrl, v);
    }
}

inline void AFXAPI DDX_Text_std_wstring(CDataExchange* pDX, int nIDC, std::function<std::wstring(void)> get, std::function<void(const std::wstring&)> set)
{
    HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
    if (pDX->m_bSaveAndValidate)
    {
        const int nLen = ::GetWindowTextLength(hWndCtrl);
        CString v;
        ::GetWindowText(hWndCtrl, v.GetBufferSetLength(nLen), nLen + 1);
        v.ReleaseBuffer();
#if defined(_UNICODE) || defined(UNICODE)
        const std::wstring t(static_cast<const wchar_t*>(v));
        set(t);
#else
        std::wstring t(nLen, 0);
        ::MultiByteToWideChar(CP_ACP, 0, v.GetBuffer(), nLen, &(t[0]), static_cast<int>(t.capacity()));
        set(t);
#endif  // #if defined(_UNICODE) || defined(UNICODE)
    }
    else
    {
        const CString v(get().c_str());
        AfxSetWindowText(hWndCtrl, v);
    }
}

template<typename PrimitiveType, class PrimitiveTypeSpecializerProperty>
PrimitiveType get_specialized_primitive_type(const PrimitiveTypeSpecializerProperty& p)
{
    return p.get().get();
}

template<class PrimitiveTypeSpecializer, typename PrimitiveType, class PrimitiveTypeSpecializerProperty>
void set_specialized_primitive_type(PrimitiveTypeSpecializerProperty& p, const PrimitiveType& v)
{
    const PrimitiveTypeSpecializer s(v);
    return p.set(s);
}

}

// go::property::property

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<BYTE>& value)
{
    detail::DDX_Text_BYTE(pDX, nIDC, std::bind(&go::property::property<BYTE>::get, &value), std::bind(&go::property::property<BYTE>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<short>& value)
{
    detail::DDX_Text_short(pDX, nIDC, std::bind(&go::property::property<short>::get, &value), std::bind(&go::property::property<short>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<int>& value)
{
    detail::DDX_Text_int(pDX, nIDC, std::bind(&go::property::property<int>::get, &value), std::bind(&go::property::property<int>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<UINT>& value)
{
    detail::DDX_Text_UINT(pDX, nIDC, std::bind(&go::property::property<UINT>::get, &value), std::bind(&go::property::property<UINT>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<long>& value)
{
    detail::DDX_Text_long(pDX, nIDC, std::bind(&go::property::property<long>::get, &value), std::bind(&go::property::property<long>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<DWORD>& value)
{
    detail::DDX_Text_DWORD(pDX, nIDC, std::bind(&go::property::property<DWORD>::get, &value), std::bind(&go::property::property<DWORD>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<LONGLONG>& value)
{
    detail::DDX_Text_LONGLONG(pDX, nIDC, std::bind(&go::property::property<LONGLONG>::get, &value), std::bind(&go::property::property<LONGLONG>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<ULONGLONG>& value)
{
    detail::DDX_Text_ULONGLONG(pDX, nIDC, std::bind(&go::property::property<ULONGLONG>::get, &value), std::bind(&go::property::property<ULONGLONG>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<float>& value)
{
    detail::DDX_Text_float(pDX, nIDC, std::bind(&go::property::property<float>::get, &value), std::bind(&go::property::property<float>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<double>& value)
{
    detail::DDX_Text_double(pDX, nIDC, std::bind(&go::property::property<double>::get, &value), std::bind(&go::property::property<double>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<CString>& value)
{
    detail::DDX_Text_CString(pDX, nIDC, std::bind(&go::property::property<CString>::get, &value), std::bind(&go::property::property<CString>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<std::string>& value)
{
    detail::DDX_Text_std_string(pDX, nIDC, std::bind(&go::property::property<std::string>::get, &value), std::bind(&go::property::property<std::string>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<std::wstring>& value)
{
    detail::DDX_Text_std_wstring(pDX, nIDC, std::bind(&go::property::property<std::wstring>::get, &value), std::bind(&go::property::property<std::wstring>::set, &value, std::placeholders::_1));
}

// go::property::property<go::type_traits::primitive_type_specializer>

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, BYTE>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_BYTE(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<BYTE, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, BYTE, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, short>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_short(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<short, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, short, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, int>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_int(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<int, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, int, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, UINT>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_UINT(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<UINT, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, UINT, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, long>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_long(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<long, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, long, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, DWORD>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_DWORD(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<DWORD, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, DWORD, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, LONGLONG>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_LONGLONG(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<LONGLONG, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, LONGLONG, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, ULONGLONG>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_ULONGLONG(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<ULONGLONG, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, ULONGLONG, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, float>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_float(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<float, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, float, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, double>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_double(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<double, go::property::property<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, double, go::property::property<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

// go::property::wproperty

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<BYTE>& value)
{
    detail::DDX_Text_BYTE(pDX, nIDC, std::bind(&go::property::wproperty<BYTE>::get, &value), std::bind(&go::property::wproperty<BYTE>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<short>& value)
{
    detail::DDX_Text_short(pDX, nIDC, std::bind(&go::property::wproperty<short>::get, &value), std::bind(&go::property::wproperty<short>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<int>& value)
{
    detail::DDX_Text_int(pDX, nIDC, std::bind(&go::property::wproperty<int>::get, &value), std::bind(&go::property::wproperty<int>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<UINT>& value)
{
    detail::DDX_Text_UINT(pDX, nIDC, std::bind(&go::property::wproperty<UINT>::get, &value), std::bind(&go::property::wproperty<UINT>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<long>& value)
{
    detail::DDX_Text_long(pDX, nIDC, std::bind(&go::property::wproperty<long>::get, &value), std::bind(&go::property::wproperty<long>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<DWORD>& value)
{
    detail::DDX_Text_DWORD(pDX, nIDC, std::bind(&go::property::wproperty<DWORD>::get, &value), std::bind(&go::property::wproperty<DWORD>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<LONGLONG>& value)
{
    detail::DDX_Text_LONGLONG(pDX, nIDC, std::bind(&go::property::wproperty<LONGLONG>::get, &value), std::bind(&go::property::wproperty<LONGLONG>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<ULONGLONG>& value)
{
    detail::DDX_Text_ULONGLONG(pDX, nIDC, std::bind(&go::property::wproperty<ULONGLONG>::get, &value), std::bind(&go::property::wproperty<ULONGLONG>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<float>& value)
{
    detail::DDX_Text_float(pDX, nIDC, std::bind(&go::property::wproperty<float>::get, &value), std::bind(&go::property::wproperty<float>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<double>& value)
{
    detail::DDX_Text_double(pDX, nIDC, std::bind(&go::property::wproperty<double>::get, &value), std::bind(&go::property::wproperty<double>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<CString>& value)
{
    detail::DDX_Text_CString(pDX, nIDC, std::bind(&go::property::wproperty<CString>::get, &value), std::bind(&go::property::wproperty<CString>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<std::string>& value)
{
    detail::DDX_Text_std_string(pDX, nIDC, std::bind(&go::property::wproperty<std::string>::get, &value), std::bind(&go::property::wproperty<std::string>::set, &value, std::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<std::wstring>& value)
{
    detail::DDX_Text_std_wstring(pDX, nIDC, std::bind(&go::property::wproperty<std::wstring>::get, &value), std::bind(&go::property::wproperty<std::wstring>::set, &value, std::placeholders::_1));
}

// go::property::wproperty<go::type_traits::primitive_type_specializer>

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, BYTE>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_BYTE(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<BYTE, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, BYTE>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, short>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_short(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<short, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, short>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, int>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_int(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<int, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, int, go::property::wproperty<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, UINT>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_UINT(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<UINT, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, UINT, go::property::wproperty<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, long>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_long(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<long, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, long, go::property::wproperty<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, DWORD>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_DWORD(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<DWORD, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, DWORD, go::property::wproperty<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, LONGLONG>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_LONGLONG(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<LONGLONG, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, LONGLONG, go::property::wproperty<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, ULONGLONG>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_ULONGLONG(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<ULONGLONG, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, ULONGLONG, go::property::wproperty<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, float>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_float(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<float, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, float, go::property::wproperty<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

template<class PrimitiveTypeSpecializer>
typename std::enable_if<std::is_base_of<go::type_traits::detail::primitive_type_specializer_base, PrimitiveTypeSpecializer>::value && std::is_same<typename PrimitiveTypeSpecializer::primitive_type, double>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<PrimitiveTypeSpecializer>& value)
{
    detail::DDX_Text_double(pDX, nIDC, std::bind(detail::get_specialized_primitive_type<double, go::property::wproperty<PrimitiveTypeSpecializer>>, std::cref(value)), std::bind(detail::set_specialized_primitive_type<PrimitiveTypeSpecializer, double, go::property::wproperty<PrimitiveTypeSpecializer>>, std::ref(value), std::placeholders::_1));
}

} // namespace utility
} // namespace mvvm
} // namespace go

#endif  // #if !defined(GO_MSVC_MFC)

#endif  // #ifndef GO_MVVM_UTILITY_MFC_DLGDATA_HPP_INCLUDED
