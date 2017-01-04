if(BUILD_BOOST_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/boost_property/test                            #
    ########################################################

    set(PROJECT_BOOST_TEST_PROPERTY_NAME ${BOOST_PROJECT_NAME_STR}_property_tests)

    file(GLOB BOOST_TEST_PROPERTY_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_BOOST_TEST_PROPERTY_NAME} ${BOOST_TEST_PROPERTY_SRC_FILES})

    if(NOT WIN32)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
            libgtest.a
            libgtest_main.a
            ${LIBBOOST_SYSTEM}
            )
    else(NOT WIN32)
        if(MSYS OR MINGW)
            find_package(Threads)
            target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
                libgtest.a
                libgtest_main.a
                ${LIBBOOST_SYSTEM}
                )
        else(MSYS OR MINGW)
            if(MSVC AND (MSVC_VERSION LESS 1800))
                target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} gtest)
                target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} gtest_main)
            else(MSVC AND (MSVC_VERSION LESS 1800))
                target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
                    debug Debug/gtest
                    optimized /Release/gtest
                    )
                target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
                    debug Debug/gtest_main
                    optimized Release/gtest_main
                    )
            endif(MSVC AND (MSVC_VERSION LESS 1800))
        endif(MSYS OR MINGW)
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_property ${PROJECT_BOOST_TEST_PROPERTY_NAME})

endif(BUILD_BOOST_TESTS)
