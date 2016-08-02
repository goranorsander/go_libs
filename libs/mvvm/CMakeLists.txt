if(WIN32 AND BUILD_STD_MFC_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    set(CMAKE_MFC_FLAG 2)
    add_definitions(-D_AFXDLL -D_UNICODE -DUNICODE -D_WINDOWS)

    ########################################################
    #  libs/mvvm/mvvm_mfc_example_1                        #
    ########################################################

    set(PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_1 ${STD_PROJECT_NAME_STR}_MFC_example_1)

    add_executable(${PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_1} WIN32
        ./mvvm_mfc_example_1/res/mvvm_mfc_example_1.ico
        ./mvvm_mfc_example_1/res/mvvm_mfc_example_1.rc2
        ./mvvm_mfc_example_1/mvvm_mfc_example_1.cpp
        ./mvvm_mfc_example_1/mvvm_mfc_example_1.h
        ./mvvm_mfc_example_1/mvvm_mfc_example_1.rc
        ./mvvm_mfc_example_1/product_model.cpp
        ./mvvm_mfc_example_1/product_model.hpp
        ./mvvm_mfc_example_1/product_repository.cpp
        ./mvvm_mfc_example_1/product_repository.hpp
        ./mvvm_mfc_example_1/product_repository_interface.hpp
        ./mvvm_mfc_example_1/product_view.cpp
        ./mvvm_mfc_example_1/product_view.hpp
        ./mvvm_mfc_example_1/product_view_model.cpp
        ./mvvm_mfc_example_1/product_view_model.hpp
        ./mvvm_mfc_example_1/Resource.h
        ./mvvm_mfc_example_1/stdafx.cpp
        ./mvvm_mfc_example_1/stdafx.h
        ./mvvm_mfc_example_1/targetver.h
    )

    ########################################################
    #  libs/mvvm/mvvm_mfc_example_2                        #
    ########################################################

    set(PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_2 ${STD_PROJECT_NAME_STR}_MFC_example_2)

    add_executable(${PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_2} WIN32
        ./mvvm_mfc_example_2/res/mvvm_mfc_example_2.ico
        ./mvvm_mfc_example_2/res/mvvm_mfc_example_2.rc2
        ./mvvm_mfc_example_2/mvvm_mfc_example_2.cpp
        ./mvvm_mfc_example_2/mvvm_mfc_example_2.h
        ./mvvm_mfc_example_2/mvvm_mfc_example_2.rc
        ./mvvm_mfc_example_2/product_model.cpp
        ./mvvm_mfc_example_2/product_model.hpp
        ./mvvm_mfc_example_2/product_repository.cpp
        ./mvvm_mfc_example_2/product_repository.hpp
        ./mvvm_mfc_example_2/product_repository_interface.hpp
        ./mvvm_mfc_example_2/product_view.cpp
        ./mvvm_mfc_example_2/product_view.hpp
        ./mvvm_mfc_example_2/product_view_model.cpp
        ./mvvm_mfc_example_2/product_view_model.hpp
        ./mvvm_mfc_example_2/Resource.h
        ./mvvm_mfc_example_2/stdafx.cpp
        ./mvvm_mfc_example_2/stdafx.h
        ./mvvm_mfc_example_2/targetver.h
    )

endif(WIN32 AND BUILD_STD_MFC_EXAMPLES)

if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})
    link_directories(${BOOST_LIBRARYDIR})

    ########################################################
    #  libs/mvvm/test                                      #
    ########################################################

    set(PROJECT_STD_TEST_MVVM_NAME ${STD_PROJECT_NAME_STR}_mvvm_tests)

    file(GLOB STD_TEST_MVVM_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_STD_TEST_MVVM_NAME} ${STD_TEST_MVVM_SRC_FILES})

    if(NOT WIN32)
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
            libgtest.a
            libgtest_main.a
            )
    else(NOT WIN32)
        if((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
            target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME} gtest_main)
        else((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
            target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
                debug Debug/gtest
                optimized /Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
                debug Debug/gtest_main
                optimized Release/gtest_main
                )
        endif((${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") AND (MSVC_VERSION LESS 1800))
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_STD_TEST_MVVM_NAME})

endif(BUILD_STD_TESTS)
