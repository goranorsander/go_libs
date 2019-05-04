#
#  CMakeLists.txt
#
#  Copyright 2019 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

set(PROJECT_GTEST_EXTENSIONS_NAME gtest_extensions)

file(GLOB GTEST_EXTENSIONS_GO_GTEST_DIR_FILES ./go_gtest/*.hpp)

add_library(${PROJECT_GTEST_EXTENSIONS_NAME} STATIC
    ${GTEST_EXTENSIONS_GO_GTEST_DIR_FILES}
)

set_target_properties(${PROJECT_GTEST_EXTENSIONS_NAME} PROPERTIES LINKER_LANGUAGE CXX FOLDER go_libs/gtest_extensions)

source_group(go_gtest FILES ${GTEST_EXTENSIONS_GO_GTEST_DIR_FILES})
