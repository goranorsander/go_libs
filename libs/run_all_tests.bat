@echo off

pushd %CD%\bin\msys-mingw

.\GO_boost_libraries_config_tests.exe --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
.\GO_boost_libraries_exception_tests.exe --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
.\GO_boost_libraries_mvvm_tests.exe --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
.\GO_boost_libraries_property_tests.exe --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
.\GO_boost_libraries_utility_tests.exe --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
.\GO_std_libraries_config_tests.exe --gtest_output=xml:GO_std_libraries_config_tests_report.xml
.\GO_std_libraries_exception_tests.exe --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
.\GO_std_libraries_mvvm_tests.exe --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
.\GO_std_libraries_property_tests.exe --gtest_output=xml:GO_std_libraries_property_tests_report.xml
.\GO_std_libraries_signals_tests.exe --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
.\GO_std_libraries_utility_tests.exe --gtest_output=xml:GO_std_libraries_utility_tests_report.xml

popd
pushd %CD%\bin\vc90

.\GO_boost_libraries_config_tests.exe --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
.\GO_boost_libraries_exception_tests.exe --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
.\GO_boost_libraries_mvvm_tests.exe --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
.\GO_boost_libraries_property_tests.exe --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
.\GO_boost_libraries_utility_tests.exe --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
.\GO_std_libraries_config_tests.exe --gtest_output=xml:GO_std_libraries_config_tests_report.xml
.\GO_std_libraries_exception_tests.exe --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
.\GO_std_libraries_mvvm_tests.exe --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
.\GO_std_libraries_property_tests.exe --gtest_output=xml:GO_std_libraries_property_tests_report.xml
.\GO_std_libraries_signals_tests.exe --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
.\GO_std_libraries_utility_tests.exe --gtest_output=xml:GO_std_libraries_utility_tests_report.xml

popd
pushd %CD%\bin\vc100

.\GO_boost_libraries_config_tests.exe --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
.\GO_boost_libraries_exception_tests.exe --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
.\GO_boost_libraries_mvvm_tests.exe --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
.\GO_boost_libraries_property_tests.exe --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
.\GO_boost_libraries_utility_tests.exe --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
.\GO_std_libraries_config_tests.exe --gtest_output=xml:GO_std_libraries_config_tests_report.xml
.\GO_std_libraries_exception_tests.exe --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
.\GO_std_libraries_mvvm_tests.exe --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
.\GO_std_libraries_property_tests.exe --gtest_output=xml:GO_std_libraries_property_tests_report.xml
.\GO_std_libraries_signals_tests.exe --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
.\GO_std_libraries_utility_tests.exe --gtest_output=xml:GO_std_libraries_utility_tests_report.xml

popd
pushd %CD%\bin\vc110

.\GO_boost_libraries_config_tests.exe --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
.\GO_boost_libraries_exception_tests.exe --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
.\GO_boost_libraries_mvvm_tests.exe --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
.\GO_boost_libraries_property_tests.exe --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
.\GO_boost_libraries_utility_tests.exe --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
.\GO_std_libraries_config_tests.exe --gtest_output=xml:GO_std_libraries_config_tests_report.xml
.\GO_std_libraries_exception_tests.exe --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
.\GO_std_libraries_mvvm_tests.exe --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
.\GO_std_libraries_property_tests.exe --gtest_output=xml:GO_std_libraries_property_tests_report.xml
.\GO_std_libraries_signals_tests.exe --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
.\GO_std_libraries_utility_tests.exe --gtest_output=xml:GO_std_libraries_utility_tests_report.xml

popd
pushd %CD%\bin\vc120

.\GO_boost_libraries_config_tests.exe --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
.\GO_boost_libraries_exception_tests.exe --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
.\GO_boost_libraries_mvvm_tests.exe --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
.\GO_boost_libraries_property_tests.exe --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
.\GO_boost_libraries_utility_tests.exe --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
.\GO_std_libraries_config_tests.exe --gtest_output=xml:GO_std_libraries_config_tests_report.xml
.\GO_std_libraries_exception_tests.exe --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
.\GO_std_libraries_mvvm_tests.exe --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
.\GO_std_libraries_property_tests.exe --gtest_output=xml:GO_std_libraries_property_tests_report.xml
.\GO_std_libraries_signals_tests.exe --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
.\GO_std_libraries_utility_tests.exe --gtest_output=xml:GO_std_libraries_utility_tests_report.xml

popd
pushd %CD%\bin\vc140

.\GO_boost_libraries_config_tests.exe --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
.\GO_boost_libraries_exception_tests.exe --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
.\GO_boost_libraries_mvvm_tests.exe --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
.\GO_boost_libraries_property_tests.exe --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
.\GO_boost_libraries_utility_tests.exe --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
.\GO_std_libraries_config_tests.exe --gtest_output=xml:GO_std_libraries_config_tests_report.xml
.\GO_std_libraries_exception_tests.exe --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
.\GO_std_libraries_mvvm_tests.exe --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
.\GO_std_libraries_property_tests.exe --gtest_output=xml:GO_std_libraries_property_tests_report.xml
.\GO_std_libraries_signals_tests.exe --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
.\GO_std_libraries_utility_tests.exe --gtest_output=xml:GO_std_libraries_utility_tests_report.xml

popd
pushd %CD%\bin\vc141

.\GO_boost_libraries_config_tests.exe --gtest_output=xml:GO_boost_libraries_config_tests_report.xml
.\GO_boost_libraries_exception_tests.exe --gtest_output=xml:GO_boost_libraries_exception_tests_report.xml
.\GO_boost_libraries_mvvm_tests.exe --gtest_output=xml:GO_boost_libraries_mvvm_tests_report.xml
.\GO_boost_libraries_property_tests.exe --gtest_output=xml:GO_boost_libraries_property_tests_report.xml
.\GO_boost_libraries_utility_tests.exe --gtest_output=xml:GO_boost_libraries_utility_tests_report.xml
.\GO_std_libraries_config_tests.exe --gtest_output=xml:GO_std_libraries_config_tests_report.xml
.\GO_std_libraries_exception_tests.exe --gtest_output=xml:GO_std_libraries_exception_tests_report.xml
.\GO_std_libraries_mvvm_tests.exe --gtest_output=xml:GO_std_libraries_mvvm_tests_report.xml
.\GO_std_libraries_property_tests.exe --gtest_output=xml:GO_std_libraries_property_tests_report.xml
.\GO_std_libraries_signals_tests.exe --gtest_output=xml:GO_std_libraries_signals_tests_report.xml
.\GO_std_libraries_utility_tests.exe --gtest_output=xml:GO_std_libraries_utility_tests_report.xml

popd
