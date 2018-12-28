---
layout: boost_lib_config
---

```c++
namespace go_boost::config
```

# Preprocessor

```c++
<go_boost/config.hpp>
```

Macro | Description
-|-
GO_BOOST_APPEND_L(_s_) | Append L to a string litteral to make it a wide string litteral, e.g. GO_BOOST_APPEND_L("text") will return L"text".
GO_BOOST_APPEND_U16(_s_) | Append u to a string litteral to make it a UTF-16 string litteral, e.g. GO_BOOST_APPEND_U16("text") will return u"text".
GO_BOOST_APPEND_U32(_s_) | Append U to a string litteral to make it a UTF-32 string litteral, e.g. GO_BOOST_APPEND_U32("text") will return U"text".
GO_BOOST_APPEND_U8(_s_) | Append u8 to a string litteral to make it a UTF-8 string litteral, e.g. GO_BOOST_APPEND_U8("text") will return u8"text".
GO_BOOST_FUNC | The name of the current function expanded to a string literal.
GO_BOOST_TO_STRING(_s_) | The argument _s_ is converted to a string literal. The preprocessor stringizing operator (#) prevents arguments from expanding.  This macro allows its argument to expand before it is stringized, e.g. using GO_BOOST_TO_STRING(\_\_LINE\_\_) on line number 47 will return "47".
GO_BOOST_TO_U16STRING(_s_) | Same as **GO_BOOST_TO_STRING** but the argument _s_ is converted to a UTF-16 string literal, e.g. using GO_BOOST_TO_U16STRING(\_\_LINE\_\_) on line number 47 will return u"47".
GO_BOOST_TO_U32STRING(_s_) | Same as **GO_BOOST_TO_STRING** but the argument _s_ is converted to a UTF-32 string literal, e.g. using GO_BOOST_TO_U32STRING(\_\_LINE\_\_) on line number 47 will return U"47".
GO_BOOST_TO_U8STRING(_s_) | Same as **GO_BOOST_TO_STRING** but the argument _s_ is converted to a UTF-8 string literal, e.g. using GO_BOOST_TO_U8STRING(\_\_LINE\_\_) on line number 47 will return u8"47".
GO_BOOST_TO_WSTRING(_s_) | Same as **GO_BOOST_TO_STRING** but the argument _s_ is converted to a wide string literal, e.g. using GO_BOOST_TO_WSTRING(\_\_LINE\_\_) on line number 47 will return L"47".
GO_BOOST_WFILE | The name of the current source file expanded to a wide string literal.
GO_BOOST_WFUNC | The name of the current function expanded to a wide string literal.
