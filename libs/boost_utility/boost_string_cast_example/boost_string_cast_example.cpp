//
//  boost_string_cast_example.cpp
//
//  Copyright 2018 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>
#include <go_boost/utility.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <iostream>

namespace u = go_boost::utility;

template<class S, typename C = unsigned int>
void print_hex(const S& s)
{
    const size_t sizeof_value_type = sizeof(S::value_type);
    const size_t hex_c_size = sizeof_value_type*2 + 3;
    const std::wstring hex_format = (boost::wformat(L"0x%%0%uX ") % (sizeof_value_type*2)).str();
    unsigned int line_length = 0;
    BOOST_FOREACH (const S::value_type c, s)
    {
        std::wcout << (boost::wformat(hex_format.c_str()) % static_cast<C>(c)).str().c_str();
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
        std::wcout << L"Sju sj�sjuka sj�m�n ... (Swedish tongue twister)" << std::endl << std::endl;

        const std::string multibyte_swedish_source =
            "Sju sj�sjuka sj�m�n p� sjunkande skeppet Shanghai sk�ttes av sju sk�na sjuksk�terskor.";
        const std::string multibyte_swedish = u::string_cast<std::string>(multibyte_swedish_source);
        const std::wstring system_wide_swedish = u::string_cast<std::wstring>(multibyte_swedish_source);
        const u::u16string utf_16_swedish = u::string_cast<u::u16string>(multibyte_swedish_source);
        const u::u32string utf_32_swedish = u::string_cast<u::u32string>(multibyte_swedish_source);
        const u::u8string utf_8_swedish = u::string_cast<u::u8string>(multibyte_swedish_source);

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

        const u::u8string utf_8_tibetan_source = u::u8string(reinterpret_cast<const u::char8_t*>(
            "\x4F\x6D\x20\x6D\x61\x6E\x69\x20\x70\x61\x64\x6D\x65\x20\x68\x75" \
            "\x6D\x20\x28\x54\x69\x62\x65\x74\x61\x6E\x20\x6D\x61\x6E\x74\x72" \
            "\x61\x29\x3A\x20\xE0\xBD\xA8\xE0\xBD\xBC\xE0\xBD\xBE\xE0\xBC\x8B" \
            "\xE0\xBD\x98\xE0\xBC\x8B\xE0\xBD\x8E\xE0\xBD\xB2\xE0\xBC\x8B\xE0" \
            "\xBD\x94\xE0\xBD\x91\xE0\xBE\xA8\xE0\xBD\xBA\xE0\xBC\x8B\xE0\xBD" \
            "\xA7\xE0\xBD\xB1\xE0\xBD\xB4\xE0\xBE\x82\xE0\xBC\x94"));
        const std::string multibyte_tibetan = u::string_cast<std::string>(utf_8_tibetan_source);
        const std::wstring system_wide_tibetan = u::string_cast<std::wstring>(utf_8_tibetan_source);
        const u::u16string utf_16_tibetan = u::string_cast<u::u16string>(utf_8_tibetan_source);
        const u::u32string utf_32_tibetan = u::string_cast<u::u32string>(utf_8_tibetan_source);
        const u::u8string utf_8_tibetan = u::string_cast<u::u8string>(utf_8_tibetan_source);

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