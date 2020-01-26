#!/bin/sh

REPO_ROOT_DIR=$1
REPORT_GENERATOR_DIR=$REPO_ROOT_DIR/libs/gtest_markdown_report
REPORT_GENERATOR=$REPORT_GENERATOR_DIR/gtest_xml_report_to_markdown.rb
REPORT_TEMPLATE_DIR=$REPORT_GENERATOR_DIR/template
REPORT_OUTPUT_DIR=$REPO_ROOT_DIR/docs/test_reports
SUMMARY_GENERATOR=$REPORT_GENERATOR_DIR/gtest_xml_reports_summary.rb
SUMMARY_INPUT_DIR=$REPORT_OUTPUT_DIR
SUMMARY_TEMPLATE=$REPORT_TEMPLATE_DIR/test_reports_header.md
SUMMARY_OUTPUT=$REPORT_OUTPUT_DIR/unit_tests.md

cd ./bin/clang

ruby $REPORT_GENERATOR -i ./GO_boost_libraries_async_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_boost_libraries_async_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_config_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_boost_libraries_config_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_diagnostics_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_boost_libraries_diagnostics_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_exception_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_boost_libraries_exception_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_mvvm_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_boost_libraries_mvvm_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_property_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_boost_libraries_property_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_string_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_boost_libraries_string_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_type_traits_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_boost_libraries_type_traits_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_utility_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_boost_libraries_utility_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_async_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_async_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_config_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_config_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_diagnostics_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_diagnostics_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_exception_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_exception_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_mvvm_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_mvvm_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_property_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_property_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_signals_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_signals_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_string_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_string_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_type_traits_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_type_traits_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_utility_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_clang_report_header.md -o $REPORT_OUTPUT_DIR/linux_clang/GO_std_libraries_utility_tests_report.md

cd ./../../bin/gcc

ruby $REPORT_GENERATOR -i ./GO_boost_libraries_async_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_boost_libraries_async_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_config_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_boost_libraries_config_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_diagnostics_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_boost_libraries_diagnostics_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_exception_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_boost_libraries_exception_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_mvvm_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_boost_libraries_mvvm_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_property_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_boost_libraries_property_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_string_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_boost_libraries_string_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_type_traits_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_boost_libraries_type_traits_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_boost_libraries_utility_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_boost_libraries_utility_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_async_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_async_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_config_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_config_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_diagnostics_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_diagnostics_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_exception_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_exception_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_mvvm_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_mvvm_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_property_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_property_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_signals_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_signals_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_string_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_string_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_type_traits_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_type_traits_tests_report.md
ruby $REPORT_GENERATOR -i ./GO_std_libraries_utility_tests_report.xml -t $REPORT_TEMPLATE_DIR/linux_gcc_report_header.md -o $REPORT_OUTPUT_DIR/linux_gcc/GO_std_libraries_utility_tests_report.md

cd ./../..

ruby $SUMMARY_GENERATOR -i $SUMMARY_INPUT_DIR -o $SUMMARY_OUTPUT -t $SUMMARY_TEMPLATE
