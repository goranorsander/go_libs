//
//  string_cast_example.cpp
//
//  Copyright 2018-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

#if defined(GO_NO_CXX11) || defined(GO_NO_CXX11_DEFAULTED_AND_DELETED_FUNCTIONS)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
int main() { return -1; }
#else

#include <iostream>
#include <go/namespace_alias.hpp>
#include <go/string.hpp>

template<class S, typename C = unsigned int>
void print_hex(const S& s)
{
    const size_t sizeof_value_type = sizeof(GO_TYPENAME S::value_type);
    const size_t hex_c_size = sizeof_value_type*2 + 3;
    const std::wstring hex_format = s::format(L"0x%%0%uX ", sizeof_value_type*2);
    unsigned int line_length = 0;
    for (const GO_TYPENAME S::value_type c : s)
    {
        std::wcout << s::format(hex_format.c_str(), static_cast<C>(c)).c_str();
        line_length += hex_c_size;
        if (line_length >= 80)
        {
            std::wcout << std::endl;
            line_length = 0;
        }
    }
    if (line_length > 0)
        std::wcout << std::endl;
}

int main()
{
    {
#if !defined(GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
        std::wcout << L"Sju sj�sjuka sj�m�n ... (Swedish tongue twister)" << std::endl << std::endl;
#else
        std::wcout << L"Sju sjosjuka sjoman ... (Swedish tongue twister)" << std::endl << std::endl;
#endif  // #if !defined(GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)

        const std::string multibyte_swedish_source =
#if !defined(GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
            "Sju sj�sjuka sj�m�n p� sjunkande skeppet Shanghai sk�ttes av sju sk�na sjuksk�terskor.";
#else
            "Sju sjosjuka sjoman pa sjunkande skeppet Shanghai skottes av sju skona sjukskoterskor.";
#endif  // #if !defined(GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
        const std::string multibyte_swedish = s::string_cast<std::string>(multibyte_swedish_source);
        const std::wstring system_wide_swedish = s::string_cast<std::wstring>(multibyte_swedish_source);
        const std::u16string utf_16_swedish = s::string_cast<std::u16string>(multibyte_swedish_source);
        const std::u32string utf_32_swedish = s::string_cast<std::u32string>(multibyte_swedish_source);
        const s::u8string utf_8_swedish = s::string_cast<s::u8string>(multibyte_swedish_source);

        std::wcout << L"Multibyte: size=" << multibyte_swedish.size() << std::endl;
        print_hex<std::string, unsigned char>(multibyte_swedish);

        std::wcout << std::endl << L"System wide: size=" << system_wide_swedish.size()
            << L", text=" << system_wide_swedish.c_str() << std::endl;
        print_hex(system_wide_swedish);

        std::wcout << std::endl << L"UTF-16: size=" << utf_16_swedish.size() << std::endl;
        print_hex(utf_16_swedish);

        std::wcout << std::endl << L"UTF-32: size=" << utf_32_swedish.size() << std::endl;
        print_hex(utf_32_swedish);

        std::wcout << std::endl << L"UTF-8: size=" << utf_8_swedish.size()
            << L", characters=" << utf_8_swedish.characters() << std::endl;
        print_hex(utf_8_swedish);
    }
    {
        std::wcout << std::endl << L"Om mani padme hum (Tibetan mantra)" << std::endl << std::endl;

        const s::u8string utf_8_tibetan_source = s::u8string(reinterpret_cast<const char8_t*>(
            "\x4F\x6D\x20\x6D\x61\x6E\x69\x20\x70\x61\x64\x6D\x65\x20\x68\x75" \
            "\x6D\x20\x28\x54\x69\x62\x65\x74\x61\x6E\x20\x6D\x61\x6E\x74\x72" \
            "\x61\x29\x3A\x20\xE0\xBD\xA8\xE0\xBD\xBC\xE0\xBD\xBE\xE0\xBC\x8B" \
            "\xE0\xBD\x98\xE0\xBC\x8B\xE0\xBD\x8E\xE0\xBD\xB2\xE0\xBC\x8B\xE0" \
            "\xBD\x94\xE0\xBD\x91\xE0\xBE\xA8\xE0\xBD\xBA\xE0\xBC\x8B\xE0\xBD" \
            "\xA7\xE0\xBD\xB1\xE0\xBD\xB4\xE0\xBE\x82\xE0\xBC\x94"));
        const std::string multibyte_tibetan = s::string_cast<std::string>(utf_8_tibetan_source);
        const std::wstring system_wide_tibetan = s::string_cast<std::wstring>(utf_8_tibetan_source);
        const std::u16string utf_16_tibetan = s::string_cast<std::u16string>(utf_8_tibetan_source);
        const std::u32string utf_32_tibetan = s::string_cast<std::u32string>(utf_8_tibetan_source);
        const s::u8string utf_8_tibetan = s::string_cast<s::u8string>(utf_8_tibetan_source);

        std::wcout << L"Multibyte: size=" << multibyte_tibetan.size() << L", text=" << multibyte_tibetan.c_str() << std::endl;
        print_hex<std::string, unsigned char>(multibyte_tibetan);

        std::wcout << std::endl << L"System wide: size=" << system_wide_tibetan.size() << std::endl;
        print_hex(system_wide_tibetan);

        std::wcout << std::endl << L"UTF-16: size=" << utf_16_tibetan.size() << std::endl;
        print_hex(utf_16_tibetan);

        std::wcout << std::endl << L"UTF-32: size=" << utf_32_tibetan.size() << std::endl;
        print_hex(utf_32_tibetan);

        std::wcout << std::endl << L"UTF-8: size=" << utf_8_tibetan.size()
            << L", characters=" << utf_8_tibetan.characters() << std::endl;
        print_hex(utf_8_tibetan);
    }
    return 0;
}

#endif  // Required C++11 feature is not supported by this compiler
