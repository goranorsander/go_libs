#
#  CMakeLists.txt
#
#  Copyright 2016-2021 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    ########################################################
    #  libs/exception/test                                 #
    ########################################################

    set(PROJECT_STD_TEST_EXCEPTION_NAME ${STD_PROJECT_NAME_STR}_exception_tests)

    file(GLOB STD_TEST_EXCEPTION_SRC_FILES test/*.[chi]pp)
    add_executable(${PROJECT_STD_TEST_EXCEPTION_NAME} ${STD_TEST_EXCEPTION_SRC_FILES})
    set_target_properties(${PROJECT_STD_TEST_EXCEPTION_NAME} PROPERTIES FOLDER go_libs/std/tests)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_EXCEPTION_NAME}
            libgtest.a
            libgtest_main.a
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_STD_TEST_EXCEPTION_NAME}
                    libgtest.a
                    libgtest_main.a
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_STD_TEST_EXCEPTION_NAME}
                libgtest.a
                libgtest_main.a
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_EXCEPTION_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_EXCEPTION_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_EXCEPTION_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_EXCEPTION_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_STD_TEST_EXCEPTION_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_exception ${PROJECT_STD_TEST_EXCEPTION_NAME})

    source_group(Test_Suites FILES ${STD_TEST_EXCEPTION_SRC_FILES})

endif(BUILD_STD_TESTS)
