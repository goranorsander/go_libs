#
#  CMakeLists.txt
#
#  Copyright 2021 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

set(PROJECT_TEST_FRAMEWORK_NAME test_framework)

include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})

file(GLOB TEST_FRAMEWORK_GO_BOOST_TEST_DIR_FILES ./go_boost_test/*.hpp)
file(GLOB TEST_FRAMEWORK_GO_TEST_DIR_FILES ./go_test/*.hpp)

add_library(${PROJECT_TEST_FRAMEWORK_NAME} STATIC
    ${TEST_FRAMEWORK_GO_BOOST_TEST_DIR_FILES}
    ${TEST_FRAMEWORK_GO_TEST_DIR_FILES}
)

set_target_properties(${PROJECT_TEST_FRAMEWORK_NAME} PROPERTIES LINKER_LANGUAGE CXX FOLDER go_libs/test_framework)

source_group(go_boost_test FILES ${TEST_FRAMEWORK_GO_BOOST_TEST_DIR_FILES})
source_group(go_test FILES ${TEST_FRAMEWORK_GO_TEST_DIR_FILES})
