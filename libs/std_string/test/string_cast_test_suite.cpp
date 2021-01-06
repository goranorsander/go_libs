//
//  string_cast_test_suite.cpp
//
//  Copyright 2017-2021 G�ran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go/config.hpp>

GO_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_END_SUPPRESS_ALL_WARNINGS

#if defined(GO_NO_CXX11_CODECVT)
GO_MESSAGE("Required C++11 feature is not supported by this compiler")
TEST(std_string_cast_test_suite, cpp11_not_supported) {}
#else

#include <go/namespace_alias.hpp>
#include <go/string/string_cast.hpp>

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
#if !defined(GO_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)
const char* iso_8859_1_printable_characters =
    " !\"#$%&'()*+,-./" \
    "0123456789:;<=>?" \
    "@ABCDEFGHIJKLMNO" \
    "PQRSTUVWXYZ[\\]^_" \
    "`abcdefghijklmno" \
    "pqrstuvwxyz{|}~" \
    "����������������" \
    "����������������" \
    "����������������" \
    "����������������" \
    "����������������" \
    "����������������";
#else
const char* iso_8859_1_printable_characters =
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
#endif  // #if !defined(GO_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)

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
#if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)
#if !defined(GO_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)
const char* swedish = "Sju sj�sjuka sj�m�n p� sjunkande skeppet Shanghai sk�ttes av sju sk�na sjuksk�terskor.";
#else
const char* swedish = "Sju sj\xF6sjuka sj\xF6m\xE4n p\xE5 sjunkande skeppet Shanghai sk\xF6ttes av sju sk\xF6na sjuksk\xF6terskor.";
#endif  // #if !defined(GO_CHAR_ILLEGAL_BYTE_SEQUENCE_ISSUE)
#else
const char* swedish = "Sju sjosjuka sjoman pa sjunkande skeppet Shanghai skottes av sju skona sjukskoterskor.";
#endif  // #if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)

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

/*// ISO/IEC 8859-1
#if !defined(GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
const wchar_t* iso_8859_1_printable_characters =
    L" !\"#$%&'()*+,-./" \
    L"0123456789:;<=>?" \
    L"@ABCDEFGHIJKLMNO" \
    L"PQRSTUVWXYZ[\\]^_" \
    L"`abcdefghijklmno" \
    L"pqrstuvwxyz{|}~" \
    L"����������������" \
    L"����������������" \
    L"����������������" \
    L"����������������" \
    L"����������������" \
    L"����������������";
#else
const wchar_t iso_8859_1_printable_characters[] =
    { 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F
    , 0x30, 0x31, 0x32, 0x0033, 0x34, 0x0035, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
    , 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F
    , 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F
    , 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F
    , 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E
    , 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF
    , 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF
    , 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF
    , 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF
    , 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF
    , 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
    , 0x00 };
#endif  // #if !defined(GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)*/

#if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)
#if !defined(GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
const wchar_t* swedish = L"Sju sj�sjuka sj�m�n p� sjunkande skeppet Shanghai sk�ttes av sju sk�na sjuksk�terskor.";
#else
const wchar_t swedish[] =
    { 0x53, 0x6A, 0x75, 0x20, 0x73, 0x6A, 0xF6, 0x73, 0x6A, 0x75, 0x6B, 0x61, 0x20                      // Sju sj�sjuka
    , 0x73, 0x6A, 0xF6, 0x6D, 0xE4, 0x6E, 0x20, 0x70, 0xE5, 0x20                                        // sj�m�n p�
    , 0x73, 0x6A, 0x75, 0x6E, 0x6B, 0x61, 0x6E, 0x64, 0x65, 0x20                                        // sjunkande
    , 0x73, 0x6B, 0x65, 0x70, 0x70, 0x65, 0x74, 0x20                                                    // skeppet
    , 0x53, 0x68, 0x61, 0x6E, 0x67, 0x68, 0x61, 0x69, 0x20                                              // Shanghai
    , 0x73, 0x6B, 0xF6, 0x74, 0x74, 0x65, 0x73, 0x20, 0x61, 0x76, 0x20                                  // sk�ttes av
    , 0x73, 0x6A, 0x75, 0x20, 0x73, 0x6B, 0xF6, 0x6E, 0x61, 0x20                                        // sju sk�na
    , 0x73, 0x6A, 0x75, 0x6B, 0x73, 0x6B, 0xF6, 0x74, 0x65, 0x72, 0x73, 0x6B, 0x6F, 0x72, 0x2E, 0x00 }; // sjuksk�terskor.
#endif  // #if !defined(GO_WCHAR_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
#else
const wchar_t* swedish = L"Sju sjosjuka sjoman pa sjunkande skeppet Shanghai skottes av sju skona sjukskoterskor.";
#endif  // #if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)

}
namespace ucs_2
{

// ASCII
const s::char2_t ascii_printable_characters[] =
    { 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F
    , 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
    , 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F
    , 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F
    , 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F
    , 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x0000 };

//// ISO/IEC 8859-1
//const s::char2_t iso_8859_1_printable_characters[] =
//    { 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F
//    , 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
//    , 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F
//    , 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F
//    , 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F
//    , 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E
//    , 0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF
//    , 0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF
//    , 0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF
//    , 0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF
//    , 0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF
//    , 0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF
//    , 0x0000 };

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
#if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)
const s::char2_t swedish[] =
    { 0x0053, 0x006A, 0x0075, 0x0020, 0x0073, 0x006A, 0x00F6, 0x0073, 0x006A, 0x0075, 0x006B, 0x0061, 0x0020                            // Sju sj�sjuka
    , 0x0073, 0x006A, 0x00F6, 0x006D, 0x00E4, 0x006E, 0x0020, 0x0070, 0x00E5, 0x0020                                                    // sj�m�n p�
    , 0x0073, 0x006A, 0x0075, 0x006E, 0x006B, 0x0061, 0x006E, 0x0064, 0x0065, 0x0020                                                    // sjunkande
    , 0x0073, 0x006B, 0x0065, 0x0070, 0x0070, 0x0065, 0x0074, 0x0020                                                                    // skeppet
    , 0x0053, 0x0068, 0x0061, 0x006E, 0x0067, 0x0068, 0x0061, 0x0069, 0x0020                                                            // Shanghai
    , 0x0073, 0x006B, 0x00F6, 0x0074, 0x0074, 0x0065, 0x0073, 0x0020, 0x0061, 0x0076, 0x0020                                            // sk�ttes av
    , 0x0073, 0x006A, 0x0075, 0x0020, 0x0073, 0x006B, 0x00F6, 0x006E, 0x0061, 0x0020                                                    // sju sk�na
    , 0x0073, 0x006A, 0x0075, 0x006B, 0x0073, 0x006B, 0x00F6, 0x0074, 0x0065, 0x0072, 0x0073, 0x006B, 0x006F, 0x0072, 0x002E, 0x0000 }; // sjuksk�terskor.
#else
const s::char2_t swedish[] =
    { 0x0053, 0x006A, 0x0075, 0x0020, 0x0073, 0x006A, 0x006F, 0x0073, 0x006A, 0x0075, 0x006B, 0x0061, 0x0020                            // Sju sjosjuka
    , 0x0073, 0x006A, 0x006F, 0x006D, 0x0061, 0x006E, 0x0020, 0x0070, 0x0061, 0x0020                                                    // sjoman pa
    , 0x0073, 0x006A, 0x0075, 0x006E, 0x006B, 0x0061, 0x006E, 0x0064, 0x0065, 0x0020                                                    // sjunkande
    , 0x0073, 0x006B, 0x0065, 0x0070, 0x0070, 0x0065, 0x0074, 0x0020                                                                    // skeppet
    , 0x0053, 0x0068, 0x0061, 0x006E, 0x0067, 0x0068, 0x0061, 0x0069, 0x0020                                                            // Shanghai
    , 0x0073, 0x006B, 0x006F, 0x0074, 0x0074, 0x0065, 0x0073, 0x0020, 0x0061, 0x0076, 0x0020                                            // skottes av
    , 0x0073, 0x006A, 0x0075, 0x0020, 0x0073, 0x006B, 0x006F, 0x006E, 0x0061, 0x0020                                                    // sju skona
    , 0x0073, 0x006A, 0x0075, 0x006B, 0x0073, 0x006B, 0x006F, 0x0074, 0x0065, 0x0072, 0x0073, 0x006B, 0x006F, 0x0072, 0x002E, 0x0000 }; // sjukskoterskor.
#endif  // #if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)

}
namespace utf_8
{

// ASCII
#if !defined(GO_NO_CXX17_U8_CHARACTER_LITERALS)
const char8_t* ascii_printable_characters = reinterpret_cast<const char8_t*>(
    u8" !\"#$%&'()*+,-./" \
    u8"0123456789:;<=>?" \
    u8"@ABCDEFGHIJKLMNO" \
    u8"PQRSTUVWXYZ[\\]^_" \
    u8"`abcdefghijklmno" \
    u8"pqrstuvwxyz{|}~");
#else
const char8_t* ascii_printable_characters = reinterpret_cast<const char8_t*>(
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F" \
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F" \
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F" \
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F" \
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E");
#endif  // !defined(GO_NO_CXX17_U8_CHARACTER_LITERALS)

/*// ISO/IEC 8859-1
#if !defined(GO_NO_CXX17_U8_CHARACTER_LITERALS) && !defined(GO_COMP_CLANG)
const char8_t* iso_8859_1_printable_characters = reinterpret_cast<const char8_t*>(
    u8" !\"#$%&'()*+,-./" \
    u8"0123456789:;<=>?" \
    u8"@ABCDEFGHIJKLMNO" \
    u8"PQRSTUVWXYZ[\\]^_" \
    u8"`abcdefghijklmno" \
    u8"pqrstuvwxyz{|}~" \
    u8"����������������" \
    u8"����������������" \
    u8"����������������" \
    u8"����������������" \
    u8"����������������" \
    u8"����������������");
#else
const char8_t* iso_8859_1_printable_characters = reinterpret_cast<const char8_t*>(
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F" \
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F" \
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F" \
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F" \
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E" \
    "\xC2\xA0\xC2\xA1\xC2\xA2\xC2\xA3\xC2\xA4\xC2\xA5\xC2\xA6\xC2\xA7\xC2\xA8\xC2\xA9\xC2\xAA\xC2\xAB\xC2\xAC\xC2\xAE\xC2\xAF" \
    "\xC2\xB0\xC2\xB1\xC2\xB2\xC2\xB3\xC2\xB4\xC2\xB5\xC2\xB6\xC2\xB7\xC2\xB8\xC2\xB9\xC2\xBA\xC2\xBB\xC2\xBC\xC2\xBD\xC2\xBE\xC2\xBF" \
    "\xC3\x80\xC3\x81\xC3\x82\xC3\x83\xC3\x84\xC3\x85\xC3\x86\xC3\x87\xC3\x88\xC3\x89\xC3\x8A\xC3\x8B\xC3\x8C\xC3\x8D\xC3\x8E\xC3\x8F" \
    "\xC3\x90\xC3\x91\xC3\x92\xC3\x93\xC3\x94\xC3\x95\xC3\x96\xC3\x97\xC3\x98\xC3\x99\xC3\x9A\xC3\x9B\xC3\x9C\xC3\x9D\xC3\x9E\xC3\x9F" \
    "\xC3\xA0\xC3\xA1\xC3\xA2\xC3\xA3\xC3\xA4\xC3\xA5\xC3\xA6\xC3\xA7\xC3\xA8\xC3\xA9\xC3\xAA\xC3\xAB\xC3\xAC\xC3\xAD\xC3\xAE\xC3\xAF" \
    "\xC3\xB0\xC3\xB1\xC3\xB2\xC3\xB3\xC3\xB4\xC3\xB5\xC3\xB6\xC3\xB7\xC3\xB8\xC3\xB9\xC3\xBA\xC3\xBB\xC3\xBC\xC3\xBD\xC3\xBE\xC3\xBF");
#endif  // !defined(GO_NO_CXX17_U8_CHARACTER_LITERALS) && !defined(GO_COMP_CLANG)*/

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
#if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)
#if !defined(GO_NO_CXX17_U8_CHARACTER_LITERALS) && !defined(GO_COMP_CLANG)
const char8_t* swedish = reinterpret_cast<const char8_t*>(u8"Sju sj�sjuka sj�m�n p� sjunkande skeppet Shanghai sk�ttes av sju sk�na sjuksk�terskor.");
#else
const char8_t* swedish = reinterpret_cast<const char8_t*>("Sju sj\xC3\xB6sjuka sj\xC3\xB6m\xC3\xA4n p\xC3\xA5 sjunkande skeppet Shanghai sk\xC3\xB6ttes av sju sk\xC3\xB6na sjuksk\xC3\xB6terskor.");
#endif  // !defined(GO_NO_CXX17_U8_CHARACTER_LITERALS) && !defined(GO_COMP_CLANG)
#else
const char8_t* swedish = reinterpret_cast<const char8_t*>("Sju sjosjuka sjoman pa sjunkande skeppet Shanghai skottes av sju skona sjukskoterskor.");
#endif  // #if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)

}
namespace utf_16
{

// ASCII
#if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS)
const char16_t* ascii_printable_characters =
    u" !\"#$%&'()*+,-./" \
    u"0123456789:;<=>?" \
    u"@ABCDEFGHIJKLMNO" \
    u"PQRSTUVWXYZ[\\]^_" \
    u"`abcdefghijklmno" \
    u"pqrstuvwxyz{|}~";
#else
const char16_t ascii_printable_characters[] =
    { 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F
    , 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
    , 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F
    , 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F
    , 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F
    , 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x0000 };
#endif  // #if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS)

/*// ISO/IEC 8859-1
#if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS) && !defined(GO_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
const char16_t* iso_8859_1_printable_characters =
    u" !\"#$%&'()*+,-./" \
    u"0123456789:;<=>?" \
    u"@ABCDEFGHIJKLMNO" \
    u"PQRSTUVWXYZ[\\]^_" \
    u"`abcdefghijklmno" \
    u"pqrstuvwxyz{|}~" \
    u"����������������" \
    u"����������������" \
    u"����������������" \
    u"����������������" \
    u"����������������" \
    u"����������������";
#else
const char16_t iso_8859_1_printable_characters[] =
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
#endif  // #if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS) && !defined(GO_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)*/

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
#if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)
#if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS) && !defined(GO_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
const char16_t* swedish = u"Sju sj�sjuka sj�m�n p� sjunkande skeppet Shanghai sk�ttes av sju sk�na sjuksk�terskor.";
#else
const char16_t swedish[] =
    { 0x0053, 0x006A, 0x0075, 0x0020, 0x0073, 0x006A, 0x00F6, 0x0073, 0x006A, 0x0075, 0x006B, 0x0061, 0x0020                            // Sju sj�sjuka
    , 0x0073, 0x006A, 0x00F6, 0x006D, 0x00E4, 0x006E, 0x0020, 0x0070, 0x00E5, 0x0020                                                    // sj�m�n p�
    , 0x0073, 0x006A, 0x0075, 0x006E, 0x006B, 0x0061, 0x006E, 0x0064, 0x0065, 0x0020                                                    // sjunkande
    , 0x0073, 0x006B, 0x0065, 0x0070, 0x0070, 0x0065, 0x0074, 0x0020                                                                    // skeppet
    , 0x0053, 0x0068, 0x0061, 0x006E, 0x0067, 0x0068, 0x0061, 0x0069, 0x0020                                                            // Shanghai
    , 0x0073, 0x006B, 0x00F6, 0x0074, 0x0074, 0x0065, 0x0073, 0x0020, 0x0061, 0x0076, 0x0020                                            // sk�ttes av
    , 0x0073, 0x006A, 0x0075, 0x0020, 0x0073, 0x006B, 0x00F6, 0x006E, 0x0061, 0x0020                                                    // sju sk�na
    , 0x0073, 0x006A, 0x0075, 0x006B, 0x0073, 0x006B, 0x00F6, 0x0074, 0x0065, 0x0072, 0x0073, 0x006B, 0x006F, 0x0072, 0x002E, 0x0000 }; // sjuksk�terskor.
#endif  // #if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS) && !defined(GO_CHAR16_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
#else
const char16_t swedish[] =
    { 0x0053, 0x006A, 0x0075, 0x0020, 0x0073, 0x006A, 0x006F, 0x0073, 0x006A, 0x0075, 0x006B, 0x0061, 0x0020                            // Sju sjosjuka
    , 0x0073, 0x006A, 0x006F, 0x006D, 0x0061, 0x006E, 0x0020, 0x0070, 0x0061, 0x0020                                                    // sjoman pa
    , 0x0073, 0x006A, 0x0075, 0x006E, 0x006B, 0x0061, 0x006E, 0x0064, 0x0065, 0x0020                                                    // sjunkande
    , 0x0073, 0x006B, 0x0065, 0x0070, 0x0070, 0x0065, 0x0074, 0x0020                                                                    // skeppet
    , 0x0053, 0x0068, 0x0061, 0x006E, 0x0067, 0x0068, 0x0061, 0x0069, 0x0020                                                            // Shanghai
    , 0x0073, 0x006B, 0x006F, 0x0074, 0x0074, 0x0065, 0x0073, 0x0020, 0x0061, 0x0076, 0x0020                                            // skottes av
    , 0x0073, 0x006A, 0x0075, 0x0020, 0x0073, 0x006B, 0x006F, 0x006E, 0x0061, 0x0020                                                    // sju skona
    , 0x0073, 0x006A, 0x0075, 0x006B, 0x0073, 0x006B, 0x006F, 0x0074, 0x0065, 0x0072, 0x0073, 0x006B, 0x006F, 0x0072, 0x002E, 0x0000 }; // sjukskoterskor.
#endif  // #if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)

}
namespace utf_32
{

// ASCII
#if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS)
const char32_t* ascii_printable_characters =
    U" !\"#$%&'()*+,-./" \
    U"0123456789:;<=>?" \
    U"@ABCDEFGHIJKLMNO" \
    U"PQRSTUVWXYZ[\\]^_" \
    U"`abcdefghijklmno" \
    U"pqrstuvwxyz{|}~";
#else
const char32_t ascii_printable_characters[] =
    { 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024, 0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x0000002A, 0x0000002B, 0x0000002C, 0x0000002D, 0x0000002E, 0x0000002F
    , 0x00000030, 0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036, 0x00000037, 0x00000038, 0x00000039, 0x0000003A, 0x0000003B, 0x0000003C, 0x0000003D, 0x0000003E, 0x0000003F
    , 0x00000040, 0x00000041, 0x00000042, 0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047, 0x00000048, 0x00000049, 0x0000004A, 0x0000004B, 0x0000004C, 0x0000004D, 0x0000004E, 0x0000004F
    , 0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054, 0x00000055, 0x00000056, 0x00000057, 0x00000058, 0x00000059, 0x0000005A, 0x0000005B, 0x0000005C, 0x0000005D, 0x0000005E, 0x0000005F
    , 0x00000060, 0x00000061, 0x00000062, 0x00000063, 0x00000064, 0x00000065, 0x00000066, 0x00000067, 0x00000068, 0x00000069, 0x0000006A, 0x0000006B, 0x0000006C, 0x0000006D, 0x0000006E, 0x0000006F
    , 0x00000070, 0x00000071, 0x00000072, 0x00000073, 0x00000074, 0x00000075, 0x00000076, 0x00000077, 0x00000078, 0x00000079, 0x0000007A, 0x0000007B, 0x0000007C, 0x0000007D, 0x0000007E, 0x0000 };
#endif  // #if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS)

/*// ISO/IEC 8859-1
#if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS) && !defined(GO_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
const char32_t* iso_8859_1_printable_characters =
    U" !\"#$%&'()*+,-./" \
    U"0123456789:;<=>?" \
    U"@ABCDEFGHIJKLMNO" \
    U"PQRSTUVWXYZ[\\]^_" \
    U"`abcdefghijklmno" \
    U"pqrstuvwxyz{|}~" \
    U"����������������" \
    U"����������������" \
    U"����������������" \
    U"����������������" \
    U"����������������" \
    U"����������������";
#else
const char32_t iso_8859_1_printable_characters[] =
    { 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024, 0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x0000002A, 0x0000002B, 0x0000002C, 0x0000002D, 0x0000002E, 0x0000002F
    , 0x00000030, 0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036, 0x00000037, 0x00000038, 0x00000039, 0x0000003A, 0x0000003B, 0x0000003C, 0x0000003D, 0x0000003E, 0x0000003F
    , 0x00000040, 0x00000041, 0x00000042, 0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047, 0x00000048, 0x00000049, 0x0000004A, 0x0000004B, 0x0000004C, 0x0000004D, 0x0000004E, 0x0000004F
    , 0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054, 0x00000055, 0x00000056, 0x00000057, 0x00000058, 0x00000059, 0x0000005A, 0x0000005B, 0x0000005C, 0x0000005D, 0x0000005E, 0x0000005F
    , 0x00000060, 0x00000061, 0x00000062, 0x00000063, 0x00000064, 0x00000065, 0x00000066, 0x00000067, 0x00000068, 0x00000069, 0x0000006A, 0x0000006B, 0x0000006C, 0x0000006D, 0x0000006E, 0x0000006F
    , 0x00000070, 0x00000071, 0x00000072, 0x00000073, 0x00000074, 0x00000075, 0x00000076, 0x00000077, 0x00000078, 0x00000079, 0x0000007A, 0x0000007B, 0x0000007C, 0x0000007D, 0x0000007E
    , 0x000000A0, 0x000000A1, 0x000000A2, 0x000000A3, 0x000000A4, 0x000000A5, 0x000000A6, 0x000000A7, 0x000000A8, 0x000000A9, 0x000000AA, 0x000000AB, 0x000000AC, 0x000000AD, 0x000000AE, 0x000000AF
    , 0x000000B0, 0x000000B1, 0x000000B2, 0x000000B3, 0x000000B4, 0x000000B5, 0x000000B6, 0x000000B7, 0x000000B8, 0x000000B9, 0x000000BA, 0x000000BB, 0x000000BC, 0x000000BD, 0x000000BE, 0x000000BF
    , 0x000000C0, 0x000000C1, 0x000000C2, 0x000000C3, 0x000000C4, 0x000000C5, 0x000000C6, 0x000000C7, 0x000000C8, 0x000000C9, 0x000000CA, 0x000000CB, 0x000000CC, 0x000000CD, 0x000000CE, 0x000000CF
    , 0x000000D0, 0x000000D1, 0x000000D2, 0x000000D3, 0x000000D4, 0x000000D5, 0x000000D6, 0x000000D7, 0x000000D8, 0x000000D9, 0x000000DA, 0x000000DB, 0x000000DC, 0x000000DD, 0x000000DE, 0x000000DF
    , 0x000000E0, 0x000000E1, 0x000000E2, 0x000000E3, 0x000000E4, 0x000000E5, 0x000000E6, 0x000000E7, 0x000000E8, 0x000000E9, 0x000000EA, 0x000000EB, 0x000000EC, 0x000000ED, 0x000000EE, 0x000000EF
    , 0x000000F0, 0x000000F1, 0x000000F2, 0x000000F3, 0x000000F4, 0x000000F5, 0x000000F6, 0x000000F7, 0x000000F8, 0x000000F9, 0x000000FA, 0x000000FB, 0x000000FC, 0x000000FD, 0x000000FE, 0x000000FF
    , 0x00000000 };
#endif  // #if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS) && !defined(GO_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)*/

// Seven seasick seamen on the sinking ship Shanghai cared for by seven beautiful nurses.
#if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)
#if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS) && !defined(GO_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
const char32_t* swedish = U"Sju sj�sjuka sj�m�n p� sjunkande skeppet Shanghai sk�ttes av sju sk�na sjuksk�terskor.";
#else
const char32_t swedish[] =
    { 0x00000053, 0x0000006A, 0x00000075, 0x00000020, 0x00000073, 0x0000006A, 0x000000F6, 0x00000073, 0x0000006A, 0x00000075, 0x0000006B, 0x00000061, 0x00000020                                        // Sju sj�sjuka
    , 0x00000073, 0x0000006A, 0x000000F6, 0x0000006D, 0x000000E4, 0x0000006E, 0x00000020, 0x00000070, 0x000000E5, 0x00000020                                                                            // sj�m�n p�
    , 0x00000073, 0x0000006A, 0x00000075, 0x0000006E, 0x0000006B, 0x00000061, 0x0000006E, 0x00000064, 0x00000065, 0x00000020                                                                            // sjunkande
    , 0x00000073, 0x0000006B, 0x00000065, 0x00000070, 0x00000070, 0x00000065, 0x00000074, 0x00000020                                                                                                    // skeppet
    , 0x00000053, 0x00000068, 0x00000061, 0x0000006E, 0x00000067, 0x00000068, 0x00000061, 0x00000069, 0x00000020                                                                                        // Shanghai
    , 0x00000073, 0x0000006B, 0x000000F6, 0x00000074, 0x00000074, 0x00000065, 0x00000073, 0x00000020, 0x00000061, 0x00000076, 0x00000020                                                                // sk�ttes av
    , 0x00000073, 0x0000006A, 0x00000075, 0x00000020, 0x00000073, 0x0000006B, 0x000000F6, 0x0000006E, 0x00000061, 0x00000020                                                                            // sju sk�na
    , 0x00000073, 0x0000006A, 0x00000075, 0x0000006B, 0x00000073, 0x0000006B, 0x000000F6, 0x00000074, 0x00000065, 0x00000072, 0x00000073, 0x0000006B, 0x0000006F, 0x00000072, 0x0000002E, 0x00000000 }; // sjuksk�terskor.
#endif  // #if !defined(GO_NO_CXX11_UNICODE_STRING_LITERALS) && !defined(GO_CHAR32_T_ILLEGAL_BYTE_SEQUENCE_ISSUE)
#else
const char32_t swedish[] =
    { 0x00000053, 0x0000006A, 0x00000075, 0x00000020, 0x00000073, 0x0000006A, 0x0000006F, 0x00000073, 0x0000006A, 0x00000075, 0x0000006B, 0x00000061, 0x00000020                                        // Sju sjosjuka
    , 0x00000073, 0x0000006A, 0x0000006F, 0x0000006D, 0x00000061, 0x0000006E, 0x00000020, 0x00000070, 0x00000061, 0x00000020                                                                            // sjoman pa
    , 0x00000073, 0x0000006A, 0x00000075, 0x0000006E, 0x0000006B, 0x00000061, 0x0000006E, 0x00000064, 0x00000065, 0x00000020                                                                            // sjunkande
    , 0x00000073, 0x0000006B, 0x00000065, 0x00000070, 0x00000070, 0x00000065, 0x00000074, 0x00000020                                                                                                    // skeppet
    , 0x00000053, 0x00000068, 0x00000061, 0x0000006E, 0x00000067, 0x00000068, 0x00000061, 0x00000069, 0x00000020                                                                                        // Shanghai
    , 0x00000073, 0x0000006B, 0x0000006F, 0x00000074, 0x00000074, 0x00000065, 0x00000073, 0x00000020, 0x00000061, 0x00000076, 0x00000020                                                                // skottes av
    , 0x00000073, 0x0000006A, 0x00000075, 0x00000020, 0x00000073, 0x0000006B, 0x0000006F, 0x0000006E, 0x00000061, 0x00000020                                                                            // sju skona
    , 0x00000073, 0x0000006A, 0x00000075, 0x0000006B, 0x00000073, 0x0000006B, 0x0000006F, 0x00000074, 0x00000065, 0x00000072, 0x00000073, 0x0000006B, 0x0000006F, 0x00000072, 0x0000002E, 0x00000000 }; // sjukskoterskor.
#endif  // #if !defined(GO_CPP_MULTIBYTE_STRING_IS_STRICTLY_ASCII_7)

}

TEST(std_string_cast_test_suite, test_char_size)
{
    const std::size_t type_size = sizeof(char);
    const std::size_t expected_size = 1;
    EXPECT_EQ(type_size, expected_size);
}

TEST(std_string_cast_test_suite, test_wchar_t_size)
{
    const std::size_t type_size = sizeof(wchar_t);
#if defined(GO_PLATFORM_WINDOWS)
    const std::size_t expected_size = 2;
#else
    const std::size_t expected_size = 4;
#endif  // #if defined(GO_PLATFORM_WINDOWS)
    EXPECT_EQ(type_size, expected_size);
}

TEST(std_string_cast_test_suite, test_char2_t_size)
{
    const std::size_t type_size = sizeof(s::char2_t);
    const std::size_t expected_size = 2;
    EXPECT_EQ(type_size, expected_size);
}

TEST(std_string_cast_test_suite, test_char8_t_size)
{
    const std::size_t type_size = sizeof(char8_t);
    const std::size_t expected_size = 1;
    EXPECT_EQ(type_size, expected_size);
}

TEST(std_string_cast_test_suite, test_char16_t_size)
{
    const std::size_t type_size = sizeof(char16_t);
    const std::size_t expected_size = 2;
    EXPECT_EQ(type_size, expected_size);
}

TEST(std_string_cast_test_suite, test_char32_t_size)
{
    const std::size_t type_size = sizeof(char32_t);
    const std::size_t expected_size = 4;
    EXPECT_EQ(type_size, expected_size);
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

TEST(std_string_cast_test_suite, test_cast_ascii_from_string_to_string)
{
    const std::string from_string(multibyte::ascii_printable_characters);
    const std::string expected_result(multibyte::ascii_printable_characters);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_iso_8859_1_from_string_to_string)
{
    const std::string from_string(multibyte::iso_8859_1_printable_characters);
    const std::string expected_result(multibyte::iso_8859_1_printable_characters);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_string_to_string)
{
    const std::string from_string(multibyte::swedish);
    const std::string expected_result(multibyte::swedish);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_wstring_to_string)
{
    const std::wstring from_string(system_wide::ascii_printable_characters);
    const std::string expected_result(multibyte::ascii_printable_characters);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_wstring_to_string)
{
    const std::wstring from_string(system_wide::swedish);
    const std::string expected_result(multibyte::swedish);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u2string_to_string)
{
    const s::u2string from_string(ucs_2::ascii_printable_characters);
    const std::string expected_result(multibyte::ascii_printable_characters);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u2string_to_string)
{
    const s::u2string from_string(ucs_2::swedish);
    const std::string expected_result(multibyte::swedish);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u8string_to_string)
{
    const s::u8string from_string(utf_8::ascii_printable_characters);
    const std::string expected_result(multibyte::ascii_printable_characters);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u8string_to_string)
{
    const s::u8string from_string(utf_8::swedish);
    const std::string expected_result(multibyte::swedish);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u16string_to_string)
{
    const std::u16string from_string(utf_16::ascii_printable_characters);
    const std::string expected_result(multibyte::ascii_printable_characters);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u16string_to_string)
{
    const std::u16string from_string(utf_16::swedish);
    const std::string expected_result(multibyte::swedish);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u32string_to_string)
{
    const std::u32string from_string(utf_32::ascii_printable_characters);
    const std::string expected_result(multibyte::ascii_printable_characters);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u32string_to_string)
{
    const std::u32string from_string(utf_32::swedish);
    const std::string expected_result(multibyte::swedish);
    const std::string cast_result = s::string_cast<std::string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_string_to_wstring)
{
    const std::string from_string(multibyte::ascii_printable_characters);
    const std::wstring expected_result(system_wide::ascii_printable_characters);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_string_to_wstring)
{
    const std::string from_string(multibyte::swedish);
    const std::wstring expected_result(system_wide::swedish);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_wstring_to_wstring)
{
    const std::wstring from_string(system_wide::ascii_printable_characters);
    const std::wstring expected_result(system_wide::ascii_printable_characters);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_wstring_to_wstring)
{
    const std::wstring from_string(system_wide::swedish);
    const std::wstring expected_result(system_wide::swedish);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u2string_to_wstring)
{
    const s::u2string from_string(ucs_2::ascii_printable_characters);
    const std::wstring expected_result(system_wide::ascii_printable_characters);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u2string_to_wstring)
{
    const s::u2string from_string(ucs_2::swedish);
    const std::wstring expected_result(system_wide::swedish);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u8string_to_wstring)
{
    const s::u8string from_string(utf_8::ascii_printable_characters);
    const std::wstring expected_result(system_wide::ascii_printable_characters);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u8string_to_wstring)
{
    const s::u8string from_string(utf_8::swedish);
    const std::wstring expected_result(system_wide::swedish);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u16string_to_wstring)
{
    const std::u16string from_string(utf_16::ascii_printable_characters);
    const std::wstring expected_result(system_wide::ascii_printable_characters);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u16string_to_wstring)
{
    const std::u16string from_string(utf_16::swedish);
    const std::wstring expected_result(system_wide::swedish);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u32string_to_wstring)
{
    const std::u32string from_string(utf_32::ascii_printable_characters);
    const std::wstring expected_result(system_wide::ascii_printable_characters);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u32string_to_wstring)
{
    const std::u32string from_string(utf_32::swedish);
    const std::wstring expected_result(system_wide::swedish);
    const std::wstring cast_result = s::string_cast<std::wstring>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_string_to_u2string)
{
    const std::string from_string(multibyte::ascii_printable_characters);
    const s::u2string expected_result(ucs_2::ascii_printable_characters);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_string_to_u2string)
{
    const std::string from_string(multibyte::swedish);
    const s::u2string expected_result(ucs_2::swedish);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_wstring_to_u2string)
{
    const std::wstring from_string(system_wide::ascii_printable_characters);
    const s::u2string expected_result(ucs_2::ascii_printable_characters);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_wstring_to_u2string)
{
    const std::wstring from_string(system_wide::swedish);
    const s::u2string expected_result(ucs_2::swedish);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u2string_to_u2string)
{
    const s::u2string from_string(ucs_2::ascii_printable_characters);
    const s::u2string expected_result(ucs_2::ascii_printable_characters);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u2string_to_u2string)
{
    const s::u2string from_string(ucs_2::swedish);
    const s::u2string expected_result(ucs_2::swedish);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u8string_to_u2string)
{
    const s::u8string from_string(utf_8::ascii_printable_characters);
    const s::u2string expected_result(ucs_2::ascii_printable_characters);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u8string_to_u2string)
{
    const s::u8string from_string(utf_8::swedish);
    const s::u2string expected_result(ucs_2::swedish);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u16string_to_u2string)
{
    const std::u16string from_string(utf_16::ascii_printable_characters);
    const s::u2string expected_result(ucs_2::ascii_printable_characters);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u16string_to_u2string)
{
    const std::u16string from_string(utf_16::swedish);
    const s::u2string expected_result(ucs_2::swedish);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u32string_to_u2string)
{
    const std::u32string from_string(utf_32::ascii_printable_characters);
    const s::u2string expected_result(ucs_2::ascii_printable_characters);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u32string_to_u2string)
{
    const std::u32string from_string(utf_32::swedish);
    const s::u2string expected_result(ucs_2::swedish);
    const s::u2string cast_result = s::string_cast<s::u2string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_string_to_u8string)
{
    const std::string from_string(multibyte::ascii_printable_characters);
    const s::u8string expected_result(utf_8::ascii_printable_characters);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_string_to_u8string)
{
    const std::string from_string(multibyte::swedish);
    const s::u8string expected_result(utf_8::swedish);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_wstring_to_u8string)
{
    const std::wstring from_string(system_wide::ascii_printable_characters);
    const s::u8string expected_result(utf_8::ascii_printable_characters);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_wstring_to_u8string)
{
    const std::wstring from_string(system_wide::swedish);
    const s::u8string expected_result(utf_8::swedish);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u2string_to_u8string)
{
    const s::u2string from_string(ucs_2::ascii_printable_characters);
    const s::u8string expected_result(utf_8::ascii_printable_characters);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u2string_to_u8string)
{
    const s::u2string from_string(ucs_2::swedish);
    const s::u8string expected_result(utf_8::swedish);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u8string_to_u8string)
{
    const s::u8string from_string(utf_8::ascii_printable_characters);
    const s::u8string expected_result(utf_8::ascii_printable_characters);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u8string_to_u8string)
{
    const s::u8string from_string(utf_8::swedish);
    const s::u8string expected_result(utf_8::swedish);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u16string_to_u8string)
{
    const std::u16string from_string(utf_16::ascii_printable_characters);
    const s::u8string expected_result(utf_8::ascii_printable_characters);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u16string_to_u8string)
{
    const std::u16string from_string(utf_16::swedish);
    const s::u8string expected_result(utf_8::swedish);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u32string_to_u8string)
{
    const std::u32string from_string(utf_32::ascii_printable_characters);
    const s::u8string expected_result(utf_8::ascii_printable_characters);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u32string_to_u8string)
{
    const std::u32string from_string(utf_32::swedish);
    const s::u8string expected_result(utf_8::swedish);
    const s::u8string cast_result = s::string_cast<s::u8string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_string_to_u16string)
{
    const std::string from_string(multibyte::ascii_printable_characters);
    const std::u16string expected_result(utf_16::ascii_printable_characters);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_string_to_u16string)
{
    const std::string from_string(multibyte::swedish);
    const std::u16string expected_result(utf_16::swedish);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_wstring_to_u16string)
{
    const std::wstring from_string(system_wide::ascii_printable_characters);
    const std::u16string expected_result(utf_16::ascii_printable_characters);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_wstring_to_u16string)
{
    const std::wstring from_string(system_wide::swedish);
    const std::u16string expected_result(utf_16::swedish);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u2string_to_u16string)
{
    const s::u2string from_string(ucs_2::ascii_printable_characters);
    const std::u16string expected_result(utf_16::ascii_printable_characters);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u2string_to_u16string)
{
    const s::u2string from_string(ucs_2::swedish);
    const std::u16string expected_result(utf_16::swedish);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u8string_to_u16string)
{
    const s::u8string from_string(utf_8::ascii_printable_characters);
    const std::u16string expected_result(utf_16::ascii_printable_characters);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u8string_to_u16string)
{
    const s::u8string from_string(utf_8::swedish);
    const std::u16string expected_result(utf_16::swedish);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u16string_to_u16string)
{
    const std::u16string from_string(utf_16::ascii_printable_characters);
    const std::u16string expected_result(utf_16::ascii_printable_characters);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u16string_to_u16string)
{
    const std::u16string from_string(utf_16::swedish);
    const std::u16string expected_result(utf_16::swedish);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u32string_to_u16string)
{
    const std::u32string from_string(utf_32::ascii_printable_characters);
    const std::u16string expected_result(utf_16::ascii_printable_characters);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u32string_to_u16string)
{
    const std::u32string from_string(utf_32::swedish);
    const std::u16string expected_result(utf_16::swedish);
    const std::u16string cast_result = s::string_cast<std::u16string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_string_to_u32string)
{
    const std::string from_string(multibyte::ascii_printable_characters);
    const std::u32string expected_result(utf_32::ascii_printable_characters);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_string_to_u32string)
{
    const std::string from_string(multibyte::swedish);
    const std::u32string expected_result(utf_32::swedish);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_wstring_to_u32string)
{
    const std::wstring from_string(system_wide::ascii_printable_characters);
    const std::u32string expected_result(utf_32::ascii_printable_characters);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_wstring_to_u32string)
{
    const std::wstring from_string(system_wide::swedish);
    const std::u32string expected_result(utf_32::swedish);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u2string_to_u32string)
{
    const s::u2string from_string(ucs_2::ascii_printable_characters);
    const std::u32string expected_result(utf_32::ascii_printable_characters);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u2string_to_u32string)
{
    const s::u2string from_string(ucs_2::swedish);
    const std::u32string expected_result(utf_32::swedish);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u8string_to_u32string)
{
    const s::u8string from_string(utf_8::ascii_printable_characters);
    const std::u32string expected_result(utf_32::ascii_printable_characters);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u8string_to_u32string)
{
    const s::u8string from_string(utf_8::swedish);
    const std::u32string expected_result(utf_32::swedish);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u16string_to_u32string)
{
    const std::u16string from_string(utf_16::ascii_printable_characters);
    const std::u32string expected_result(utf_32::ascii_printable_characters);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u16string_to_u32string)
{
    const std::u16string from_string(utf_16::swedish);
    const std::u32string expected_result(utf_32::swedish);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_ascii_from_u32string_to_u32string)
{
    const std::u32string from_string(utf_32::ascii_printable_characters);
    const std::u32string expected_result(utf_32::ascii_printable_characters);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

TEST(std_string_cast_test_suite, test_cast_swedish_from_u32string_to_u32string)
{
    const std::u32string from_string(utf_32::swedish);
    const std::u32string expected_result(utf_32::swedish);
    const std::u32string cast_result = s::string_cast<std::u32string>(from_string);
    EXPECT_EQ(expected_result, cast_result);
}

}

#endif  // Required C++11 feature is not supported by this compiler
