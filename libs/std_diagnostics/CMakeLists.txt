#
#  CMakeLists.txt
#
#  Copyright 2018-2020 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    if(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-write-strings" )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        endif(WIN32)
    endif(CMAKE_COMPILER_IS_GNUCC)

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
    #  libs/diagnostics/stopwatch_example                  #
    ########################################################

    set(PROJECT_STD_STOPWATCH_EXAMPLE ${STD_PROJECT_NAME_STR}_stopwatch_example)

    file(GLOB STD_STOPWATCH_EXAMPLE_SRC_FILES stopwatch_example/*.cpp)
    add_executable(${PROJECT_STD_STOPWATCH_EXAMPLE} ${STD_STOPWATCH_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_STOPWATCH_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_STOPWATCH_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

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

if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    ########################################################
    #  libs/diagnostics/test                               #
    ########################################################

    set(PROJECT_STD_TEST_DIAGNOSTICS_NAME ${STD_PROJECT_NAME_STR}_diagnostics_tests)

    file(GLOB STD_TEST_DIAGNOSTICS_SRC_FILES test/*.[chi]pp)
    add_executable(${PROJECT_STD_TEST_DIAGNOSTICS_NAME} ${STD_TEST_DIAGNOSTICS_SRC_FILES})
    set_target_properties(${PROJECT_STD_TEST_DIAGNOSTICS_NAME} PROPERTIES FOLDER go_libs/std/tests)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_DIAGNOSTICS_NAME}
            libgtest.a
            libgtest_main.a
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_STD_TEST_DIAGNOSTICS_NAME}
                    libgtest.a
                    libgtest_main.a
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_STD_TEST_DIAGNOSTICS_NAME}
                libgtest.a
                libgtest_main.a
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_DIAGNOSTICS_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_DIAGNOSTICS_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_DIAGNOSTICS_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_DIAGNOSTICS_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_STD_TEST_DIAGNOSTICS_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_diagnostics ${PROJECT_STD_TEST_DIAGNOSTICS_NAME})

    source_group(Test_Suites FILES ${STD_TEST_DIAGNOSTICS_SRC_FILES})

endif(BUILD_STD_TESTS)
