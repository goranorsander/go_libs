#
#  CMakeLists.txt
#
#  Copyright 2016-2017 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(WIN32 AND BUILD_BOOST_MFC_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${BOOST_INCLUDEDIR} ${COMMON_INCLUDES})

    link_directories(${BOOST_LIBRARYDIR})
    
    set(CMAKE_MFC_FLAG 2)
    add_definitions(-D_AFXDLL -D_UNICODE -DUNICODE -D_WINDOWS)

    ########################################################
    #  libs/boost_mvvm/boost_mvvm_mfc_example_1            #
    ########################################################

    set(PROJECT_BOOST_EXAMPLE_MVVM_MFC_EXAMPLE_1 ${BOOST_PROJECT_NAME_STR}_MFC_example_1)

	set(BOOST_MVVM_MFC_EXAMPLE_1_MFC_APPLICATION_CODE
        ./boost_mvvm_mfc_example_1/res/boost_mvvm_mfc_example_1.ico
        ./boost_mvvm_mfc_example_1/res/boost_mvvm_mfc_example_1.rc2
        ./boost_mvvm_mfc_example_1/boost_mvvm_mfc_example_1.cpp
        ./boost_mvvm_mfc_example_1/boost_mvvm_mfc_example_1.hpp
        ./boost_mvvm_mfc_example_1/boost_mvvm_mfc_example_1.rc
        ./boost_mvvm_mfc_example_1/Resource.h
        ./boost_mvvm_mfc_example_1/stdafx.cpp
        ./boost_mvvm_mfc_example_1/stdafx.h
        ./boost_mvvm_mfc_example_1/targetver.h
	)
	set(BOOST_MVVM_MFC_EXAMPLE_1_MVVM_MODEL_CODE
        ./boost_mvvm_mfc_example_1/product_model.cpp
        ./boost_mvvm_mfc_example_1/product_model.hpp
        ./boost_mvvm_mfc_example_1/product_repository.cpp
        ./boost_mvvm_mfc_example_1/product_repository.hpp
        ./boost_mvvm_mfc_example_1/product_repository_interface.hpp
	)
	set(BOOST_MVVM_MFC_EXAMPLE_1_MVVM_VIEW_CODE
        ./boost_mvvm_mfc_example_1/product_view.cpp
        ./boost_mvvm_mfc_example_1/product_view.hpp
	)
	set(BOOST_MVVM_MFC_EXAMPLE_1_MVVM_VIEW_MODEL_CODE
        ./boost_mvvm_mfc_example_1/product_view_model.cpp
        ./boost_mvvm_mfc_example_1/product_view_model.hpp
	)
	
    add_executable(${PROJECT_BOOST_EXAMPLE_MVVM_MFC_EXAMPLE_1} WIN32
		${BOOST_MVVM_MFC_EXAMPLE_1_MFC_APPLICATION_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_1_MVVM_MODEL_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_1_MVVM_VIEW_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_1_MVVM_VIEW_MODEL_CODE}
    )

	source_group(MFC_Application_Code FILES ${BOOST_MVVM_MFC_EXAMPLE_1_MFC_APPLICATION_CODE})
	source_group(MVVM_Example\\Model FILES ${BOOST_MVVM_MFC_EXAMPLE_1_MVVM_MODEL_CODE})
	source_group(MVVM_Example\\View FILES ${BOOST_MVVM_MFC_EXAMPLE_1_MVVM_VIEW_CODE})
	source_group(MVVM_Example\\View_Model FILES ${BOOST_MVVM_MFC_EXAMPLE_1_MVVM_VIEW_MODEL_CODE})

    ########################################################
    #  libs/boost_mvvm/boost_mvvm_mfc_example_2            #
    ########################################################

    if(MSVC AND (NOT (MSVC_VERSION LESS 1800)))
        set(PROJECT_BOOST_EXAMPLE_MVVM_MFC_EXAMPLE_2 ${BOOST_PROJECT_NAME_STR}_MFC_example_2)

        set(BOOST_MVVM_MFC_EXAMPLE_2_MFC_APPLICATION_CODE
            ./boost_mvvm_mfc_example_2/res/boost_mvvm_mfc_example_2.ico
            ./boost_mvvm_mfc_example_2/res/boost_mvvm_mfc_example_2.rc2
            ./boost_mvvm_mfc_example_2/boost_mvvm_mfc_example_2.cpp
            ./boost_mvvm_mfc_example_2/boost_mvvm_mfc_example_2.hpp
            ./boost_mvvm_mfc_example_2/boost_mvvm_mfc_example_2.rc
            ./boost_mvvm_mfc_example_2/Resource.h
            ./boost_mvvm_mfc_example_2/stdafx.cpp
            ./boost_mvvm_mfc_example_2/stdafx.h
            ./boost_mvvm_mfc_example_2/targetver.h
        )
        set(BOOST_MVVM_MFC_EXAMPLE_2_MVVM_MODEL_CODE
            ./boost_mvvm_mfc_example_2/product_model.cpp
            ./boost_mvvm_mfc_example_2/product_model.hpp
            ./boost_mvvm_mfc_example_2/product_repository.cpp
            ./boost_mvvm_mfc_example_2/product_repository.hpp
            ./boost_mvvm_mfc_example_2/product_repository_interface.hpp
        )
        set(BOOST_MVVM_MFC_EXAMPLE_2_MVVM_VIEW_CODE
            ./boost_mvvm_mfc_example_2/product_view.cpp
            ./boost_mvvm_mfc_example_2/product_view.hpp
        )
        set(BOOST_MVVM_MFC_EXAMPLE_2_MVVM_VIEW_MODEL_CODE
            ./boost_mvvm_mfc_example_2/product_view_model.cpp
            ./boost_mvvm_mfc_example_2/product_view_model.hpp
        )
        
        add_executable(${PROJECT_BOOST_EXAMPLE_MVVM_MFC_EXAMPLE_2} WIN32
            ${BOOST_MVVM_MFC_EXAMPLE_2_MFC_APPLICATION_CODE}
            ${BOOST_MVVM_MFC_EXAMPLE_2_MVVM_MODEL_CODE}
            ${BOOST_MVVM_MFC_EXAMPLE_2_MVVM_VIEW_CODE}
            ${BOOST_MVVM_MFC_EXAMPLE_2_MVVM_VIEW_MODEL_CODE}
        )

        source_group(MFC_Application_Code FILES ${BOOST_MVVM_MFC_EXAMPLE_2_MFC_APPLICATION_CODE})
        source_group(MVVM_Example\\Model FILES ${BOOST_MVVM_MFC_EXAMPLE_2_MVVM_MODEL_CODE})
        source_group(MVVM_Example\\View FILES ${BOOST_MVVM_MFC_EXAMPLE_2_MVVM_VIEW_CODE})
        source_group(MVVM_Example\\View_Model FILES ${BOOST_MVVM_MFC_EXAMPLE_2_MVVM_VIEW_MODEL_CODE})
    endif(MSVC AND (NOT (MSVC_VERSION LESS 1800)))

    ########################################################
    #  libs/boost_mvvm/boost_mvvm_mfc_example_3            #
    ########################################################

    set(PROJECT_BOOST_EXAMPLE_BOOST_MVVM_MFC_EXAMPLE_3 ${BOOST_PROJECT_NAME_STR}_MFC_example_3)

	set(BOOST_MVVM_MFC_EXAMPLE_3_MFC_APPLICATION_CODE
        ./boost_mvvm_mfc_example_3/res/boost_mvvm_mfc_example_3.ico
        ./boost_mvvm_mfc_example_3/res/boost_mvvm_mfc_example_3.rc2
        ./boost_mvvm_mfc_example_3/res/boost_mvvm_mfc_example_3Doc.ico
        ./boost_mvvm_mfc_example_3/res/classview.bmp
        ./boost_mvvm_mfc_example_3/res/classview_hc.bmp
        ./boost_mvvm_mfc_example_3/res/class_view.ico
        ./boost_mvvm_mfc_example_3/res/class_view_hc.ico
        ./boost_mvvm_mfc_example_3/res/explorer.bmp
        ./boost_mvvm_mfc_example_3/res/explorer_hc.bmp
        ./boost_mvvm_mfc_example_3/res/fileview.bmp
        ./boost_mvvm_mfc_example_3/res/fileview_hc.bmp
        ./boost_mvvm_mfc_example_3/res/file_view.ico
        ./boost_mvvm_mfc_example_3/res/file_view_hc.ico
        ./boost_mvvm_mfc_example_3/res/menuimages.bmp
        ./boost_mvvm_mfc_example_3/res/menuimages_hc.bmp
        ./boost_mvvm_mfc_example_3/res/output_wnd.ico
        ./boost_mvvm_mfc_example_3/res/output_wnd_hc.ico
        ./boost_mvvm_mfc_example_3/res/properties.bmp
        ./boost_mvvm_mfc_example_3/res/properties_hc.bmp
        ./boost_mvvm_mfc_example_3/res/properties_wnd.ico
        ./boost_mvvm_mfc_example_3/res/properties_wnd_hc.ico
        ./boost_mvvm_mfc_example_3/res/sort.bmp
        ./boost_mvvm_mfc_example_3/res/sort_hc.bmp
        ./boost_mvvm_mfc_example_3/res/Toolbar.bmp
        ./boost_mvvm_mfc_example_3/res/Toolbar256.bmp
        ./boost_mvvm_mfc_example_3/boost_mvvm_mfc_example_3.cpp
        ./boost_mvvm_mfc_example_3/boost_mvvm_mfc_example_3.hpp
        ./boost_mvvm_mfc_example_3/boost_mvvm_mfc_example_3.rc
        ./boost_mvvm_mfc_example_3/Resource.h
        ./boost_mvvm_mfc_example_3/stdafx.cpp
        ./boost_mvvm_mfc_example_3/stdafx.h
        ./boost_mvvm_mfc_example_3/targetver.h
	)
	set(BOOST_MVVM_MFC_EXAMPLE_3_MVVM_CODE
        ./boost_mvvm_mfc_example_3/boost_mvvm_mfc_example_3_namespace_alias.hpp
        ./boost_mvvm_mfc_example_3/fleet_repository_populator.cpp
        ./boost_mvvm_mfc_example_3/fleet_repository_populator.hpp
        ./boost_mvvm_mfc_example_3/mdi_frame_interface.hpp
	)
	set(BOOST_MVVM_MFC_EXAMPLE_3_MVVM_MODEL_CODE
        ./boost_mvvm_mfc_example_3/equipment_interface.hpp
        ./boost_mvvm_mfc_example_3/equipment_model.cpp
        ./boost_mvvm_mfc_example_3/equipment_model.hpp
        ./boost_mvvm_mfc_example_3/fleet_organization_interface.hpp
        ./boost_mvvm_mfc_example_3/fleet_organization_model.cpp
        ./boost_mvvm_mfc_example_3/fleet_organization_model.hpp
        ./boost_mvvm_mfc_example_3/fleet_repository.cpp
        ./boost_mvvm_mfc_example_3/fleet_repository.hpp
        ./boost_mvvm_mfc_example_3/fleet_repository_interface.hpp
        ./boost_mvvm_mfc_example_3/spaceship_interface.hpp
        ./boost_mvvm_mfc_example_3/spaceship_model.cpp
        ./boost_mvvm_mfc_example_3/spaceship_model.hpp
	)
	set(BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CODE
        ./boost_mvvm_mfc_example_3/add_equipment_view.cpp
        ./boost_mvvm_mfc_example_3/add_equipment_view.hpp
        ./boost_mvvm_mfc_example_3/child_frame_view.cpp
        ./boost_mvvm_mfc_example_3/child_frame_view.hpp
        ./boost_mvvm_mfc_example_3/fleet_organization_view.cpp
        ./boost_mvvm_mfc_example_3/fleet_organization_view.hpp
        ./boost_mvvm_mfc_example_3/main_frame_view.cpp
        ./boost_mvvm_mfc_example_3/main_frame_view.hpp
        ./boost_mvvm_mfc_example_3/output_view.cpp
        ./boost_mvvm_mfc_example_3/output_view.hpp
        ./boost_mvvm_mfc_example_3/properties_view.cpp
        ./boost_mvvm_mfc_example_3/properties_view.hpp
        ./boost_mvvm_mfc_example_3/spaceship_view.cpp
        ./boost_mvvm_mfc_example_3/spaceship_view.hpp
	)
	set(BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CONTROL_CODE
        ./boost_mvvm_mfc_example_3/dialog_view.cpp
        ./boost_mvvm_mfc_example_3/dialog_view.hpp
        ./boost_mvvm_mfc_example_3/fleet_organization_view_tool_bar.cpp
        ./boost_mvvm_mfc_example_3/fleet_organization_view_tool_bar.hpp
        ./boost_mvvm_mfc_example_3/main_frame_view_menu_bar.cpp
        ./boost_mvvm_mfc_example_3/main_frame_view_menu_bar.hpp
        ./boost_mvvm_mfc_example_3/main_frame_view_tool_bar.cpp
        ./boost_mvvm_mfc_example_3/main_frame_view_tool_bar.hpp
        ./boost_mvvm_mfc_example_3/output_view_list.cpp
        ./boost_mvvm_mfc_example_3/output_view_list.hpp
        ./boost_mvvm_mfc_example_3/properties_view_grid.cpp
        ./boost_mvvm_mfc_example_3/properties_view_grid.hpp
        ./boost_mvvm_mfc_example_3/properties_view_tool_bar.cpp
        ./boost_mvvm_mfc_example_3/properties_view_tool_bar.hpp
        ./boost_mvvm_mfc_example_3/tree_control.cpp
        ./boost_mvvm_mfc_example_3/tree_control.hpp
        ./boost_mvvm_mfc_example_3/tree_control_observer.hpp
	)
	set(BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_CODE
        ./boost_mvvm_mfc_example_3/add_equipment_view_model.cpp
        ./boost_mvvm_mfc_example_3/add_equipment_view_model.hpp
        ./boost_mvvm_mfc_example_3/fleet_organization_view_model.cpp
        ./boost_mvvm_mfc_example_3/fleet_organization_view_model.hpp
        ./boost_mvvm_mfc_example_3/main_frame_view_model.cpp
        ./boost_mvvm_mfc_example_3/main_frame_view_model.hpp
        ./boost_mvvm_mfc_example_3/properties_view_model.cpp
        ./boost_mvvm_mfc_example_3/properties_view_model.hpp
        ./boost_mvvm_mfc_example_3/spaceship_view_model.cpp
        ./boost_mvvm_mfc_example_3/spaceship_view_model.hpp
	)
	set(BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_COMMAND_CODE
        ./boost_mvvm_mfc_example_3/activate_spaceship_command_parameters.cpp
        ./boost_mvvm_mfc_example_3/activate_spaceship_command_parameters.hpp
        ./boost_mvvm_mfc_example_3/add_equipment_command_parameters.cpp
        ./boost_mvvm_mfc_example_3/add_equipment_command_parameters.hpp
        ./boost_mvvm_mfc_example_3/close_spaceship_command_parameters.cpp
        ./boost_mvvm_mfc_example_3/close_spaceship_command_parameters.hpp
        ./boost_mvvm_mfc_example_3/delete_dialog_view_command_parameters.cpp
        ./boost_mvvm_mfc_example_3/delete_dialog_view_command_parameters.hpp
        ./boost_mvvm_mfc_example_3/fleet_organization_command_parameters.cpp
        ./boost_mvvm_mfc_example_3/fleet_organization_command_parameters.hpp
        ./boost_mvvm_mfc_example_3/open_add_equipment_view_command_parameters.cpp
        ./boost_mvvm_mfc_example_3/open_add_equipment_view_command_parameters.hpp
        ./boost_mvvm_mfc_example_3/remove_equipment_command_parameters.cpp
        ./boost_mvvm_mfc_example_3/remove_equipment_command_parameters.hpp
	)
	set(BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_EVENT_CODE
        ./boost_mvvm_mfc_example_3/close_spaceship_event.cpp
        ./boost_mvvm_mfc_example_3/close_spaceship_event.hpp
        ./boost_mvvm_mfc_example_3/select_fleet_organization_event.cpp
        ./boost_mvvm_mfc_example_3/select_fleet_organization_event.hpp
        ./boost_mvvm_mfc_example_3/show_spaceship_event.cpp
        ./boost_mvvm_mfc_example_3/show_spaceship_event.hpp
	)
	
    add_executable(${PROJECT_BOOST_EXAMPLE_BOOST_MVVM_MFC_EXAMPLE_3} WIN32
		${BOOST_MVVM_MFC_EXAMPLE_3_MFC_APPLICATION_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_MODEL_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CONTROL_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_COMMAND_CODE}
		${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_EVENT_CODE}
    )

	source_group(MFC_Application_Code FILES ${BOOST_MVVM_MFC_EXAMPLE_3_MFC_APPLICATION_CODE})
	source_group(MVVM_Example FILES ${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_CODE})
	source_group(MVVM_Example\\Model FILES ${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_MODEL_CODE})
	source_group(MVVM_Example\\View FILES ${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CODE})
	source_group(MVVM_Example\\View\\Control FILES ${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CONTROL_CODE})
	source_group(MVVM_Example\\View_Model FILES ${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_CODE})
	source_group(MVVM_Example\\View_Model\\Command FILES ${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_COMMAND_CODE})
	source_group(MVVM_Example\\View_Model\\Event FILES ${BOOST_MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_EVENT_CODE})

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

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
            libgtest.a
            libgtest_main.a
			${LIBBOOST_LOCALE}
            ${LIBBOOST_SYSTEM}
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
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
            target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
                libgtest.a
                libgtest_main.a
				${LIBBOOST_LOCALE}
                ${LIBBOOST_SYSTEM}
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME} gtest)
            target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_BOOST_TEST_MVVM_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_BOOST_TEST_MVVM_NAME})

endif(BUILD_BOOST_TESTS)
