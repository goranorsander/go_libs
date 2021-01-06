#
#  CMakeLists.txt
#
#  Copyright 2018-2021 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_BOOST_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/boost_diagnostics/log_example                  #
    ########################################################

    set(PROJECT_BOOST_LOG_EXAMPLE ${BOOST_PROJECT_NAME_STR}_log_example)

    file(GLOB BOOST_LOG_EXAMPLE_SRC_FILES log_example/*.cpp)
    add_executable(${PROJECT_BOOST_LOG_EXAMPLE} ${BOOST_LOG_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_LOG_EXAMPLE} PROPERTIES FOLDER go_libs/boost/examples)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_LOG_EXAMPLE}
            ${LIBBOOST_CHRONO}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${LIBBOOST_THREAD}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_LOG_EXAMPLE}
                    ${LIBBOOST_CHRONO}
                    ${LIBBOOST_LOCALE}
                    ${LIBBOOST_SYSTEM}
                    ${LIBBOOST_THREAD}
                    ${CMAKE_THREAD_LIBS_INIT}
                    )
                set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-write-strings" )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_BOOST_LOG_EXAMPLE}
                ${LIBBOOST_CHRONO}
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
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_LOG_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/boost_diagnostics/stopwatch_example            #
    ########################################################

    set(PROJECT_BOOST_STOPWATCH_EXAMPLE ${BOOST_PROJECT_NAME_STR}_stopwatch_example)

    file(GLOB BOOST_STOPWATCH_EXAMPLE_SRC_FILES stopwatch_example/*.cpp)
    add_executable(${PROJECT_BOOST_STOPWATCH_EXAMPLE} ${BOOST_STOPWATCH_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_STOPWATCH_EXAMPLE} PROPERTIES FOLDER go_libs/boost/examples)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_STOPWATCH_EXAMPLE}
            ${LIBBOOST_CHRONO}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${LIBBOOST_THREAD}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_STOPWATCH_EXAMPLE}
                    ${LIBBOOST_CHRONO}
                    ${LIBBOOST_LOCALE}
                    ${LIBBOOST_SYSTEM}
                    ${LIBBOOST_THREAD}
                    ${CMAKE_THREAD_LIBS_INIT}
                    )
                set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-write-strings" )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_BOOST_STOPWATCH_EXAMPLE}
                ${LIBBOOST_CHRONO}
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
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_STOPWATCH_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    ########################################################
    #  libs/boost_diagnostics/wlog_example                 #
    ########################################################

    set(PROJECT_BOOST_WLOG_EXAMPLE ${BOOST_PROJECT_NAME_STR}_wlog_example)

    file(GLOB BOOST_WLOG_EXAMPLE_SRC_FILES wlog_example/*.cpp)
    add_executable(${PROJECT_BOOST_WLOG_EXAMPLE} ${BOOST_WLOG_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_WLOG_EXAMPLE} PROPERTIES FOLDER go_libs/boost/examples)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_WLOG_EXAMPLE}
            ${LIBBOOST_CHRONO}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${LIBBOOST_THREAD}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_WLOG_EXAMPLE}
                    ${LIBBOOST_CHRONO}
                    ${LIBBOOST_LOCALE}
                    ${LIBBOOST_SYSTEM}
                    ${LIBBOOST_THREAD}
                    ${CMAKE_THREAD_LIBS_INIT}
                    )
                set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-write-strings" )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_BOOST_WLOG_EXAMPLE}
                ${LIBBOOST_CHRONO}
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
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_WLOG_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

endif(BUILD_BOOST_EXAMPLES)

if(BUILD_BOOST_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/boost_diagnostics/test                         #
    ########################################################

    set(PROJECT_BOOST_TEST_DIAGNOSTICS_NAME ${BOOST_PROJECT_NAME_STR}_diagnostics_tests)

    file(GLOB BOOST_TEST_DIAGNOSTICS_SRC_FILES test/*.[chi]pp)
    add_executable(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME} ${BOOST_TEST_DIAGNOSTICS_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME} PROPERTIES FOLDER go_libs/boost/tests)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME}
            libgtest.a
            libgtest_main.a
            ${LIBBOOST_CHRONO}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${LIBBOOST_THREAD}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME}
                    libgtest.a
                    libgtest_main.a
                    ${LIBBOOST_CHRONO}
                    ${LIBBOOST_LOCALE}
                    ${LIBBOOST_SYSTEM}
                    ${LIBBOOST_THREAD}
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME}
                libgtest.a
                libgtest_main.a
                ${LIBBOOST_CHRONO}
                ${LIBBOOST_LOCALE}
                ${LIBBOOST_SYSTEM}
                ${LIBBOOST_THREAD}
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION GREATER 1900)
            # using Visual Studio 2017 C++
            # Boost.Config is almost always older than your compiler version, suppress Boost warning message.
            set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /D \"BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE\"" )
        endif(MSVC_VERSION GREATER 1900)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME} gtest)
            target_link_libraries(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_diagnostics ${PROJECT_BOOST_TEST_DIAGNOSTICS_NAME})

    source_group(Test_Suites FILES ${BOOST_TEST_DIAGNOSTICS_SRC_FILES})

endif(BUILD_BOOST_TESTS)
