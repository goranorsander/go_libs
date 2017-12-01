#
#  CMakeLists.txt
#
#  Copyright 2017 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_BOOST_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/boost_mvvm/boost_signals_example               #
    ########################################################

    set(PROJECT_BOOST_SIGNALS_EXAMPLE ${BOOST_PROJECT_NAME_STR}_signals_example)

    file(GLOB BOOST_SIGNALS_EXAMPLE_SRC_FILES boost_signals_example/*.cpp)
    add_executable(${PROJECT_BOOST_SIGNALS_EXAMPLE} ${BOOST_SIGNALS_EXAMPLE_SRC_FILES})

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_SIGNALS_EXAMPLE}
            ${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            ${CMAKE_THREAD_LIBS_INIT}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_SIGNALS_EXAMPLE}
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
            target_link_libraries(${PROJECT_BOOST_SIGNALS_EXAMPLE}
                ${LIBBOOST_LOCALE}
                ${LIBBOOST_SYSTEM}
                ${CMAKE_THREAD_LIBS_INIT}
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_SIGNALS_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    add_test(test_mvvm ${PROJECT_BOOST_SIGNALS_EXAMPLE})

endif(BUILD_BOOST_EXAMPLES)
