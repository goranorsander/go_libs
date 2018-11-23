#
#  CMakeLists.txt
#
#  Copyright 2017-2018 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    ########################################################
    #  libs/utility/erase_example                          #
    ########################################################

    set(PROJECT_STD_ERASE_EXAMPLE ${STD_PROJECT_NAME_STR}_erase_example)

    file(GLOB STD_ERASE_EXAMPLE_SRC_FILES erase_example/*.cpp)
    add_executable(${PROJECT_STD_ERASE_EXAMPLE} ${STD_ERASE_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_ERASE_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_ERASE_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    #############################################################
    #  libs/utility/primitive_type_implicit_specializer_example #
    #############################################################

    set(PROJECT_STD_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE ${STD_PROJECT_NAME_STR}_primitive_type_implicit_specializer_example)

    file(GLOB STD_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE_SRC_FILES primitive_type_implicit_specializer_example/*.cpp)
    add_executable(${PROJECT_STD_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE} ${STD_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_PRIMITIVE_TYPE_IMPLICIT_SPECIALIZER_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    ########################################################
    #  libs/utility/primitive_type_specializer_example     #
    ########################################################

    set(PROJECT_STD_PRIMITIVE_TYPE_SPECIALIZER_EXAMPLE ${STD_PROJECT_NAME_STR}_primitive_type_specializer_example)

    file(GLOB STD_PRIMITIVE_TYPE_SPECIALIZER_EXAMPLE_SRC_FILES primitive_type_specializer_example/*.cpp)
    add_executable(${PROJECT_STD_PRIMITIVE_TYPE_SPECIALIZER_EXAMPLE} ${STD_PRIMITIVE_TYPE_SPECIALIZER_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_PRIMITIVE_TYPE_SPECIALIZER_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_PRIMITIVE_TYPE_SPECIALIZER_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    ########################################################
    #  libs/utility/scope_guard_example                    #
    ########################################################

    set(PROJECT_STD_SCOPE_GUARD_EXAMPLE ${STD_PROJECT_NAME_STR}_scope_guard_example)

    file(GLOB STD_SCOPE_GUARD_EXAMPLE_SRC_FILES scope_guard_example/*.cpp)
    add_executable(${PROJECT_STD_SCOPE_GUARD_EXAMPLE} ${STD_SCOPE_GUARD_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_SCOPE_GUARD_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_SCOPE_GUARD_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    ########################################################
    #  libs/utility/scope_guard_new_example                #
    ########################################################

    set(PROJECT_STD_SCOPE_GUARD_NEW_EXAMPLE ${STD_PROJECT_NAME_STR}_scope_guard_new_example)

    file(GLOB STD_SCOPE_GUARD_NEW_EXAMPLE_SRC_FILES scope_guard_new_example/*.cpp)
    add_executable(${PROJECT_STD_SCOPE_GUARD_NEW_EXAMPLE} ${STD_SCOPE_GUARD_NEW_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_SCOPE_GUARD_NEW_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_SCOPE_GUARD_NEW_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    ########################################################
    #  libs/utility/string_cast_example                    #
    ########################################################

    set(PROJECT_STD_STRING_CAST_EXAMPLE ${STD_PROJECT_NAME_STR}_string_cast_example)

    file(GLOB STD_STRING_CAST_EXAMPLE_SRC_FILES string_cast_example/*.cpp)
    add_executable(${PROJECT_STD_STRING_CAST_EXAMPLE} ${STD_STRING_CAST_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_STRING_CAST_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_STRING_CAST_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    ########################################################
    #  libs/utility/try_move_backward_example              #
    ########################################################

    set(PROJECT_STD_TRY_MOVE_BACKWARD_EXAMPLE ${STD_PROJECT_NAME_STR}_try_move_backward_example)

    file(GLOB STD_TRY_MOVE_BACKWARD_EXAMPLE_SRC_FILES try_move_backward_example/*.cpp)
    add_executable(${PROJECT_STD_TRY_MOVE_BACKWARD_EXAMPLE} ${STD_TRY_MOVE_BACKWARD_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_TRY_MOVE_BACKWARD_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_TRY_MOVE_BACKWARD_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    ########################################################
    #  libs/utility/value_guard_example                    #
    ########################################################

    set(PROJECT_STD_VALUE_GUARD_EXAMPLE ${STD_PROJECT_NAME_STR}_value_guard_example)

    file(GLOB STD_VALUE_GUARD_EXAMPLE_SRC_FILES value_guard_example/*.cpp)
    add_executable(${PROJECT_STD_VALUE_GUARD_EXAMPLE} ${STD_VALUE_GUARD_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_VALUE_GUARD_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_VALUE_GUARD_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

endif(BUILD_STD_EXAMPLES)

if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    ########################################################
    #  libs/utility/test                                   #
    ########################################################

    set(PROJECT_STD_TEST_UTILITY_NAME ${STD_PROJECT_NAME_STR}_utility_tests)

    file(GLOB STD_TEST_UTILITY_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_STD_TEST_UTILITY_NAME} ${STD_TEST_UTILITY_SRC_FILES})
    set_target_properties(${PROJECT_STD_TEST_UTILITY_NAME} PROPERTIES FOLDER go_libs/std/tests)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_UTILITY_NAME}
            libgtest.a
            libgtest_main.a
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_STD_TEST_UTILITY_NAME}
                    libgtest.a
                    libgtest_main.a
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_STD_TEST_UTILITY_NAME}
                libgtest.a
                libgtest_main.a
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_UTILITY_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_UTILITY_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_UTILITY_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_UTILITY_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_STD_TEST_UTILITY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_utility ${PROJECT_STD_TEST_UTILITY_NAME})

endif(BUILD_STD_TESTS)
