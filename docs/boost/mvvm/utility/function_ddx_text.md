---
layout: boost_lib_mvvm_utility
---

```c++
namespace go_boost::mvvm::utility
```

# function template equals

```c++
<go_boost/mvvm/utility/mfc_dlgdata.hpp>
```

The **DDX_Text** function manages the transfer of some commonly used property types
between an edit control in a dialog box, form view, or control view and a CString
data member of the dialog box, form view, or control view object.

It is declared as:

```c++
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<BYTE>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<short>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<int>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<UINT>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<long>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<DWORD>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<LONGLONG>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<ULONGLONG>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<float>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<double>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<CString>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<std::string>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<std::wstring>& value);

void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<BYTE>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<short>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<int>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<UINT>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<long>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<DWORD>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<LONGLONG>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<ULONGLONG>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<float>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::property<go_boost::type_traits::fundamental_type_specializer<double>>& value);

void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<BYTE>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<short>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<int>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<UINT>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<long>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<DWORD>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<LONGLONG>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<ULONGLONG>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<float>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<double>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<CString>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<std::string>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<std::wstring>& value);

void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<BYTE>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<short>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<int>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<UINT>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<long>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<DWORD>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<LONGLONG>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<ULONGLONG>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<float>>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go_boost::property::wproperty<go_boost::type_traits::fundamental_type_specializer<double>>& value);
```

## Parameters

Parameter | Description
-|-
pDX|A pointer to a **CDataExchange** object. The MFC-framework supplies this object to establish the context of the data exchange, including its direction.
nIDC|The ID of an edit control in the dialog box, form view, or control view object.
value|A reference to a property member in the dialog box, form view, or control view object. The data type of value depends on which of the overloaded versions of DDX_Text you use.
