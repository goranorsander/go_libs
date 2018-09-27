@echo off

pushd %CD%\bin\msys-mingw

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

popd
pushd %CD%\bin\vc90

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

popd
pushd %CD%\bin\vc100

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

popd
pushd %CD%\bin\vc110

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

popd
pushd %CD%\bin\vc120

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

popd
pushd %CD%\bin\vc140

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

popd
pushd %CD%\bin\vc141

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

popd
