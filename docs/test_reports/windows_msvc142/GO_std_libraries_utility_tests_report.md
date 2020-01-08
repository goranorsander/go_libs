---
layout: unit_tests
---

# Test environment and toolset 

* Windows 10 Professional, 64 bit
* Visual Studio 2019, Community Edition, version 16.4.2

# Summary

Test suites *AllTests* with 227 test cases was executed 2020-01-08 at 19:03:19 with result:

* 0 errors
* 0 failures

Test suites execution took 0.161 seconds.

# Details

## std_ascii_test_suite

Test suite *std_ascii_test_suite* with 36 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.024 seconds.

### Successful test cases

Test case|Execution time
-|-
test_multibyte_character_count | 0
test_system_wide_character_count | 0
test_ucs_2_character_count | 0
test_utf_8_character_count | 0
test_utf_16_character_count | 0
test_utf_32_character_count | 0
test_char_is_7_bit_ascii_character | 0
test_char8_t_is_7_bit_ascii_character | 0
test_wchar_t_is_7_bit_ascii_character | 0
test_char2_t_is_7_bit_ascii_character | 0
test_char16_t_is_7_bit_ascii_character | 0
test_char32_t_is_7_bit_ascii_character | 0
test_multibyte_reduce_iso_8859_1_to_7_bit_ascii_characters | 0
test_system_wide_reduce_iso_8859_1_to_7_bit_ascii_characters | 0
test_ucs_2_reduce_iso_8859_1_to_7_bit_ascii_characters | 0
test_utf_8_reduce_iso_8859_1_to_7_bit_ascii_characters | 0
test_utf_16_reduce_iso_8859_1_to_7_bit_ascii_characters | 0
test_utf_32_reduce_iso_8859_1_to_7_bit_ascii_characters | 0
test_multibyte_reduce_iso_8859_1_to_7_bit_ascii_non_strict_characters | 0
test_system_wide_reduce_iso_8859_1_to_7_bit_ascii_non_strict_characters | 0
test_ucs_2_reduce_iso_8859_1_to_7_bit_ascii_non_strict_characters | 0.001
test_utf_8_reduce_iso_8859_1_to_7_bit_ascii_non_strict_characters | 0
test_utf_16_reduce_iso_8859_1_to_7_bit_ascii_non_strict_characters | 0
test_utf_32_reduce_iso_8859_1_to_7_bit_ascii_non_strict_characters | 0
test_multibyte_reduce_windows_1252_to_7_bit_ascii_characters | 0
test_system_wide_reduce_windows_1252_to_7_bit_ascii_characters | 0
test_ucs_2_reduce_windows_1252_to_7_bit_ascii_characters | 0.001
test_utf_8_reduce_windows_1252_to_7_bit_ascii_characters | 0
test_utf_16_reduce_windows_1252_to_7_bit_ascii_characters | 0
test_utf_32_reduce_windows_1252_to_7_bit_ascii_characters | 0
test_multibyte_reduce_windows_1252_to_7_bit_ascii_non_strict_characters | 0
test_system_wide_reduce_windows_1252_to_7_bit_ascii_non_strict_characters | 0
test_ucs_2_reduce_windows_1252_to_7_bit_ascii_non_strict_characters | 0
test_utf_8_reduce_windows_1252_to_7_bit_ascii_non_strict_characters | 0
test_utf_16_reduce_windows_1252_to_7_bit_ascii_non_strict_characters | 0
test_utf_32_reduce_windows_1252_to_7_bit_ascii_non_strict_characters | 0

## std_circular_buffer_test_suite

Test suite *std_circular_buffer_test_suite* with 19 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.013 seconds.

### Successful test cases

Test case|Execution time
-|-
test_constructor | 0
test_assign_value | 0
test_iterator | 0
test_const_iterator | 0
test_reverse_iterator | 0
test_const_reverse_iterator | 0
test_push_back_to_capacity_pop_front_to_empty | 0
test_push_back_pop_front_without_overflow | 0
test_push_back_pop_front_with_overflow | 0
test_push_front_to_capacity_pop_back_to_empty | 0
test_push_front_pop_back_without_overflow | 0
test_push_front_pop_back_with_overflow | 0
test_operator_at | 0
test_at | 0
test_front_back | 0
test_resize | 0
test_swap | 0
test_insert | 0
test_erase | 0

## std_container_size_test_suite

Test suite *std_container_size_test_suite* with 5 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.002 seconds.

### Successful test cases

Test case|Execution time
-|-
test_size_on_deque | 0
test_size_on_list | 0
test_size_on_vector | 0
test_size_on_map | 0
test_size_on_set | 0

## std_create_string_test_suite

Test suite *std_create_string_test_suite* with 36 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.028 seconds.

### Successful test cases

Test case|Execution time
-|-
test_create_string_from_char | 0
test_create_string_from_wchar_t | 0.001
test_create_string_from_char2_t | 0
test_create_string_from_char8_t | 0
test_create_string_from_char16_t | 0
test_create_string_from_char32_t | 0
test_create_wstring_from_char | 0
test_create_wstring_from_wchar_t | 0
test_create_wstring_from_char2_t | 0
test_create_wstring_from_char8_t | 0
test_create_wstring_from_char16_t | 0
test_create_wstring_from_char32_t | 0
test_create_u2string_from_char | 0
test_create_u2string_from_wchar_t | 0
test_create_u2string_from_char2_t | 0
test_create_u2string_from_char8_t | 0
test_create_u2string_from_char16_t | 0
test_create_u2string_from_char32_t | 0
test_create_u8string_from_char | 0
test_create_u8string_from_wchar_t | 0
test_create_u8string_from_char2_t | 0
test_create_u8string_from_char8_t | 0
test_create_u8string_from_char16_t | 0
test_create_u8string_from_char32_t | 0.001
test_create_u16string_from_char | 0
test_create_u16string_from_wchar_t | 0
test_create_u16string_from_char2_t | 0
test_create_u16string_from_char8_t | 0.001
test_create_u16string_from_char16_t | 0
test_create_u16string_from_char32_t | 0
test_create_u32string_from_char | 0
test_create_u32string_from_wchar_t | 0
test_create_u32string_from_char2_t | 0
test_create_u32string_from_char8_t | 0
test_create_u32string_from_char16_t | 0
test_create_u32string_from_char32_t | 0

## std_erase_iterator_test_suite

Test suite *std_erase_iterator_test_suite* with 5 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.003 seconds.

### Successful test cases

Test case|Execution time
-|-
test_erase_iterator_on_deque | 0
test_erase_iterator_on_list | 0
test_erase_iterator_on_vector | 0
test_erase_iterator_on_map | 0
test_erase_iterator_on_set | 0

## std_iso_8859_1_test_suite

Test suite *std_iso_8859_1_test_suite* with 12 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.008 seconds.

### Successful test cases

Test case|Execution time
-|-
test_multibyte_character_count | 0
test_system_wide_character_count | 0
test_ucs_2_character_count | 0
test_utf_8_character_count | 0
test_utf_16_character_count | 0
test_utf_32_character_count | 0
test_char_is_iso_8859_1_character | 0
test_char8_t_is_iso_8859_1_character | 0
test_wchar_t_is_iso_8859_1_character | 0
test_char2_t_is_iso_8859_1_character | 0
test_char16_t_is_iso_8859_1_character | 0
test_char32_t_is_iso_8859_1_character | 0

## std_reverse_test_suite

Test suite *std_reverse_test_suite* with 5 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.002 seconds.

### Successful test cases

Test case|Execution time
-|-
test_reverse_deque | 0
test_reverse_list | 0
test_reverse_vector | 0
test_reverse_map | 0
test_reverse_set | 0

## std_scope_guard_new_test_suite

Test suite *std_scope_guard_new_test_suite* with 1 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0 seconds.

### Successful test cases

Test case|Execution time
-|-
test_scope_guard_new | 0

## std_scope_guard_test_suite

Test suite *std_scope_guard_test_suite* with 1 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0 seconds.

### Successful test cases

Test case|Execution time
-|-
test_scope_guard | 0

## std_string_cast_test_suite

Test suite *std_string_cast_test_suite* with 81 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.058 seconds.

### Successful test cases

Test case|Execution time
-|-
test_char_size | 0
test_wchar_t_size | 0
test_char2_t_size | 0
test_char8_t_size | 0
test_char16_t_size | 0
test_char32_t_size | 0
test_multibyte_ascii_printable_characters | 0
test_multibyte_iso_8859_1_printable_characters | 0
test_cast_ascii_from_string_to_string | 0
test_cast_iso_8859_1_from_string_to_string | 0
test_cast_swedish_from_string_to_string | 0
test_cast_ascii_from_wstring_to_string | 0
test_cast_swedish_from_wstring_to_string | 0
test_cast_ascii_from_u2string_to_string | 0
test_cast_swedish_from_u2string_to_string | 0
test_cast_ascii_from_u8string_to_string | 0
test_cast_swedish_from_u8string_to_string | 0
test_cast_ascii_from_u16string_to_string | 0.001
test_cast_swedish_from_u16string_to_string | 0
test_cast_ascii_from_u32string_to_string | 0.001
test_cast_swedish_from_u32string_to_string | 0
test_cast_ascii_from_string_to_wstring | 0
test_cast_swedish_from_string_to_wstring | 0
test_cast_ascii_from_wstring_to_wstring | 0
test_cast_swedish_from_wstring_to_wstring | 0
test_cast_ascii_from_u2string_to_wstring | 0
test_cast_swedish_from_u2string_to_wstring | 0
test_cast_ascii_from_u8string_to_wstring | 0
test_cast_swedish_from_u8string_to_wstring | 0
test_cast_ascii_from_u16string_to_wstring | 0
test_cast_swedish_from_u16string_to_wstring | 0
test_cast_ascii_from_u32string_to_wstring | 0
test_cast_swedish_from_u32string_to_wstring | 0
test_cast_ascii_from_string_to_u2string | 0
test_cast_swedish_from_string_to_u2string | 0
test_cast_ascii_from_wstring_to_u2string | 0
test_cast_swedish_from_wstring_to_u2string | 0
test_cast_ascii_from_u2string_to_u2string | 0
test_cast_swedish_from_u2string_to_u2string | 0
test_cast_ascii_from_u8string_to_u2string | 0
test_cast_swedish_from_u8string_to_u2string | 0
test_cast_ascii_from_u16string_to_u2string | 0
test_cast_swedish_from_u16string_to_u2string | 0
test_cast_ascii_from_u32string_to_u2string | 0
test_cast_swedish_from_u32string_to_u2string | 0
test_cast_ascii_from_string_to_u8string | 0
test_cast_swedish_from_string_to_u8string | 0
test_cast_ascii_from_wstring_to_u8string | 0
test_cast_swedish_from_wstring_to_u8string | 0
test_cast_ascii_from_u2string_to_u8string | 0
test_cast_swedish_from_u2string_to_u8string | 0
test_cast_ascii_from_u8string_to_u8string | 0
test_cast_swedish_from_u8string_to_u8string | 0
test_cast_ascii_from_u16string_to_u8string | 0
test_cast_swedish_from_u16string_to_u8string | 0
test_cast_ascii_from_u32string_to_u8string | 0
test_cast_swedish_from_u32string_to_u8string | 0
test_cast_ascii_from_string_to_u16string | 0
test_cast_swedish_from_string_to_u16string | 0
test_cast_ascii_from_wstring_to_u16string | 0
test_cast_swedish_from_wstring_to_u16string | 0
test_cast_ascii_from_u2string_to_u16string | 0
test_cast_swedish_from_u2string_to_u16string | 0
test_cast_ascii_from_u8string_to_u16string | 0
test_cast_swedish_from_u8string_to_u16string | 0
test_cast_ascii_from_u16string_to_u16string | 0
test_cast_swedish_from_u16string_to_u16string | 0
test_cast_ascii_from_u32string_to_u16string | 0
test_cast_swedish_from_u32string_to_u16string | 0
test_cast_ascii_from_string_to_u32string | 0.001
test_cast_swedish_from_string_to_u32string | 0
test_cast_ascii_from_wstring_to_u32string | 0
test_cast_swedish_from_wstring_to_u32string | 0
test_cast_ascii_from_u2string_to_u32string | 0
test_cast_swedish_from_u2string_to_u32string | 0
test_cast_ascii_from_u8string_to_u32string | 0
test_cast_swedish_from_u8string_to_u32string | 0
test_cast_ascii_from_u16string_to_u32string | 0
test_cast_swedish_from_u16string_to_u32string | 0
test_cast_ascii_from_u32string_to_u32string | 0
test_cast_swedish_from_u32string_to_u32string | 0

## std_try_move_iterator_backward_test_suite

Test suite *std_try_move_iterator_backward_test_suite* with 13 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.009 seconds.

### Successful test cases

Test case|Execution time
-|-
test_try_move_backward_on_array | 0
test_try_move_backward_on_deque | 0
test_try_move_backward_on_forward_list | 0
test_try_move_backward_on_list | 0
test_try_move_backward_on_vector | 0
test_try_move_backward_on_map | 0
test_try_move_backward_on_set | 0
test_try_move_backward_on_multimap | 0
test_try_move_backward_on_multiset | 0
test_try_move_backward_on_unordered_map | 0
test_try_move_backward_on_unordered_set | 0
test_try_move_backward_on_unordered_multimap | 0
test_try_move_backward_on_unordered_multiset | 0

## std_value_guard_test_suite

Test suite *std_value_guard_test_suite* with 1 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.001 seconds.

### Successful test cases

Test case|Execution time
-|-
test_value_guard | 0

## std_windows_1252_test_suite

Test suite *std_windows_1252_test_suite* with 12 test cases was executed with result:

* 0 errors
* 0 failures

Test suite execution took 0.009 seconds.

### Successful test cases

Test case|Execution time
-|-
test_multibyte_character_count | 0
test_system_wide_character_count | 0
test_ucs_2_character_count | 0
test_utf_8_character_count | 0
test_utf_16_character_count | 0
test_utf_32_character_count | 0
test_char_is_windows_1252_character | 0
test_char8_t_is_windows_1252_character | 0
test_wchar_t_is_windows_1252_character | 0
test_char2_t_is_windows_1252_character | 0
test_char16_t_is_windows_1252_character | 0
test_char32_t_is_windows_1252_character | 0
