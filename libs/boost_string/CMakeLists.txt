#
#  CMakeLists.txt
#
#  Copyright 2020-2021 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_BOOST_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/boost_string/string_cast_example               #
    ########################################################

    set(PROJECT_BOOST_STRING_CAST_EXAMPLE ${BOOST_PROJECT_NAME_STR}_string_cast_example)

    file(GLOB BOOST_STRING_CAST_EXAMPLE_SRC_FILES string_cast_example/*.cpp)
    add_executable(${PROJECT_BOOST_STRING_CAST_EXAMPLE} ${BOOST_STRING_CAST_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_STRING_CAST_EXAMPLE} PROPERTIES FOLDER go_libs/boost/examples)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_STRING_CAST_EXAMPLE}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_STRING_CAST_EXAMPLE}
                    ${LIBBOOST_LOCALE}
                    ${LIBBOOST_SYSTEM}
                    ${CMAKE_THREAD_LIBS_INIT}
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_BOOST_STRING_CAST_EXAMPLE}
                ${LIBBOOST_LOCALE}
                ${LIBBOOST_SYSTEM}
                ${CMAKE_THREAD_LIBS_INIT}
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION GREATER 1900)
            # using Visual Studio 2017 C++
            # Boost.Config is almost always older than your compiler version, suppress Boost warning message.
            set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /D \"BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE\"" )
        endif(MSVC_VERSION GREATER 1900)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_STRING_CAST_EXAMPLE}
            ${CMAKE_THREAD_LIBS_INIT})
        target_link_libraries(${PROJECT_BOOST_STRING_CAST_EXAMPLE}
            debug ${LIBBOOST_LOCALE_DEBUG}
            optimized ${LIBBOOST_LOCALE})
        target_link_libraries(${PROJECT_BOOST_STRING_CAST_EXAMPLE}
            debug ${LIBBOOST_SYSTEM_DEBUG}
            optimized ${LIBBOOST_SYSTEM})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

endif(BUILD_BOOST_EXAMPLES)

if(BUILD_BOOST_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/boost_string/test                              #
    ########################################################

    set(PROJECT_BOOST_TEST_STRING_NAME ${BOOST_PROJECT_NAME_STR}_string_tests)

    file(GLOB BOOST_TEST_STRING_SRC_FILES test/*.[chi]pp)
    add_executable(${PROJECT_BOOST_TEST_STRING_NAME} ${BOOST_TEST_STRING_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_TEST_STRING_NAME} PROPERTIES FOLDER go_libs/boost/tests)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_TEST_STRING_NAME}
            libgtest.a
            libgtest_main.a
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${LIBBOOST_THREAD}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_TEST_STRING_NAME}
                    libgtest.a
                    libgtest_main.a
                    ${LIBBOOST_LOCALE}
                    ${LIBBOOST_SYSTEM}
                    ${LIBBOOST_THREAD}
                    ${CMAKE_THREAD_LIBS_INIT}
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_BOOST_TEST_STRING_NAME}
                libgtest.a
                libgtest_main.a
                ${LIBBOOST_LOCALE}
                ${LIBBOOST_SYSTEM}
                ${LIBBOOST_THREAD}
                ${CMAKE_THREAD_LIBS_INIT}
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION GREATER 1900)
            # using Visual Studio 2017 C++
            # Boost.Config is almost always older than your compiler version, suppress Boost warning message.
            set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /D \"BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE\"" )
        endif(MSVC_VERSION GREATER 1900)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_STRING_NAME} gtest)
            target_link_libraries(${PROJECT_BOOST_TEST_STRING_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_STRING_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_BOOST_TEST_STRING_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_BOOST_TEST_STRING_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_string ${PROJECT_BOOST_TEST_STRING_NAME})

    source_group(Test_Suites FILES ${BOOST_TEST_STRING_SRC_FILES})

endif(BUILD_BOOST_TESTS)
