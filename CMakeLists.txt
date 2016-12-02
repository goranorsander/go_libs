cmake_minimum_required(VERSION 3.0)

project(GO_LIBS)

#Import all files, Headers and cpp files seperate.

#Options-------------------------------------------------

option(USE_SOLUTION_FOLDERS "Organise all projects into folders in your solution." ON)
option(BUILD_STD_MFC_EXAMPLES "Build the GO libraries MFC examples for std-implementation. Requires C++14.")
option(BUILD_BOOST_MFC_EXAMPLES "Build the GO libraries MFC examples for boost-implementation. Requires the Boost libraries.")
option(BUILD_STD_TESTS "Build the GO libraries unit tests for std-implementation. Uses the google test framework. Requires C++14.")
option(BUILD_BOOST_TESTS "Build the GO libraries unit tests for boost-implementation. Uses the google test framework. Requires the Boost libraries.")
set(BOOST_MAJOR_VERSION "1" CACHE STRING "Boost libraries major version.")
set(BOOST_MINOR_VERSION "61" CACHE STRING "Boost libraries minor version.")
set(BOOST_INCLUDEDIR $ENV{BOOST_LIBS_INCLUDE} CACHE STRING "Boost libraries include directory.")
set(BOOST_LIBRARYDIR $ENV{BOOST_LIBS_STATIC_LINK} CACHE STRING "Boost libraries library directory.")

if(USE_SOLUTION_FOLDERS)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
else(USE_SOLUTION_FOLDERS)
    set_property(GLOBAL PROPERTY USE_FOLDERS OFF)
endif(USE_SOLUTION_FOLDERS)

########################################################
#  compiler flags                                      #
########################################################

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # using Clang
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # using gcc/g++
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14 -fpermissive  -ftemplate-backtrace-limit=0" )
	
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
    # using Intel C++
elseif(MSVC)
    # using Visual Studio C++
    if(MSVC_VERSION EQUAL 1700)
        # using Visual Studio 2012 C++
        set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /D \"_VARIADIC_MAX=10\"" )
    endif(MSVC_VERSION EQUAL 1700)
endif()

########################################################
#  compiler version                                    #
########################################################

if(CMAKE_COMPILER_IS_GNUCC)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS ${GCC_VERSION})
    list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
    list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)
endif(CMAKE_COMPILER_IS_GNUCC)

########################################################
#  external dependencies                               #
########################################################

if(CMAKE_COMPILER_IS_GNUCC)
	set(BOOST_GCC_VERSION "${GCC_MAJOR}${GCC_MINOR}")
    if(MSYS OR MINGW)
	    set(LIBBOOST_SYSTEM "libboost_system-mgw${BOOST_GCC_VERSION}-mt-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
	else(MSYS OR MINGW)
	    set(LIBBOOST_SYSTEM "libboost_system-gcc${BOOST_GCC_VERSION}-mt-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
	endif(MSYS OR MINGW)
endif(CMAKE_COMPILER_IS_GNUCC)

if(BUILD_STD_TESTS OR BUILD_BOOST_TESTS)

    # Download and unpack googletest at configure time
    configure_file(CMakeLists.googletest.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

    # Prevent GoogleTest from overriding our
    # compiler/linker options when building with
    # Visual Studio
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif(MSVC)

    # Properly disable phtreads when compiling with
    # MSYS/MinGW on Windows
    if(MSYS OR MINGW)
        set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
    endif(MSYS OR MINGW)

    # Add googletest directly to our build. This adds
    # the following targets: gtest, gtest_main, gmock
    # and gmock_main
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src ${CMAKE_BINARY_DIR}/googletest-build)

    include_directories("${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")
    link_directories("${gtest_BINARY_DIR}" "${gmock_BINARY_DIR}")

endif(BUILD_STD_TESTS OR BUILD_BOOST_TESTS)

########################################################
#  go                                                  #
########################################################

set(GO_DIRNAME go)
set(GO_DIR ${GO_LIBS_SOURCE_DIR}/go)

# *.hpp

set(GO_LIBS_SRC_GO_HPP
    ${GO_DIR}/config.hpp
    ${GO_DIR}/mvvm.hpp
    ${GO_DIR}/property.hpp
    ${GO_DIR}/signals.hpp
    ${GO_DIR}/utility.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_CPP)

########################################################
#  go/config                                           #
########################################################

set(GO_CONFIG_DIRNAME config)
set(GO_CONFIG_DIR ${GO_DIR}/config)

# *.hpp

set(GO_LIBS_SRC_GO_CONFIG_HPP
    ${GO_CONFIG_DIR}/select_compiler_config.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_CONFIG_CPP)

########################################################
#  go/config/compiler                                  #
########################################################

set(GO_CONFIG_COMPILER_DIRNAME config/compiler)
set(GO_CONFIG_COMPILER_DIR ${GO_CONFIG_DIR}/compiler)

# *.hpp

set(GO_LIBS_SRC_GO_CONFIG_COMPILER_HPP
    ${GO_CONFIG_COMPILER_DIR}/gcc.hpp
    ${GO_CONFIG_COMPILER_DIR}/visualc.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_CONFIG_COMPILER_CPP)

########################################################
#  go/mvvm                                             #
########################################################

set(GO_MVVM_DIRNAME mvvm)
set(GO_MVVM_DIR ${GO_DIR}/mvvm)

# *.hpp

set(GO_LIBS_SRC_GO_MVVM_HPP
    ${GO_MVVM_DIR}/command.hpp
    ${GO_MVVM_DIR}/command_execution_observer_interface.hpp
    ${GO_MVVM_DIR}/command_manager.hpp
    ${GO_MVVM_DIR}/command_parameters.hpp
    ${GO_MVVM_DIR}/container_changed_arguments.hpp
    ${GO_MVVM_DIR}/data_context_changed_arguments.hpp
    ${GO_MVVM_DIR}/data_context_changing_arguments.hpp
    ${GO_MVVM_DIR}/data_context_interface.hpp
    ${GO_MVVM_DIR}/notify_command_execution_interface.hpp
    ${GO_MVVM_DIR}/notify_container_changed_action.hpp
    ${GO_MVVM_DIR}/notify_container_changed_interface.hpp
    ${GO_MVVM_DIR}/notify_data_context_changed_interface.hpp
    ${GO_MVVM_DIR}/notify_property_changed_interface.hpp
    ${GO_MVVM_DIR}/notify_view_model_changed_interface.hpp
    ${GO_MVVM_DIR}/object.hpp
    ${GO_MVVM_DIR}/object_observer_interface.hpp
    ${GO_MVVM_DIR}/observable_array.hpp
    ${GO_MVVM_DIR}/observable_associative_container.hpp
    ${GO_MVVM_DIR}/observable_container.hpp
    ${GO_MVVM_DIR}/observable_deque.hpp
    ${GO_MVVM_DIR}/observable_forward_list.hpp
    ${GO_MVVM_DIR}/observable_list.hpp
    ${GO_MVVM_DIR}/observable_map.hpp
    ${GO_MVVM_DIR}/observable_multimap.hpp
    ${GO_MVVM_DIR}/observable_multiset.hpp
    ${GO_MVVM_DIR}/observable_object.hpp
    ${GO_MVVM_DIR}/observable_ordered_associative_container.hpp
    ${GO_MVVM_DIR}/observable_sequence_container.hpp
    ${GO_MVVM_DIR}/observable_set.hpp
    ${GO_MVVM_DIR}/observable_unordered_associative_container.hpp
    ${GO_MVVM_DIR}/observable_unordered_map.hpp
    ${GO_MVVM_DIR}/observable_unordered_multimap.hpp
    ${GO_MVVM_DIR}/observable_unordered_multiset.hpp
    ${GO_MVVM_DIR}/observable_unordered_set.hpp
    ${GO_MVVM_DIR}/observable_vector.hpp
    ${GO_MVVM_DIR}/property_changed_arguments.hpp
    ${GO_MVVM_DIR}/relay_command.hpp
    ${GO_MVVM_DIR}/utility.hpp
    ${GO_MVVM_DIR}/view_model_changed_arguments.hpp
    ${GO_MVVM_DIR}/view_model_changing_arguments.hpp
    ${GO_MVVM_DIR}/view_model_interface.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_MVVM_CPP)

########################################################
#  go/mvvm/utility                                     #
########################################################

set(GO_MVVM_UTILITY_DIRNAME utility)
set(GO_MVVM_UTILITY_DIR ${GO_MVVM_DIR}/utility)

# *.hpp

set(GO_LIBS_SRC_GO_MVVM_UTILITY_HPP
    ${GO_MVVM_UTILITY_DIR}/mfc_dlgdata.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_MVVM_UTILITY_CPP)

########################################################
#  go/property                                         #
########################################################

set(GO_PROPERTY_DIRNAME /property)
set(GO_PROPERTY_DIR ${GO_DIR}/property)

# *.hpp

set(GO_LIBS_SRC_GO_PROPERTY_HPP
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

set(GO_LIBS_SRC_GO_PROPERTY_CPP)

########################################################
#  go/property/detail                                  #
########################################################

set(GO_PROPERTY_DETAIL_DIRNAME property/detail)
set(GO_PROPERTY_DETAIL_DIR ${GO_DIR}/property/detail)

# *.hpp

set(GO_LIBS_SRC_GO_PROPERTY_DETAIL_HPP
    ${GO_PROPERTY_DETAIL_DIR}/arithmetic_comparison_operators.hpp
    ${GO_PROPERTY_DETAIL_DIR}/assignment_operator.hpp
    ${GO_PROPERTY_DETAIL_DIR}/property_base.hpp
    ${GO_PROPERTY_DETAIL_DIR}/read_only_property_base.hpp
    ${GO_PROPERTY_DETAIL_DIR}/write_only_property_base.hpp
)

set(GO_LIBS_SRC_GO_PROPERTY_DETAIL_CPP)

########################################################
#  go/property/nameless                                #
########################################################

set(GO_PROPERTY_NAMELESS_DIRNAME property/nameless)
set(GO_PROPERTY_NAMELESS_DIR ${GO_DIR}/property/nameless)

# *.hpp

set(GO_LIBS_SRC_GO_PROPERTY_NAMELESS_HPP
    ${GO_PROPERTY_NAMELESS_DIR}/property.hpp
    ${GO_PROPERTY_NAMELESS_DIR}/read_only_property.hpp
    ${GO_PROPERTY_NAMELESS_DIR}/read_only_reference_property.hpp
    ${GO_PROPERTY_NAMELESS_DIR}/read_only_value_property.hpp
    ${GO_PROPERTY_NAMELESS_DIR}/reference_property.hpp
    ${GO_PROPERTY_NAMELESS_DIR}/value_property.hpp
    ${GO_PROPERTY_NAMELESS_DIR}/write_only_property.hpp
    ${GO_PROPERTY_NAMELESS_DIR}/write_only_reference_property.hpp
    ${GO_PROPERTY_NAMELESS_DIR}/write_only_value_property.hpp
)

set(GO_LIBS_SRC_GO_PROPERTY_NAMELESS_CPP)

########################################################
#  go/property/nameless/detail                         #
########################################################

set(GO_PROPERTY_NAMELESS_DETAIL_DIRNAME property/nameless/detail)
set(GO_PROPERTY_NAMELESS_DETAIL_DIR ${GO_DIR}/property/nameless/detail)

# *.hpp

set(GO_LIBS_SRC_GO_PROPERTY_NAMELESS_DETAIL_HPP
    ${GO_PROPERTY_NAMELESS_DETAIL_DIR}/arithmetic_comparison_operators.hpp
    ${GO_PROPERTY_NAMELESS_DETAIL_DIR}/property_base.hpp
    ${GO_PROPERTY_NAMELESS_DETAIL_DIR}/read_only_property_base.hpp
    ${GO_PROPERTY_NAMELESS_DETAIL_DIR}/write_only_property_base.hpp
)

set(GO_LIBS_SRC_GO_PROPERTY_NAMELESS_DETAIL_CPP)

########################################################
#  go/property/policy                                  #
########################################################

set(GO_PROPERTY_POLICY_DIRNAME property/policy)
set(GO_PROPERTY_POLICY_DIR ${GO_DIR}/property/policy)

# *.hpp

set(GO_LIBS_SRC_GO_PROPERTY_POLICY_HPP
    ${GO_PROPERTY_POLICY_DIR}/proxy.hpp
    ${GO_PROPERTY_POLICY_DIR}/reference.hpp
    ${GO_PROPERTY_POLICY_DIR}/value.hpp
)

set(GO_LIBS_SRC_GO_PROPERTY_POLICY_CPP)

########################################################
#  go/signals                                          #
########################################################

set(GO_SIGNALS_DIRNAME signals)
set(GO_SIGNALS_DIR ${GO_DIR}/signals)

# *.hpp

set(GO_LIBS_SRC_GO_SIGNALS_HPP
    ${GO_SIGNALS_DIR}/signal.hpp
    ${GO_SIGNALS_DIR}/slot.hpp
    ${GO_SIGNALS_DIR}/slot_arguments.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_SIGNALS_CPP)

########################################################
#  go/utility                                          #
########################################################

set(GO_UTILITY_DIRNAME utility)
set(GO_UTILITY_DIR ${GO_DIR}/utility)

# *.hpp

set(GO_LIBS_SRC_GO_UTILITY_HPP
    ${GO_UTILITY_DIR}/noncopyable.hpp
    ${GO_UTILITY_DIR}/noncopyable_nonmovable.hpp
    ${GO_UTILITY_DIR}/nonmovable.hpp
    ${GO_UTILITY_DIR}/sanity.hpp
    ${GO_UTILITY_DIR}/scope_guard.hpp
    ${GO_UTILITY_DIR}/scope_guard_new.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_UTILITY_CPP)

########################################################
#  go/utility/iterator                                 #
########################################################

set(GO_UTILITY_ITERATOR_DIRNAME utility/iterator)
set(GO_UTILITY_ITERATOR_DIR ${GO_DIR}/utility/iterator)

# *.hpp

set(GO_LIBS_SRC_GO_UTILITY_ITERATOR_HPP
    ${GO_UTILITY_ITERATOR_DIR}/forward_iterator.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_UTILITY_ITERATOR_CPP)

########################################################
#  go_boost                                            #
########################################################

set(GO_BOOST_DIRNAME go_boost)
set(GO_BOOST_DIR ${GO_LIBS_SOURCE_DIR}/go_boost)

# *.hpp

set(GO_LIBS_SRC_GO_BOOST_HPP
    ${GO_BOOST_DIR}/mvvm.hpp
    ${GO_BOOST_DIR}/property.hpp
    ${GO_BOOST_DIR}/signals.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_BOOST_CPP)

########################################################
#  go_boost/mvvm                                       #
########################################################

set(GO_BOOST_MVVM_DIRNAME mvvm)
set(GO_BOOST_MVVM_DIR ${GO_BOOST_DIR}/mvvm)

# *.hpp

set(GO_LIBS_SRC_GO_BOOST_MVVM_HPP
    ${GO_BOOST_MVVM_DIR}/command.hpp
    ${GO_BOOST_MVVM_DIR}/command_execution_observer_interface.hpp
    ${GO_BOOST_MVVM_DIR}/command_manager.hpp
    ${GO_BOOST_MVVM_DIR}/command_parameters.hpp
    ${GO_BOOST_MVVM_DIR}/container_changed_arguments.hpp
    ${GO_BOOST_MVVM_DIR}/data_context_changed_arguments.hpp
    ${GO_BOOST_MVVM_DIR}/data_context_changing_arguments.hpp
    ${GO_BOOST_MVVM_DIR}/data_context_interface.hpp
    ${GO_BOOST_MVVM_DIR}/notify_command_execution_interface.hpp
    ${GO_BOOST_MVVM_DIR}/notify_container_changed_action.hpp
    ${GO_BOOST_MVVM_DIR}/notify_container_changed_interface.hpp
    ${GO_BOOST_MVVM_DIR}/notify_data_context_changed_interface.hpp
    ${GO_BOOST_MVVM_DIR}/notify_property_changed_interface.hpp
    ${GO_BOOST_MVVM_DIR}/notify_view_model_changed_interface.hpp
    ${GO_BOOST_MVVM_DIR}/object.hpp
    ${GO_BOOST_MVVM_DIR}/object_observer_interface.hpp
    ${GO_BOOST_MVVM_DIR}/observable_array.hpp
    ${GO_BOOST_MVVM_DIR}/observable_associative_container.hpp
    ${GO_BOOST_MVVM_DIR}/observable_container.hpp
    ${GO_BOOST_MVVM_DIR}/observable_deque.hpp
    ${GO_BOOST_MVVM_DIR}/observable_forward_list.hpp
    ${GO_BOOST_MVVM_DIR}/observable_list.hpp
    ${GO_BOOST_MVVM_DIR}/observable_map.hpp
    ${GO_BOOST_MVVM_DIR}/observable_multimap.hpp
    ${GO_BOOST_MVVM_DIR}/observable_multiset.hpp
    ${GO_BOOST_MVVM_DIR}/observable_object.hpp
    ${GO_BOOST_MVVM_DIR}/observable_ordered_associative_container.hpp
    ${GO_BOOST_MVVM_DIR}/observable_sequence_container.hpp
    ${GO_BOOST_MVVM_DIR}/observable_set.hpp
    ${GO_BOOST_MVVM_DIR}/observable_unordered_associative_container.hpp
    ${GO_BOOST_MVVM_DIR}/observable_unordered_map.hpp
    ${GO_BOOST_MVVM_DIR}/observable_unordered_multimap.hpp
    ${GO_BOOST_MVVM_DIR}/observable_unordered_multiset.hpp
    ${GO_BOOST_MVVM_DIR}/observable_unordered_set.hpp
    ${GO_BOOST_MVVM_DIR}/observable_vector.hpp
    ${GO_BOOST_MVVM_DIR}/property_changed_arguments.hpp
    ${GO_BOOST_MVVM_DIR}/relay_command.hpp
    ${GO_BOOST_MVVM_DIR}/utility.hpp
    ${GO_BOOST_MVVM_DIR}/view_model_changed_arguments.hpp
    ${GO_BOOST_MVVM_DIR}/view_model_changing_arguments.hpp
    ${GO_BOOST_MVVM_DIR}/view_model_interface.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_BOOST_MVVM_CPP)

########################################################
#  go_boost/mvvm/utility                               #
########################################################

set(GO_BOOST_MVVM_UTILITY_DIRNAME mvvm)
set(GO_BOOST_MVVM_UTILITY_DIR ${GO_BOOST_DIR}/mvvm/utility)

# *.hpp

set(GO_LIBS_SRC_GO_BOOST_MVVM_UTILITY_HPP
    ${GO_BOOST_MVVM_UTILITY_DIR}/mfc_dlgdata.hpp
    ${GO_BOOST_MVVM_UTILITY_DIR}/phoenix_property_get_relay_command_functor.hpp
    ${GO_BOOST_MVVM_UTILITY_DIR}/phoenix_property_set_value_notify_changed_functor.hpp
    ${GO_BOOST_MVVM_UTILITY_DIR}/phoenix_property_value_access_functor.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_BOOST_MVVM_UTILITY_CPP)

########################################################
#  go_boost/property                                   #
########################################################

set(GO_BOOST_PROPERTY_DIRNAME /property)
set(GO_BOOST_PROPERTY_DIR ${GO_BOOST_DIR}/property)

# *.hpp

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_HPP
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

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_CPP)

########################################################
#  go_boost/property/detail                            #
########################################################

set(GO_BOOST_PROPERTY_DETAIL_DIRNAME property/detail)
set(GO_BOOST_PROPERTY_DETAIL_DIR ${GO_BOOST_DIR}/property/detail)

# *.hpp

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_DETAIL_HPP
    ${GO_BOOST_PROPERTY_DETAIL_DIR}/arithmetic_comparison_operators.hpp
    ${GO_BOOST_PROPERTY_DETAIL_DIR}/assignment_operator.hpp
    ${GO_BOOST_PROPERTY_DETAIL_DIR}/property_base.hpp
    ${GO_BOOST_PROPERTY_DETAIL_DIR}/read_only_property_base.hpp
    ${GO_BOOST_PROPERTY_DETAIL_DIR}/write_only_property_base.hpp
)

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_DETAIL_CPP)

########################################################
#  go_boost/property/nameless                          #
########################################################

set(GO_BOOST_PROPERTY_NAMELESS_DIRNAME property/nameless)
set(GO_BOOST_PROPERTY_NAMELESS_DIR ${GO_DIR}/property/nameless)

# *.hpp

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_HPP
    ${GO_BOOST_PROPERTY_NAMELESS_DIR}/property.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DIR}/read_only_property.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DIR}/read_only_reference_property.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DIR}/read_only_value_property.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DIR}/reference_property.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DIR}/value_property.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DIR}/write_only_property.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DIR}/write_only_reference_property.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DIR}/write_only_value_property.hpp
)

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_CPP)

########################################################
#  go_boost/property/nameless/detail                   #
########################################################

set(GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIRNAME property/nameless/detail)
set(GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR ${GO_DIR}/property/nameless/detail)

# *.hpp

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_DETAIL_HPP
    ${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR}/arithmetic_comparison_operators.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR}/property_base.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR}/read_only_property_base.hpp
    ${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR}/write_only_property_base.hpp
)

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_DETAIL_CPP)

########################################################
#  go_boost/property/policy                            #
########################################################

set(GO_BOOST_PROPERTY_POLICY_DIRNAME property/policy)
set(GO_BOOST_PROPERTY_POLICY_DIR ${GO_BOOST_DIR}/property/policy)

# *.hpp

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_POLICY_HPP
    ${GO_BOOST_PROPERTY_POLICY_DIR}/proxy.hpp
    ${GO_BOOST_PROPERTY_POLICY_DIR}/reference.hpp
    ${GO_BOOST_PROPERTY_POLICY_DIR}/value.hpp
)

set(GO_LIBS_SRC_GO_BOOST_PROPERTY_POLICY_CPP)

########################################################
#  go_boost/signals                                    #
########################################################

set(GO_BOOST_SIGNALS_DIRNAME signals)
set(GO_BOOST_SIGNALS_DIR ${GO_BOOST_DIR}/signals)

# *.hpp

set(GO_LIBS_SRC_GO_BOOST_SIGNALS_HPP
    ${GO_BOOST_SIGNALS_DIR}/slot.hpp
    ${GO_BOOST_SIGNALS_DIR}/slot_arguments.hpp
)

# *.cpp

set(GO_LIBS_SRC_GO_BOOST_SIGNALS_CPP)

########################################################
#  libs                                                #
########################################################

set(BOOST_PROJECT_NAME_STR GO_libraries_boost)
set(STD_PROJECT_NAME_STR GO_libraries_std)

ADD_SUBDIRECTORY(go)
ADD_SUBDIRECTORY(go_boost)
ADD_SUBDIRECTORY(libs)

INSTALL(FILES ${GO_LIBS_SRC_GO_HPP}                            DESTINATION  include/${GO_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_CONFIG_HPP}                     DESTINATION  include/${GO_DIRNAME}/${GO_CONFIG_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_CONFIG_COMPILER_HPP}            DESTINATION  include/${GO_DIRNAME}/${GO_CONFIG_COMPILER_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_MVVM_HPP}                       DESTINATION  include/${GO_DIRNAME}/${GO_MVVM_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_MVVM_UTILITY_HPP}               DESTINATION  include/${GO_DIRNAME}/${GO_MVVM_UTILITY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_HPP}                   DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_DETAIL_HPP}            DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_NAMELESS_HPP}          DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_NAMELESS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_NAMELESS_DETAIL_HPP}   DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_NAMELESS_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_POLICY_HPP}            DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_POLICY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_SIGNALS_HPP}                    DESTINATION  include/${GO_DIRNAME}/${GO_SIGNALS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_UTILITY_HPP}                    DESTINATION  include/${GO_DIRNAME}/${GO_UTILITY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_UTILITY_ITERATOR_HPP}           DESTINATION  include/${GO_DIRNAME}/${GO_UTILITY_ITERATOR_DIRNAME})

INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_HPP}                            DESTINATION  include/${GO_BOOST_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_MVVM_HPP}                       DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_MVVM_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_MVVM_UTILITY_HPP}               DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_MVVM_UTILITY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_HPP}                   DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_DETAIL_HPP}            DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_HPP}          DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_NAMELESS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_DETAIL_HPP}   DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_POLICY_HPP}            DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_POLICY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_SIGNALS_HPP}                    DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_SIGNALS_DIRNAME})
