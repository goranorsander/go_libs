#
#  CMakeLists.txt
#
#  Copyright 2016-2021 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    ########################################################
    #  libs/mvvm/event_manager_example                     #
    ########################################################

    set(PROJECT_STD_EVENT_MANAGER_EXAMPLE ${STD_PROJECT_NAME_STR}_event_manager_example)

    file(GLOB STD_EVENT_MANAGER_EXAMPLE_SRC_FILES event_manager_example/*.cpp)
    add_executable(${PROJECT_STD_EVENT_MANAGER_EXAMPLE} ${STD_EVENT_MANAGER_EXAMPLE_SRC_FILES})
    set_target_properties(${PROJECT_STD_EVENT_MANAGER_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_EVENT_MANAGER_EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})

endif(BUILD_STD_EXAMPLES)

if(WIN32 AND BUILD_STD_MFC_EXAMPLES)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    set(CMAKE_MFC_FLAG 2)
    add_definitions(-D_AFXDLL -D_UNICODE -DUNICODE -D_WINDOWS)

    ########################################################
    #  libs/mvvm/mvvm_mfc_product_example                  #
    ########################################################

    set(PROJECT_STD_MVVM_MFC_PRODUCT_EXAMPLE ${STD_PROJECT_NAME_STR}_MFC_product_example)

    set(STD_MVVM_MFC_PRODUCT_EXAMPLE_MFC_APPLICATION_CODE
        ./mvvm_mfc_product_example/res/mvvm_mfc_product_example.ico
        ./mvvm_mfc_product_example/res/mvvm_mfc_product_example.rc2
        ./mvvm_mfc_product_example/mvvm_mfc_product_example.cpp
        ./mvvm_mfc_product_example/mvvm_mfc_product_example.hpp
        ./mvvm_mfc_product_example/mvvm_mfc_product_example.rc
        ./mvvm_mfc_product_example/Resource.h
        ./mvvm_mfc_product_example/stdafx.cpp
        ./mvvm_mfc_product_example/stdafx.h
        ./mvvm_mfc_product_example/targetver.h
    )
    set(STD_MVVM_MFC_PRODUCT_EXAMPLE_MVVM_MODEL_CODE
        ./mvvm_mfc_product_example/product_model.cpp
        ./mvvm_mfc_product_example/product_model.hpp
        ./mvvm_mfc_product_example/product_repository.cpp
        ./mvvm_mfc_product_example/product_repository.hpp
        ./mvvm_mfc_product_example/product_repository_interface.hpp
    )
    set(STD_MVVM_MFC_PRODUCT_EXAMPLE_MVVM_VIEW_CODE
        ./mvvm_mfc_product_example/product_view.cpp
        ./mvvm_mfc_product_example/product_view.hpp
    )
    set(STD_MVVM_MFC_PRODUCT_EXAMPLE_MVVM_VIEW_MODEL_CODE
        ./mvvm_mfc_product_example/product_view_model.cpp
        ./mvvm_mfc_product_example/product_view_model.hpp
    )
    
    add_executable(${PROJECT_STD_MVVM_MFC_PRODUCT_EXAMPLE} WIN32
        ${STD_MVVM_MFC_PRODUCT_EXAMPLE_MFC_APPLICATION_CODE}
        ${STD_MVVM_MFC_PRODUCT_EXAMPLE_MVVM_MODEL_CODE}
        ${STD_MVVM_MFC_PRODUCT_EXAMPLE_MVVM_VIEW_CODE}
        ${STD_MVVM_MFC_PRODUCT_EXAMPLE_MVVM_VIEW_MODEL_CODE}
    )
    set_target_properties(${PROJECT_STD_MVVM_MFC_PRODUCT_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)

    source_group(MFC_Application_Code FILES ${STD_MVVM_MFC_PRODUCT_EXAMPLE_MFC_APPLICATION_CODE})
    source_group(MVVM_Example\\Model FILES ${STD_MVVM_MFC_PRODUCT_EXAMPLE_MVVM_MODEL_CODE})
    source_group(MVVM_Example\\View FILES ${STD_MVVM_MFC_PRODUCT_EXAMPLE_MVVM_VIEW_CODE})
    source_group(MVVM_Example\\View_Model FILES ${STD_MVVM_MFC_PRODUCT_EXAMPLE_MVVM_VIEW_MODEL_CODE})

    ########################################################
    #  libs/mvvm/mvvm_mfc_lambda_product_example           #
    ########################################################

    set(PROJECT_STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE ${STD_PROJECT_NAME_STR}_MFC_lambda_product_example)

    set(STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MFC_APPLICATION_CODE
        ./mvvm_mfc_lambda_product_example/res/mvvm_mfc_lambda_product_example.ico
        ./mvvm_mfc_lambda_product_example/res/mvvm_mfc_lambda_product_example.rc2
        ./mvvm_mfc_lambda_product_example/mvvm_mfc_lambda_product_example.cpp
        ./mvvm_mfc_lambda_product_example/mvvm_mfc_lambda_product_example.hpp
        ./mvvm_mfc_lambda_product_example/mvvm_mfc_lambda_product_example.rc
        ./mvvm_mfc_lambda_product_example/Resource.h
        ./mvvm_mfc_lambda_product_example/stdafx.cpp
        ./mvvm_mfc_lambda_product_example/stdafx.h
        ./mvvm_mfc_lambda_product_example/targetver.h
    )
    set(STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MVVM_MODEL_CODE
        ./mvvm_mfc_lambda_product_example/product_model.cpp
        ./mvvm_mfc_lambda_product_example/product_model.hpp
        ./mvvm_mfc_lambda_product_example/product_repository.cpp
        ./mvvm_mfc_lambda_product_example/product_repository.hpp
        ./mvvm_mfc_lambda_product_example/product_repository_interface.hpp
    )
    set(STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MVVM_VIEW_CODE
        ./mvvm_mfc_lambda_product_example/product_view.cpp
        ./mvvm_mfc_lambda_product_example/product_view.hpp
    )
    set(STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MVVM_VIEW_MODEL_CODE
        ./mvvm_mfc_lambda_product_example/product_view_model.cpp
        ./mvvm_mfc_lambda_product_example/product_view_model.hpp
    )
    
    add_executable(${PROJECT_STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE} WIN32
        ${STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MFC_APPLICATION_CODE}
        ${STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MVVM_MODEL_CODE}
        ${STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MVVM_VIEW_CODE}
        ${STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MVVM_VIEW_MODEL_CODE}
    )
    set_target_properties(${PROJECT_STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)

    source_group(MFC_Application_Code FILES ${STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MFC_APPLICATION_CODE})
    source_group(MVVM_Example\\Model FILES ${STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MVVM_MODEL_CODE})
    source_group(MVVM_Example\\View FILES ${STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MVVM_VIEW_CODE})
    source_group(MVVM_Example\\View_Model FILES ${STD_MVVM_MFC_LAMBDA_PRODUCT_EXAMPLE_MVVM_VIEW_MODEL_CODE})

    ########################################################
    #  libs/mvvm/mvvm_mfc_starfleet_example                #
    ########################################################

    set(PROJECT_STD_MVVM_MFC_STARFLEET_EXAMPLE ${STD_PROJECT_NAME_STR}_MFC_starfleet_example)

    set(STD_MVVM_MFC_STARFLEET_EXAMPLE_MFC_APPLICATION_CODE
        ./mvvm_mfc_starfleet_example/res/classview.bmp
        ./mvvm_mfc_starfleet_example/res/classview_hc.bmp
        ./mvvm_mfc_starfleet_example/res/class_view.ico
        ./mvvm_mfc_starfleet_example/res/class_view_hc.ico
        ./mvvm_mfc_starfleet_example/res/explorer.bmp
        ./mvvm_mfc_starfleet_example/res/explorer_hc.bmp
        ./mvvm_mfc_starfleet_example/res/fileview.bmp
        ./mvvm_mfc_starfleet_example/res/fileview_hc.bmp
        ./mvvm_mfc_starfleet_example/res/file_view.ico
        ./mvvm_mfc_starfleet_example/res/file_view_hc.ico
        ./mvvm_mfc_starfleet_example/res/menuimages.bmp
        ./mvvm_mfc_starfleet_example/res/menuimages_hc.bmp
        ./mvvm_mfc_starfleet_example/res/mvvm_mfc_starfleet_example.ico
        ./mvvm_mfc_starfleet_example/res/mvvm_mfc_starfleet_example.rc2
        ./mvvm_mfc_starfleet_example/res/mvvm_mfc_starfleet_exampleDoc.ico
        ./mvvm_mfc_starfleet_example/res/output_wnd.ico
        ./mvvm_mfc_starfleet_example/res/output_wnd_hc.ico
        ./mvvm_mfc_starfleet_example/res/properties.bmp
        ./mvvm_mfc_starfleet_example/res/properties_hc.bmp
        ./mvvm_mfc_starfleet_example/res/properties_wnd.ico
        ./mvvm_mfc_starfleet_example/res/properties_wnd_hc.ico
        ./mvvm_mfc_starfleet_example/res/sort.bmp
        ./mvvm_mfc_starfleet_example/res/sort_hc.bmp
        ./mvvm_mfc_starfleet_example/res/Toolbar.bmp
        ./mvvm_mfc_starfleet_example/res/Toolbar256.bmp
        ./mvvm_mfc_starfleet_example/mvvm_mfc_starfleet_example.cpp
        ./mvvm_mfc_starfleet_example/mvvm_mfc_starfleet_example.hpp
        ./mvvm_mfc_starfleet_example/mvvm_mfc_starfleet_example.rc
        ./mvvm_mfc_starfleet_example/Resource.h
        ./mvvm_mfc_starfleet_example/stdafx.cpp
        ./mvvm_mfc_starfleet_example/stdafx.h
        ./mvvm_mfc_starfleet_example/targetver.h
    )
    set(STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_CODE
        ./mvvm_mfc_starfleet_example/fleet_repository_populator.cpp
        ./mvvm_mfc_starfleet_example/fleet_repository_populator.hpp
        ./mvvm_mfc_starfleet_example/mdi_frame_interface.hpp
        ./mvvm_mfc_starfleet_example/mvvm_mfc_starfleet_example_namespace_alias.hpp
    )
    set(STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_MODEL_CODE
        ./mvvm_mfc_starfleet_example/equipment_id_type.hpp
        ./mvvm_mfc_starfleet_example/equipment_interface.hpp
        ./mvvm_mfc_starfleet_example/equipment_model.cpp
        ./mvvm_mfc_starfleet_example/equipment_model.hpp
        ./mvvm_mfc_starfleet_example/fleet_organization_id_type.hpp
        ./mvvm_mfc_starfleet_example/fleet_organization_interface.hpp
        ./mvvm_mfc_starfleet_example/fleet_organization_model.cpp
        ./mvvm_mfc_starfleet_example/fleet_organization_model.hpp
        ./mvvm_mfc_starfleet_example/fleet_repository.cpp
        ./mvvm_mfc_starfleet_example/fleet_repository.hpp
        ./mvvm_mfc_starfleet_example/fleet_repository_interface.hpp
        ./mvvm_mfc_starfleet_example/quantity_type.hpp
        ./mvvm_mfc_starfleet_example/spaceship_interface.hpp
        ./mvvm_mfc_starfleet_example/spaceship_model.cpp
        ./mvvm_mfc_starfleet_example/spaceship_model.hpp
    )
    set(STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_CODE
        ./mvvm_mfc_starfleet_example/add_equipment_view.cpp
        ./mvvm_mfc_starfleet_example/add_equipment_view.hpp
        ./mvvm_mfc_starfleet_example/child_frame_view.cpp
        ./mvvm_mfc_starfleet_example/child_frame_view.hpp
        ./mvvm_mfc_starfleet_example/fleet_organization_view.cpp
        ./mvvm_mfc_starfleet_example/fleet_organization_view.hpp
        ./mvvm_mfc_starfleet_example/main_frame_view.cpp
        ./mvvm_mfc_starfleet_example/main_frame_view.hpp
        ./mvvm_mfc_starfleet_example/output_view.cpp
        ./mvvm_mfc_starfleet_example/output_view.hpp
        ./mvvm_mfc_starfleet_example/properties_view.cpp
        ./mvvm_mfc_starfleet_example/properties_view.hpp
        ./mvvm_mfc_starfleet_example/spaceship_view.cpp
        ./mvvm_mfc_starfleet_example/spaceship_view.hpp
    )
    set(STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_CONTROL_CODE
        ./mvvm_mfc_starfleet_example/dialog_view.cpp
        ./mvvm_mfc_starfleet_example/dialog_view.hpp
        ./mvvm_mfc_starfleet_example/fleet_organization_view_tool_bar.cpp
        ./mvvm_mfc_starfleet_example/fleet_organization_view_tool_bar.hpp
        ./mvvm_mfc_starfleet_example/main_frame_view_menu_bar.cpp
        ./mvvm_mfc_starfleet_example/main_frame_view_menu_bar.hpp
        ./mvvm_mfc_starfleet_example/main_frame_view_tool_bar.cpp
        ./mvvm_mfc_starfleet_example/main_frame_view_tool_bar.hpp
        ./mvvm_mfc_starfleet_example/output_view_list.cpp
        ./mvvm_mfc_starfleet_example/output_view_list.hpp
        ./mvvm_mfc_starfleet_example/properties_view_grid.cpp
        ./mvvm_mfc_starfleet_example/properties_view_grid.hpp
        ./mvvm_mfc_starfleet_example/properties_view_tool_bar.cpp
        ./mvvm_mfc_starfleet_example/properties_view_tool_bar.hpp
        ./mvvm_mfc_starfleet_example/tree_control.cpp
        ./mvvm_mfc_starfleet_example/tree_control.hpp
        ./mvvm_mfc_starfleet_example/tree_control_observer.hpp
    )
    set(STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_MODEL_CODE
        ./mvvm_mfc_starfleet_example/add_equipment_view_model.cpp
        ./mvvm_mfc_starfleet_example/add_equipment_view_model.hpp
        ./mvvm_mfc_starfleet_example/fleet_organization_view_model.cpp
        ./mvvm_mfc_starfleet_example/fleet_organization_view_model.hpp
        ./mvvm_mfc_starfleet_example/main_frame_view_model.cpp
        ./mvvm_mfc_starfleet_example/main_frame_view_model.hpp
        ./mvvm_mfc_starfleet_example/properties_view_model.cpp
        ./mvvm_mfc_starfleet_example/properties_view_model.hpp
        ./mvvm_mfc_starfleet_example/spaceship_view_model.cpp
        ./mvvm_mfc_starfleet_example/spaceship_view_model.hpp
    )
    set(STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_MODEL_COMMAND_CODE
        ./mvvm_mfc_starfleet_example/activate_spaceship_command_parameters.cpp
        ./mvvm_mfc_starfleet_example/activate_spaceship_command_parameters.hpp
        ./mvvm_mfc_starfleet_example/add_equipment_command_parameters.cpp
        ./mvvm_mfc_starfleet_example/add_equipment_command_parameters.hpp
        ./mvvm_mfc_starfleet_example/close_spaceship_command_parameters.cpp
        ./mvvm_mfc_starfleet_example/close_spaceship_command_parameters.hpp
        ./mvvm_mfc_starfleet_example/delete_dialog_view_command_parameters.cpp
        ./mvvm_mfc_starfleet_example/delete_dialog_view_command_parameters.hpp
        ./mvvm_mfc_starfleet_example/fleet_organization_command_parameters.cpp
        ./mvvm_mfc_starfleet_example/fleet_organization_command_parameters.hpp
        ./mvvm_mfc_starfleet_example/open_add_equipment_view_command_parameters.cpp
        ./mvvm_mfc_starfleet_example/open_add_equipment_view_command_parameters.hpp
        ./mvvm_mfc_starfleet_example/remove_equipment_command_parameters.cpp
        ./mvvm_mfc_starfleet_example/remove_equipment_command_parameters.hpp
    )
    set(STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_MODEL_EVENT_CODE
        ./mvvm_mfc_starfleet_example/close_spaceship_event.cpp
        ./mvvm_mfc_starfleet_example/close_spaceship_event.hpp
        ./mvvm_mfc_starfleet_example/select_fleet_organization_event.cpp
        ./mvvm_mfc_starfleet_example/select_fleet_organization_event.hpp
        ./mvvm_mfc_starfleet_example/show_spaceship_event.cpp
        ./mvvm_mfc_starfleet_example/show_spaceship_event.hpp
    )
    
    add_executable(${PROJECT_STD_MVVM_MFC_STARFLEET_EXAMPLE} WIN32
        ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MFC_APPLICATION_CODE}
        ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_CODE}
        ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_MODEL_CODE}
        ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_CODE}
        ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_CONTROL_CODE}
        ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_MODEL_CODE}
        ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_MODEL_COMMAND_CODE}
        ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_MODEL_EVENT_CODE}
    )
    set_target_properties(${PROJECT_STD_MVVM_MFC_STARFLEET_EXAMPLE} PROPERTIES FOLDER go_libs/std/examples)

    source_group(MFC_Application_Code FILES ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MFC_APPLICATION_CODE})
    source_group(MVVM_Example FILES ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_CODE})
    source_group(MVVM_Example\\Model FILES ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_MODEL_CODE})
    source_group(MVVM_Example\\View FILES ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_CODE})
    source_group(MVVM_Example\\View\\Control FILES ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_CONTROL_CODE})
    source_group(MVVM_Example\\View_Model FILES ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_MODEL_CODE})
    source_group(MVVM_Example\\View_Model\\Command FILES ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_MODEL_COMMAND_CODE})
    source_group(MVVM_Example\\View_Model\\Event FILES ${STD_MVVM_MFC_STARFLEET_EXAMPLE_MVVM_VIEW_MODEL_EVENT_CODE})

endif(WIN32 AND BUILD_STD_MFC_EXAMPLES)

if(BUILD_STD_TESTS)

    include_directories(${GO_LIBS_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

    ########################################################
    #  libs/mvvm/test                                      #
    ########################################################

    set(PROJECT_STD_TEST_MVVM_NAME ${STD_PROJECT_NAME_STR}_mvvm_tests)

    file(GLOB STD_TEST_MVVM_SRC_FILES test/*.[chi]pp)
    add_executable(${PROJECT_STD_TEST_MVVM_NAME} ${STD_TEST_MVVM_SRC_FILES})
    set_target_properties(${PROJECT_STD_TEST_MVVM_NAME} PROPERTIES FOLDER go_libs/std/tests)

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

    source_group(Test_Suites FILES ${STD_TEST_MVVM_SRC_FILES})

endif(BUILD_STD_TESTS)
