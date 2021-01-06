#
#  CMakeLists.txt
#
#  Copyright 2016-2021 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

set(PROJECT_GO_BOOST_LIBS_NAME GO_boost_libraries)

file(GLOB GO_BOOST_DIR_FILES ./*.hpp)
file(GLOB GO_BOOST_ASYNC_DIR_FILES ./async/*.hpp)
file(GLOB GO_BOOST_CONFIG_DIR_FILES ./config/*.hpp)
file(GLOB GO_BOOST_CONFIG_COMPILER_DIR_FILES ./config/compiler/*.hpp)
file(GLOB GO_BOOST_CONFIG_PLATFORM_DIR_FILES ./config/platform/*.hpp)
file(GLOB GO_BOOST_DIAGNOSTICS_DIR_FILES ./diagnostics/*.hpp)
file(GLOB GO_BOOST_DIAGNOSTICS_BENCHMARK_DIR_FILES ./diagnostics/benchmark/*.hpp)
file(GLOB GO_BOOST_DIAGNOSTICS_LOG_DIR_FILES ./diagnostics/log/*.hpp)
file(GLOB GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DIR_FILES ./diagnostics/log/detail/*.hpp)
file(GLOB GO_BOOST_DIAGNOSTICS_LOG_POLICY_DIR_FILES ./diagnostics/log/policy/*.hpp)
file(GLOB GO_BOOST_EXCEPTION_DIR_FILES ./exception/*.hpp)
file(GLOB GO_BOOST_MVVM_DIR_FILES ./mvvm/*.hpp)
file(GLOB GO_BOOST_MVVM_ITERATOR_DIR_FILES ./mvvm/iterator/*.hpp)
file(GLOB GO_BOOST_MVVM_UTILITY_DIR_FILES ./mvvm/utility/*.hpp)
file(GLOB GO_BOOST_PROPERTY_DIR_FILES ./property/*.hpp)
file(GLOB GO_BOOST_PROPERTY_DETAIL_DIR_FILES ./property/detail/*.hpp)
file(GLOB GO_BOOST_PROPERTY_NAMELESS_DIR_FILES ./property/nameless/*.hpp)
file(GLOB GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR_FILES ./property/nameless/detail/*.hpp)
file(GLOB GO_BOOST_PROPERTY_POLICY_DIR_FILES ./property/policy/*.hpp)
file(GLOB GO_BOOST_SIGNALS_DIR_FILES ./signals/*.hpp)
file(GLOB GO_BOOST_STRING_DIR_FILES ./string/*.hpp)
file(GLOB GO_BOOST_STRING_CONVERT_DIR_FILES ./string/convert/*.hpp)
file(GLOB GO_BOOST_STRING_ENCODING_DIR_FILES ./string/encoding/*.hpp)
file(GLOB GO_BOOST_STRING_TRAITS_DIR_FILES ./string/traits/*.hpp)
file(GLOB GO_BOOST_TYPE_TRAITS_DIR_FILES ./type_traits/*.hpp)
file(GLOB GO_BOOST_TYPE_TRAITS_DETAIL_DIR_FILES ./type_traits/detail/*.hpp)
file(GLOB GO_BOOST_UTILITY_DIR_FILES ./utility/*.hpp)
file(GLOB GO_BOOST_UTILITY_CONTAINER_DIR_FILES ./utility/container/*.hpp)
file(GLOB GO_BOOST_UTILITY_ITERATOR_DIR_FILES ./utility/iterator/*.hpp)
file(GLOB GO_BOOST_UTILITY_RANGE_DIR_FILES ./utility/range/*.hpp)
file(GLOB GO_BOOST_UTILITY_SMART_PTR_DIR_FILES ./utility/smart_ptr/*.hpp)
file(GLOB GO_BOOST_VS_DIR_FILES ./.vs/*.cpp)

add_library(${PROJECT_GO_BOOST_LIBS_NAME} STATIC
    ${GO_BOOST_DIR_FILES}
    ${GO_BOOST_ASYNC_DIR_FILES}
    ${GO_BOOST_CONFIG_DIR_FILES}
    ${GO_BOOST_CONFIG_COMPILER_DIR_FILES}
    ${GO_BOOST_CONFIG_PLATFORM_DIR_FILES}
    ${GO_BOOST_DIAGNOSTICS_DIR_FILES}
    ${GO_BOOST_DIAGNOSTICS_BENCHMARK_DIR_FILES}
    ${GO_BOOST_DIAGNOSTICS_LOG_DIR_FILES}
    ${GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DIR_FILES}
    ${GO_BOOST_DIAGNOSTICS_LOG_POLICY_DIR_FILES}
    ${GO_BOOST_EXCEPTION_DIR_FILES}
    ${GO_BOOST_MVVM_DIR_FILES}
    ${GO_BOOST_MVVM_ITERATOR_DIR_FILES}
    ${GO_BOOST_MVVM_UTILITY_DIR_FILES}
    ${GO_BOOST_PROPERTY_DIR_FILES}
    ${GO_BOOST_PROPERTY_DETAIL_DIR_FILES}
    ${GO_BOOST_PROPERTY_NAMELESS_DIR_FILES}
    ${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR_FILES}
    ${GO_BOOST_PROPERTY_POLICY_DIR_FILES}
    ${GO_BOOST_SIGNALS_DIR_FILES}
    ${GO_BOOST_STRING_DIR_FILES}
    ${GO_BOOST_STRING_CONVERT_DIR_FILES}
    ${GO_BOOST_STRING_ENCODING_DIR_FILES}
    ${GO_BOOST_STRING_TRAITS_DIR_FILES}
    ${GO_BOOST_TYPE_TRAITS_DIR_FILES}
    ${GO_BOOST_TYPE_TRAITS_DETAIL_DIR_FILES}
    ${GO_BOOST_UTILITY_DIR_FILES}
    ${GO_BOOST_UTILITY_CONTAINER_DIR_FILES}
    ${GO_BOOST_UTILITY_ITERATOR_DIR_FILES}
    ${GO_BOOST_UTILITY_RANGE_DIR_FILES}
    ${GO_BOOST_UTILITY_SMART_PTR_DIR_FILES}
    ${GO_BOOST_VS_DIR_FILES}
)

set_target_properties(${PROJECT_GO_BOOST_LIBS_NAME} PROPERTIES LINKER_LANGUAGE CXX FOLDER go_libs/boost/libs)

source_group(go_boost FILES ${GO_BOOST_DIR_FILES})
source_group(go_boost\\async FILES ${GO_BOOST_ASYNC_DIR_FILES})
source_group(go_boost\\config FILES ${GO_BOOST_CONFIG_DIR_FILES})
source_group(go_boost\\config\\compiler FILES ${GO_BOOST_CONFIG_COMPILER_DIR_FILES})
source_group(go_boost\\config\\platform FILES ${GO_BOOST_CONFIG_PLATFORM_DIR_FILES})
source_group(go_boost\\diagnostics FILES ${GO_BOOST_DIAGNOSTICS_DIR_FILES})
source_group(go_boost\\diagnostics\\benchmark FILES ${GO_BOOST_DIAGNOSTICS_BENCHMARK_DIR_FILES})
source_group(go_boost\\diagnostics\\log FILES ${GO_BOOST_DIAGNOSTICS_LOG_DIR_FILES})
source_group(go_boost\\diagnostics\\log\\detail FILES ${GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DIR_FILES})
source_group(go_boost\\diagnostics\\log\\policy FILES ${GO_BOOST_DIAGNOSTICS_LOG_POLICY_DIR_FILES})
source_group(go_boost\\exception FILES ${GO_BOOST_EXCEPTION_DIR_FILES})
source_group(go_boost\\mvvm FILES ${GO_BOOST_MVVM_DIR_FILES})
source_group(go_boost\\mvvm\\iterator FILES ${GO_BOOST_MVVM_ITERATOR_DIR_FILES})
source_group(go_boost\\mvvm\\utility FILES ${GO_BOOST_MVVM_UTILITY_DIR_FILES})
source_group(go_boost\\property FILES ${GO_BOOST_PROPERTY_DIR_FILES})
source_group(go_boost\\property\\detail FILES ${GO_BOOST_PROPERTY_DETAIL_DIR_FILES})
source_group(go_boost\\property\\nameless FILES ${GO_BOOST_PROPERTY_NAMELESS_DIR_FILES})
source_group(go_boost\\property\\nameless\\detail FILES ${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR_FILES})
source_group(go_boost\\property\\policy FILES ${GO_BOOST_PROPERTY_POLICY_DIR_FILES})
source_group(go_boost\\signals FILES ${GO_BOOST_SIGNALS_DIR_FILES})
source_group(go_boost\\string FILES ${GO_BOOST_STRING_DIR_FILES})
source_group(go_boost\\string\\convert FILES ${GO_BOOST_STRING_CONVERT_DIR_FILES})
source_group(go_boost\\string\\encoding FILES ${GO_BOOST_STRING_ENCODING_DIR_FILES})
source_group(go_boost\\string\\traits FILES ${GO_BOOST_STRING_TRAITS_DIR_FILES})
source_group(go_boost\\type_traits FILES ${GO_BOOST_TYPE_TRAITS_DIR_FILES})
source_group(go_boost\\type_traits\\detail FILES ${GO_BOOST_TYPE_TRAITS_DETAIL_DIR_FILES})
source_group(go_boost\\utility FILES ${GO_BOOST_UTILITY_DIR_FILES})
source_group(go_boost\\utility\\container FILES ${GO_BOOST_UTILITY_CONTAINER_DIR_FILES})
source_group(go_boost\\utility\\iterator FILES ${GO_BOOST_UTILITY_ITERATOR_DIR_FILES})
source_group(go_boost\\utility\\range FILES ${GO_BOOST_UTILITY_RANGE_DIR_FILES})
source_group(go_boost\\utility\\smart_ptr FILES ${GO_BOOST_UTILITY_SMART_PTR_DIR_FILES})
source_group(go_boost\\.vs FILES ${GO_BOOST_VS_DIR_FILES})
