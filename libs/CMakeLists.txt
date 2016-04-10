IF(BUILD_TESTS)

    set(PROJECT_NAME_STR GO_LIBS)

    find_package(Threads REQUIRED)

    add_subdirectory(googletest)
    enable_testing()

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    link_directories(${GMOCK_LIBS_DIR} ${GTEST_LIBS_DIR})

    ########################################################
    #  libs/mvvm/test                                      #
    ########################################################

    set(PROJECT_TEST_MVVM_NAME ${PROJECT_NAME_STR}_mvvm_tests)

    file(GLOB TEST_MVVM_SRC_FILES mvvm/test/*.cpp)
    add_executable(${PROJECT_TEST_MVVM_NAME} ${TEST_MVVM_SRC_FILES})
    add_dependencies(${PROJECT_TEST_MVVM_NAME} googletest)

    if(NOT WIN32)
        target_link_libraries(${PROJECT_TEST_MVVM_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_TEST_MVVM_NAME}
            debug DebugLibs/gtest
            optimized /ReleaseLibs/gtest
            )
        target_link_libraries(${PROJECT_TEST_MVVM_NAME}
            debug DebugLibs/gtest_main
            optimized ReleaseLibs/gtest_main
            )
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_TEST_MVVM_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_TEST_MVVM_NAME})

    ########################################################
    #  libs/property/test                                  #
    ########################################################

    set(PROJECT_TEST_PROPERTY_NAME ${PROJECT_NAME_STR}_property_tests)

    file(GLOB TEST_PROPERTY_SRC_FILES property/test/*.cpp)
    add_executable(${PROJECT_TEST_PROPERTY_NAME} ${TEST_PROPERTY_SRC_FILES})
    add_dependencies(${PROJECT_TEST_PROPERTY_NAME} googletest)

    if(NOT WIN32)
        target_link_libraries(${PROJECT_TEST_PROPERTY_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_TEST_PROPERTY_NAME}
            debug DebugLibs/gtest
            optimized /ReleaseLibs/gtest
            )
        target_link_libraries(${PROJECT_TEST_PROPERTY_NAME}
            debug DebugLibs/gtest_main
            optimized ReleaseLibs/gtest_main
            )
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_TEST_PROPERTY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_property ${PROJECT_TEST_PROPERTY_NAME})

    ########################################################
    #  libs/signals/test                                   #
    ########################################################

    set(PROJECT_TEST_SIGNALS_NAME ${PROJECT_NAME_STR}_signals_tests)

    file(GLOB TEST_SIGNALS_SRC_FILES signals/test/*.cpp)
    add_executable(${PROJECT_TEST_SIGNALS_NAME} ${TEST_SIGNALS_SRC_FILES})
    add_dependencies(${PROJECT_TEST_SIGNALS_NAME} googletest)

    if(NOT WIN32)
        target_link_libraries(${PROJECT_TEST_SIGNALS_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_TEST_SIGNALS_NAME}
            debug DebugLibs/gtest
            optimized /ReleaseLibs/gtest
            )
        target_link_libraries(${PROJECT_TEST_SIGNALS_NAME}
            debug DebugLibs/gtest_main
            optimized ReleaseLibs/gtest_main
            )
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_TEST_SIGNALS_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_signals ${PROJECT_TEST_SIGNALS_NAME})

ENDIF(BUILD_TESTS)
