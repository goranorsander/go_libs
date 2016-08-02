if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/property/test                                  #
    ########################################################

    set(PROJECT_STD_TEST_PROPERTY_NAME ${STD_PROJECT_NAME_STR}_property_tests)

    file(GLOB STD_TEST_PROPERTY_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_STD_TEST_PROPERTY_NAME} ${STD_TEST_PROPERTY_SRC_FILES})

    if(NOT WIN32)
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        if((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
            target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME} gtest_main)
        else((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
            target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
                debug Debug/gtest
                optimized /Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
                debug Debug/gtest_main
                optimized Release/gtest_main
                )
        endif((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_property ${PROJECT_STD_TEST_PROPERTY_NAME})

endif(BUILD_STD_TESTS)
