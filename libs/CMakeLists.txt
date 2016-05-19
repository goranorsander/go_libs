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
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
            debug Debug/gtest
            optimized /Release/gtest
            )
        target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
            debug Debug/gtest_main
            optimized Release/gtest_main
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
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
            debug Debug/gtest
            optimized /Release/gtest
            )
        target_link_libraries(${PROJECT_STD_TEST_PROPERTY_NAME}
            debug Debug/gtest_main
            optimized Release/gtest_main
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
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME}
            debug Debug/gtest
            optimized /Release/gtest
            )
        target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME}
            debug Debug/gtest_main
            optimized Release/gtest_main
            )
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_STD_TEST_SIGNALS_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_signals ${PROJECT_STD_TEST_SIGNALS_NAME})

ENDIF(BUILD_STD_TESTS)

IF(BUILD_BOOST_TESTS)

    set(PROJECT_NAME_STR GO_libraries_boost)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

	IF((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION EQUAL 1500))
		set(MSVC_90_GMOCK_LIBS_DIR ${CMAKE_BINARY_DIR}/libs/${GMOCK_LIBS_DIR})
		set(MSVC_90_GTEST_LIBS_DIR ${CMAKE_BINARY_DIR}/libs/${GTEST_LIBS_DIR})
	   link_directories(${MSVC_90_GMOCK_LIBS_DIR} ${MSVC_90_GTEST_LIBS_DIR} ${BOOST_LIBRARYDIR})
	ELSE((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION EQUAL 1500))
	   link_directories(${GMOCK_LIBS_DIR} ${GTEST_LIBS_DIR} ${BOOST_LIBRARYDIR})
	ENDIF((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION EQUAL 1500))

    ########################################################
    #  libs/boost_mvvm/test                                #
    ########################################################

    set(PROJECT_BOOST_TEST_MVVM_NAME ${PROJECT_NAME_STR}_mvvm_tests)

    file(GLOB BOOST_TEST_MVVM_SRC_FILES boost_mvvm/test/*.cpp)
    add_executable(${PROJECT_BOOST_TEST_MVVM_NAME} ${BOOST_TEST_MVVM_SRC_FILES})
    add_dependencies(${PROJECT_BOOST_TEST_MVVM_NAME} googletest)

    if(NOT WIN32)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
            libgtest.a
            libgtest_main.a
            libboost_system-gcc61-mt-1_61.a
            )
    else(NOT WIN32)
		IF((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
			target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME} gtest)
			target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME} gtest_main)
		ELSE((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
			target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
				debug Debug/gtest
				optimized /Release/gtest
				)
			target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
				debug Debug/gtest_main
				optimized Release/gtest_main
				)
		ENDIF((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
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
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
            libgtest.a
            libgtest_main.a
            libboost_system-gcc61-mt-1_61.a
            )
    else(NOT WIN32)
		IF((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
			target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} gtest)
			target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} gtest_main)
		ELSE((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
			target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
				debug Debug/gtest
				optimized /Release/gtest
				)
			target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME}
				debug Debug/gtest_main
				optimized Release/gtest_main
				)
		ENDIF((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_BOOST_TEST_PROPERTY_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_property ${PROJECT_BOOST_TEST_PROPERTY_NAME})

ENDIF(BUILD_BOOST_TESTS)
