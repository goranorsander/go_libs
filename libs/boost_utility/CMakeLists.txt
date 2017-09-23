#
#  CMakeLists.txt
#
#  Copyright 2017 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_BOOST_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/boost_utility/test                             #
    ########################################################

    set(PROJECT_BOOST_TEST_UTILITY_NAME ${BOOST_PROJECT_NAME_STR}_utility_tests)

    file(GLOB BOOST_TEST_UTILITY_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_BOOST_TEST_UTILITY_NAME} ${BOOST_TEST_UTILITY_SRC_FILES})

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_TEST_UTILITY_NAME}
            libgtest.a
            libgtest_main.a
			${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_TEST_UTILITY_NAME}
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
            target_link_libraries(${PROJECT_BOOST_TEST_UTILITY_NAME}
                libgtest.a
                libgtest_main.a
				${LIBBOOST_LOCALE}
                ${LIBBOOST_SYSTEM}
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_UTILITY_NAME} gtest)
            target_link_libraries(${PROJECT_BOOST_TEST_UTILITY_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_UTILITY_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_BOOST_TEST_UTILITY_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_BOOST_TEST_UTILITY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_utility ${PROJECT_BOOST_TEST_UTILITY_NAME})

endif(BUILD_BOOST_TESTS)
