#ifndef GO_BOOST_MVVM_UTILITY_MFC_DLGDATA_HPP_INCLUDED
#define GO_BOOST_MVVM_UTILITY_MFC_DLGDATA_HPP_INCLUDED

//
//  mfc_dlgdata.hpp
//
//  Copyright 2015-2021 Göran Orsander
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
#include <go_boost/type_traits/fundamental_type_specializer.hpp>

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

inline void AFXAPI DDX_Text_BYTE(CDataExchange* pDX, int nIDC, boost::function<BYTE(void)> get, boost::function<void(const BYTE&)> set)
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

inline void AFXAPI DDX_Text_short(CDataExchange* pDX, int nIDC, boost::function<short(void)> get, boost::function<void(const short&)> set)
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

inline void AFXAPI DDX_Text_int(CDataExchange* pDX, int nIDC, boost::function<int(void)> get, boost::function<void(const int&)> set)
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

inline void AFXAPI DDX_Text_UINT(CDataExchange* pDX, int nIDC, boost::function<UINT(void)> get, boost::function<void(const UINT&)> set)
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

inline void AFXAPI DDX_Text_long(CDataExchange* pDX, int nIDC, boost::function<long(void)> get, boost::function<void(const long&)> set)
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

inline void AFXAPI DDX_Text_DWORD(CDataExchange* pDX, int nIDC, boost::function<DWORD(void)> get, boost::function<void(const DWORD&)> set)
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

inline void AFXAPI DDX_Text_LONGLONG(CDataExchange* pDX, int nIDC, boost::function<LONGLONG(void)> get, boost::function<void(const LONGLONG&)> set)
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

inline void AFXAPI DDX_Text_ULONGLONG(CDataExchange* pDX, int nIDC, boost::function<ULONGLONG(void)> get, boost::function<void(const ULONGLONG&)> set)
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

inline void AFXAPI DDX_Text_float(CDataExchange* pDX, int nIDC, boost::function<float(void)> get, boost::function<void(const float&)> set)
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

inline void AFXAPI DDX_Text_double(CDataExchange* pDX, int nIDC, boost::function<double(void)> get, boost::function<void(const double&)> set)
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

inline void AFXAPI DDX_Text_CString(CDataExchange* pDX, int nIDC, boost::function<CString(void)> get, boost::function<void(const CString&)> set)
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

inline void AFXAPI DDX_Text_std_string(CDataExchange* pDX, int nIDC, boost::function<std::string(void)> get, boost::function<void(const std::string&)> set)
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

inline void AFXAPI DDX_Text_std_wstring(CDataExchange* pDX, int nIDC, boost::function<std::wstring(void)> get, boost::function<void(const std::wstring&)> set)
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

template<typename FundamentalType, class FundamentalTypeSpecializerProperty>
FundamentalType get_specialized_fundamental_type(const FundamentalTypeSpecializerProperty& p)
{
    return p.get().get();
}

template<class FundamentalTypeSpecializer, typename FundamentalType, class FundamentalTypeSpecializerProperty>
void set_specialized_fundamental_type(FundamentalTypeSpecializerProperty& p, const FundamentalType& v)
{
    const FundamentalTypeSpecializer s(v);
    return p.set(s);
}

}

// go_boost::property::property

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<BYTE>& value)
{
    detail::DDX_Text_BYTE(pDX, nIDC, boost::bind(&go_boost::property::property<BYTE>::get, &value), boost::bind(&go_boost::property::property<BYTE>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<short>& value)
{
    detail::DDX_Text_short(pDX, nIDC, boost::bind(&go_boost::property::property<short>::get, &value), boost::bind(&go_boost::property::property<short>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<int>& value)
{
    detail::DDX_Text_int(pDX, nIDC, boost::bind(&go_boost::property::property<int>::get, &value), boost::bind(&go_boost::property::property<int>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<UINT>& value)
{
    detail::DDX_Text_UINT(pDX, nIDC, boost::bind(&go_boost::property::property<UINT>::get, &value), boost::bind(&go_boost::property::property<UINT>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<long>& value)
{
    detail::DDX_Text_long(pDX, nIDC, boost::bind(&go_boost::property::property<long>::get, &value), boost::bind(&go_boost::property::property<long>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<DWORD>& value)
{
    detail::DDX_Text_DWORD(pDX, nIDC, boost::bind(&go_boost::property::property<DWORD>::get, &value), boost::bind(&go_boost::property::property<DWORD>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<LONGLONG>& value)
{
    detail::DDX_Text_LONGLONG(pDX, nIDC, boost::bind(&go_boost::property::property<LONGLONG>::get, &value), boost::bind(&go_boost::property::property<LONGLONG>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<ULONGLONG>& value)
{
    detail::DDX_Text_ULONGLONG(pDX, nIDC, boost::bind(&go_boost::property::property<ULONGLONG>::get, &value), boost::bind(&go_boost::property::property<ULONGLONG>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<float>& value)
{
    detail::DDX_Text_float(pDX, nIDC, boost::bind(&go_boost::property::property<float>::get, &value), boost::bind(&go_boost::property::property<float>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<double>& value)
{
    detail::DDX_Text_double(pDX, nIDC, boost::bind(&go_boost::property::property<double>::get, &value), boost::bind(&go_boost::property::property<double>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<CString>& value)
{
    detail::DDX_Text_CString(pDX, nIDC, boost::bind(&go_boost::property::property<CString>::get, &value), boost::bind(&go_boost::property::property<CString>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<std::string>& value)
{
    detail::DDX_Text_std_string(pDX, nIDC, boost::bind(&go_boost::property::property<std::string>::get, &value), boost::bind(&go_boost::property::property<std::string>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<std::wstring>& value)
{
    detail::DDX_Text_std_wstring(pDX, nIDC, boost::bind(&go_boost::property::property<std::wstring>::get, &value), boost::bind(&go_boost::property::property<std::wstring>::set, &value, boost::placeholders::_1));
}

// go_boost::property::property<go_boost::type_traits::fundamental_type_specializer>

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, BYTE>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_BYTE(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<BYTE, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, BYTE, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, short>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_short(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<short, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, short, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, int>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_int(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<int, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, int, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, UINT>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_UINT(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<UINT, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, UINT, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, long>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_long(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<long, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, long, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, DWORD>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_DWORD(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<DWORD, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, DWORD, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, LONGLONG>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_LONGLONG(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<LONGLONG, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, LONGLONG, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, ULONGLONG>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_ULONGLONG(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<ULONGLONG, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, ULONGLONG, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, float>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_float(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<float, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, float, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, double>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_double(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<double, go_boost::property::property<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, double, go_boost::property::property<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

// go_boost::property::wproperty

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<BYTE>& value)
{
    detail::DDX_Text_BYTE(pDX, nIDC, boost::bind(&go_boost::property::wproperty<BYTE>::get, &value), boost::bind(&go_boost::property::wproperty<BYTE>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<short>& value)
{
    detail::DDX_Text_short(pDX, nIDC, boost::bind(&go_boost::property::wproperty<short>::get, &value), boost::bind(&go_boost::property::wproperty<short>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<int>& value)
{
    detail::DDX_Text_int(pDX, nIDC, boost::bind(&go_boost::property::wproperty<int>::get, &value), boost::bind(&go_boost::property::wproperty<int>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<UINT>& value)
{
    detail::DDX_Text_UINT(pDX, nIDC, boost::bind(&go_boost::property::wproperty<UINT>::get, &value), boost::bind(&go_boost::property::wproperty<UINT>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<long>& value)
{
    detail::DDX_Text_long(pDX, nIDC, boost::bind(&go_boost::property::wproperty<long>::get, &value), boost::bind(&go_boost::property::wproperty<long>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<DWORD>& value)
{
    detail::DDX_Text_DWORD(pDX, nIDC, boost::bind(&go_boost::property::wproperty<DWORD>::get, &value), boost::bind(&go_boost::property::wproperty<DWORD>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<LONGLONG>& value)
{
    detail::DDX_Text_LONGLONG(pDX, nIDC, boost::bind(&go_boost::property::wproperty<LONGLONG>::get, &value), boost::bind(&go_boost::property::wproperty<LONGLONG>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<ULONGLONG>& value)
{
    detail::DDX_Text_ULONGLONG(pDX, nIDC, boost::bind(&go_boost::property::wproperty<ULONGLONG>::get, &value), boost::bind(&go_boost::property::wproperty<ULONGLONG>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<float>& value)
{
    detail::DDX_Text_float(pDX, nIDC, boost::bind(&go_boost::property::wproperty<float>::get, &value), boost::bind(&go_boost::property::wproperty<float>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<double>& value)
{
    detail::DDX_Text_double(pDX, nIDC, boost::bind(&go_boost::property::wproperty<double>::get, &value), boost::bind(&go_boost::property::wproperty<double>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<CString>& value)
{
    detail::DDX_Text_CString(pDX, nIDC, boost::bind(&go_boost::property::wproperty<CString>::get, &value), boost::bind(&go_boost::property::wproperty<CString>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<std::string>& value)
{
    detail::DDX_Text_std_string(pDX, nIDC, boost::bind(&go_boost::property::wproperty<std::string>::get, &value), boost::bind(&go_boost::property::wproperty<std::string>::set, &value, boost::placeholders::_1));
}

inline void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<std::wstring>& value)
{
    detail::DDX_Text_std_wstring(pDX, nIDC, boost::bind(&go_boost::property::wproperty<std::wstring>::get, &value), boost::bind(&go_boost::property::wproperty<std::wstring>::set, &value, boost::placeholders::_1));
}

// go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer>

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, BYTE>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_BYTE(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<BYTE, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, BYTE>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, short>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_short(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<short, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, short>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, int>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_int(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<int, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, int, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, UINT>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_UINT(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<UINT, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, UINT, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, long>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_long(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<long, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, long, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, DWORD>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_DWORD(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<DWORD, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, DWORD, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, LONGLONG>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_LONGLONG(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<LONGLONG, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, LONGLONG, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, ULONGLONG>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_ULONGLONG(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<ULONGLONG, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, ULONGLONG, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, float>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_float(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<float, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, float, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

template<class FundamentalTypeSpecializer>
typename boost::enable_if_c<boost::is_base_of<go_boost::type_traits::detail::fundamental_type_specializer_base, FundamentalTypeSpecializer>::value && boost::is_same<typename FundamentalTypeSpecializer::fundamental_type, double>::value, void>::type AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<FundamentalTypeSpecializer>& value)
{
    detail::DDX_Text_double(pDX, nIDC, boost::bind(detail::get_specialized_fundamental_type<double, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::cref(value)), boost::bind(detail::set_specialized_fundamental_type<FundamentalTypeSpecializer, double, go_boost::property::wproperty<FundamentalTypeSpecializer>>, boost::ref(value), boost::placeholders::_1));
}

} // namespace utility
} // namespace mvvm
} // namespace go_boost

#endif  // #if !defined(_MFC_VER)

#endif  // #ifndef GO_BOOST_MVVM_UTILITY_MFC_DLGDATA_HPP_INCLUDED
