#
#  CMakeLists.txt
#
#  Copyright 2019-2021 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_BOOST_RND)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  rnd/boost_rnd/container_benchmark                   #
    ########################################################

    set(PROJECT_BOOST_CONTAINER_BENCHMARK ${BOOST_PROJECT_NAME_STR}_container_benchmark)

    file(GLOB BOOST_CONTAINER_BENCHMARK_SRC_FILES container_benchmark/*.cpp)
    add_executable(${PROJECT_BOOST_CONTAINER_BENCHMARK} ${BOOST_CONTAINER_BENCHMARK_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_CONTAINER_BENCHMARK} PROPERTIES FOLDER rnd/boost)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_CONTAINER_BENCHMARK}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${LIBBOOST_THREAD}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_CONTAINER_BENCHMARK}
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
            target_link_libraries(${PROJECT_BOOST_CONTAINER_BENCHMARK}
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
        target_link_libraries(${PROJECT_BOOST_CONTAINER_BENCHMARK} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    #########################################################
    #  rnd/boost_rnd/fundamental_type_specializer_benchmark #
    #########################################################

    set(PROJECT_BOOST_FUNDAMENTAL_TYPE_SPECIALIZER_BENCHMARK ${BOOST_PROJECT_NAME_STR}_fundamental_type_specializer_benchmark)

    file(GLOB BOOST_FUNDAMENTAL_TYPE_SPECIALIZER_BENCHMARK_SRC_FILES fundamental_type_specializer_benchmark/*.cpp)
    add_executable(${PROJECT_BOOST_FUNDAMENTAL_TYPE_SPECIALIZER_BENCHMARK} ${BOOST_FUNDAMENTAL_TYPE_SPECIALIZER_BENCHMARK_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_FUNDAMENTAL_TYPE_SPECIALIZER_BENCHMARK} PROPERTIES FOLDER rnd/boost)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_FUNDAMENTAL_TYPE_SPECIALIZER_BENCHMARK}
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
                target_link_libraries(${PROJECT_BOOST_FUNDAMENTAL_TYPE_SPECIALIZER_BENCHMARK}
                    ${LIBBOOST_CHRONO}
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
            target_link_libraries(${PROJECT_BOOST_FUNDAMENTAL_TYPE_SPECIALIZER_BENCHMARK}
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
        target_link_libraries(${PROJECT_BOOST_FUNDAMENTAL_TYPE_SPECIALIZER_BENCHMARK} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    ########################################################
    #  rnd/boost_rnd/lockable_benchmark                    #
    ########################################################

    set(PROJECT_BOOST_LOCKABLE_BENCHMARK ${BOOST_PROJECT_NAME_STR}_lockable_benchmark)

    file(GLOB BOOST_LOCKABLE_BENCHMARK_SRC_FILES lockable_benchmark/*.cpp)
    add_executable(${PROJECT_BOOST_LOCKABLE_BENCHMARK} ${BOOST_LOCKABLE_BENCHMARK_SRC_FILES})
    set_target_properties(${PROJECT_BOOST_LOCKABLE_BENCHMARK} PROPERTIES FOLDER rnd/boost)

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_LOCKABLE_BENCHMARK}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${LIBBOOST_THREAD}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_LOCKABLE_BENCHMARK}
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
            target_link_libraries(${PROJECT_BOOST_LOCKABLE_BENCHMARK}
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
        target_link_libraries(${PROJECT_BOOST_LOCKABLE_BENCHMARK} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

endif(BUILD_BOOST_RND)
