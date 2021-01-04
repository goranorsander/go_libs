#
#  CMakeLists.txt
#
#  Copyright 2017-2020 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    #####################################################################
    #  libs/std_type_traits/fundamental_type_implicit_specializer_example #
    #####################################################################

    set(PROJECT_STD_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE ${STD_PROJECT_NAME_STR}_fundamental_type_implicit_specializer_example)

    file(GLOB STD_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE_SRC_FILES fundamental_type_implicit_specializer_example/*.cpp)
    add_executable(${PROJECT_STD_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE} ${STD_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_FUNDAMENTAL_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    ################################################################
    #  libs/std_type_traits/fundamental_type_specializer_example     #
    ################################################################

    set(PROJECT_STD_FUNDAMENTAL_TYPE_SPECIALIZER_EXAMPLE ${STD_PROJECT_NAME_STR}_fundamental_type_specializer_example)

    file(GLOB STD_FUNDAMENTAL_TYPE_SPECIALIZER_EXAMPLE_SRC_FILES fundamental_type_specializer_example/*.cpp)
    add_executable(${PROJECT_STD_FUNDAMENTAL_TYPE_SPECIALIZER_EXAMPLE} ${STD_FUNDAMENTAL_TYPE_SPECIALIZER_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_FUNDAMENTAL_TYPE_SPECIALIZER_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_FUNDAMENTAL_TYPE_SPECIALIZER_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

endif(BUILD_STD_EXAMPLES)

if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    ########################################################
    #  libs/std_type_traits/test                           #
    ########################################################

    set(PROJECT_STD_TEST_TYPE_TRAITS_NAME ${STD_PROJECT_NAME_STR}_type_traits_tests)

    file(GLOB STD_TEST_TYPE_TRAITS_SRC_FILES test/*.[chi]pp)
    add_executable(${PROJECT_STD_TEST_TYPE_TRAITS_NAME} ${STD_TEST_TYPE_TRAITS_SRC_FILES})
    set_target_properties(${PROJECT_STD_TEST_TYPE_TRAITS_NAME} PROPERTIES FOLDER go_libs/std/tests)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_TYPE_TRAITS_NAME}
            libgtest.a
            libgtest_main.a
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_STD_TEST_TYPE_TRAITS_NAME}
                    libgtest.a
                    libgtest_main.a
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_STD_TEST_TYPE_TRAITS_NAME}
                libgtest.a
                libgtest_main.a
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_TYPE_TRAITS_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_TYPE_TRAITS_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_TYPE_TRAITS_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_TYPE_TRAITS_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_STD_TEST_TYPE_TRAITS_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_std_type_traits ${PROJECT_STD_TEST_TYPE_TRAITS_NAME})

    source_group(Test_Suites FILES ${STD_TEST_TYPE_TRAITS_SRC_FILES})

endif(BUILD_STD_TESTS)
