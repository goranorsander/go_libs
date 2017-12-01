#
#  CMakeLists.txt
#
#  Copyright 2016-2017 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    ########################################################
    #  libs/mvvm/std_proxy_property_example                #
    ########################################################

    set(PROJECT_STD_PROXY_PROPERTY_EXAMPLE  ${STD_PROJECT_NAME_STR}_proxy_property_example)

    file(GLOB STD_PROXY_PROPERTY_EXAMPLE_SRC_FILES std_proxy_property_example/*.cpp)
    add_executable(${PROJECT_STD_PROXY_PROPERTY_EXAMPLE} ${STD_PROXY_PROPERTY_EXAMPLE_SRC_FILES})
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_PROXY_PROPERTY_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_STD_PROXY_PROPERTY_EXAMPLE})

    ########################################################
    #  libs/mvvm/std_reference_property_example            #
    ########################################################

    set(PROJECT_STD_REFERENCE_PROPERTY_EXAMPLE ${STD_PROJECT_NAME_STR}_reference_property_example)

    file(GLOB STD_REFERENCE_PROPERTY_EXAMPLE_SRC_FILES std_reference_property_example/*.cpp)
    add_executable(${PROJECT_STD_REFERENCE_PROPERTY_EXAMPLE} ${STD_REFERENCE_PROPERTY_EXAMPLE_SRC_FILES})
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_REFERENCE_PROPERTY_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_STD_REFERENCE_PROPERTY_EXAMPLE})

    ########################################################
    #  libs/mvvm/std_value_property_example                #
    ########################################################

    set(PROJECT_STD_VALUE_PROPERTY_EXAMPLE ${STD_PROJECT_NAME_STR}_value_property_example)

    file(GLOB STD_VALUE_PROPERTY_EXAMPLE_SRC_FILES std_value_property_example/*.cpp)
    add_executable(${PROJECT_STD_VALUE_PROPERTY_EXAMPLE} ${STD_VALUE_PROPERTY_EXAMPLE_SRC_FILES})
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_VALUE_PROPERTY_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_STD_VALUE_PROPERTY_EXAMPLE})

endif(BUILD_STD_EXAMPLES)

if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    ########################################################
    #  libs/property/test                                  #
    ########################################################

    set(PROJECT_STD_TEST_PROPERTY_NAME ${STD_PROJECT_NAME_STR}_property_tests)

    file(GLOB STD_TEST_PROPERTY_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_STD_TEST_PROPERTY_NAME} ${STD_TEST_PROPERTY_SRC_FILES})

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
            libgtest.a
            libgtest_main.a
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
                    libgtest.a
                    libgtest_main.a
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
                libgtest.a
                libgtest_main.a
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_property ${PROJECT_STD_TEST_PROPERTY_NAME})

endif(BUILD_STD_TESTS)
