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

ruby.exe %report_generator% -i %CD%\GO_libraries_boost_config_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_boost_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_exception_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_boost_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_mvvm_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_boost_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_property_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_boost_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_utility_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_boost_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_config_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_std_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_exception_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_std_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_mvvm_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_std_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_property_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_std_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_signals_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_std_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_utility_tests_report.xml -t %report_template_dir%\windows_gcc_report_header.md -o %report_output_dir%\windows_gcc\GO_libraries_std_utility_tests_report.md

popd
pushd %CD%\bin\vc90

ruby.exe %report_generator% -i %CD%\GO_libraries_boost_config_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_boost_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_exception_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_boost_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_boost_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_property_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_boost_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_utility_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_boost_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_config_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_std_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_exception_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_std_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_std_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_property_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_std_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_signals_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_std_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_utility_tests_report.xml -t %report_template_dir%\windows_msvc90_report_header.md -o %report_output_dir%\windows_msvc90\GO_libraries_std_utility_tests_report.md

popd
pushd %CD%\bin\vc100

ruby.exe %report_generator% -i %CD%\GO_libraries_boost_config_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_boost_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_exception_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_boost_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_boost_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_property_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_boost_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_utility_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_boost_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_config_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_std_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_exception_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_std_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_std_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_property_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_std_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_signals_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_std_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_utility_tests_report.xml -t %report_template_dir%\windows_msvc100_report_header.md -o %report_output_dir%\windows_msvc100\GO_libraries_std_utility_tests_report.md

popd
pushd %CD%\bin\vc110

ruby.exe %report_generator% -i %CD%\GO_libraries_boost_config_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_boost_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_exception_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_boost_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_boost_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_property_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_boost_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_utility_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_boost_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_config_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_std_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_exception_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_std_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_std_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_property_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_std_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_signals_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_std_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_utility_tests_report.xml -t %report_template_dir%\windows_msvc110_report_header.md -o %report_output_dir%\windows_msvc110\GO_libraries_std_utility_tests_report.md

popd
pushd %CD%\bin\vc120

ruby.exe %report_generator% -i %CD%\GO_libraries_boost_config_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_boost_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_exception_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_boost_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_boost_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_property_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_boost_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_utility_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_boost_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_config_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_std_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_exception_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_std_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_std_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_property_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_std_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_signals_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_std_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_utility_tests_report.xml -t %report_template_dir%\windows_msvc120_report_header.md -o %report_output_dir%\windows_msvc120\GO_libraries_std_utility_tests_report.md

popd
pushd %CD%\bin\vc140

ruby.exe %report_generator% -i %CD%\GO_libraries_boost_config_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_boost_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_exception_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_boost_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_boost_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_property_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_boost_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_utility_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_boost_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_config_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_std_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_exception_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_std_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_std_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_property_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_std_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_signals_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_std_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_utility_tests_report.xml -t %report_template_dir%\windows_msvc140_report_header.md -o %report_output_dir%\windows_msvc140\GO_libraries_std_utility_tests_report.md

popd
pushd %CD%\bin\vc141

ruby.exe %report_generator% -i %CD%\GO_libraries_boost_config_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_boost_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_exception_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_boost_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_boost_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_property_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_boost_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_boost_utility_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_boost_utility_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_config_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_std_config_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_exception_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_std_exception_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_mvvm_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_std_mvvm_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_property_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_std_property_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_signals_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_std_signals_tests_report.md
ruby.exe %report_generator% -i %CD%\GO_libraries_std_utility_tests_report.xml -t %report_template_dir%\windows_msvc141_report_header.md -o %report_output_dir%\windows_msvc141\GO_libraries_std_utility_tests_report.md

popd

ruby.exe %summary_generator% -i %summary_input_dir% -o %summary_output% -t %summary_template%