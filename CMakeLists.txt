CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(GO_LIBS)

#Import all files, Headers and cpp files seperate.

#Options-------------------------------------------------

OPTION(USE_SOLUTION_FOLDERS "Organise all projects into folders in your solution." ON)
OPTION(BUILD_STD_TESTS "Build the GO libraries unit tests for std-implementation. Uses the google test framework. Requires C++11.")
OPTION(BUILD_BOOST_TESTS "Build the GO libraries unit tests for boost-implementation. Uses the google test framework. Requires the Boost libraries.")
SET(BOOST_INCLUDEDIR $ENV{BOOST_LIBS_INCLUDE} CACHE STRING "Boost libraries include directory.")
SET(BOOST_LIBRARYDIR $ENV{BOOST_LIBS_STATIC_LINK} CACHE STRING "Boost libraries library directory.")

IF(USE_SOLUTION_FOLDERS)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
ELSE(USE_SOLUTION_FOLDERS)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS OFF)
ENDIF(USE_SOLUTION_FOLDERS)

########################################################
#  compiler flags                                      #
########################################################

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # using Clang
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # using GCC
    SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14 -fpermissive" )
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
    # using Intel C++
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # using Visual Studio C++
	if(MSVC_VERSION EQUAL 1700)
		# using Visual Studio 2012 C++
		SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /D \"_VARIADIC_MAX=10\"" )
	endif(MSVC_VERSION EQUAL 1700)
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
    ${GO_PROPERTY_DIR}/read_only_property.hpp
    ${GO_PROPERTY_DIR}/read_only_reference_property.hpp
    ${GO_PROPERTY_DIR}/read_only_value_property.hpp
    ${GO_PROPERTY_DIR}/reference_property.hpp
    ${GO_PROPERTY_DIR}/value_property.hpp
    ${GO_PROPERTY_DIR}/write_only_property.hpp
    ${GO_PROPERTY_DIR}/write_only_reference_property.hpp
    ${GO_PROPERTY_DIR}/write_only_value_property.hpp
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
    ${GO_PROPERTY_DETAIL_DIR}/read_only_property_base.hpp
    ${GO_PROPERTY_DETAIL_DIR}/write_only_property_base.hpp
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
    ${GO_PROPERTY_POLICY_DIR}/reference.hpp
    ${GO_PROPERTY_POLICY_DIR}/value.hpp
)

SET(GO_LIBS_SRC_GO_PROPERTY_POLICY_CPP)

########################################################
#  go/signals                                          #
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
#  go_boost                                            #
########################################################

SET(GO_BOOST_DIRNAME go_boost)
SET(GO_BOOST_DIR ${GO_LIBS_SOURCE_DIR}/go_boost)

# *.hpp

SET(GO_LIBS_SRC_GO_BOOST_HPP
    ${GO_BOOST_DIR}/mvvm.hpp
    ${GO_BOOST_DIR}/property.hpp
    ${GO_BOOST_DIR}/signals.hpp
)

# *.cpp

SET(GO_LIBS_SRC_GO_BOOST_CPP)

########################################################
#  go_boost/mvvm                                       #
########################################################

SET(GO_BOOST_MVVM_DIRNAME mvvm)
SET(GO_BOOST_MVVM_DIR ${GO_BOOST_DIR}/mvvm)

# *.hpp

SET(GO_LIBS_SRC_GO_BOOST_MVVM_HPP
    ${GO_BOOST_MVVM_DIR}/command.hpp
    ${GO_BOOST_MVVM_DIR}/command_manager.hpp
    ${GO_BOOST_MVVM_DIR}/command_parameters.hpp
    ${GO_BOOST_MVVM_DIR}/container_changed_arguments.hpp
    ${GO_BOOST_MVVM_DIR}/notify_container_changed.hpp
    ${GO_BOOST_MVVM_DIR}/notify_container_changed_action.hpp
    ${GO_BOOST_MVVM_DIR}/notify_property_changed.hpp
    ${GO_BOOST_MVVM_DIR}/object.hpp
    ${GO_BOOST_MVVM_DIR}/observable_object.hpp
    ${GO_BOOST_MVVM_DIR}/property_changed_arguments.hpp
    ${GO_BOOST_MVVM_DIR}/relay_command.hpp
    ${GO_BOOST_MVVM_DIR}/utility.hpp
)

# *.cpp

SET(GO_LIBS_SRC_GO_BOOST_MVVM_CPP)

########################################################
#  go_boost/mvvm/utility                               #
########################################################

SET(GO_BOOST_MVVM_UTILITY_DIRNAME mvvm)
SET(GO_BOOST_MVVM_UTILITY_DIR ${GO_BOOST_DIR}/mvvm/utility)

# *.hpp

SET(GO_LIBS_SRC_GO_BOOST_MVVM_UTILITY_HPP
    ${GO_BOOST_MVVM_UTILITY_DIR}/phoenix_property_get_relay_command_functor.hpp
    ${GO_BOOST_MVVM_UTILITY_DIR}/phoenix_property_set_value_notify_changed_functor.hpp
    ${GO_BOOST_MVVM_UTILITY_DIR}/phoenix_property_value_access_functor.hpp
)

# *.cpp

SET(GO_LIBS_SRC_GO_BOOST_MVVM_UTILITY_CPP)

########################################################
#  go_boost/property                                   #
########################################################

SET(GO_BOOST_PROPERTY_DIRNAME /property)
SET(GO_BOOST_PROPERTY_DIR ${GO_BOOST_DIR}/property)

# *.hpp

SET(GO_LIBS_SRC_GO_BOOST_PROPERTY_HPP
    ${GO_BOOST_PROPERTY_DIR}/property.hpp
    ${GO_BOOST_PROPERTY_DIR}/read_only_property.hpp
    ${GO_BOOST_PROPERTY_DIR}/read_only_reference_property.hpp
    ${GO_BOOST_PROPERTY_DIR}/read_only_value_property.hpp
    ${GO_BOOST_PROPERTY_DIR}/reference_property.hpp
    ${GO_BOOST_PROPERTY_DIR}/value_property.hpp
    ${GO_BOOST_PROPERTY_DIR}/write_only_property.hpp
    ${GO_BOOST_PROPERTY_DIR}/write_only_reference_property.hpp
    ${GO_BOOST_PROPERTY_DIR}/write_only_value_property.hpp
)

# *.cpp

SET(GO_LIBS_SRC_GO_BOOST_PROPERTY_CPP)

########################################################
#  go_boost/property/detail                            #
########################################################

SET(GO_BOOST_PROPERTY_DETAIL_DIRNAME property/detail)
SET(GO_BOOST_PROPERTY_DETAIL_DIR ${GO_BOOST_DIR}/property/detail)

# *.hpp

SET(GO_LIBS_SRC_GO_BOOST_PROPERTY_DETAIL_HPP
    ${GO_BOOST_PROPERTY_DETAIL_DIR}/assignment_operator.hpp
    ${GO_BOOST_PROPERTY_DETAIL_DIR}/property_base.hpp
    ${GO_BOOST_PROPERTY_DETAIL_DIR}/read_only_property_base.hpp
    ${GO_BOOST_PROPERTY_DETAIL_DIR}/write_only_property_base.hpp
)

SET(GO_LIBS_SRC_GO_BOOST_PROPERTY_DETAIL_CPP)

########################################################
#  go_boost/property/policy                            #
########################################################

SET(GO_BOOST_PROPERTY_POLICY_DIRNAME property/policy)
SET(GO_BOOST_PROPERTY_POLICY_DIR ${GO_BOOST_DIR}/property/policy)

# *.hpp

SET(GO_LIBS_SRC_GO_BOOST_PROPERTY_POLICY_HPP
    ${GO_BOOST_PROPERTY_POLICY_DIR}/proxy.hpp
    ${GO_BOOST_PROPERTY_POLICY_DIR}/reference.hpp
    ${GO_BOOST_PROPERTY_POLICY_DIR}/value.hpp
)

SET(GO_LIBS_SRC_GO_BOOST_PROPERTY_POLICY_CPP)

########################################################
#  go_boost/signals                                    #
########################################################

SET(GO_BOOST_SIGNALS_DIRNAME signals)
SET(GO_BOOST_SIGNALS_DIR ${GO_BOOST_DIR}/signals)

# *.hpp

SET(GO_LIBS_SRC_GO_BOOST_SIGNALS_HPP
    ${GO_BOOST_SIGNALS_DIR}/slot.hpp
    ${GO_BOOST_SIGNALS_DIR}/slot_arguments.hpp
)

# *.cpp

SET(GO_LIBS_SRC_GO_BOOST_SIGNALS_CPP)

########################################################
#  libs                                                #
########################################################

ADD_SUBDIRECTORY(libs)

INSTALL(FILES ${GO_LIBS_SRC_GO_HPP}                  DESTINATION  include/${GO_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_MVVM_HPP}             DESTINATION  include/${GO_DIRNAME}/${GO_MVVM_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_HPP}         DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_DETAIL_HPP}  DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_POLICY_HPP}  DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_POLICY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_SIGNALS_HPP}          DESTINATION  include/${GO_DIRNAME}/${GO_SIGNALS_DIRNAME})

INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_HPP}                  DESTINATION  include/${GO_BOOST_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_MVVM_HPP}             DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_MVVM_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_MVVM_UTILITY_HPP}     DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_MVVM_UTILITY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_HPP}         DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_DETAIL_HPP}  DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_POLICY_HPP}  DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_POLICY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_SIGNALS_HPP}          DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_SIGNALS_DIRNAME})
