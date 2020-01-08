#!/bin/sh

cd ./bin/clang

./GO_boost_libraries_async_tests --gtest_output=xml:GO_boost_libraries_async_tests_report.xml
./GO_boost_libraries_config_tests --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
./GO_boost_libraries_diagnostics_tests --gtest_output=xml:GO_boost_libraries_diagnostics_tests_report.xml
./GO_boost_libraries_exception_tests --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
./GO_boost_libraries_mvvm_tests --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
./GO_boost_libraries_property_tests --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
./GO_boost_libraries_type_traits_tests --gtest_output=xml:GO_boost_libraries_type_traits_tests_report.xml
./GO_boost_libraries_utility_tests --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
./GO_std_libraries_async_tests --gtest_output=xml:GO_std_libraries_async_tests_report.xml
./GO_std_libraries_config_tests --gtest_output=xml:GO_std_libraries_config_tests_report.xml
./GO_std_libraries_diagnostics_tests --gtest_output=xml:GO_std_libraries_diagnostics_tests_report.xml
./GO_std_libraries_exception_tests --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
./GO_std_libraries_mvvm_tests --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
./GO_std_libraries_property_tests --gtest_output=xml:GO_std_libraries_property_tests_report.xml
./GO_std_libraries_signals_tests --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
./GO_std_libraries_type_traits_tests --gtest_output=xml:GO_std_libraries_type_traits_tests_report.xml
./GO_std_libraries_utility_tests --gtest_output=xml:GO_std_libraries_utility_tests_report.xml

cd ./../../bin/gcc

./GO_boost_libraries_async_tests --gtest_output=xml:GO_boost_libraries_async_tests_report.xml
./GO_boost_libraries_config_tests --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
./GO_boost_libraries_diagnostics_tests --gtest_output=xml:GO_boost_libraries_diagnostics_tests_report.xml
./GO_boost_libraries_exception_tests --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
./GO_boost_libraries_mvvm_tests --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
./GO_boost_libraries_property_tests --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
./GO_boost_libraries_type_traits_tests --gtest_output=xml:GO_boost_libraries_type_traits_tests_report.xml
./GO_boost_libraries_utility_tests --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
./GO_std_libraries_async_tests --gtest_output=xml:GO_std_libraries_async_tests_report.xml
./GO_std_libraries_config_tests --gtest_output=xml:GO_std_libraries_config_tests_report.xml
./GO_std_libraries_diagnostics_tests --gtest_output=xml:GO_std_libraries_diagnostics_tests_report.xml
./GO_std_libraries_exception_tests --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
./GO_std_libraries_mvvm_tests --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
./GO_std_libraries_property_tests --gtest_output=xml:GO_std_libraries_property_tests_report.xml
./GO_std_libraries_signals_tests --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
./GO_std_libraries_type_traits_tests --gtest_output=xml:GO_std_libraries_type_traits_tests_report.xml
./GO_std_libraries_utility_tests --gtest_output=xml:GO_std_libraries_utility_tests_report.xml

cd ./../..