#
#  CMakeLists.txt
#
#  Copyright 2016-2018 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_BOOST_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/mvvm/proxy_property_example                    #
    ########################################################

    set(PROJECT_BOOST_PROXY_PROPERTY_EXAMPLE ${BOOST_PROJECT_NAME_STR}_proxy_property_example)

    file(GLOB BOOST_PROXY_PROPERTY_EXAMPLE_SRC_FILES proxy_property_example/*.cpp)
    add_executable(${PROJECT_BOOST_PROXY_PROPERTY_EXAMPLE} ${BOOST_PROXY_PROPERTY_EXAMPLE_SRC_FILES})
    set_target_properties (${PROJECT_BOOST_PROXY_PROPERTY_EXAMPLE} PROPERTIES FOLDER go_libs/boost/examples)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_PROXY_PROPERTY_EXAMPLE}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_PROXY_PROPERTY_EXAMPLE}
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
            target_link_libraries(${PROJECT_BOOST_PROXY_PROPERTY_EXAMPLE}
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
        target_link_libraries(${PROJECT_BOOST_PROXY_PROPERTY_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    add_test(test_mvvm ${PROJECT_BOOST_PROXY_PROPERTY_EXAMPLE})

    ########################################################
    #  libs/mvvm/reference_property_example                #
    ########################################################

    set(PROJECT_BOOST_REFERENCE_PROPERTY_EXAMPLE ${BOOST_PROJECT_NAME_STR}_reference_property_example)

    file(GLOB BOOST_REFERENCE_PROPERTY_EXAMPLE_SRC_FILES reference_property_example/*.cpp)
    add_executable(${PROJECT_BOOST_REFERENCE_PROPERTY_EXAMPLE} ${BOOST_REFERENCE_PROPERTY_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_REFERENCE_PROPERTY_EXAMPLE} PROPERTIES FOLDER go_libs/boost/examples)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_REFERENCE_PROPERTY_EXAMPLE}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_REFERENCE_PROPERTY_EXAMPLE}
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
            target_link_libraries(${PROJECT_BOOST_REFERENCE_PROPERTY_EXAMPLE}
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
        target_link_libraries(${PROJECT_BOOST_REFERENCE_PROPERTY_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    add_test(test_mvvm ${PROJECT_BOOST_REFERENCE_PROPERTY_EXAMPLE})

    ########################################################
    #  libs/mvvm/value_property_example                    #
    ########################################################

    set(PROJECT_BOOST_VALUE_PROPERTY_EXAMPLE ${BOOST_PROJECT_NAME_STR}_value_property_example)

    file(GLOB BOOST_VALUE_PROPERTY_EXAMPLE_SRC_FILES value_property_example/*.cpp)
    add_executable(${PROJECT_BOOST_VALUE_PROPERTY_EXAMPLE} ${BOOST_VALUE_PROPERTY_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_VALUE_PROPERTY_EXAMPLE} PROPERTIES FOLDER go_libs/boost/examples)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_VALUE_PROPERTY_EXAMPLE}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_VALUE_PROPERTY_EXAMPLE}
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
            target_link_libraries(${PROJECT_BOOST_VALUE_PROPERTY_EXAMPLE}
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
        target_link_libraries(${PROJECT_BOOST_VALUE_PROPERTY_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    add_test(test_mvvm ${PROJECT_BOOST_VALUE_PROPERTY_EXAMPLE})

endif(BUILD_BOOST_EXAMPLES)

if(BUILD_BOOST_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/boost_property/test                            #
    ########################################################

    set(PROJECT_BOOST_TEST_PROPERTY_NAME ${BOOST_PROJECT_NAME_STR}_property_tests)

    file(GLOB BOOST_TEST_PROPERTY_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_BOOST_TEST_PROPERTY_NAME} ${BOOST_TEST_PROPERTY_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_TEST_PROPERTY_NAME} PROPERTIES FOLDER go_libs/boost/tests)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
            libgtest.a
            libgtest_main.a
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
                    libgtest.a
                    libgtest_main.a
                    ${LIBBOOST_LOCALE}
                    ${LIBBOOST_SYSTEM}
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
                libgtest.a
                libgtest_main.a
                ${LIBBOOST_LOCALE}
                ${LIBBOOST_SYSTEM}
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION GREATER 1900)
            # using Visual Studio 2017 C++
            # Boost.Config is almost always older than your compiler version, suppress Boost warning message.
            set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /D \"BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE\"" )
        endif(MSVC_VERSION GREATER 1900)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} gtest)
            target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_property ${PROJECT_BOOST_TEST_PROPERTY_NAME})

endif(BUILD_BOOST_TESTS)
