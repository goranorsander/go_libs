@echo off

.\GO_boost_libraries_config_tests.exe --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
.\GO_boost_libraries_diagnostics_tests.exe --gtest_output=xml:GO_boost_libraries_diagnostics_tests_report.xml
.\GO_boost_libraries_exception_tests.exe --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
.\GO_boost_libraries_mvvm_tests.exe --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
.\GO_boost_libraries_property_tests.exe --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
.\GO_boost_libraries_type_traits_tests.exe --gtest_output=xml:GO_boost_libraries_type_traits_tests_report.xml
.\GO_boost_libraries_utility_tests.exe --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
.\GO_std_libraries_config_tests.exe --gtest_output=xml:GO_std_libraries_config_tests_report.xml
.\GO_std_libraries_diagnostics_tests.exe --gtest_output=xml:GO_std_libraries_diagnostics_tests_report.xml
.\GO_std_libraries_exception_tests.exe --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
.\GO_std_libraries_mvvm_tests.exe --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
.\GO_std_libraries_property_tests.exe --gtest_output=xml:GO_std_libraries_property_tests_report.xml
.\GO_std_libraries_signals_tests.exe --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
.\GO_std_libraries_type_traits_tests.exe --gtest_output=xml:GO_std_libraries_type_traits_tests_report.xml
.\GO_std_libraries_utility_tests.exe --gtest_output=xml:GO_std_libraries_utility_tests_report.xml
