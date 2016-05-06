IF(BUILD_STD_TESTS OR BUILD_BOOST_TESTS)

    add_subdirectory(googletest)
    enable_testing()

ENDIF(BUILD_STD_TESTS OR BUILD_BOOST_TESTS)

IF(BUILD_STD_TESTS)

    set(PROJECT_NAME_STR GO_libraries_std)

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    link_directories(${GMOCK_LIBS_DIR} ${GTEST_LIBS_DIR})

    ########################################################
    #  libs/mvvm/test                                      #
    ########################################################

    set(PROJECT_STD_TEST_MVVM_NAME ${PROJECT_NAME_STR}_mvvm_tests)

    file(GLOB STD_TEST_MVVM_SRC_FILES mvvm/test/*.cpp)
    add_executable(${PROJECT_STD_TEST_MVVM_NAME} ${STD_TEST_MVVM_SRC_FILES})
    add_dependencies(${PROJECT_STD_TEST_MVVM_NAME} googletest)

    if(NOT WIN32)
        target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
            debug DebugLibs/gtest
            optimized /ReleaseLibs/gtest
            )
        target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
            debug DebugLibs/gtest_main
            optimized ReleaseLibs/gtest_main
            )
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_STD_TEST_MVVM_NAME})

    ########################################################
    #  libs/property/test                                  #
    ########################################################

    set(PROJECT_STD_TEST_PROPERTY_NAME ${PROJECT_NAME_STR}_property_tests)

    file(GLOB STD_TEST_PROPERTY_SRC_FILES property/test/*.cpp)
    add_executable(${PROJECT_STD_TEST_PROPERTY_NAME} ${STD_TEST_PROPERTY_SRC_FILES})
    add_dependencies(${PROJECT_STD_TEST_PROPERTY_NAME} googletest)

    if(NOT WIN32)
        target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
            debug DebugLibs/gtest
            optimized /ReleaseLibs/gtest
            )
        target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
            debug DebugLibs/gtest_main
            optimized ReleaseLibs/gtest_main
            )
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_property ${PROJECT_STD_TEST_PROPERTY_NAME})

    ########################################################
    #  libs/signals/test                                   #
    ########################################################

    set(PROJECT_STD_TEST_SIGNALS_NAME ${PROJECT_NAME_STR}_signals_tests)

    file(GLOB STD_TEST_SIGNALS_SRC_FILES signals/test/*.cpp)
    add_executable(${PROJECT_STD_TEST_SIGNALS_NAME} ${STD_TEST_SIGNALS_SRC_FILES})
    add_dependencies(${PROJECT_STD_TEST_SIGNALS_NAME} googletest)

    if(NOT WIN32)
        target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME}
            debug DebugLibs/gtest
            optimized /ReleaseLibs/gtest
            )
        target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME}
            debug DebugLibs/gtest_main
            optimized ReleaseLibs/gtest_main
            )
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_signals ${PROJECT_STD_TEST_SIGNALS_NAME})

ENDIF(BUILD_STD_TESTS)

IF(BUILD_BOOST_TESTS)

    set(PROJECT_NAME_STR GO_libraries_boost)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    link_directories(${GMOCK_LIBS_DIR} ${BOOST_LIBRARYDIR} ${GTEST_LIBS_DIR})

    ########################################################
    #  libs/boost_mvvm/test                                #
    ########################################################

    set(PROJECT_BOOST_TEST_MVVM_NAME ${PROJECT_NAME_STR}_mvvm_tests)

    file(GLOB BOOST_TEST_MVVM_SRC_FILES boost_mvvm/test/*.cpp)
    add_executable(${PROJECT_BOOST_TEST_MVVM_NAME} ${BOOST_TEST_MVVM_SRC_FILES})
    add_dependencies(${PROJECT_BOOST_TEST_MVVM_NAME} googletest)

    if(NOT WIN32)
        target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
            debug DebugLibs/gtest
            optimized /ReleaseLibs/gtest
            )
        target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
            debug DebugLibs/gtest_main
            optimized ReleaseLibs/gtest_main
            )
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_BOOST_TEST_MVVM_NAME})

    ########################################################
    #  libs/boost_property/test                            #
    ########################################################

    set(PROJECT_BOOST_TEST_PROPERTY_NAME ${PROJECT_NAME_STR}_property_tests)

    file(GLOB BOOST_TEST_PROPERTY_SRC_FILES boost_property/test/*.cpp)
    add_executable(${PROJECT_BOOST_TEST_PROPERTY_NAME} ${BOOST_TEST_PROPERTY_SRC_FILES})
    add_dependencies(${PROJECT_BOOST_TEST_PROPERTY_NAME} googletest)

    if(NOT WIN32)
        target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
            debug DebugLibs/gtest
            optimized /ReleaseLibs/gtest
            )
        target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
            debug DebugLibs/gtest_main
            optimized ReleaseLibs/gtest_main
            )
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_property ${PROJECT_BOOST_TEST_PROPERTY_NAME})

ENDIF(BUILD_BOOST_TESTS)
