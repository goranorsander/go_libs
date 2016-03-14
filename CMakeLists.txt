CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(GO_LIBS)

#Import all files, Headers and cpp files seperate.

#Options-------------------------------------------------

OPTION(USE_SOLUTION_FOLDERS "Organise all projects into folders in your solution." ON)
OPTION(BUILD_TESTS "Build the GO_LIBS unit tests. Uses the google test framework.")

IF(USE_SOLUTION_FOLDERS)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
ELSE(USE_SOLUTION_FOLDERS)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS OFF)
ENDIF(USE_SOLUTION_FOLDERS)

########################################################
#  compiler flags                                      #
########################################################

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
endif()

########################################################
#  external dependencies                               #
########################################################

#ADD_SUBDIRECTORY(external)

########################################################
#  go                                                  #
########################################################

SET(GO_DIRNAME go)
SET(GO_DIR ${GO_LIBS_SOURCE_DIR}/go)

# *.hpp

SET(GO_LIBS_SRC_GO_HPP
    ${GO_DIR}/mvvm.hpp
    ${GO_DIR}/property.hpp
    ${GO_DIR}/signals.hpp
)

# *.cpp

SET(GO_LIBS_SRC_GO_CPP)

########################################################
#  go/mvvm                                             #
########################################################

SET(GO_MVVM_DIRNAME mvvm)
SET(GO_MVVM_DIR ${GO_DIR}/mvvm)

# *.hpp

SET(GO_LIBS_SRC_GO_MVVM_HPP
    ${GO_MVVM_DIR}/command.hpp
    ${GO_MVVM_DIR}/command_manager.hpp
    ${GO_MVVM_DIR}/command_parameters.hpp
    ${GO_MVVM_DIR}/container_changed_arguments.hpp
    ${GO_MVVM_DIR}/notify_container_changed.hpp
    ${GO_MVVM_DIR}/notify_container_changed_action.hpp
    ${GO_MVVM_DIR}/notify_property_changed.hpp
    ${GO_MVVM_DIR}/object.hpp
    ${GO_MVVM_DIR}/observable_object.hpp
    ${GO_MVVM_DIR}/property_changed_arguments.hpp
    ${GO_MVVM_DIR}/relay_command.hpp
)

# *.cpp

SET(GO_LIBS_SRC_GO_MVVM_CPP)

########################################################
#  go/property                                         #
########################################################

SET(GO_PROPERTY_DIRNAME /property)
SET(GO_PROPERTY_DIR ${GO_DIR}/property)

# *.hpp

SET(GO_LIBS_SRC_GO_PROPERTY_HPP
    ${GO_PROPERTY_DIR}/property.hpp
    ${GO_PROPERTY_DIR}/ref_scalar_property.hpp
    ${GO_PROPERTY_DIR}/ro_property.hpp
    ${GO_PROPERTY_DIR}/ro_ref_scalar_property.hpp
    ${GO_PROPERTY_DIR}/ro_value_scalar_property.hpp
    ${GO_PROPERTY_DIR}/value_scalar_property.hpp
    ${GO_PROPERTY_DIR}/wo_property.hpp
    ${GO_PROPERTY_DIR}/wo_ref_scalar_property.hpp
    ${GO_PROPERTY_DIR}/wo_value_scalar_property.hpp
)

# *.cpp

SET(GO_LIBS_SRC_GO_PROPERTY_CPP)

########################################################
#  go/property/detail                                  #
########################################################

SET(GO_PROPERTY_DETAIL_DIRNAME property/detail)
SET(GO_PROPERTY_DETAIL_DIR ${GO_DIR}/property/detail)

# *.hpp

SET(GO_LIBS_SRC_GO_PROPERTY_DETAIL_HPP
    ${GO_PROPERTY_DETAIL_DIR}/assignment_operator.hpp
    ${GO_PROPERTY_DETAIL_DIR}/property_base.hpp
    ${GO_PROPERTY_DETAIL_DIR}/ro_property_base.hpp
    ${GO_PROPERTY_DETAIL_DIR}/wo_property_base.hpp
)

SET(GO_LIBS_SRC_GO_PROPERTY_DETAIL_CPP)

########################################################
#  go/property/policy                                  #
########################################################

SET(GO_PROPERTY_POLICY_DIRNAME property/policy)
SET(GO_PROPERTY_POLICY_DIR ${GO_DIR}/property/policy)

# *.hpp

SET(GO_LIBS_SRC_GO_PROPERTY_POLICY_HPP
    ${GO_PROPERTY_POLICY_DIR}/proxy.hpp
    ${GO_PROPERTY_POLICY_DIR}/ref.hpp
    ${GO_PROPERTY_POLICY_DIR}/value.hpp
)

SET(GO_LIBS_SRC_GO_PROPERTY_POLICY_CPP)

########################################################
#  go/signals                                             #
########################################################

SET(GO_SIGNALS_DIRNAME signals)
SET(GO_SIGNALS_DIR ${GO_DIR}/signals)

# *.hpp

SET(GO_LIBS_SRC_GO_SIGNALS_HPP
    ${GO_SIGNALS_DIR}/signal.hpp
    ${GO_SIGNALS_DIR}/slot.hpp
    ${GO_SIGNALS_DIR}/slot_arguments.hpp
)

# *.cpp

SET(GO_LIBS_SRC_GO_SIGNALS_CPP)

########################################################
#  libs                                                #
########################################################

ADD_SUBDIRECTORY(libs)

INSTALL(TARGETS ${GO_LIBS_DLL} LIBRARY DESTINATION lib)

INSTALL(FILES ${GO_LIBS_SRC_GO_HPP}                  DESTINATION  include/${GO_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_MVVM_HPP}             DESTINATION  include/${GO_DIRNAME}/${GO_MVVM_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_HPP}         DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_DETAIL_HPP}  DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_POLICY_HPP}  DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_POLICY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_SIGNALS_HPP}          DESTINATION  include/${GO_DIRNAME}/${GO_SIGNALS_DIRNAME})
