---
layout: boost_lib_string
---

```c++
namespace go_boost::string
```

# function template string_cast

```c++
<go_boost/string/string_cast.hpp>
```

The **string_cast** function is used to convert string objects from one
string class to another. The following string classes are supported:

Class|Expected encoding
-|-
std\::string|ASCII, ISO/IEC 8859-1, or Windows 1252
std\::wstring|UCS-2 or UCS-4
go_boost\::string\::u2string|UCS-2
go_boost\::string\::u8string|UTF-8
go_boost\::string\::u16string|UTF-16
go_boost\::string\::u32string|UTF-32

The **string_cast** function will try to encode the string using the expected
encoding for the destination string class.

It is declared as:

```c++
template <typename to_string, typename from_string>
to_string string_cast(const from_string& from);
```

## Template parameters

Parameter | Description
-|-
to_string|The string class to convert to
from_string|The string class to convert from, usually implicit

## Parameters

Parameter | Description
-|-
from|The string being converted

## Return value

A string object of the **to_string** class.

# Example

Casting a **go_boost\::string\::u8string** object to each of the other supported string
classes. The sample string contains the Tibetan mantra
*[Om mani padme hum](https://en.wikipedia.org/wiki/Om_mani_padme_hum)* with both
latin and Tibetan transcriptions. Note that the Tibetan part of the string is stripped
from the **std::string** by the **string_cast** function since it have no support for
Tibetan characters/symbols.

```c++
#include <iostream>
#include <go_boost/string.hpp>

namespace u = go_boost::utility;
namespace us = go_boost::string;

template<class S, typename C = unsigned int>
void print_hex(const S& s)
{
    const size_t sizeof_value_type = sizeof(S::value_type);
    const size_t hex_c_size = sizeof_value_type*2 + 3;
    const std::wstring hex_format = s::format(L"0x%%0%uX ", sizeof_value_type *2);
    unsigned int line_length = 0;
    for (const S::value_type c : s)
    {
        boost::wcout << s::format(hex_format, static_cast<C>(c)).c_str();
        line_length += hex_c_size;
        if (line_length >= 80)
        {
            boost::wcout << boost::endl;
            line_length = 0;
        }
    }
    if (line_length > 0)
        boost::wcout << boost::endl;
}

int main()
{
    boost::wcout << boost::endl << L"Om mani padme hum (Tibetan mantra)" << boost::endl << boost::endl;

    const s::u8string utf_8_source = s::u8string(reinterpret_cast<const char8_t*>(
        "\x4F\x6D\x20\x6D\x61\x6E\x69\x20\x70\x61\x64\x6D\x65\x20\x68\x75" \
        "\x6D\x20\x28\x54\x69\x62\x65\x74\x61\x6E\x20\x6D\x61\x6E\x74\x72" \
        "\x61\x29\x3A\x20\xE0\xBD\xA8\xE0\xBD\xBC\xE0\xBD\xBE\xE0\xBC\x8B" \
        "\xE0\xBD\x98\xE0\xBC\x8B\xE0\xBD\x8E\xE0\xBD\xB2\xE0\xBC\x8B\xE0" \
        "\xBD\x94\xE0\xBD\x91\xE0\xBE\xA8\xE0\xBD\xBA\xE0\xBC\x8B\xE0\xBD" \
        "\xA7\xE0\xBD\xB1\xE0\xBD\xB4\xE0\xBE\x82\xE0\xBC\x94"));
    const std::string multibyte = s::string_cast<std::string>(utf_8_source);
    const std::wstring system_wide = s::string_cast<std::wstring>(utf_8_source);
    const go_boost::u16string utf_16 = s::string_cast<go_boost::u16string>(utf_8_source);
    const go_boost::u32string utf_32 = s::string_cast<go_boost::u32string>(utf_8_source);
    const s::u8string utf_8 = s::string_cast<s::u8string>(utf_8_source);

    boost::wcout << L"Multibyte: size=" << multibyte.size() << L", text=" << multibyte.c_str() << boost::endl;
    print_hex<std::string, unsigned char>(multibyte);

    boost::wcout << boost::endl << L"System wide: size=" << system_wide.size() << boost::endl;
    print_hex(system_wide);

    boost::wcout << boost::endl << L"UTF-16: size=" << utf_16.size() << boost::endl;
    print_hex(utf_16);

    boost::wcout << boost::endl << L"UTF-32: size=" << utf_32.size() << boost::endl;
    print_hex(utf_32);

    boost::wcout << boost::endl << L"UTF-8: size=" << utf_8.size()
        << L", characters=" << utf_8.characters() << boost::endl;
    print_hex(utf_8);

    return 0;
}
```

Output

```
Om mani padme hum (Tibetan mantra)

Multibyte: size=36, text=Om mani padme hum (Tibetan mantra):
0x4F 0x6D 0x20 0x6D 0x61 0x6E 0x69 0x20 0x70 0x61 0x64 0x6D 0x65 0x20 0x68 0x75
0x6D 0x20 0x28 0x54 0x69 0x62 0x65 0x74 0x61 0x6E 0x20 0x6D 0x61 0x6E 0x74 0x72
0x61 0x29 0x3A 0x20

System wide: size=55
0x004F 0x006D 0x0020 0x006D 0x0061 0x006E 0x0069 0x0020 0x0070 0x0061 0x0064 0x006D
0x0065 0x0020 0x0068 0x0075 0x006D 0x0020 0x0028 0x0054 0x0069 0x0062 0x0065 0x0074
0x0061 0x006E 0x0020 0x006D 0x0061 0x006E 0x0074 0x0072 0x0061 0x0029 0x003A 0x0020
0x0F68 0x0F7C 0x0F7E 0x0F0B 0x0F58 0x0F0B 0x0F4E 0x0F72 0x0F0B 0x0F54 0x0F51 0x0FA8
0x0F7A 0x0F0B 0x0F67 0x0F71 0x0F74 0x0F82 0x0F14

UTF-16: size=55
0x004F 0x006D 0x0020 0x006D 0x0061 0x006E 0x0069 0x0020 0x0070 0x0061 0x0064 0x006D
0x0065 0x0020 0x0068 0x0075 0x006D 0x0020 0x0028 0x0054 0x0069 0x0062 0x0065 0x0074
0x0061 0x006E 0x0020 0x006D 0x0061 0x006E 0x0074 0x0072 0x0061 0x0029 0x003A 0x0020
0x0F68 0x0F7C 0x0F7E 0x0F0B 0x0F58 0x0F0B 0x0F4E 0x0F72 0x0F0B 0x0F54 0x0F51 0x0FA8
0x0F7A 0x0F0B 0x0F67 0x0F71 0x0F74 0x0F82 0x0F14

UTF-32: size=55
0x0000004F 0x0000006D 0x00000020 0x0000006D 0x00000061 0x0000006E 0x00000069 0x00000020
0x00000070 0x00000061 0x00000064 0x0000006D 0x00000065 0x00000020 0x00000068 0x00000075
0x0000006D 0x00000020 0x00000028 0x00000054 0x00000069 0x00000062 0x00000065 0x00000074
0x00000061 0x0000006E 0x00000020 0x0000006D 0x00000061 0x0000006E 0x00000074 0x00000072
0x00000061 0x00000029 0x0000003A 0x00000020 0x00000F68 0x00000F7C 0x00000F7E 0x00000F0B
0x00000F58 0x00000F0B 0x00000F4E 0x00000F72 0x00000F0B 0x00000F54 0x00000F51 0x00000FA8
0x00000F7A 0x00000F0B 0x00000F67 0x00000F71 0x00000F74 0x00000F82 0x00000F14

UTF-8: size=93, characters=55
0x4F 0x6D 0x20 0x6D 0x61 0x6E 0x69 0x20 0x70 0x61 0x64 0x6D 0x65 0x20 0x68 0x75
0x6D 0x20 0x28 0x54 0x69 0x62 0x65 0x74 0x61 0x6E 0x20 0x6D 0x61 0x6E 0x74 0x72
0x61 0x29 0x3A 0x20 0xE0 0xBD 0xA8 0xE0 0xBD 0xBC 0xE0 0xBD 0xBE 0xE0 0xBC 0x8B
0xE0 0xBD 0x98 0xE0 0xBC 0x8B 0xE0 0xBD 0x8E 0xE0 0xBD 0xB2 0xE0 0xBC 0x8B 0xE0
0xBD 0x94 0xE0 0xBD 0x91 0xE0 0xBE 0xA8 0xE0 0xBD 0xBA 0xE0 0xBC 0x8B 0xE0 0xBD
0xA7 0xE0 0xBD 0xB1 0xE0 0xBD 0xB4 0xE0 0xBE 0x82 0xE0 0xBC 0x94
```
