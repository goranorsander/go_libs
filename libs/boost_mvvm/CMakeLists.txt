if(WIN32 AND BUILD_BOOST_MFC_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})

    link_directories(${BOOST_LIBRARYDIR})
    
    set(CMAKE_MFC_FLAG 2)
    add_definitions(-D_AFXDLL -D_UNICODE -DUNICODE -D_WINDOWS)

    ########################################################
    #  libs/boost_mvvm/boost_mvvm_mfc_example_1            #
    ########################################################

    set(PROJECT_BOOST_EXAMPLE_MVVM_MFC_EXAMPLE_1 ${BOOST_PROJECT_NAME_STR}_MFC_example_1)

    add_executable(${PROJECT_BOOST_EXAMPLE_MVVM_MFC_EXAMPLE_1} WIN32
        ./boost_mvvm_mfc_example_1/res/boost_mvvm_mfc_example_1.ico
        ./boost_mvvm_mfc_example_1/res/boost_mvvm_mfc_example_1.rc2
        ./boost_mvvm_mfc_example_1/boost_mvvm_mfc_example_1.cpp
        ./boost_mvvm_mfc_example_1/boost_mvvm_mfc_example_1.h
        ./boost_mvvm_mfc_example_1/boost_mvvm_mfc_example_1.rc
        ./boost_mvvm_mfc_example_1/product_model.cpp
        ./boost_mvvm_mfc_example_1/product_model.hpp
        ./boost_mvvm_mfc_example_1/product_repository.cpp
        ./boost_mvvm_mfc_example_1/product_repository.hpp
        ./boost_mvvm_mfc_example_1/product_repository_interface.hpp
        ./boost_mvvm_mfc_example_1/product_view.cpp
        ./boost_mvvm_mfc_example_1/product_view.hpp
        ./boost_mvvm_mfc_example_1/product_view_model.cpp
        ./boost_mvvm_mfc_example_1/product_view_model.hpp
        ./boost_mvvm_mfc_example_1/Resource.h
        ./boost_mvvm_mfc_example_1/stdafx.cpp
        ./boost_mvvm_mfc_example_1/stdafx.h
        ./boost_mvvm_mfc_example_1/targetver.h
    )

    ########################################################
    #  libs/boost_mvvm/boost_mvvm_mfc_example_2            #
    ########################################################

    set(PROJECT_BOOST_EXAMPLE_MVVM_MFC_EXAMPLE_2 ${BOOST_PROJECT_NAME_STR}_MFC_example_2)

    add_executable(${PROJECT_BOOST_EXAMPLE_MVVM_MFC_EXAMPLE_2} WIN32
        ./boost_mvvm_mfc_example_2/res/boost_mvvm_mfc_example_2.ico
        ./boost_mvvm_mfc_example_2/res/boost_mvvm_mfc_example_2.rc2
        ./boost_mvvm_mfc_example_2/boost_mvvm_mfc_example_2.cpp
        ./boost_mvvm_mfc_example_2/boost_mvvm_mfc_example_2.h
        ./boost_mvvm_mfc_example_2/boost_mvvm_mfc_example_2.rc
        ./boost_mvvm_mfc_example_2/product_model.cpp
        ./boost_mvvm_mfc_example_2/product_model.hpp
        ./boost_mvvm_mfc_example_2/product_repository.cpp
        ./boost_mvvm_mfc_example_2/product_repository.hpp
        ./boost_mvvm_mfc_example_2/product_repository_interface.hpp
        ./boost_mvvm_mfc_example_2/product_view.cpp
        ./boost_mvvm_mfc_example_2/product_view.hpp
        ./boost_mvvm_mfc_example_2/product_view_model.cpp
        ./boost_mvvm_mfc_example_2/product_view_model.hpp
        ./boost_mvvm_mfc_example_2/Resource.h
        ./boost_mvvm_mfc_example_2/stdafx.cpp
        ./boost_mvvm_mfc_example_2/stdafx.h
        ./boost_mvvm_mfc_example_2/targetver.h
    )

endif(WIN32 AND BUILD_BOOST_MFC_EXAMPLES)

if(BUILD_BOOST_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    if(MSVC AND (MSVC_VERSION EQUAL 1500))
        set(MSVC_90_GMOCK_LIBS_DIR ${CMAKE_BINARY_DIR}/libs/${GMOCK_LIBS_DIR})
        set(MSVC_90_GTEST_LIBS_DIR ${CMAKE_BINARY_DIR}/libs/${GTEST_LIBS_DIR})
        link_directories(${MSVC_90_GMOCK_LIBS_DIR} ${MSVC_90_GTEST_LIBS_DIR} ${BOOST_LIBRARYDIR})
    else(MSVC AND (MSVC_VERSION EQUAL 1500))
        link_directories(${GMOCK_LIBS_DIR} ${GTEST_LIBS_DIR} ${BOOST_LIBRARYDIR})
    endif(MSVC AND (MSVC_VERSION EQUAL 1500))

    ########################################################
    #  libs/boost_mvvm/test                                #
    ########################################################

    set(PROJECT_BOOST_TEST_MVVM_NAME ${BOOST_PROJECT_NAME_STR}_mvvm_tests)

    file(GLOB BOOST_TEST_MVVM_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_BOOST_TEST_MVVM_NAME} ${BOOST_TEST_MVVM_SRC_FILES})

    if(NOT WIN32)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
            libgtest.a
            libgtest_main.a
            ${LIBBOOST_SYSTEM}
            )
    else(NOT WIN32)
        if(MSYS OR MINGW)
            find_package(Threads)
            target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
                libgtest.a
                libgtest_main.a
                ${LIBBOOST_SYSTEM}
                )
        else(MSYS OR MINGW)
            if(MSVC AND (MSVC_VERSION LESS 1800))
                target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME} gtest)
                target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME} gtest_main)
            else(MSVC AND (MSVC_VERSION LESS 1800))
                target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
                    debug Debug/gtest
                    optimized Release/gtest
                    )
                target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
                    debug Debug/gtest_main
                    optimized Release/gtest_main
                    )
            endif(MSVC AND (MSVC_VERSION LESS 1800))
        endif(MSYS OR MINGW)
    endif(NOT WIN32)

    target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_BOOST_TEST_MVVM_NAME})

endif(BUILD_BOOST_TESTS)
