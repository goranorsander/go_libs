@echo off

set repo_root_dir=%1
set report_generator_dir=%repo_root_dir%\libs\gtest_markdown_report
set report_generator=%report_generator_dir%\gtest_xml_report_to_markdown.rb
set report_template_dir=%report_generator_dir%\template
set report_output_dir=%repo_root_dir%\docs\test_reports
set summary_generator=%report_generator_dir%\gtest_xml_reports_summary.rb
set summary_input_dir=%report_output_dir%
set summary_template=%report_template_dir%\test_reports_header.md
set summary_output=%report_output_dir%\unit_tests.md

pushd %CD%\bin\msys-mingw

ruby.exe %report_generator% -i %CD%\GO_boost_libraries_async_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_boost_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_config_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_boost_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_boost_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_exception_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_boost_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_boost_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_property_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_boost_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_string_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_boost_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_boost_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_utility_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_boost_libraries_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_async_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_config_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_exception_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_property_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_signals_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_string_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_utility_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_std_libraries_utility_tests_report.md

popd
pushd %CD%\bin\vc90

ruby.exe %report_generator% -i %CD%\GO_boost_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_boost_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_boost_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_boost_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_boost_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_boost_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_boost_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_boost_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_boost_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_boost_libraries_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_signals_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_std_libraries_utility_tests_report.md

popd
pushd %CD%\bin\vc100

ruby.exe %report_generator% -i %CD%\GO_boost_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_boost_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_boost_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_boost_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_boost_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_boost_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_boost_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_boost_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_boost_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_boost_libraries_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_signals_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_std_libraries_utility_tests_report.md

popd
pushd %CD%\bin\vc110

ruby.exe %report_generator% -i %CD%\GO_boost_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_boost_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_boost_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_boost_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_boost_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_boost_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_boost_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_boost_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_boost_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_boost_libraries_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_signals_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_std_libraries_utility_tests_report.md

popd
pushd %CD%\bin\vc120

ruby.exe %report_generator% -i %CD%\GO_boost_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_boost_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_boost_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_boost_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_boost_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_boost_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_boost_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_boost_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_boost_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_boost_libraries_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_signals_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_std_libraries_utility_tests_report.md

popd
pushd %CD%\bin\vc140

ruby.exe %report_generator% -i %CD%\GO_boost_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_boost_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_boost_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_boost_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_boost_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_boost_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_boost_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_boost_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_boost_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_boost_libraries_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_signals_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_std_libraries_utility_tests_report.md

popd
pushd %CD%\bin\vc141

ruby.exe %report_generator% -i %CD%\GO_boost_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_boost_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_boost_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_boost_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_boost_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_boost_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_boost_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_boost_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_boost_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_boost_libraries_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_signals_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_std_libraries_utility_tests_report.md

popd
pushd %CD%\bin\vc142

ruby.exe %report_generator% -i %CD%\GO_boost_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_boost_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_boost_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_boost_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_boost_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_boost_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_boost_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_boost_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_boost_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_boost_libraries_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_signals_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc142_report_header.md -o %report_output_dir%\windows_msvc142\GO_std_libraries_utility_tests_report.md

popd
pushd %CD%\bin\vc143

ruby.exe %report_generator% -i %CD%\GO_boost_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_boost_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_boost_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_boost_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_boost_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_boost_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_boost_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_boost_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_boost_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_boost_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_boost_libraries_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_async_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_async_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_config_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_diagnostics_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_diagnostics_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_exception_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_property_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_signals_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_string_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_string_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_type_traits_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_type_traits_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_std_libraries_utility_tests_report.xml -t %report_template_dir%\windows_msvc143_report_header.md -o %report_output_dir%\windows_msvc143\GO_std_libraries_utility_tests_report.md

popd

ruby.exe %summary_generator% -i %summary_input_dir% -o %summary_output% -t %summary_template%
