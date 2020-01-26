#
#  CMakeLists.txt
#
#  Copyright 2016-2020 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

set(PROJECT_GO_STD_LIBS_NAME GO_std_libraries)

file(GLOB GO_DIR_FILES ./*.hpp)
file(GLOB GO_ASYNC_DIR_FILES ./async/*.hpp)
file(GLOB GO_CONFIG_DIR_FILES ./config/*.hpp)
file(GLOB GO_CONFIG_COMPILER_DIR_FILES ./config/compiler/*.hpp)
file(GLOB GO_CONFIG_PLATFORM_DIR_FILES ./config/platform/*.hpp)
file(GLOB GO_DIAGNOSTICS_DIR_FILES ./diagnostics/*.hpp)
file(GLOB GO_DIAGNOSTICS_BENCHMARK_DIR_FILES ./diagnostics/benchmark/*.hpp)
file(GLOB GO_DIAGNOSTICS_LOG_DIR_FILES ./diagnostics/log/*.hpp)
file(GLOB GO_DIAGNOSTICS_LOG_DETAIL_DIR_FILES ./diagnostics/log/detail/*.hpp)
file(GLOB GO_DIAGNOSTICS_LOG_POLICY_DIR_FILES ./diagnostics/log/policy/*.hpp)
file(GLOB GO_EXCEPTION_DIR_FILES ./exception/*.hpp)
file(GLOB GO_MVVM_DIR_FILES ./mvvm/*.hpp)
file(GLOB GO_MVVM_ITERATOR_DIR_FILES ./mvvm/iterator/*.hpp)
file(GLOB GO_MVVM_UTILITY_DIR_FILES ./mvvm/utility/*.hpp)
file(GLOB GO_PROPERTY_DIR_FILES ./property/*.hpp)
file(GLOB GO_PROPERTY_DETAIL_DIR_FILES ./property/detail/*.hpp)
file(GLOB GO_PROPERTY_NAMELESS_DIR_FILES ./property/nameless/*.hpp)
file(GLOB GO_PROPERTY_NAMELESS_DETAIL_DIR_FILES ./property/nameless/detail/*.hpp)
file(GLOB GO_PROPERTY_POLICY_DIR_FILES ./property/policy/*.hpp)
file(GLOB GO_SIGNALS_DIR_FILES ./signals/*.hpp)
file(GLOB GO_STRING_DIR_FILES ./string/*.hpp)
file(GLOB GO_STRING_DETAIL_DIR_FILES ./string/detail/*.hpp)
file(GLOB GO_TYPE_TRAITS_DIR_FILES ./type_traits/*.hpp)
file(GLOB GO_TYPE_TRAITS_DETAIL_DIR_FILES ./type_traits/detail/*.hpp)
file(GLOB GO_UTILITY_DIR_FILES ./utility/*.hpp)
file(GLOB GO_UTILITY_CONTAINER_DIR_FILES ./utility/container/*.hpp)
file(GLOB GO_UTILITY_ITERATOR_DIR_FILES ./utility/iterator/*.hpp)
file(GLOB GO_UTILITY_RANGE_DIR_FILES ./utility/range/*.hpp)
file(GLOB GO_VS_DIR_FILES ./.vs/*.cpp)

add_library(${PROJECT_GO_STD_LIBS_NAME} STATIC
    ${GO_DIR_FILES}
    ${GO_ASYNC_DIR_FILES}
    ${GO_CONFIG_DIR_FILES}
    ${GO_CONFIG_COMPILER_DIR_FILES}
    ${GO_CONFIG_PLATFORM_DIR_FILES}
    ${GO_DIAGNOSTICS_DIR_FILES}
    ${GO_DIAGNOSTICS_BENCHMARK_DIR_FILES}
    ${GO_DIAGNOSTICS_LOG_DIR_FILES}
    ${GO_DIAGNOSTICS_LOG_DETAIL_DIR_FILES}
    ${GO_DIAGNOSTICS_LOG_POLICY_DIR_FILES}
    ${GO_EXCEPTION_DIR_FILES}
    ${GO_MVVM_DIR_FILES}
    ${GO_MVVM_ITERATOR_DIR_FILES}
    ${GO_MVVM_UTILITY_DIR_FILES}
    ${GO_PROPERTY_DIR_FILES}
    ${GO_PROPERTY_DETAIL_DIR_FILES}
    ${GO_PROPERTY_NAMELESS_DIR_FILES}
    ${GO_PROPERTY_NAMELESS_DETAIL_DIR_FILES}
    ${GO_PROPERTY_POLICY_DIR_FILES}
    ${GO_SIGNALS_DIR_FILES}
    ${GO_STRING_DIR_FILES}
    ${GO_STRING_DETAIL_DIR_FILES}
    ${GO_TYPE_TRAITS_DIR_FILES}
    ${GO_TYPE_TRAITS_DETAIL_DIR_FILES}
    ${GO_UTILITY_DIR_FILES}
    ${GO_UTILITY_CONTAINER_DIR_FILES}
    ${GO_UTILITY_ITERATOR_DIR_FILES}
    ${GO_UTILITY_RANGE_DIR_FILES}
    ${GO_VS_DIR_FILES}
)

set_target_properties(${PROJECT_GO_STD_LIBS_NAME} PROPERTIES LINKER_LANGUAGE CXX FOLDER go_libs/std/libs)

source_group(go FILES ${GO_DIR_FILES})
source_group(go\\async FILES ${GO_ASYNC_DIR_FILES})
source_group(go\\config FILES ${GO_CONFIG_DIR_FILES})
source_group(go\\config\\compiler FILES ${GO_CONFIG_COMPILER_DIR_FILES})
source_group(go\\config\\platform FILES ${GO_CONFIG_PLATFORM_DIR_FILES})
source_group(go\\diagnostics FILES ${GO_DIAGNOSTICS_DIR_FILES})
source_group(go\\diagnostics\\benchmark FILES ${GO_DIAGNOSTICS_BENCHMARK_DIR_FILES})
source_group(go\\diagnostics\\log FILES ${GO_DIAGNOSTICS_LOG_DIR_FILES})
source_group(go\\diagnostics\\log\\detail FILES ${GO_DIAGNOSTICS_LOG_DETAIL_DIR_FILES})
source_group(go\\diagnostics\\log\\policy FILES ${GO_DIAGNOSTICS_LOG_POLICY_DIR_FILES})
source_group(go\\exception FILES ${GO_EXCEPTION_DIR_FILES})
source_group(go\\mvvm FILES ${GO_MVVM_DIR_FILES})
source_group(go\\mvvm\\iterator FILES ${GO_MVVM_ITERATOR_DIR_FILES})
source_group(go\\mvvm\\utility FILES ${GO_MVVM_UTILITY_DIR_FILES})
source_group(go\\property FILES ${GO_PROPERTY_DIR_FILES})
source_group(go\\property\\detail FILES ${GO_PROPERTY_DETAIL_DIR_FILES})
source_group(go\\property\\nameless FILES ${GO_PROPERTY_NAMELESS_DIR_FILES})
source_group(go\\property\\nameless\\detail FILES ${GO_PROPERTY_NAMELESS_DETAIL_DIR_FILES})
source_group(go\\property\\policy FILES ${GO_PROPERTY_POLICY_DIR_FILES})
source_group(go\\signals FILES ${GO_SIGNALS_DIR_FILES})
source_group(go\\string FILES ${GO_STRING_DIR_FILES})
source_group(go\\string\\detail FILES ${GO_STRING_DETAIL_DIR_FILES})
source_group(go\\type_traits FILES ${GO_TYPE_TRAITS_DIR_FILES})
source_group(go\\type_traits\\detail FILES ${GO_TYPE_TRAITS_DETAIL_DIR_FILES})
source_group(go\\utility FILES ${GO_UTILITY_DIR_FILES})
source_group(go\\utility\\container FILES ${GO_UTILITY_CONTAINER_DIR_FILES})
source_group(go\\utility\\iterator FILES ${GO_UTILITY_ITERATOR_DIR_FILES})
source_group(go\\utility\\range FILES ${GO_UTILITY_RANGE_DIR_FILES})
source_group(go\\.vs FILES ${GO_VS_DIR_FILES})
