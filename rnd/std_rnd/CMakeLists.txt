#
#  CMakeLists.txt
#
#  Copyright 2019 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

if(BUILD_STD_RND)

    include_directories(${GO_LIBS_SOURCE_DIR} ${COMMON_INCLUDES})

    ########################################################
    #  rnd/std_rnd/lambda_binding                          #
    ########################################################

    set(PROJECT_STD_LAMBDA_BINDING ${STD_PROJECT_NAME_STR}_lambda_binding)

    file(GLOB STD_LAMBDA_BINDING_SRC_FILES lambda_binding/*.cpp)
    add_executable(${PROJECT_STD_LAMBDA_BINDING} ${STD_LAMBDA_BINDING_SRC_FILES})
    set_target_properties(${PROJECT_STD_LAMBDA_BINDING} PROPERTIES FOLDER rnd/std)
    find_package(Threads)

    target_link_libraries(${PROJECT_STD_LAMBDA_BINDING} ${CMAKE_THREAD_LIBS_INIT})

endif(BUILD_STD_RND)
