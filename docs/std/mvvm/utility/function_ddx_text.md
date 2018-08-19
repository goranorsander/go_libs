---
layout: std_lib_mvvm_utility
---

```c++
namespace go::mvvm::utility
```

# function template equals

```c++
<go/mvvm/utility/mfc_dlgdata.hpp>
```

The **DDX_Text** function manages the transfer of some commonly used property types
between an edit control in a dialog box, form view, or control view and a CString
data member of the dialog box, form view, or control view object.

It is declared as:

```c++
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<BYTE>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<short>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<int>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<UINT>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<long>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<DWORD>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<LONGLONG>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<ULONGLONG>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<float>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<double>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<CString>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<std::string>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::property<std::wstring>& value);

void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<BYTE>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<short>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<int>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<UINT>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<long>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<DWORD>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<LONGLONG>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<ULONGLONG>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<float>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<double>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<CString>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<std::string>& value);
void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, go::property::wproperty<std::wstring>& value);
```

## Parameters

Parameter | Description
-|-
pDX|A pointer to a **CDataExchange** object. The MFC-framework supplies this object to establish the context of the data exchange, including its direction.
nIDC|The ID of an edit control in the dialog box, form view, or control view object.
value|A reference to a property member in the dialog box, form view, or control view object. The data type of value depends on which of the overloaded versions of DDX_Text you use.
