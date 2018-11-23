#
#  CMakeLists.txt
#
#  Copyright 2018 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    ########################################################
    #  libs/diagnostics/log_example                        #
    ########################################################

    set(PROJECT_STD_LOG_EXAMPLE ${STD_PROJECT_NAME_STR}_log_example)

    file(GLOB STD_LOG_EXAMPLE_SRC_FILES log_example/*.cpp)
    add_executable(${PROJECT_STD_LOG_EXAMPLE} ${STD_LOG_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_LOG_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_LOG_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    ########################################################
    #  libs/diagnostics/wlog_example                       #
    ########################################################

    set(PROJECT_STD_WLOG_EXAMPLE ${STD_PROJECT_NAME_STR}_wlog_example)

    file(GLOB STD_WLOG_EXAMPLE_SRC_FILES wlog_example/*.cpp)
    add_executable(${PROJECT_STD_WLOG_EXAMPLE} ${STD_WLOG_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_WLOG_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_WLOG_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

endif(BUILD_STD_EXAMPLES)
