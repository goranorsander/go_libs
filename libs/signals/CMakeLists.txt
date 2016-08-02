if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/signals/test                                   #
    ########################################################

    set(PROJECT_STD_TEST_SIGNALS_NAME ${STD_PROJECT_NAME_STR}_signals_tests)

    file(GLOB STD_TEST_SIGNALS_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_STD_TEST_SIGNALS_NAME} ${STD_TEST_SIGNALS_SRC_FILES})

    if((NOT WIN32) OR (WIN32 AND (MSYS OR MINGW)))
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME}
            libgtest.a
            libgtest_main.a
            )
    else((NOT WIN32) OR (WIN32 AND (MSYS OR MINGW)))
        if(MSVC AND (MSVC_VERSION LESS 1800))
            target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME} gtest_main)
        else(MSVC AND (MSVC_VERSION LESS 1800))
            target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME}
                debug Debug/gtest
                optimized /Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME}
                debug Debug/gtest_main
                optimized Release/gtest_main
                )
        endif(MSVC AND (MSVC_VERSION LESS 1800))
    endif((NOT WIN32) OR (WIN32 AND (MSYS OR MINGW)))

    target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_signals ${PROJECT_STD_TEST_SIGNALS_NAME})

endif(BUILD_STD_TESTS)
