#
#  CMakeLists.txt
#
#  Copyright 2020-2021 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    ########################################################
    #  libs/std_string/string_cast_example                 #
    ########################################################

    set(PROJECT_STD_STRING_CAST_EXAMPLE ${STD_PROJECT_NAME_STR}_string_cast_example)

    file(GLOB STD_STRING_CAST_EXAMPLE_SRC_FILES string_cast_example/*.cpp)
    add_executable(${PROJECT_STD_STRING_CAST_EXAMPLE} ${STD_STRING_CAST_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_STRING_CAST_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_STRING_CAST_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

endif(BUILD_STD_EXAMPLES)

if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    ########################################################
    #  libs/std_string/test                                #
    ########################################################

    set(PROJECT_STD_TEST_STRING_NAME ${STD_PROJECT_NAME_STR}_string_tests)

    file(GLOB STD_TEST_STRING_SRC_FILES test/*.[chi]pp)
    add_executable(${PROJECT_STD_TEST_STRING_NAME} ${STD_TEST_STRING_SRC_FILES})
    set_target_properties(${PROJECT_STD_TEST_STRING_NAME} PROPERTIES FOLDER go_libs/std/tests)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_STRING_NAME}
            libgtest.a
            libgtest_main.a
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_STD_TEST_STRING_NAME}
                    libgtest.a
                    libgtest_main.a
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_STD_TEST_STRING_NAME}
                libgtest.a
                libgtest_main.a
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_STRING_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_STRING_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_STRING_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_STRING_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_STD_TEST_STRING_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_string ${PROJECT_STD_TEST_STRING_NAME})

    source_group(Test_Suites FILES ${STD_TEST_STRING_SRC_FILES})

endif(BUILD_STD_TESTS)
