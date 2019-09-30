//
//  iso_8859_1_test_suite.cpp
//
//  Copyright 2017-2019 Göran Orsander
//
//  This file is part of the GO.libraries.
//  Distributed under the GO Software License, Version 2.0.
//  See accompanying file LICENSE.md.
//

#include <go_boost/config.hpp>

GO_BOOST_BEGIN_SUPPRESS_ALL_WARNINGS
#include <go_gtest/go_test.hpp>
GO_BOOST_END_SUPPRESS_ALL_WARNINGS

#include <go_boost/utility/string/algorithm.hpp>
#include <go_boost/utility/string/iso_8859_1.hpp>
#include <go_boost/utility/u2string.hpp>
#include <go_boost/utility/u8string.hpp>
#include <go_boost/utility/u16string.hpp>
#include <go_boost/utility/u32string.hpp>

namespace u = go_boost::utility;
namespace us = go_boost::utility::string;

namespace
{
namespace multibyte
{

// ASCII, see https://en.wikipedia.org/wiki/ASCII
const char* ascii_printable_characters_from_hex_codes =
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F" \
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F" \
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F" \
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F" \
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E";
const std::size_t ascii_printable_characters_count = 95;

// ISO/IEC 8859-1, see https://en.wikipedia.org/wiki/ISO/IEC_8859-1
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
const std::size_t iso_8859_1_printable_characters_count = 191;

}
namespace system_wide
{

// ASCII
const wchar_t* ascii_printable_characters_from_hex_codes =
    L"\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
    L"\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F" \
    L"\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F" \
    L"\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F" \
    L"\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F" \
    L"\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E";
const std::size_t ascii_printable_characters_count = 95;

// ISO/IEC 8859-1
const wchar_t iso_8859_1_printable_characters_from_hex_codes[] =
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
const std::size_t iso_8859_1_printable_characters_count = 191;

}
namespace ucs_2
{

// ASCII
const u::char2_t ascii_printable_characters_from_hex_codes[] =
    { 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F
    , 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
    , 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F
    , 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F
    , 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F
    , 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x0000 };
const std::size_t ascii_printable_characters_count = 95;

// ISO/IEC 8859-1
const u::char2_t iso_8859_1_printable_characters_from_hex_codes[] =
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
const std::size_t iso_8859_1_printable_characters_count = 191;

}
namespace utf_8
{

// ASCII
const char8_t* ascii_printable_characters_from_hex_codes = reinterpret_cast<const char8_t*>(
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F" \
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F" \
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F" \
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F" \
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E");
const std::size_t ascii_printable_characters_count = 95;

// ISO/IEC 8859-1
const char8_t* iso_8859_1_printable_characters_from_hex_codes = reinterpret_cast<const char8_t*>(
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F" \
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F" \
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F" \
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F" \
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E" \
    "\xC2\xA0\xC2\xA1\xC2\xA2\xC2\xA3\xC2\xA4\xC2\xA5\xC2\xA6\xC2\xA7\xC2\xA8\xC2\xA9\xC2\xAA\xC2\xAB\xC2\xAC\xC2\xAD\xC2\xAE\xC2\xAF" \
    "\xC2\xB0\xC2\xB1\xC2\xB2\xC2\xB3\xC2\xB4\xC2\xB5\xC2\xB6\xC2\xB7\xC2\xB8\xC2\xB9\xC2\xBA\xC2\xBB\xC2\xBC\xC2\xBD\xC2\xBE\xC2\xBF" \
    "\xC3\x80\xC3\x81\xC3\x82\xC3\x83\xC3\x84\xC3\x85\xC3\x86\xC3\x87\xC3\x88\xC3\x89\xC3\x8A\xC3\x8B\xC3\x8C\xC3\x8D\xC3\x8E\xC3\x8F" \
    "\xC3\x90\xC3\x91\xC3\x92\xC3\x93\xC3\x94\xC3\x95\xC3\x96\xC3\x97\xC3\x98\xC3\x99\xC3\x9A\xC3\x9B\xC3\x9C\xC3\x9D\xC3\x9E\xC3\x9F" \
    "\xC3\xA0\xC3\xA1\xC3\xA2\xC3\xA3\xC3\xA4\xC3\xA5\xC3\xA6\xC3\xA7\xC3\xA8\xC3\xA9\xC3\xAA\xC3\xAB\xC3\xAC\xC3\xAD\xC3\xAE\xC3\xAF" \
    "\xC3\xB0\xC3\xB1\xC3\xB2\xC3\xB3\xC3\xB4\xC3\xB5\xC3\xB6\xC3\xB7\xC3\xB8\xC3\xB9\xC3\xBA\xC3\xBB\xC3\xBC\xC3\xBD\xC3\xBE\xC3\xBF");
const std::size_t iso_8859_1_printable_characters_count = 191;
const std::size_t iso_8859_1_printable_characters_size = 287;

}
namespace utf_16
{

// ASCII
const char16_t ascii_printable_characters_from_hex_codes[] =
    { 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F
    , 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
    , 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F
    , 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F
    , 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F
    , 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x0000 };
const std::size_t ascii_printable_characters_count = 95;

// ISO/IEC 8859-1
const char16_t iso_8859_1_printable_characters_from_hex_codes[] =
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
const std::size_t iso_8859_1_printable_characters_count = 191;

}
namespace utf_32
{

// ASCII
const char32_t ascii_printable_characters_from_hex_codes[] =
    { 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024, 0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x0000002A, 0x0000002B, 0x0000002C, 0x0000002D, 0x0000002E, 0x0000002F
    , 0x00000030, 0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036, 0x00000037, 0x00000038, 0x00000039, 0x0000003A, 0x0000003B, 0x0000003C, 0x0000003D, 0x0000003E, 0x0000003F
    , 0x00000040, 0x00000041, 0x00000042, 0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047, 0x00000048, 0x00000049, 0x0000004A, 0x0000004B, 0x0000004C, 0x0000004D, 0x0000004E, 0x0000004F
    , 0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054, 0x00000055, 0x00000056, 0x00000057, 0x00000058, 0x00000059, 0x0000005A, 0x0000005B, 0x0000005C, 0x0000005D, 0x0000005E, 0x0000005F
    , 0x00000060, 0x00000061, 0x00000062, 0x00000063, 0x00000064, 0x00000065, 0x00000066, 0x00000067, 0x00000068, 0x00000069, 0x0000006A, 0x0000006B, 0x0000006C, 0x0000006D, 0x0000006E, 0x0000006F
    , 0x00000070, 0x00000071, 0x00000072, 0x00000073, 0x00000074, 0x00000075, 0x00000076, 0x00000077, 0x00000078, 0x00000079, 0x0000007A, 0x0000007B, 0x0000007C, 0x0000007D, 0x0000007E, 0x0000 };
const std::size_t ascii_printable_characters_count = 95;

// ISO/IEC 8859-1
const char32_t iso_8859_1_printable_characters_from_hex_codes[] =
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
const std::size_t iso_8859_1_printable_characters_count = 191;

}

TEST(boost_iso_8859_1_test_suite, test_multibyte_character_count)
{
    const std::string ascii_printable_characters(multibyte::ascii_printable_characters_from_hex_codes);
    const std::string iso_8859_1_printable_characters(multibyte::iso_8859_1_printable_characters_from_hex_codes);
    const std::size_t ascii_printable_characters_count = ascii_printable_characters.size();
    const std::size_t iso_8859_1_printable_characters_count = iso_8859_1_printable_characters.size();
    EXPECT_EQ(multibyte::ascii_printable_characters_count, ascii_printable_characters_count);
    EXPECT_EQ(multibyte::iso_8859_1_printable_characters_count, iso_8859_1_printable_characters_count);
}

TEST(boost_iso_8859_1_test_suite, test_system_wide_character_count)
{
    const std::wstring ascii_printable_characters(system_wide::ascii_printable_characters_from_hex_codes);
    const std::wstring iso_8859_1_printable_characters(system_wide::iso_8859_1_printable_characters_from_hex_codes);
    const std::size_t ascii_printable_characters_count = ascii_printable_characters.size();
    const std::size_t iso_8859_1_printable_characters_count = iso_8859_1_printable_characters.size();
    EXPECT_EQ(system_wide::ascii_printable_characters_count, ascii_printable_characters_count);
    EXPECT_EQ(system_wide::iso_8859_1_printable_characters_count, iso_8859_1_printable_characters_count);
}

TEST(boost_iso_8859_1_test_suite, test_ucs_2_character_count)
{
    const u::u2string ascii_printable_characters(ucs_2::ascii_printable_characters_from_hex_codes);
    const u::u2string iso_8859_1_printable_characters(ucs_2::iso_8859_1_printable_characters_from_hex_codes);
    const std::size_t ascii_printable_characters_count = ascii_printable_characters.size();
    const std::size_t iso_8859_1_printable_characters_count = iso_8859_1_printable_characters.size();
    EXPECT_EQ(ucs_2::ascii_printable_characters_count, ascii_printable_characters_count);
    EXPECT_EQ(ucs_2::iso_8859_1_printable_characters_count, iso_8859_1_printable_characters_count);
}

TEST(boost_iso_8859_1_test_suite, test_utf_8_character_count)
{
    const u::u8string ascii_printable_characters(utf_8::ascii_printable_characters_from_hex_codes);
    const u::u8string iso_8859_1_printable_characters(utf_8::iso_8859_1_printable_characters_from_hex_codes);
    const std::size_t ascii_printable_characters_count = ascii_printable_characters.size();
    const std::size_t iso_8859_1_printable_characters_count = iso_8859_1_printable_characters.characters();
    const std::size_t iso_8859_1_printable_characters_size = iso_8859_1_printable_characters.size();
    EXPECT_EQ(utf_8::ascii_printable_characters_count, ascii_printable_characters_count);
    EXPECT_EQ(utf_8::iso_8859_1_printable_characters_count, iso_8859_1_printable_characters_count);
    EXPECT_EQ(utf_8::iso_8859_1_printable_characters_size, iso_8859_1_printable_characters_size);
}

TEST(boost_iso_8859_1_test_suite, test_utf_16_character_count)
{
    const u::u16string ascii_printable_characters(utf_16::ascii_printable_characters_from_hex_codes);
    const u::u16string iso_8859_1_printable_characters(utf_16::iso_8859_1_printable_characters_from_hex_codes);
    const std::size_t ascii_printable_characters_count = ascii_printable_characters.size();
    const std::size_t iso_8859_1_printable_characters_count = iso_8859_1_printable_characters.size();
    EXPECT_EQ(utf_16::ascii_printable_characters_count, ascii_printable_characters_count);
    EXPECT_EQ(utf_16::iso_8859_1_printable_characters_count, iso_8859_1_printable_characters_count);
}

TEST(boost_iso_8859_1_test_suite, test_utf_32_character_count)
{
    const u::u32string ascii_printable_characters(utf_32::ascii_printable_characters_from_hex_codes);
    const u::u32string iso_8859_1_printable_characters(utf_32::iso_8859_1_printable_characters_from_hex_codes);
    const std::size_t ascii_printable_characters_count = ascii_printable_characters.size();
    const std::size_t iso_8859_1_printable_characters_count = iso_8859_1_printable_characters.size();
    EXPECT_EQ(utf_32::ascii_printable_characters_count, ascii_printable_characters_count);
    EXPECT_EQ(utf_32::iso_8859_1_printable_characters_count, iso_8859_1_printable_characters_count);
}

TEST(boost_iso_8859_1_test_suite, test_char_is_iso_8859_1_character)
{
    {
        char c = -1;
        while (c < 31)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 126)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
        }
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
    }
    {
        char c = -128;
        while (c < -96)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
            ++c;
        }
        while (c < 0)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
            ++c;
        }
    }
}

TEST(boost_iso_8859_1_test_suite, test_char8_t_is_iso_8859_1_character)
{
    {
        char8_t c = 0;
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 31)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 126)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
        }
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
    }
    {
        char8_t c = 127;
        while (c < 159)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 255)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
        }
    }
}

TEST(boost_iso_8859_1_test_suite, test_wchar_t_is_iso_8859_1_character)
{
    {
        wchar_t c = 0;
        while (c < 32)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
            ++c;
        }
        while (c < 127)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
            ++c;
        }
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
    }
    {
#if defined(GO_BOOST_PLATFORM_WINDOWS)
        short c = -256;
#else
        long c = -256;
#endif  // #if defined(GO_BOOST_PLATFORM_WINDOWS)
        while (c < 0)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(static_cast<wchar_t>(c));
            EXPECT_EQ(is_iso_8859_1, false);
            ++c;
        }
    }
    {
        wchar_t c = 128;
        while (c < 160)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
            ++c;
        }
        while (c < 256)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
            ++c;
        }
    }
}

TEST(boost_iso_8859_1_test_suite, test_char2_t_is_iso_8859_1_character)
{
    {
        u::char2_t c = 0;
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 31)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 126)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
        }
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
    }
    {
        u::char2_t c = 128;
        while (c < 160)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
            ++c;
        }
        while (c < 256)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
            ++c;
        }
    }
}

TEST(boost_iso_8859_1_test_suite, test_char16_t_is_iso_8859_1_character)
{
    {
        char16_t c = 0;
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 31)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 126)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
        }
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
    }
    {
        short c = -256;
        while (c < 0)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(static_cast<char16_t>(c));
            EXPECT_EQ(is_iso_8859_1, false);
            ++c;
        }
    }
    {
        char16_t c = 128;
        while (c < 160)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
            ++c;
        }
        while (c < 256)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
            ++c;
        }
    }
}

TEST(boost_iso_8859_1_test_suite, test_char32_t_is_iso_8859_1_character)
{
    {
        char32_t c = 0;
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 31)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
        while (c < 126)
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
        }
        {
            ++c;
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
        }
    }
    {
        long c = -256;
        while (c < 0)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(static_cast<char32_t>(c));
            EXPECT_EQ(is_iso_8859_1, false);
            ++c;
        }
    }
    {
        char32_t c = 128;
        while (c < 160)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, false);
            ++c;
        }
        while (c < 256)
        {
            const bool is_iso_8859_1 = us::is_iso_8859_1_character(c);
            EXPECT_EQ(is_iso_8859_1, true);
            ++c;
        }
    }
}

//TEST(boost_iso_8859_1_test_suite, test_multibyte_reduce_iso_8859_1_to_7_bit_ascii_characters)
//{
//    const std::string ascii_printable_characters(multibyte::ascii_printable_characters_from_hex_codes);
//    const std::string iso_8859_1_printable_characters(multibyte::iso_8859_1_printable_characters_from_hex_codes);
//    const std::string iso_8859_1_reduced_to_7_bit_ascii = us::reduce_to_7_bit_ascii_copy(iso_8859_1_printable_characters);
//    EXPECT_EQ(ascii_printable_characters, iso_8859_1_reduced_to_7_bit_ascii);
//}
//
//TEST(boost_iso_8859_1_test_suite, test_system_wide_reduce_iso_8859_1_to_7_bit_ascii_characters)
//{
//    const std::wstring ascii_printable_characters(system_wide::ascii_printable_characters_from_hex_codes);
//    const std::wstring iso_8859_1_printable_characters(system_wide::iso_8859_1_printable_characters_from_hex_codes);
//    const std::wstring iso_8859_1_reduced_to_7_bit_ascii = us::reduce_to_7_bit_ascii_copy(iso_8859_1_printable_characters);
//    EXPECT_EQ(ascii_printable_characters, iso_8859_1_reduced_to_7_bit_ascii);
//}
//
//TEST(boost_iso_8859_1_test_suite, test_ucs_2_reduce_iso_8859_1_to_7_bit_ascii_characters)
//{
//    const u::u2string ascii_printable_characters(ucs_2::ascii_printable_characters_from_hex_codes);
//    const u::u2string iso_8859_1_printable_characters(ucs_2::iso_8859_1_printable_characters_from_hex_codes);
//    const u::u2string iso_8859_1_reduced_to_7_bit_ascii = us::reduce_to_7_bit_ascii_copy(iso_8859_1_printable_characters);
//    EXPECT_EQ(ascii_printable_characters, iso_8859_1_reduced_to_7_bit_ascii);
//}
//
//TEST(boost_iso_8859_1_test_suite, test_utf_8_reduce_iso_8859_1_to_7_bit_ascii_characters)
//{
//    const u::u8string ascii_printable_characters(utf_8::ascii_printable_characters_from_hex_codes);
//    const u::u8string iso_8859_1_printable_characters(utf_8::iso_8859_1_printable_characters_from_hex_codes);
//    const u::u8string iso_8859_1_reduced_to_7_bit_ascii = us::reduce_to_7_bit_ascii_copy(iso_8859_1_printable_characters);
//    EXPECT_EQ(ascii_printable_characters, iso_8859_1_reduced_to_7_bit_ascii);
//}
//
//TEST(boost_iso_8859_1_test_suite, test_utf_16_reduce_iso_8859_1_to_7_bit_ascii_characters)
//{
//    const u::u16string ascii_printable_characters(utf_16::ascii_printable_characters_from_hex_codes);
//    const u::u16string iso_8859_1_printable_characters(utf_16::iso_8859_1_printable_characters_from_hex_codes);
//    const u::u16string iso_8859_1_reduced_to_7_bit_ascii = us::reduce_to_7_bit_ascii_copy(iso_8859_1_printable_characters);
//    EXPECT_EQ(ascii_printable_characters, iso_8859_1_reduced_to_7_bit_ascii);
//}
//
//TEST(boost_iso_8859_1_test_suite, test_utf_32_reduce_iso_8859_1_to_7_bit_ascii_characters)
//{
//    const u::u32string ascii_printable_characters(utf_32::ascii_printable_characters_from_hex_codes);
//    const u::u32string iso_8859_1_printable_characters(utf_32::iso_8859_1_printable_characters_from_hex_codes);
//    const u::u32string iso_8859_1_reduced_to_7_bit_ascii = us::reduce_to_7_bit_ascii_copy(iso_8859_1_printable_characters);
//    EXPECT_EQ(ascii_printable_characters, iso_8859_1_reduced_to_7_bit_ascii);
//}

}
