@echo off

.\GO_libraries_boost_config_tests.exe --gtest_output=xml:GO_libraries_boost_config_tests_report.xml
.\GO_libraries_boost_exception_tests.exe --gtest_output=xml:GO_libraries_boost_exception_tests_report.xml
.\GO_libraries_boost_mvvm_tests.exe --gtest_output=xml:GO_libraries_boost_mvvm_tests_report.xml
.\GO_libraries_boost_property_tests.exe --gtest_output=xml:GO_libraries_boost_property_tests_report.xml
.\GO_libraries_boost_utility_tests.exe --gtest_output=xml:GO_libraries_boost_utility_tests_report.xml
.\GO_libraries_std_config_tests.exe --gtest_output=xml:GO_libraries_std_config_tests_report.xml
.\GO_libraries_std_exception_tests.exe --gtest_output=xml:GO_libraries_std_exception_tests_report.xml
.\GO_libraries_std_mvvm_tests.exe --gtest_output=xml:GO_libraries_std_mvvm_tests_report.xml
.\GO_libraries_std_property_tests.exe --gtest_output=xml:GO_libraries_std_property_tests_report.xml
.\GO_libraries_std_signals_tests.exe --gtest_output=xml:GO_libraries_std_signals_tests_report.xml
.\GO_libraries_std_utility_tests.exe --gtest_output=xml:GO_libraries_std_utility_tests_report.xml