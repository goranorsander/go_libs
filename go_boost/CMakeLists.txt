#
#  CMakeLists.txt
#
#  Copyright 2016-2018 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

set(PROJECT_GO_LIBS_BOOST_NAME GO_libraries_boost)

file(GLOB GO_BOOST_DIR_FILES ./*.hpp)
file(GLOB GO_BOOST_CONFIG_DIR_FILES ./config/*.hpp)
file(GLOB GO_BOOST_CONFIG_COMPILER_DIR_FILES ./config/compiler/*.hpp)
file(GLOB GO_BOOST_CONFIG_PLATFORM_DIR_FILES ./config/platform/*.hpp)
file(GLOB GO_BOOST_EXCEPTION_DIR_FILES ./exception/*.hpp)
file(GLOB GO_BOOST_MVVM_DIR_FILES ./mvvm/*.hpp)
file(GLOB GO_BOOST_MVVM_UTILITY_DIR_FILES ./mvvm/utility/*.hpp)
file(GLOB GO_BOOST_PROPERTY_DIR_FILES ./property/*.hpp)
file(GLOB GO_BOOST_PROPERTY_DETAIL_DIR_FILES ./property/detail/*.hpp)
file(GLOB GO_BOOST_PROPERTY_NAMELESS_DIR_FILES ./property/nameless/*.hpp)
file(GLOB GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR_FILES ./property/nameless/detail/*.hpp)
file(GLOB GO_BOOST_PROPERTY_POLICY_DIR_FILES ./property/policy/*.hpp)
file(GLOB GO_BOOST_DIR_SIGNALS_FILES ./signals/*.hpp)
file(GLOB GO_BOOST_DIR_UTILITY_FILES ./utility/*.hpp)
file(GLOB GO_BOOST_DIR_UTILITY_ITERATOR_FILES ./utility/iterator/*.hpp)
file(GLOB GO_BOOST_DIR_UTILITY_STRING_FILES ./utility/string/*.hpp)
file(GLOB GO_BOOST_DIR_UTILITY_STRING_DETAIL_FILES ./utility/string/detail/*.hpp)

add_library(${PROJECT_GO_LIBS_BOOST_NAME} STATIC
    ${GO_BOOST_DIR_FILES}
    ${GO_BOOST_CONFIG_DIR_FILES}
    ${GO_BOOST_CONFIG_COMPILER_DIR_FILES}
    ${GO_BOOST_CONFIG_PLATFORM_DIR_FILES}
    ${GO_BOOST_EXCEPTION_DIR_FILES}
    ${GO_BOOST_MVVM_DIR_FILES}
    ${GO_BOOST_MVVM_UTILITY_DIR_FILES}
    ${GO_BOOST_PROPERTY_DIR_FILES}
    ${GO_BOOST_PROPERTY_DETAIL_DIR_FILES}
    ${GO_BOOST_PROPERTY_NAMELESS_DIR_FILES}
    ${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR_FILES}
    ${GO_BOOST_PROPERTY_POLICY_DIR_FILES}
    ${GO_BOOST_DIR_SIGNALS_FILES}
    ${GO_BOOST_DIR_UTILITY_FILES}
    ${GO_BOOST_DIR_UTILITY_ITERATOR_FILES}
    ${GO_BOOST_DIR_UTILITY_STRING_FILES}
    ${GO_BOOST_DIR_UTILITY_STRING_DETAIL_FILES}
)

set_target_properties(${PROJECT_GO_LIBS_BOOST_NAME} PROPERTIES LINKER_LANGUAGE CXX FOLDER go_libs/boost/libs)

source_group(go_boost FILES ${GO_BOOST_DIR_FILES})
source_group(go_boost\\config FILES ${GO_BOOST_CONFIG_DIR_FILES})
source_group(go_boost\\config\\compiler FILES ${GO_BOOST_CONFIG_COMPILER_DIR_FILES})
source_group(go_boost\\config\\platform FILES ${GO_BOOST_CONFIG_PLATFORM_DIR_FILES})
source_group(go_boost\\exception FILES ${GO_BOOST_EXCEPTION_DIR_FILES})
source_group(go_boost\\mvvm FILES ${GO_BOOST_MVVM_DIR_FILES})
source_group(go_boost\\mvvm\\utility FILES ${GO_BOOST_MVVM_UTILITY_DIR_FILES})
source_group(go_boost\\property FILES ${GO_BOOST_PROPERTY_DIR_FILES})
source_group(go_boost\\property\\detail FILES ${GO_BOOST_PROPERTY_DETAIL_DIR_FILES})
source_group(go_boost\\property\\nameless FILES ${GO_BOOST_PROPERTY_NAMELESS_DIR_FILES})
source_group(go_boost\\property\\nameless\\detail FILES ${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR_FILES})
source_group(go_boost\\property\\policy FILES ${GO_BOOST_PROPERTY_POLICY_DIR_FILES})
source_group(go_boost\\signals FILES ${GO_BOOST_DIR_SIGNALS_FILES})
source_group(go_boost\\utility FILES ${GO_BOOST_DIR_UTILITY_FILES})
source_group(go_boost\\utility\\iterator FILES ${GO_BOOST_DIR_UTILITY_ITERATOR_FILES})
source_group(go_boost\\utility\\string FILES ${GO_BOOST_DIR_UTILITY_STRING_FILES})
source_group(go_boost\\utility\\string\\detail FILES ${GO_BOOST_DIR_UTILITY_STRING_DETAIL_FILES})
