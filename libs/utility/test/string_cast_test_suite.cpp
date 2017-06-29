//
//  string_cast_test_suite.cpp
//
//  Copyright 2017 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <gtest/gtest.h>
#include <go/config.hpp>

#if defined(GO_NO_CXX11)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_string_cast_test_suite, cpp11_not_supported) {}
#else

#include <go/utility/string_cast.hpp>

namespace u = go::utility;

namespace
{
namespace multibyte
{

// ASCII, see https://en.wikipedia.org/wiki/ASCII
const char* ascii_printable_characters =
    " !\"#$%&'()*+,-./" \
    "0123456789:;<=>?" \
    "@ABCDEFGHIJKLMNO" \
    "PQRSTUVWXYZ[\\]^_" \
    "`abcdefghijklmno" \
    "pqrstuvwxyz{|}~";

const char* ascii_printable_characters_from_hex_codes =
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F" \
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F" \
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F" \
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F" \
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E";

// ISO/IEC 8859-1, see https://en.wikipedia.org/wiki/ISO/IEC_8859-1
const char* iso_8859_1_printable_characters =
    " !\"#$%&'()*+,-./" \
    "0123456789:;<=>?" \
    "@ABCDEFGHIJKLMNO" \
    "PQRSTUVWXYZ[\\]^_" \
    "`abcdefghijklmno" \
    "pqrstuvwxyz{|}~" \
    " ¡¢£¤¥¦§¨©ª«¬­®¯" \
    "°±²³´µ¶·¸¹º»¼½¾¿" \
    "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏ" \
    "ĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß" \
    "àáâãäåæçèéêëìíîï" \
    "ğñòóôõö÷øùúûüışÿ";

const char* iso_8859_1_printable_characters_from_hex_codes =
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F" \
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F" \
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F" \
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F" \
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E" \
    "\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF" \
    "\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF" \
    "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF" \
    "\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF" \
    "\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF" \
    "\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
const char* swedish = "Sju sjösjuka sjömän på sjunkande skeppet Shanghai sköttes av sju sköna sjuksköterskor.";

}
namespace system_wide
{

// ASCII
const wchar_t* ascii_printable_characters =
    L" !\"#$%&'()*+,-./" \
    L"0123456789:;<=>?" \
    L"@ABCDEFGHIJKLMNO" \
    L"PQRSTUVWXYZ[\\]^_" \
    L"`abcdefghijklmno" \
    L"pqrstuvwxyz{|}~";

// ISO/IEC 8859-1
const wchar_t* iso_8859_1_printable_characters =
    L" !\"#$%&'()*+,-./" \
    L"0123456789:;<=>?" \
    L"@ABCDEFGHIJKLMNO" \
    L"PQRSTUVWXYZ[\\]^_" \
    L"`abcdefghijklmno" \
    L"pqrstuvwxyz{|}~" \
    L" ¡¢£¤¥¦§¨©ª«¬­®¯" \
    L"°±²³´µ¶·¸¹º»¼½¾¿" \
    L"ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏ" \
    L"ĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß" \
    L"àáâãäåæçèéêëìíîï" \
    L"ğñòóôõö÷øùúûüışÿ";

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
const wchar_t* swedish = L"Sju sjösjuka sjömän på sjunkande skeppet Shanghai sköttes av sju sköna sjuksköterskor.";

}
namespace ucs_2
{

// ASCII
const u::char2_t ascii_printable_characters[] =
    { 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F
    , 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
    , 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F
    , 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F
    , 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F
    , 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x0000 };

// ISO/IEC 8859-1
const u::char2_t iso_8859_1_printable_characters[] =
    { 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F
    , 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
    , 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F
    , 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F
    , 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F
    , 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E
    , 0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF
    , 0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF
    , 0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF
    , 0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF
    , 0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF
    , 0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF
    , 0x0000 };

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
const u::char2_t swedish[] =
    { 0x0053, 0x006A, 0x0075, 0x0020, 0x0073, 0x006A, 0x00F6, 0x0073, 0x006A, 0x0075, 0x006B, 0x0061, 0x0020                            // Sju sjösjuka
    , 0x0073, 0x006A, 0x00F6, 0x006D, 0x00E4, 0x006E, 0x0020, 0x0070, 0x00E5, 0x0020                                                    // sjömän på
    , 0x0073, 0x006A, 0x0075, 0x006E, 0x006B, 0x0061, 0x006E, 0x0064, 0x0065, 0x0020                                                    // sjunkande
    , 0x0073, 0x006B, 0x0065, 0x0070, 0x0070, 0x0065, 0x0074, 0x0020                                                                    // skeppet
    , 0x0053, 0x0068, 0x0061, 0x006E, 0x0067, 0x0068, 0x0061, 0x0069, 0x0020                                                            // Shanghai
    , 0x0073, 0x006B, 0x00F6, 0x0074, 0x0074, 0x0065, 0x0073, 0x0020, 0x0061, 0x0076, 0x0020                                            // sköttes av
    , 0x0073, 0x006A, 0x0075, 0x0020, 0x0073, 0x006B, 0x00F6, 0x006E, 0x0061, 0x0020                                                    // sju sköna
    , 0x0073, 0x006A, 0x0075, 0x006B, 0x0073, 0x006B, 0x00F6, 0x0074, 0x0065, 0x0072, 0x0073, 0x006B, 0x006F, 0x0072, 0x002E, 0x0000 }; // sjuksköterskor.

}
namespace utf_8
{

// ASCII
const u::char8_t* ascii_printable_characters = reinterpret_cast<const u::char8_t*>(
    u8" !\"#$%&'()*+,-./" \
    u8"0123456789:;<=>?" \
    u8"@ABCDEFGHIJKLMNO" \
    u8"PQRSTUVWXYZ[\\]^_" \
    u8"`abcdefghijklmno" \
    u8"pqrstuvwxyz{|}~");

// ISO/IEC 8859-1
const u::char8_t* iso_8859_1_printable_characters = reinterpret_cast<const u::char8_t*>(
    u8" !\"#$%&'()*+,-./" \
    u8"0123456789:;<=>?" \
    u8"@ABCDEFGHIJKLMNO" \
    u8"PQRSTUVWXYZ[\\]^_" \
    u8"`abcdefghijklmno" \
    u8"pqrstuvwxyz{|}~" \
    u8" ¡¢£¤¥¦§¨©ª«¬­®¯" \
    u8"°±²³´µ¶·¸¹º»¼½¾¿" \
    u8"ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏ" \
    u8"ĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß" \
    u8"àáâãäåæçèéêëìíîï" \
    u8"ğñòóôõö÷øùúûüışÿ");

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
const u::char8_t* swedish = reinterpret_cast<const u::char8_t*>(u8"Sju sjösjuka sjömän på sjunkande skeppet Shanghai sköttes av sju sköna sjuksköterskor.");

}
namespace utf_16
{

// ASCII
const char16_t* ascii_printable_characters =
    u" !\"#$%&'()*+,-./" \
    u"0123456789:;<=>?" \
    u"@ABCDEFGHIJKLMNO" \
    u"PQRSTUVWXYZ[\\]^_" \
    u"`abcdefghijklmno" \
    u"pqrstuvwxyz{|}~";

// ISO/IEC 8859-1
const char16_t* iso_8859_1_printable_characters =
    u" !\"#$%&'()*+,-./" \
    u"0123456789:;<=>?" \
    u"@ABCDEFGHIJKLMNO" \
    u"PQRSTUVWXYZ[\\]^_" \
    u"`abcdefghijklmno" \
    u"pqrstuvwxyz{|}~" \
    u" ¡¢£¤¥¦§¨©ª«¬­®¯" \
    u"°±²³´µ¶·¸¹º»¼½¾¿" \
    u"ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏ" \
    u"ĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß" \
    u"àáâãäåæçèéêëìíîï" \
    u"ğñòóôõö÷øùúûüışÿ";

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
const char16_t* swedish = u"Sju sjösjuka sjömän på sjunkande skeppet Shanghai sköttes av sju sköna sjuksköterskor.";

}
namespace utf_32
{

// ASCII
const char32_t* ascii_printable_characters =
    U" !\"#$%&'()*+,-./" \
    U"0123456789:;<=>?" \
    U"@ABCDEFGHIJKLMNO" \
    U"PQRSTUVWXYZ[\\]^_" \
    U"`abcdefghijklmno" \
    U"pqrstuvwxyz{|}~";

// ISO/IEC 8859-1
const char32_t* iso_8859_1_printable_characters =
    U" !\"#$%&'()*+,-./" \
    U"0123456789:;<=>?" \
    U"@ABCDEFGHIJKLMNO" \
    U"PQRSTUVWXYZ[\\]^_" \
    U"`abcdefghijklmno" \
    U"pqrstuvwxyz{|}~" \
    U" ¡¢£¤¥¦§¨©ª«¬­®¯" \
    U"°±²³´µ¶·¸¹º»¼½¾¿" \
    U"ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏ" \
    U"ĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß" \
    U"àáâãäåæçèéêëìíîï" \
    U"ğñòóôõö÷øùúûüışÿ";

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
const char32_t* swedish = U"Sju sjösjuka sjömän på sjunkande skeppet Shanghai sköttes av sju sköna sjuksköterskor.";

}

TEST(std_string_cast_test_suite, test_multibyte_ascii_printable_characters)
{
    const std::string ascii_printable_characters(multibyte::ascii_printable_characters);
    const std::string ascii_printable_characters_from_hex_codes(multibyte::ascii_printable_characters_from_hex_codes);
    EXPECT_EQ(ascii_printable_characters, ascii_printable_characters_from_hex_codes);
}

TEST(std_string_cast_test_suite, test_multibyte_iso_8859_1_printable_characters)
{
    const std::string iso_8859_1_printable_characters(multibyte::iso_8859_1_printable_characters);
    const std::string iso_8859_1_printable_characters_from_hex_codes(multibyte::iso_8859_1_printable_characters_from_hex_codes);
    EXPECT_EQ(iso_8859_1_printable_characters, iso_8859_1_printable_characters_from_hex_codes);
}

TEST(std_string_cast_test_suite, test_cast_from_string_to_string)
{
    {
        const std::string ascii_printable_characters(multibyte::ascii_printable_characters);
        const std::string expected_result(multibyte::ascii_printable_characters);
        const std::string cast_result = u::string_cast<std::string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::string swedish(multibyte::swedish);
        const std::string expected_result(multibyte::swedish);
        const std::string cast_result = u::string_cast<std::string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_wstring_to_string)
{
    {
        const std::wstring ascii_printable_characters(system_wide::ascii_printable_characters);
        const std::string expected_result(multibyte::ascii_printable_characters);
        const std::string cast_result = u::string_cast<std::string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::wstring swedish(system_wide::swedish);
        const std::string expected_result(multibyte::swedish);
        const std::string cast_result = u::string_cast<std::string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u2string_to_string)
{
    {
        const u::u2string ascii_printable_characters(ucs_2::ascii_printable_characters);
        const std::string expected_result(multibyte::ascii_printable_characters);
        const std::string cast_result = u::string_cast<std::string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u2string swedish(ucs_2::swedish);
        const std::string expected_result(multibyte::swedish);
        const std::string cast_result = u::string_cast<std::string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u8string_to_string)
{
    {
        const u::u8string ascii_printable_characters(utf_8::ascii_printable_characters);
        const std::string expected_result(multibyte::ascii_printable_characters);
        const std::string cast_result = u::string_cast<std::string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u8string swedish(utf_8::swedish);
        const std::string expected_result(multibyte::swedish);
        const std::string cast_result = u::string_cast<std::string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u16string_to_string)
{
    {
        const std::u16string ascii_printable_characters(utf_16::ascii_printable_characters);
        const std::string expected_result(multibyte::ascii_printable_characters);
        const std::string cast_result = u::string_cast<std::string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u16string swedish(utf_16::swedish);
        const std::string expected_result(multibyte::swedish);
        const std::string cast_result = u::string_cast<std::string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u32string_to_string)
{
    {
        const std::u32string ascii_printable_characters(utf_32::ascii_printable_characters);
        const std::string expected_result(multibyte::ascii_printable_characters);
        const std::string cast_result = u::string_cast<std::string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u32string swedish(utf_32::swedish);
        const std::string expected_result(multibyte::swedish);
        const std::string cast_result = u::string_cast<std::string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_string_to_wstring)
{
    {
        const std::string ascii_printable_characters(multibyte::ascii_printable_characters);
        const std::wstring expected_result(system_wide::ascii_printable_characters);
        const std::wstring cast_result = u::string_cast<std::wstring>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::string swedish(multibyte::swedish);
        const std::wstring expected_result(system_wide::swedish);
        const std::wstring cast_result = u::string_cast<std::wstring>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_wstring_to_wstring)
{
    {
        const std::wstring ascii_printable_characters(system_wide::ascii_printable_characters);
        const std::wstring expected_result(system_wide::ascii_printable_characters);
        const std::wstring cast_result = u::string_cast<std::wstring>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::wstring swedish(system_wide::swedish);
        const std::wstring expected_result(system_wide::swedish);
        const std::wstring cast_result = u::string_cast<std::wstring>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u2string_to_wstring)
{
    {
        const u::u2string ascii_printable_characters(ucs_2::ascii_printable_characters);
        const std::wstring expected_result(system_wide::ascii_printable_characters);
        const std::wstring cast_result = u::string_cast<std::wstring>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u2string swedish(ucs_2::swedish);
        const std::wstring expected_result(system_wide::swedish);
        const std::wstring cast_result = u::string_cast<std::wstring>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u8string_to_wstring)
{
    {
        const u::u8string ascii_printable_characters(utf_8::ascii_printable_characters);
        const std::wstring expected_result(system_wide::ascii_printable_characters);
        const std::wstring cast_result = u::string_cast<std::wstring>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u8string swedish(utf_8::swedish);
        const std::wstring expected_result(system_wide::swedish);
        const std::wstring cast_result = u::string_cast<std::wstring>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u16string_to_wstring)
{
    {
        const std::u16string ascii_printable_characters(utf_16::ascii_printable_characters);
        const std::wstring expected_result(system_wide::ascii_printable_characters);
        const std::wstring cast_result = u::string_cast<std::wstring>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u16string swedish(utf_16::swedish);
        const std::wstring expected_result(system_wide::swedish);
        const std::wstring cast_result = u::string_cast<std::wstring>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u32string_to_wstring)
{
    {
        const std::u32string ascii_printable_characters(utf_32::ascii_printable_characters);
        const std::wstring expected_result(system_wide::ascii_printable_characters);
        const std::wstring cast_result = u::string_cast<std::wstring>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u32string swedish(utf_32::swedish);
        const std::wstring expected_result(system_wide::swedish);
        const std::wstring cast_result = u::string_cast<std::wstring>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_string_to_u2string)
{
    {
        const std::string ascii_printable_characters(multibyte::ascii_printable_characters);
        const u::u2string expected_result(ucs_2::ascii_printable_characters);
        const u::u2string cast_result = u::string_cast<u::u2string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::string swedish(multibyte::swedish);
        const u::u2string expected_result(ucs_2::swedish);
        const u::u2string cast_result = u::string_cast<u::u2string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_wstring_to_u2string)
{
    {
        const std::wstring ascii_printable_characters(system_wide::ascii_printable_characters);
        const u::u2string expected_result(ucs_2::ascii_printable_characters);
        const u::u2string cast_result = u::string_cast<u::u2string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::wstring swedish(system_wide::swedish);
        const u::u2string expected_result(ucs_2::swedish);
        const u::u2string cast_result = u::string_cast<u::u2string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u2string_to_u2string)
{
    {
        const u::u2string ascii_printable_characters(ucs_2::ascii_printable_characters);
        const u::u2string expected_result(ucs_2::ascii_printable_characters);
        const u::u2string cast_result = u::string_cast<u::u2string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u2string swedish(ucs_2::swedish);
        const u::u2string expected_result(ucs_2::swedish);
        const u::u2string cast_result = u::string_cast<u::u2string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u8string_to_u2string)
{
    {
        const u::u8string ascii_printable_characters(utf_8::ascii_printable_characters);
        const u::u2string expected_result(ucs_2::ascii_printable_characters);
        const u::u2string cast_result = u::string_cast<u::u2string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u8string swedish(utf_8::swedish);
        const u::u2string expected_result(ucs_2::swedish);
        const u::u2string cast_result = u::string_cast<u::u2string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u16string_to_u2string)
{
    {
        const std::u16string ascii_printable_characters(utf_16::ascii_printable_characters);
        const u::u2string expected_result(ucs_2::ascii_printable_characters);
        const u::u2string cast_result = u::string_cast<u::u2string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u16string swedish(utf_16::swedish);
        const u::u2string expected_result(ucs_2::swedish);
        const u::u2string cast_result = u::string_cast<u::u2string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u32string_to_u2string)
{
    {
        const std::u32string ascii_printable_characters(utf_32::ascii_printable_characters);
        const u::u2string expected_result(ucs_2::ascii_printable_characters);
        const u::u2string cast_result = u::string_cast<u::u2string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u32string swedish(utf_32::swedish);
        const u::u2string expected_result(ucs_2::swedish);
        const u::u2string cast_result = u::string_cast<u::u2string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_string_to_u8string)
{
    {
        const std::string ascii_printable_characters(multibyte::ascii_printable_characters);
        const u::u8string expected_result(utf_8::ascii_printable_characters);
        const u::u8string cast_result = u::string_cast<u::u8string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::string swedish(multibyte::swedish);
        const u::u8string expected_result(utf_8::swedish);
        const u::u8string cast_result = u::string_cast<u::u8string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_wstring_to_u8string)
{
    {
        const std::wstring ascii_printable_characters(system_wide::ascii_printable_characters);
        const u::u8string expected_result(utf_8::ascii_printable_characters);
        const u::u8string cast_result = u::string_cast<u::u8string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::wstring swedish(system_wide::swedish);
        const u::u8string expected_result(utf_8::swedish);
        const u::u8string cast_result = u::string_cast<u::u8string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u2string_to_u8string)
{
    {
        const u::u2string ascii_printable_characters(ucs_2::ascii_printable_characters);
        const u::u8string expected_result(utf_8::ascii_printable_characters);
        const u::u8string cast_result = u::string_cast<u::u8string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u2string swedish(ucs_2::swedish);
        const u::u8string expected_result(utf_8::swedish);
        const u::u8string cast_result = u::string_cast<u::u8string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u8string_to_u8string)
{
    {
        const u::u8string ascii_printable_characters(utf_8::ascii_printable_characters);
        const u::u8string expected_result(utf_8::ascii_printable_characters);
        const u::u8string cast_result = u::string_cast<u::u8string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u8string swedish(utf_8::swedish);
        const u::u8string expected_result(utf_8::swedish);
        const u::u8string cast_result = u::string_cast<u::u8string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u16string_to_u8string)
{
    {
        const std::u16string ascii_printable_characters(utf_16::ascii_printable_characters);
        const u::u8string expected_result(utf_8::ascii_printable_characters);
        const u::u8string cast_result = u::string_cast<u::u8string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u16string swedish(utf_16::swedish);
        const u::u8string expected_result(utf_8::swedish);
        const u::u8string cast_result = u::string_cast<u::u8string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u32string_to_u8string)
{
    {
        const std::u32string ascii_printable_characters(utf_32::ascii_printable_characters);
        const u::u8string expected_result(utf_8::ascii_printable_characters);
        const u::u8string cast_result = u::string_cast<u::u8string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u32string swedish(utf_32::swedish);
        const u::u8string expected_result(utf_8::swedish);
        const u::u8string cast_result = u::string_cast<u::u8string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_string_to_u16string)
{
    {
        const std::string ascii_printable_characters(multibyte::ascii_printable_characters);
        const std::u16string expected_result(utf_16::ascii_printable_characters);
        const std::u16string cast_result = u::string_cast<std::u16string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::string swedish(multibyte::swedish);
        const std::u16string expected_result(utf_16::swedish);
        const std::u16string cast_result = u::string_cast<std::u16string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_wstring_to_u16string)
{
    {
        const std::wstring ascii_printable_characters(system_wide::ascii_printable_characters);
        const std::u16string expected_result(utf_16::ascii_printable_characters);
        const std::u16string cast_result = u::string_cast<std::u16string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::wstring swedish(system_wide::swedish);
        const std::u16string expected_result(utf_16::swedish);
        const std::u16string cast_result = u::string_cast<std::u16string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u2string_to_u16string)
{
    {
        const u::u2string ascii_printable_characters(ucs_2::ascii_printable_characters);
        const std::u16string expected_result(utf_16::ascii_printable_characters);
        const std::u16string cast_result = u::string_cast<std::u16string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u2string swedish(ucs_2::swedish);
        const std::u16string expected_result(utf_16::swedish);
        const std::u16string cast_result = u::string_cast<std::u16string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u8string_to_u16string)
{
    {
        const u::u8string ascii_printable_characters(utf_8::ascii_printable_characters);
        const std::u16string expected_result(utf_16::ascii_printable_characters);
        const std::u16string cast_result = u::string_cast<std::u16string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u8string swedish(utf_8::swedish);
        const std::u16string expected_result(utf_16::swedish);
        const std::u16string cast_result = u::string_cast<std::u16string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u16string_to_u16string)
{
    {
        const std::u16string ascii_printable_characters(utf_16::ascii_printable_characters);
        const std::u16string expected_result(utf_16::ascii_printable_characters);
        const std::u16string cast_result = u::string_cast<std::u16string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u16string swedish(utf_16::swedish);
        const std::u16string expected_result(utf_16::swedish);
        const std::u16string cast_result = u::string_cast<std::u16string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u32string_to_u16string)
{
    {
        const std::u32string ascii_printable_characters(utf_32::ascii_printable_characters);
        const std::u16string expected_result(utf_16::ascii_printable_characters);
        const std::u16string cast_result = u::string_cast<std::u16string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u32string swedish(utf_32::swedish);
        const std::u16string expected_result(utf_16::swedish);
        const std::u16string cast_result = u::string_cast<std::u16string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_string_to_u32string)
{
    {
        const std::string ascii_printable_characters(multibyte::ascii_printable_characters);
        const std::u32string expected_result(utf_32::ascii_printable_characters);
        const std::u32string cast_result = u::string_cast<std::u32string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::string swedish(multibyte::swedish);
        const std::u32string expected_result(utf_32::swedish);
        const std::u32string cast_result = u::string_cast<std::u32string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_wstring_to_u32string)
{
    {
        const std::wstring ascii_printable_characters(system_wide::ascii_printable_characters);
        const std::u32string expected_result(utf_32::ascii_printable_characters);
        const std::u32string cast_result = u::string_cast<std::u32string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::wstring swedish(system_wide::swedish);
        const std::u32string expected_result(utf_32::swedish);
        const std::u32string cast_result = u::string_cast<std::u32string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u2string_to_u32string)
{
    {
        const u::u2string ascii_printable_characters(ucs_2::ascii_printable_characters);
        const std::u32string expected_result(utf_32::ascii_printable_characters);
        const std::u32string cast_result = u::string_cast<std::u32string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u2string swedish(ucs_2::swedish);
        const std::u32string expected_result(utf_32::swedish);
        const std::u32string cast_result = u::string_cast<std::u32string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u8string_to_u32string)
{
    {
        const u::u8string ascii_printable_characters(utf_8::ascii_printable_characters);
        const std::u32string expected_result(utf_32::ascii_printable_characters);
        const std::u32string cast_result = u::string_cast<std::u32string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const u::u8string swedish(utf_8::swedish);
        const std::u32string expected_result(utf_32::swedish);
        const std::u32string cast_result = u::string_cast<std::u32string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u16string_to_u32string)
{
    {
        const std::u16string ascii_printable_characters(utf_16::ascii_printable_characters);
        const std::u32string expected_result(utf_32::ascii_printable_characters);
        const std::u32string cast_result = u::string_cast<std::u32string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u16string swedish(utf_16::swedish);
        const std::u32string expected_result(utf_32::swedish);
        const std::u32string cast_result = u::string_cast<std::u32string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

TEST(std_string_cast_test_suite, test_cast_from_u32string_to_u32string)
{
    {
        const std::u32string ascii_printable_characters(utf_32::ascii_printable_characters);
        const std::u32string expected_result(utf_32::ascii_printable_characters);
        const std::u32string cast_result = u::string_cast<std::u32string>(ascii_printable_characters);
        EXPECT_EQ(expected_result, cast_result);
    }
    {
        const std::u32string swedish(utf_32::swedish);
        const std::u32string expected_result(utf_32::swedish);
        const std::u32string cast_result = u::string_cast<std::u32string>(swedish);
        EXPECT_EQ(expected_result, cast_result);
    }
}

}

#endif  // Required C++11 feature is not supported by this compiler
