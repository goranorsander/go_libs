#
#  CMakeLists.txt
#
#  Copyright 2016-2018 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    ########################################################
    #  libs/mvvm/std_event_manager_example                 #
    ########################################################

    set(PROJECT_STD_EVENT_MANAGER_EXAMPLE ${STD_PROJECT_NAME_STR}_event_manager_example)

    file(GLOB STD_EVENT_MANAGER_EXAMPLE_SRC_FILES std_event_manager_example/*.cpp)
    add_executable(${PROJECT_STD_EVENT_MANAGER_EXAMPLE} ${STD_EVENT_MANAGER_EXAMPLE_SRC_FILES})
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_EVENT_MANAGER_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_STD_EVENT_MANAGER_EXAMPLE})

endif(BUILD_STD_EXAMPLES)

if(WIN32 AND BUILD_STD_MFC_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    set(CMAKE_MFC_FLAG 2)
    add_definitions(-D_AFXDLL -D_UNICODE -DUNICODE -D_WINDOWS)

    ########################################################
    #  libs/mvvm/mvvm_mfc_example_1                        #
    ########################################################

    set(PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_1 ${STD_PROJECT_NAME_STR}_MFC_example_1)

    set(MVVM_MFC_EXAMPLE_1_MFC_APPLICATION_CODE
        ./mvvm_mfc_example_1/res/mvvm_mfc_example_1.ico
        ./mvvm_mfc_example_1/res/mvvm_mfc_example_1.rc2
        ./mvvm_mfc_example_1/mvvm_mfc_example_1.cpp
        ./mvvm_mfc_example_1/mvvm_mfc_example_1.hpp
        ./mvvm_mfc_example_1/mvvm_mfc_example_1.rc
        ./mvvm_mfc_example_1/Resource.h
        ./mvvm_mfc_example_1/stdafx.cpp
        ./mvvm_mfc_example_1/stdafx.h
        ./mvvm_mfc_example_1/targetver.h
    )
    set(MVVM_MFC_EXAMPLE_1_MVVM_MODEL_CODE
        ./mvvm_mfc_example_1/product_model.cpp
        ./mvvm_mfc_example_1/product_model.hpp
        ./mvvm_mfc_example_1/product_repository.cpp
        ./mvvm_mfc_example_1/product_repository.hpp
        ./mvvm_mfc_example_1/product_repository_interface.hpp
    )
    set(MVVM_MFC_EXAMPLE_1_MVVM_VIEW_CODE
        ./mvvm_mfc_example_1/product_view.cpp
        ./mvvm_mfc_example_1/product_view.hpp
    )
    set(MVVM_MFC_EXAMPLE_1_MVVM_VIEW_MODEL_CODE
        ./mvvm_mfc_example_1/product_view_model.cpp
        ./mvvm_mfc_example_1/product_view_model.hpp
    )
    
    add_executable(${PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_1} WIN32
        ${MVVM_MFC_EXAMPLE_1_MFC_APPLICATION_CODE}
        ${MVVM_MFC_EXAMPLE_1_MVVM_MODEL_CODE}
        ${MVVM_MFC_EXAMPLE_1_MVVM_VIEW_CODE}
        ${MVVM_MFC_EXAMPLE_1_MVVM_VIEW_MODEL_CODE}
    )

    source_group(MFC_Application_Code FILES ${MVVM_MFC_EXAMPLE_1_MFC_APPLICATION_CODE})
    source_group(MVVM_Example\\Model FILES ${MVVM_MFC_EXAMPLE_1_MVVM_MODEL_CODE})
    source_group(MVVM_Example\\View FILES ${MVVM_MFC_EXAMPLE_1_MVVM_VIEW_CODE})
    source_group(MVVM_Example\\View_Model FILES ${MVVM_MFC_EXAMPLE_1_MVVM_VIEW_MODEL_CODE})

    ########################################################
    #  libs/mvvm/mvvm_mfc_example_2                        #
    ########################################################

    set(PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_2 ${STD_PROJECT_NAME_STR}_MFC_example_2)

    set(MVVM_MFC_EXAMPLE_2_MFC_APPLICATION_CODE
        ./mvvm_mfc_example_2/res/mvvm_mfc_example_2.ico
        ./mvvm_mfc_example_2/res/mvvm_mfc_example_2.rc2
        ./mvvm_mfc_example_2/mvvm_mfc_example_2.cpp
        ./mvvm_mfc_example_2/mvvm_mfc_example_2.hpp
        ./mvvm_mfc_example_2/mvvm_mfc_example_2.rc
        ./mvvm_mfc_example_2/Resource.h
        ./mvvm_mfc_example_2/stdafx.cpp
        ./mvvm_mfc_example_2/stdafx.h
        ./mvvm_mfc_example_2/targetver.h
    )
    set(MVVM_MFC_EXAMPLE_2_MVVM_MODEL_CODE
        ./mvvm_mfc_example_2/product_model.cpp
        ./mvvm_mfc_example_2/product_model.hpp
        ./mvvm_mfc_example_2/product_repository.cpp
        ./mvvm_mfc_example_2/product_repository.hpp
        ./mvvm_mfc_example_2/product_repository_interface.hpp
    )
    set(MVVM_MFC_EXAMPLE_2_MVVM_VIEW_CODE
        ./mvvm_mfc_example_2/product_view.cpp
        ./mvvm_mfc_example_2/product_view.hpp
    )
    set(MVVM_MFC_EXAMPLE_2_MVVM_VIEW_MODEL_CODE
        ./mvvm_mfc_example_2/product_view_model.cpp
        ./mvvm_mfc_example_2/product_view_model.hpp
    )
    
    add_executable(${PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_2} WIN32
        ${MVVM_MFC_EXAMPLE_2_MFC_APPLICATION_CODE}
        ${MVVM_MFC_EXAMPLE_2_MVVM_MODEL_CODE}
        ${MVVM_MFC_EXAMPLE_2_MVVM_VIEW_CODE}
        ${MVVM_MFC_EXAMPLE_2_MVVM_VIEW_MODEL_CODE}
    )

    source_group(MFC_Application_Code FILES ${MVVM_MFC_EXAMPLE_2_MFC_APPLICATION_CODE})
    source_group(MVVM_Example\\Model FILES ${MVVM_MFC_EXAMPLE_2_MVVM_MODEL_CODE})
    source_group(MVVM_Example\\View FILES ${MVVM_MFC_EXAMPLE_2_MVVM_VIEW_CODE})
    source_group(MVVM_Example\\View_Model FILES ${MVVM_MFC_EXAMPLE_2_MVVM_VIEW_MODEL_CODE})

    ########################################################
    #  libs/mvvm/mvvm_mfc_example_3                        #
    ########################################################

    set(PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_3 ${STD_PROJECT_NAME_STR}_MFC_example_3)

    set(MVVM_MFC_EXAMPLE_3_MFC_APPLICATION_CODE
        ./mvvm_mfc_example_3/res/classview.bmp
        ./mvvm_mfc_example_3/res/classview_hc.bmp
        ./mvvm_mfc_example_3/res/class_view.ico
        ./mvvm_mfc_example_3/res/class_view_hc.ico
        ./mvvm_mfc_example_3/res/explorer.bmp
        ./mvvm_mfc_example_3/res/explorer_hc.bmp
        ./mvvm_mfc_example_3/res/fileview.bmp
        ./mvvm_mfc_example_3/res/fileview_hc.bmp
        ./mvvm_mfc_example_3/res/file_view.ico
        ./mvvm_mfc_example_3/res/file_view_hc.ico
        ./mvvm_mfc_example_3/res/menuimages.bmp
        ./mvvm_mfc_example_3/res/menuimages_hc.bmp
        ./mvvm_mfc_example_3/res/mvvm_mfc_example_3.ico
        ./mvvm_mfc_example_3/res/mvvm_mfc_example_3.rc2
        ./mvvm_mfc_example_3/res/mvvm_mfc_example_3Doc.ico
        ./mvvm_mfc_example_3/res/output_wnd.ico
        ./mvvm_mfc_example_3/res/output_wnd_hc.ico
        ./mvvm_mfc_example_3/res/properties.bmp
        ./mvvm_mfc_example_3/res/properties_hc.bmp
        ./mvvm_mfc_example_3/res/properties_wnd.ico
        ./mvvm_mfc_example_3/res/properties_wnd_hc.ico
        ./mvvm_mfc_example_3/res/sort.bmp
        ./mvvm_mfc_example_3/res/sort_hc.bmp
        ./mvvm_mfc_example_3/res/Toolbar.bmp
        ./mvvm_mfc_example_3/res/Toolbar256.bmp
        ./mvvm_mfc_example_3/mvvm_mfc_example_3.cpp
        ./mvvm_mfc_example_3/mvvm_mfc_example_3.hpp
        ./mvvm_mfc_example_3/mvvm_mfc_example_3.rc
        ./mvvm_mfc_example_3/Resource.h
        ./mvvm_mfc_example_3/stdafx.cpp
        ./mvvm_mfc_example_3/stdafx.h
        ./mvvm_mfc_example_3/targetver.h
    )
    set(MVVM_MFC_EXAMPLE_3_MVVM_CODE
        ./mvvm_mfc_example_3/fleet_repository_populator.cpp
        ./mvvm_mfc_example_3/fleet_repository_populator.hpp
        ./mvvm_mfc_example_3/mdi_frame_interface.hpp
        ./mvvm_mfc_example_3/mvvm_mfc_example_3_namespace_alias.hpp
    )
    set(MVVM_MFC_EXAMPLE_3_MVVM_MODEL_CODE
        ./mvvm_mfc_example_3/equipment_interface.hpp
        ./mvvm_mfc_example_3/equipment_model.cpp
        ./mvvm_mfc_example_3/equipment_model.hpp
        ./mvvm_mfc_example_3/fleet_organization_interface.hpp
        ./mvvm_mfc_example_3/fleet_organization_model.cpp
        ./mvvm_mfc_example_3/fleet_organization_model.hpp
        ./mvvm_mfc_example_3/fleet_repository.cpp
        ./mvvm_mfc_example_3/fleet_repository.hpp
        ./mvvm_mfc_example_3/fleet_repository_interface.hpp
        ./mvvm_mfc_example_3/spaceship_interface.hpp
        ./mvvm_mfc_example_3/spaceship_model.cpp
        ./mvvm_mfc_example_3/spaceship_model.hpp
    )
    set(MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CODE
        ./mvvm_mfc_example_3/add_equipment_view.cpp
        ./mvvm_mfc_example_3/add_equipment_view.hpp
        ./mvvm_mfc_example_3/child_frame_view.cpp
        ./mvvm_mfc_example_3/child_frame_view.hpp
        ./mvvm_mfc_example_3/fleet_organization_view.cpp
        ./mvvm_mfc_example_3/fleet_organization_view.hpp
        ./mvvm_mfc_example_3/main_frame_view.cpp
        ./mvvm_mfc_example_3/main_frame_view.hpp
        ./mvvm_mfc_example_3/output_view.cpp
        ./mvvm_mfc_example_3/output_view.hpp
        ./mvvm_mfc_example_3/properties_view.cpp
        ./mvvm_mfc_example_3/properties_view.hpp
        ./mvvm_mfc_example_3/spaceship_view.cpp
        ./mvvm_mfc_example_3/spaceship_view.hpp
    )
    set(MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CONTROL_CODE
        ./mvvm_mfc_example_3/dialog_view.cpp
        ./mvvm_mfc_example_3/dialog_view.hpp
        ./mvvm_mfc_example_3/fleet_organization_view_tool_bar.cpp
        ./mvvm_mfc_example_3/fleet_organization_view_tool_bar.hpp
        ./mvvm_mfc_example_3/main_frame_view_menu_bar.cpp
        ./mvvm_mfc_example_3/main_frame_view_menu_bar.hpp
        ./mvvm_mfc_example_3/main_frame_view_tool_bar.cpp
        ./mvvm_mfc_example_3/main_frame_view_tool_bar.hpp
        ./mvvm_mfc_example_3/output_view_list.cpp
        ./mvvm_mfc_example_3/output_view_list.hpp
        ./mvvm_mfc_example_3/properties_view_grid.cpp
        ./mvvm_mfc_example_3/properties_view_grid.hpp
        ./mvvm_mfc_example_3/properties_view_tool_bar.cpp
        ./mvvm_mfc_example_3/properties_view_tool_bar.hpp
        ./mvvm_mfc_example_3/tree_control.cpp
        ./mvvm_mfc_example_3/tree_control.hpp
        ./mvvm_mfc_example_3/tree_control_observer.hpp
    )
    set(MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_CODE
        ./mvvm_mfc_example_3/add_equipment_view_model.cpp
        ./mvvm_mfc_example_3/add_equipment_view_model.hpp
        ./mvvm_mfc_example_3/fleet_organization_view_model.cpp
        ./mvvm_mfc_example_3/fleet_organization_view_model.hpp
        ./mvvm_mfc_example_3/main_frame_view_model.cpp
        ./mvvm_mfc_example_3/main_frame_view_model.hpp
        ./mvvm_mfc_example_3/properties_view_model.cpp
        ./mvvm_mfc_example_3/properties_view_model.hpp
        ./mvvm_mfc_example_3/spaceship_view_model.cpp
        ./mvvm_mfc_example_3/spaceship_view_model.hpp
    )
    set(MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_COMMAND_CODE
        ./mvvm_mfc_example_3/activate_spaceship_command_parameters.cpp
        ./mvvm_mfc_example_3/activate_spaceship_command_parameters.hpp
        ./mvvm_mfc_example_3/add_equipment_command_parameters.cpp
        ./mvvm_mfc_example_3/add_equipment_command_parameters.hpp
        ./mvvm_mfc_example_3/close_spaceship_command_parameters.cpp
        ./mvvm_mfc_example_3/close_spaceship_command_parameters.hpp
        ./mvvm_mfc_example_3/delete_dialog_view_command_parameters.cpp
        ./mvvm_mfc_example_3/delete_dialog_view_command_parameters.hpp
        ./mvvm_mfc_example_3/fleet_organization_command_parameters.cpp
        ./mvvm_mfc_example_3/fleet_organization_command_parameters.hpp
        ./mvvm_mfc_example_3/open_add_equipment_view_command_parameters.cpp
        ./mvvm_mfc_example_3/open_add_equipment_view_command_parameters.hpp
        ./mvvm_mfc_example_3/remove_equipment_command_parameters.cpp
        ./mvvm_mfc_example_3/remove_equipment_command_parameters.hpp
    )
    set(MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_EVENT_CODE
        ./mvvm_mfc_example_3/close_spaceship_event.cpp
        ./mvvm_mfc_example_3/close_spaceship_event.hpp
        ./mvvm_mfc_example_3/select_fleet_organization_event.cpp
        ./mvvm_mfc_example_3/select_fleet_organization_event.hpp
        ./mvvm_mfc_example_3/show_spaceship_event.cpp
        ./mvvm_mfc_example_3/show_spaceship_event.hpp
    )
    
    add_executable(${PROJECT_STD_EXAMPLE_MVVM_MFC_EXAMPLE_3} WIN32
        ${MVVM_MFC_EXAMPLE_3_MFC_APPLICATION_CODE}
        ${MVVM_MFC_EXAMPLE_3_MVVM_CODE}
        ${MVVM_MFC_EXAMPLE_3_MVVM_MODEL_CODE}
        ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CODE}
        ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CONTROL_CODE}
        ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_CODE}
        ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_COMMAND_CODE}
        ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_EVENT_CODE}
    )

    source_group(MFC_Application_Code FILES ${MVVM_MFC_EXAMPLE_3_MFC_APPLICATION_CODE})
    source_group(MVVM_Example FILES ${MVVM_MFC_EXAMPLE_3_MVVM_CODE})
    source_group(MVVM_Example\\Model FILES ${MVVM_MFC_EXAMPLE_3_MVVM_MODEL_CODE})
    source_group(MVVM_Example\\View FILES ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CODE})
    source_group(MVVM_Example\\View\\Control FILES ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_CONTROL_CODE})
    source_group(MVVM_Example\\View_Model FILES ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_CODE})
    source_group(MVVM_Example\\View_Model\\Command FILES ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_COMMAND_CODE})
    source_group(MVVM_Example\\View_Model\\Event FILES ${MVVM_MFC_EXAMPLE_3_MVVM_VIEW_MODEL_EVENT_CODE})

endif(WIN32 AND BUILD_STD_MFC_EXAMPLES)

if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    ########################################################
    #  libs/mvvm/test                                      #
    ########################################################

    set(PROJECT_STD_TEST_MVVM_NAME ${STD_PROJECT_NAME_STR}_mvvm_tests)

    file(GLOB STD_TEST_MVVM_SRC_FILES test/*.cpp)
    add_executable(${PROJECT_STD_TEST_MVVM_NAME} ${STD_TEST_MVVM_SRC_FILES})

    if(CMAKE_COMPILER_IS_CLANG)
        find_package(Threads)
        target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
            libgtest.a
            libgtest_main.a
            )
    elseif(CMAKE_COMPILER_IS_GNUCC)
        if(WIN32)
            if(MSYS OR MINGW)
                find_package(Threads)
                target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
                    libgtest.a
                    libgtest_main.a
                    )
            else(MSYS OR MINGW)
                # Unsupported compiler
                message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported on Windows")
            endif(MSYS OR MINGW)
        else(WIN32)
            find_package(Threads)
            target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
                libgtest.a
                libgtest_main.a
                )
        endif(WIN32)
    elseif(CMAKE_COMPILER_IS_MSVC)
        if(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME} gtest)
            target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME} gtest_main)
        else(MSVC_VERSION LESS 1800)
            target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
                debug Debug/gtestd
                optimized Release/gtest
                )
            target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME}
                debug Debug/gtest_maind
                optimized Release/gtest_main
                )
        endif(MSVC_VERSION LESS 1800)
    else(CMAKE_COMPILER_IS_CLANG)
        # Unsupported compiler
        message(SEND_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported")
    endif(CMAKE_COMPILER_IS_CLANG)

    target_link_libraries(${PROJECT_STD_TEST_MVVM_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(test_mvvm ${PROJECT_STD_TEST_MVVM_NAME})

endif(BUILD_STD_TESTS)
