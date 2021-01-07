#
#  CMakeLists.txt
#
#  Copyright 2016-2021 Göran Orsander
#
#  This file is part of the GO.libraries.
#  Distributed under the GO Software License, Version 2.0.
#  See accompanying file LICENSE.md.
#

cmake_minimum_required(VERSION 3.10)

project(GO_LIBS)

#Import all files, Headers and cpp files seperate.

#Options-------------------------------------------------

option(USE_SOLUTION_FOLDERS "Organise all projects into folders in your solution." ON)
option(BUILD_STD_EXAMPLES "Build the GO libraries examples for std-implementation. Requires C++11/14/17/20.")
option(BUILD_STD_MFC_EXAMPLES "Build the GO libraries MFC examples for std-implementation. Requires MFC and C++11/14/17/20.")
option(BUILD_BOOST_EXAMPLES "Build the GO libraries examples for boost-implementation. Requires the Boost libraries.")
option(BUILD_BOOST_MFC_EXAMPLES "Build the GO libraries MFC examples for boost-implementation. Requires MFC and the Boost libraries.")
option(BUILD_STD_TESTS "Build the GO libraries unit tests for std-implementation. Uses the google test framework. Requires C++11/14/17/20.")
option(BUILD_BOOST_TESTS "Build the GO libraries unit tests for boost-implementation. Uses the google test framework. Requires the Boost libraries.")
option(BUILD_STD_RND "Build RnD applications for std-implementation. Uses the GO Std libraries. Requires C++11/14/17/20.")
option(BUILD_BOOST_RND "Build RnD applications for boost-implementation. Uses the GO Boost libraries. Requires the Boost libraries.")
option(ENABLE_SUPPRESS_WARNINGS "Enable the GO libraries macros to suppress warnings selectively" ON)

set(CXX_COMPILER_WARNING_LEVEL "W3" CACHE STRING "C++ compiler warning level")
set(CMAKE_CXX_COMPILER_WARNING_LEVELS "W0;W1;W2;W3;W4;W5")
set_property(CACHE CXX_COMPILER_WARNING_LEVEL PROPERTY STRINGS ${CMAKE_CXX_COMPILER_WARNING_LEVELS})

set(BOOST_MAJOR_VERSION "1" CACHE STRING "Boost libraries major version.")
set(BOOST_MINOR_VERSION "75" CACHE STRING "Boost libraries minor version.")
set(BOOST_PATCH_LEVEL "0" CACHE STRING "Boost libraries patch level.")
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

set( CMAKE_COMPILER_IS_CLANG FALSE )
set( CMAKE_COMPILER_IS_INTEL FALSE )
set( CMAKE_COMPILER_IS_MSVC FALSE )

set( CMAKE_MSVC_TOOLSET_VERSION 0 )

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # using Clang, see https://clang.llvm.org/docs/UsersManual.html and  https://clang.llvm.org/docs/DiagnosticsReference.html
    set( CMAKE_COMPILER_IS_CLANG TRUE )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a" )
	if(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W0")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w" )
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W1")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment -Wno-deprecated" )
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W2")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment -Wno-deprecated" )
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W3")
		# Use default warnings
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W4")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated -Wno-unused-local-typedefs" )
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W5")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra" )
	endif()
	if(ENABLE_SUPPRESS_WARNINGS)
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGO_ENABLE_SUPPRESS_WARNINGS=1 -DGO_BOOST_ENABLE_SUPPRESS_WARNINGS=1" )
	endif()
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # using gcc/g++, see https://gcc.gnu.org/onlinedocs/gcc/Standards.html#C_002b_002b-Language and https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
    else()
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a" )
    endif()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -ftemplate-backtrace-limit=0" )
	if(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W0")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w" )
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W1")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment -Wno-cpp -Wno-deprecated" )
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W2")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment -Wno-deprecated" )
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W3")
		# Use default warnings
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W4")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-class-memaccess -Wno-deprecated -Wno-unused-local-typedefs" )
	elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W5")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra" )
	endif()
	if(ENABLE_SUPPRESS_WARNINGS)
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGO_ENABLE_SUPPRESS_WARNINGS=1 -DGO_BOOST_ENABLE_SUPPRESS_WARNINGS=1" )
	endif()
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
    # using Intel C++
    set( CMAKE_COMPILER_IS_INTEL TRUE )
elseif(MSVC)
    # using Visual Studio C++, see https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/c-cpp-build-errors
    set( CMAKE_COMPILER_IS_MSVC TRUE )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj" )
    if((MSVC_VERSION GREATER_EQUAL 1500) AND (MSVC_VERSION LESS 1600))
        # using Visual Studio 2008 C++
        set( CMAKE_MSVC_TOOLSET_VERSION 90 )
		if(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W0")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W1")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1 /wd4503 /wd4505 /wd4512 /wd4714 /D _CRT_SECURE_NO_WARNINGS" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W2")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2 /wd4503 /wd4505 /wd4512 /wd4714 /D _CRT_SECURE_NO_WARNINGS" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W3")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /wd4503 /wd4505 /wd4512 /wd4714 /D _CRT_SECURE_NO_WARNINGS" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W4")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /wd4503 /wd4505 /wd4512 /wd4714 /D _CRT_SECURE_NO_WARNINGS" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W5")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
		endif()
    elseif(MSVC_VERSION GREATER_EQUAL 1600)
		if((MSVC_VERSION GREATER_EQUAL 1600) AND (MSVC_VERSION LESS 1700))
			# using Visual Studio 2010 C++
			set( CMAKE_MSVC_TOOLSET_VERSION 100 )
		elseif((MSVC_VERSION GREATER_EQUAL 1700) AND (MSVC_VERSION LESS 1800))
			# using Visual Studio 2012 C++
			set( CMAKE_MSVC_TOOLSET_VERSION 110 )
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D \"_VARIADIC_MAX=10\"" )
		elseif((MSVC_VERSION GREATER_EQUAL 1800) AND (MSVC_VERSION LESS 1900))
			# using Visual Studio 2013 C++
			set( CMAKE_MSVC_TOOLSET_VERSION 120 )
		elseif((MSVC_VERSION GREATER_EQUAL 1900) AND (MSVC_VERSION LESS 1910))
			# using Visual Studio 2015 C++
			set( CMAKE_MSVC_TOOLSET_VERSION 140 )
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14" )
		elseif((MSVC_VERSION GREATER_EQUAL 1910) AND (MSVC_VERSION LESS 1920))
			# using Visual Studio 2017 C++
			set( CMAKE_MSVC_TOOLSET_VERSION 141 )
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /D \"_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING\"" )
		elseif(MSVC_VERSION GREATER_EQUAL 1920)
			# using Visual Studio 2019 C++
			set( CMAKE_MSVC_TOOLSET_VERSION 142 )
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /D \"_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING\"" )
		endif((MSVC_VERSION GREATER_EQUAL 1600) AND (MSVC_VERSION LESS 1700))
		if(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W0")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W1")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W2")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W3")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W4")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
		elseif(${CXX_COMPILER_WARNING_LEVEL} STREQUAL "W5")
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall" )
		endif()
		if(MSVC_VERSION LESS_EQUAL 1900)
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4503" )
		endif()
		if(MSVC_VERSION LESS_EQUAL 1800)
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4512 /wd4714 /D _CRT_SECURE_NO_WARNINGS" )
		endif()
		if(MSVC_VERSION LESS_EQUAL 1600)
			set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4505" )
		endif()
    endif((MSVC_VERSION GREATER_EQUAL 1500) AND (MSVC_VERSION LESS 1600))
	if(ENABLE_SUPPRESS_WARNINGS)
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D \"GO_ENABLE_SUPPRESS_WARNINGS=1\" /D \"GO_BOOST_ENABLE_SUPPRESS_WARNINGS=1\"" )
	endif()
endif()

########################################################
#  architecture                                        #
########################################################

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64 bits
    set(LIBBOOST_ARCHITECTURE "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # 32 bits
    set(LIBBOOST_ARCHITECTURE "x32")
endif()

########################################################
#  compiler version                                    #
########################################################

if(CMAKE_COMPILER_IS_CLANG)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE CLANG_VERSION_OUTPUT)
    string(REGEX REPLACE ".*clang version ([0-9]+\\.[0-9]+).*" "\\1" CLANG_VERSION ${CLANG_VERSION_OUTPUT})
    string(REGEX MATCHALL "[0-9]+" CLANG_VERSION_COMPONENTS ${CLANG_VERSION})
    list(GET CLANG_VERSION_COMPONENTS 0 CLANG_MAJOR)
    list(GET CLANG_VERSION_COMPONENTS 1 CLANG_MINOR)
elseif(CMAKE_COMPILER_IS_GNUCC)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS ${GCC_VERSION})
    list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
    list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)
endif(CMAKE_COMPILER_IS_CLANG)

########################################################
#  external dependencies                               #
########################################################

if(CMAKE_COMPILER_IS_CLANG)
    set(BOOST_CLANG_VERSION "${CLANG_MAJOR}")
    if(${BOOST_PATCH_LEVEL} STREQUAL "0")
        set(LIBBOOST_CHRONO "libboost_chrono-clang${BOOST_CLANG_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
        set(LIBBOOST_LOCALE "libboost_locale-clang${BOOST_CLANG_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
        set(LIBBOOST_SYSTEM "libboost_system-clang${BOOST_CLANG_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
        set(LIBBOOST_THREAD "libboost_thread-clang${BOOST_CLANG_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
    else(${BOOST_PATCH_LEVEL} STREQUAL "0")
        set(LIBBOOST_CHRONO "libboost_chrono-clang${BOOST_CLANG_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
        set(LIBBOOST_LOCALE "libboost_locale-clang${BOOST_CLANG_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
        set(LIBBOOST_SYSTEM "libboost_system-clang${BOOST_CLANG_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
        set(LIBBOOST_THREAD "libboost_thread-clang${BOOST_CLANG_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
    endif(${BOOST_PATCH_LEVEL} STREQUAL "0")
elseif(CMAKE_COMPILER_IS_GNUCC)
    set(BOOST_GCC_VERSION "${GCC_MAJOR}")
    if(${BOOST_PATCH_LEVEL} STREQUAL "0")
        if(MSYS OR MINGW)
            set(LIBBOOST_CHRONO "libboost_chrono-mgw${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
            set(LIBBOOST_LOCALE "libboost_locale-mgw${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
            set(LIBBOOST_SYSTEM "libboost_system-mgw${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
            set(LIBBOOST_THREAD "libboost_thread-mgw${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
        else(MSYS OR MINGW)
            set(LIBBOOST_CHRONO "libboost_chrono-gcc${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
            set(LIBBOOST_LOCALE "libboost_locale-gcc${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
            set(LIBBOOST_SYSTEM "libboost_system-gcc${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
            set(LIBBOOST_THREAD "libboost_thread-gcc${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.a")
        endif(MSYS OR MINGW)
    else(${BOOST_PATCH_LEVEL} STREQUAL "0")
        if(MSYS OR MINGW)
            set(LIBBOOST_CHRONO "libboost_chrono-mgw${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
            set(LIBBOOST_LOCALE "libboost_locale-mgw${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
            set(LIBBOOST_SYSTEM "libboost_system-mgw${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
            set(LIBBOOST_THREAD "libboost_thread-mgw${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
        else(MSYS OR MINGW)
            set(LIBBOOST_CHRONO "libboost_chrono-gcc${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
            set(LIBBOOST_LOCALE "libboost_locale-gcc${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
            set(LIBBOOST_SYSTEM "libboost_system-gcc${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
            set(LIBBOOST_THREAD "libboost_thread-gcc${BOOST_GCC_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.a")
        endif(MSYS OR MINGW)
    endif(${BOOST_PATCH_LEVEL} STREQUAL "0")
elseif(CMAKE_COMPILER_IS_MSVC)
    if(${BOOST_PATCH_LEVEL} STREQUAL "0")
        set(LIBBOOST_CHRONO "libboost_chrono-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.lib")
        set(LIBBOOST_LOCALE "libboost_locale-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.lib")
        set(LIBBOOST_SYSTEM "libboost_system-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.lib")
        set(LIBBOOST_THREAD "libboost_thread-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.lib")
        set(LIBBOOST_CHRONO_DEBUG "libboost_chrono-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-gd-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.lib")
        set(LIBBOOST_LOCALE_DEBUG "libboost_locale-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-gd-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.lib")
        set(LIBBOOST_SYSTEM_DEBUG "libboost_system-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-gd-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.lib")
        set(LIBBOOST_THREAD_DEBUG "libboost_thread-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-gd-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}.lib")
    else(${BOOST_PATCH_LEVEL} STREQUAL "0")
        set(LIBBOOST_CHRONO "libboost_chrono-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.lib")
        set(LIBBOOST_LOCALE "libboost_locale-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.lib")
        set(LIBBOOST_SYSTEM "libboost_system-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.lib")
        set(LIBBOOST_THREAD "libboost_thread-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.lib")
        set(LIBBOOST_CHRONO_DEBUG "libboost_chrono-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-gd-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.lib")
        set(LIBBOOST_LOCALE_DEBUG "libboost_locale-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-gd-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.lib")
        set(LIBBOOST_SYSTEM_DEBUG "libboost_system-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-gd-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.lib")
        set(LIBBOOST_THREAD_DEBUG "libboost_thread-vc${CMAKE_MSVC_TOOLSET_VERSION}-mt-gd-${LIBBOOST_ARCHITECTURE}-${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_LEVEL}.lib")
    endif(${BOOST_PATCH_LEVEL} STREQUAL "0")
endif(CMAKE_COMPILER_IS_CLANG)

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

    # Set googletest and googlemock directories
    set(GMOCK_INCLUDE_DIR ${CMAKE_BINARY_DIR}/googletest-src/googlemock/include)
    set(GTEST_INCLUDE_DIR ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)

    set(GMOCK_LIBS_DIR ${CMAKE_BINARY_DIR}/googletest-build/googlemock)
    set(GTEST_LIBS_DIR ${CMAKE_BINARY_DIR}/googletest-build/googlemock/gtest)

    set(GTEST_EXTENSIONS_INCLUDE_DIR ${GO_LIBS_SOURCE_DIR}/libs/gtest_extensions)

    # Add googletest directly to our build. This adds
    # the following targets: gtest, gtest_main, gmock
    # and gmock_main
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src ${CMAKE_BINARY_DIR}/googletest-build)

    include_directories(${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR} ${GTEST_EXTENSIONS_INCLUDE_DIR})
    link_directories(${GTEST_LIBS_DIR} ${GMOCK_LIBS_DIR})

endif(BUILD_STD_TESTS OR BUILD_BOOST_TESTS)

########################################################
#  .                                                   #
########################################################

set(ROOT_DIRNAME go_libs_root)
set(ROOT_DIR ${GO_LIBS_SOURCE_DIR})

# *.md

set(GO_LIBS_MD
    ${ROOT_DIR}/ACKNOWLEDGEMENTS.md
    ${ROOT_DIR}/COPYING.LESSER.md
    ${ROOT_DIR}/COPYING.md
    ${ROOT_DIR}/LICENSE.md
)

########################################################
#  go                                                  #
########################################################

set(GO_DIRNAME go)
set(GO_DIR ${GO_LIBS_SOURCE_DIR}/go)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_HPP ${GO_DIR}/*.hpp)

########################################################
#  go/async                                            #
########################################################

set(GO_ASYNC_DIRNAME async)
set(GO_ASYNC_DIR ${GO_DIR}/async)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_ASYNC_HPP ${GO_ASYNC_DIR}/*.hpp)

########################################################
#  go/config                                           #
########################################################

set(GO_CONFIG_DIRNAME config)
set(GO_CONFIG_DIR ${GO_DIR}/config)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_CONFIG_HPP ${GO_CONFIG_DIR}/*.hpp)

########################################################
#  go/config/compiler                                  #
########################################################

set(GO_CONFIG_COMPILER_DIRNAME config/compiler)
set(GO_CONFIG_COMPILER_DIR ${GO_CONFIG_DIR}/compiler)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_CONFIG_COMPILER_HPP ${GO_CONFIG_COMPILER_DIR}/*.hpp)

########################################################
#  go/config/platform                                  #
########################################################

set(GO_CONFIG_PLATFORM_DIRNAME config/platform)
set(GO_CONFIG_PLATFORM_DIR ${GO_CONFIG_DIR}/platform)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_CONFIG_PLATFORM_HPP ${GO_CONFIG_PLATFORM_DIR}/*.hpp)

########################################################
#  go/diagnostics                                      #
########################################################

set(GO_DIAGNOSTICS_DIRNAME diagnostics)
set(GO_DIAGNOSTICS_DIR ${GO_DIR}/diagnostics)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_DIAGNOSTICS_HPP ${GO_DIAGNOSTICS_DIR}/*.hpp)

########################################################
#  go/diagnostics/benchmark                            #
########################################################

set(GO_DIAGNOSTICS_BENCHMARK_DIRNAME diagnostics/benchmark)
set(GO_DIAGNOSTICS_BENCHMARK_DIR ${GO_DIAGNOSTICS_DIR}/benchmark)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_DIAGNOSTICS_BENCHMARK_HPP ${GO_DIAGNOSTICS_BENCHMARK_DIR}/*.hpp)

########################################################
#  go/diagnostics/log                                  #
########################################################

set(GO_DIAGNOSTICS_LOG_DIRNAME diagnostics/log)
set(GO_DIAGNOSTICS_LOG_DIR ${GO_DIAGNOSTICS_DIR}/log)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_DIAGNOSTICS_LOG_HPP ${GO_DIAGNOSTICS_LOG_DIR}/*.hpp)

########################################################
#  go/diagnostics/log/detail                           #
########################################################

set(GO_DIAGNOSTICS_LOG_DETAIL_DIRNAME diagnostics/log/detail)
set(GO_DIAGNOSTICS_LOG_DETAIL_DIR ${GO_DIAGNOSTICS_DIR}/log/detail)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_DIAGNOSTICS_LOG_DETAIL_HPP ${GO_DIAGNOSTICS_LOG_DETAIL_DIR}/*.hpp)

########################################################
#  go/diagnostics/log/policy                           #
########################################################

set(GO_DIAGNOSTICS_LOG_POLICY_DIRNAME diagnostics/log/policy)
set(GO_DIAGNOSTICS_LOG_POLICY_DIR ${GO_DIAGNOSTICS_DIR}/log/policy)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_DIAGNOSTICS_LOG_POLICY_HPP ${GO_DIAGNOSTICS_LOG_POLICY_DIR}/*.hpp)

########################################################
#  go/exception                                        #
########################################################

set(GO_EXCEPTION_DIRNAME exception)
set(GO_EXCEPTION_DIR ${GO_DIR}/exception)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_EXCEPTION_HPP ${GO_EXCEPTION_DIR}/*.hpp)

########################################################
#  go/mvvm                                             #
########################################################

set(GO_MVVM_DIRNAME mvvm)
set(GO_MVVM_DIR ${GO_DIR}/mvvm)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_MVVM_HPP ${GO_MVVM_DIR}/*.hpp)

########################################################
#  go/mvvm/iterator                                    #
########################################################

set(GO_MVVM_ITERATOR_DIRNAME iterator)
set(GO_MVVM_ITERATOR_DIR ${GO_MVVM_DIR}/iterator)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_MVVM_ITERATOR_HPP ${GO_MVVM_ITERATOR_DIR}/*.hpp)

########################################################
#  go/mvvm/utility                                     #
########################################################

set(GO_MVVM_UTILITY_DIRNAME utility)
set(GO_MVVM_UTILITY_DIR ${GO_MVVM_DIR}/utility)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_MVVM_UTILITY_HPP ${GO_MVVM_UTILITY_DIR}/*.hpp)

########################################################
#  go/property                                         #
########################################################

set(GO_PROPERTY_DIRNAME /property)
set(GO_PROPERTY_DIR ${GO_DIR}/property)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_PROPERTY_HPP ${GO_PROPERTY_DIR}/*.hpp)

########################################################
#  go/property/detail                                  #
########################################################

set(GO_PROPERTY_DETAIL_DIRNAME property/detail)
set(GO_PROPERTY_DETAIL_DIR ${GO_DIR}/property/detail)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_PROPERTY_DETAIL_HPP ${GO_PROPERTY_DETAIL_DIR}/*.hpp)

########################################################
#  go/property/nameless                                #
########################################################

set(GO_PROPERTY_NAMELESS_DIRNAME property/nameless)
set(GO_PROPERTY_NAMELESS_DIR ${GO_DIR}/property/nameless)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_PROPERTY_NAMELESS_HPP ${GO_PROPERTY_NAMELESS_DIR}/*.hpp)

########################################################
#  go/property/nameless/detail                         #
########################################################

set(GO_PROPERTY_NAMELESS_DETAIL_DIRNAME property/nameless/detail)
set(GO_PROPERTY_NAMELESS_DETAIL_DIR ${GO_DIR}/property/nameless/detail)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_PROPERTY_NAMELESS_DETAIL_HPP ${GO_PROPERTY_NAMELESS_DETAIL_DIR}/*.hpp)

########################################################
#  go/property/policy                                  #
########################################################

set(GO_PROPERTY_POLICY_DIRNAME property/policy)
set(GO_PROPERTY_POLICY_DIR ${GO_DIR}/property/policy)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_PROPERTY_POLICY_HPP ${GO_PROPERTY_POLICY_DIR}/*.hpp)

########################################################
#  go/signals                                          #
########################################################

set(GO_SIGNALS_DIRNAME signals)
set(GO_SIGNALS_DIR ${GO_DIR}/signals)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_SIGNALS_HPP ${GO_SIGNALS_DIR}/*.hpp)

########################################################
#  go/string                                           #
########################################################

set(GO_STRING_DIRNAME string)
set(GO_STRING_DIR ${GO_DIR}/string)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_STRING_HPP ${GO_STRING_DIR}/*.hpp)

########################################################
#  go/string/convert                                   #
########################################################

set(GO_STRING_CONVERT_DIRNAME string/convert)
set(GO_STRING_CONVERT_DIR ${GO_DIR}/string/convert)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_STRING_CONVERT_HPP ${GO_STRING_CONVERT_DIR}/*.hpp)

########################################################
#  go/string/encoding                                  #
########################################################

set(GO_STRING_ENCODING_DIRNAME string/encoding)
set(GO_STRING_ENCODING_DIR ${GO_DIR}/string/encoding)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_STRING_ENCODING_HPP ${GO_STRING_ENCODING_DIR}/*.hpp)

########################################################
#  go/string/traits                                    #
########################################################

set(GO_STRING_TRAITS_DIRNAME string/traits)
set(GO_STRING_TRAITS_DIR ${GO_DIR}/string/traits)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_STRING_TRAITS_HPP ${GO_STRING_TRAITS_DIR}/*.hpp)

########################################################
#  go/type_traits                                      #
########################################################

set(GO_TYPE_TRAITS_DIRNAME type_traits)
set(GO_TYPE_TRAITS_DIR ${GO_DIR}/type_traits)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_TYPE_TRAITS_HPP ${GO_TYPE_TRAITS_DIR}/*.hpp)

########################################################
#  go/type_traits/detail                               #
########################################################

set(GO_TYPE_TRAITS_DETAIL_DIRNAME type_traits/detail)
set(GO_TYPE_TRAITS_DETAIL_DIR ${GO_DIR}/type_traits/detail)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_TYPE_TRAITS_DETAIL_HPP ${GO_TYPE_TRAITS_DETAIL_DIR}/*.hpp)

########################################################
#  go/utility                                          #
########################################################

set(GO_UTILITY_DIRNAME utility)
set(GO_UTILITY_DIR ${GO_DIR}/utility)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_UTILITY_HPP ${GO_UTILITY_DIR}/*.hpp)

########################################################
#  go/utility/container                                #
########################################################

set(GO_UTILITY_CONTAINER_DIRNAME utility/container)
set(GO_UTILITY_CONTAINER_DIR ${GO_DIR}/utility/container)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_UTILITY_CONTAINER_HPP ${GO_UTILITY_CONTAINER_DIR}/*.hpp)

########################################################
#  go/utility/iterator                                 #
########################################################

set(GO_UTILITY_ITERATOR_DIRNAME utility/iterator)
set(GO_UTILITY_ITERATOR_DIR ${GO_DIR}/utility/iterator)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_UTILITY_ITERATOR_HPP ${GO_UTILITY_ITERATOR_DIR}/*.hpp)

########################################################
#  go/utility/range                                    #
########################################################

set(GO_UTILITY_RANGE_DIRNAME utility/range)
set(GO_UTILITY_RANGE_DIR ${GO_DIR}/utility/range)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_UTILITY_RANGE_HPP ${GO_UTILITY_RANGE_DIR}/*.hpp)

########################################################
#  go/utility/smart_ptr                                #
########################################################

set(GO_UTILITY_SMART_PTR_DIRNAME utility/smart_ptr)
set(GO_UTILITY_SMART_PTR_DIR ${GO_DIR}/utility/smart_ptr)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_UTILITY_SMART_PTR_HPP ${GO_UTILITY_SMART_PTR_DIR}/*.hpp)

########################################################
#  go_boost                                            #
########################################################

set(GO_BOOST_DIRNAME go_boost)
set(GO_BOOST_DIR ${GO_LIBS_SOURCE_DIR}/go_boost)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_HPP ${GO_BOOST_DIR}/*.hpp)

########################################################
#  go_boost/async                                      #
########################################################

set(GO_BOOST_ASYNC_DIRNAME async)
set(GO_BOOST_ASYNC_DIR ${GO_BOOST_DIR}/async)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_ASYNC_HPP ${GO_BOOST_ASYNC_DIR}/*.hpp)

########################################################
#  go_boost/config                                     #
########################################################

set(GO_BOOST_CONFIG_DIRNAME config)
set(GO_BOOST_CONFIG_DIR ${GO_DIR}/config)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_CONFIG_HPP ${GO_BOOST_CONFIG_DIR}/*.hpp)

########################################################
#  go_boost/config/compiler                            #
########################################################

set(GO_BOOST_CONFIG_COMPILER_DIRNAME config/compiler)
set(GO_BOOST_CONFIG_COMPILER_DIR ${GO_CONFIG_DIR}/compiler)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_CONFIG_COMPILER_HPP ${GO_BOOST_CONFIG_COMPILER_DIR}/*.hpp)

########################################################
#  go_boost/config/platform                            #
########################################################

set(GO_BOOST_CONFIG_PLATFORM_DIRNAME config/platform)
set(GO_BOOST_CONFIG_PLATFORM_DIR ${GO_BOOST_CONFIG_DIR}/platform)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_CONFIG_PLATFORM_HPP ${GO_BOOST_CONFIG_PLATFORM_DIR}/*.hpp)

########################################################
#  go_boost/diagnostics                                #
########################################################

set(GO_BOOST_DIAGNOSTICS_DIRNAME diagnostics)
set(GO_BOOST_DIAGNOSTICS_DIR ${GO_BOOST_DIR}/diagnostics)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_HPP ${GO_BOOST_DIAGNOSTICS_DIR}/*.hpp)

########################################################
#  go_boost/diagnostics/benchmark                      #
########################################################

set(GO_BOOST_DIAGNOSTICS_BENCHMARK_DIRNAME diagnostics/benchmark)
set(GO_BOOST_DIAGNOSTICS_BENCHMARK_DIR ${GO_BOOST_DIAGNOSTICS_DIR}/benchmark)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_BENCHMARK_HPP ${GO_BOOST_DIAGNOSTICS_BENCHMARK_DIR}/*.hpp)

########################################################
#  go_boost/diagnostics/log                            #
########################################################

set(GO_BOOST_DIAGNOSTICS_LOG_DIRNAME diagnostics/log)
set(GO_BOOST_DIAGNOSTICS_LOG_DIR ${GO_BOOST_DIAGNOSTICS_DIR}/log)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_LOG_HPP ${GO_BOOST_DIAGNOSTICS_LOG_DIR}/*.hpp)

########################################################
#  go_boost/diagnostics/log/detail                     #
########################################################

set(GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DIRNAME diagnostics/log/detail)
set(GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DIR ${GO_BOOST_DIAGNOSTICS_DIR}/log/detail)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_LOG_DETAIL_HPP ${GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DIR}/*.hpp)

########################################################
#  go_boost/diagnostics/log/policy                     #
########################################################

set(GO_BOOST_DIAGNOSTICS_LOG_POLICY_DIRNAME diagnostics/log/policy)
set(GO_BOOST_DIAGNOSTICS_LOG_POLICY_DIR ${GO_BOOST_DIAGNOSTICS_DIR}/log/policy)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_LOG_POLICY_HPP ${GO_BOOST_DIAGNOSTICS_LOG_POLICY_DIR}/*.hpp)

########################################################
#  go_boost/exception                                  #
########################################################

set(GO_BOOST_EXCEPTION_DIRNAME exception)
set(GO_BOOST_EXCEPTION_DIR ${GO_BOOST_DIR}/exception)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_EXCEPTION_HPP ${GO_BOOST_EXCEPTION_DIR}/*.hpp)

########################################################
#  go_boost/mvvm                                       #
########################################################

set(GO_BOOST_MVVM_DIRNAME mvvm)
set(GO_BOOST_MVVM_DIR ${GO_BOOST_DIR}/mvvm)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_MVVM_HPP ${GO_BOOST_MVVM_DIR}/*.hpp)

########################################################
#  go_boost/mvvm/iterator                              #
########################################################

set(GO_BOOST_MVVM_ITERATOR_DIRNAME iterator)
set(GO_BOOST_MVVM_ITERATOR_DIR ${GO_BOOST_MVVM_DIR}/iterator)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_MVVM_ITERATOR_HPP ${GO_BOOST_MVVM_ITERATOR_DIR}/*.hpp)

########################################################
#  go_boost/mvvm/utility                               #
########################################################

set(GO_BOOST_MVVM_UTILITY_DIRNAME mvvm)
set(GO_BOOST_MVVM_UTILITY_DIR ${GO_BOOST_DIR}/mvvm/utility)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_MVVM_UTILITY_HPP ${GO_BOOST_MVVM_UTILITY_DIR}/*.hpp)

########################################################
#  go_boost/property                                   #
########################################################

set(GO_BOOST_PROPERTY_DIRNAME /property)
set(GO_BOOST_PROPERTY_DIR ${GO_BOOST_DIR}/property)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_PROPERTY_HPP ${GO_BOOST_PROPERTY_DIR}/*.hpp)

########################################################
#  go_boost/property/detail                            #
########################################################

set(GO_BOOST_PROPERTY_DETAIL_DIRNAME property/detail)
set(GO_BOOST_PROPERTY_DETAIL_DIR ${GO_BOOST_DIR}/property/detail)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_PROPERTY_DETAIL_HPP ${GO_BOOST_PROPERTY_DETAIL_DIR}/*.hpp)

########################################################
#  go_boost/property/nameless                          #
########################################################

set(GO_BOOST_PROPERTY_NAMELESS_DIRNAME property/nameless)
set(GO_BOOST_PROPERTY_NAMELESS_DIR ${GO_BOOST_DIR}/property/nameless)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_HPP ${GO_BOOST_PROPERTY_NAMELESS_DIR}/*.hpp)

########################################################
#  go_boost/property/nameless/detail                   #
########################################################

set(GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIRNAME property/nameless/detail)
set(GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR ${GO_BOOST_DIR}/property/nameless/detail)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_DETAIL_HPP ${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIR}/*.hpp)

########################################################
#  go_boost/property/policy                            #
########################################################

set(GO_BOOST_PROPERTY_POLICY_DIRNAME property/policy)
set(GO_BOOST_PROPERTY_POLICY_DIR ${GO_BOOST_DIR}/property/policy)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_PROPERTY_POLICY_HPP ${GO_BOOST_PROPERTY_POLICY_DIR}/*.hpp)

########################################################
#  go_boost/signals                                    #
########################################################

set(GO_BOOST_SIGNALS_DIRNAME signals)
set(GO_BOOST_SIGNALS_DIR ${GO_BOOST_DIR}/signals)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_SIGNALS_HPP ${GO_BOOST_SIGNALS_DIR}/*.hpp)

########################################################
#  go_boost/string                                     #
########################################################

set(GO_BOOST_STRING_DIRNAME string)
set(GO_BOOST_STRING_DIR ${GO_BOOST_DIR}/string)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_STRING_HPP ${GO_BOOST_STRING_DIR}/*.hpp)

########################################################
#  go_boost/string/convert                             #
########################################################

set(GO_BOOST_STRING_CONVERT_DIRNAME string/convert)
set(GO_BOOST_STRING_CONVERT_DIR ${GO_BOOST_DIR}/string/convert)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_STRING_CONVERT_HPP ${GO_BOOST_STRING_CONVERT_DIR}/*.hpp)

########################################################
#  go_boost/string/encoding                            #
########################################################

set(GO_BOOST_STRING_ENCODING_DIRNAME string/encoding)
set(GO_BOOST_STRING_ENCODING_DIR ${GO_BOOST_DIR}/string/encoding)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_STRING_ENCODING_HPP ${GO_BOOST_STRING_ENCODING_DIR}/*.hpp)

########################################################
#  go_boost/string/traits                              #
########################################################

set(GO_BOOST_STRING_TRAITS_DIRNAME string/traits)
set(GO_BOOST_STRING_TRAITS_DIR ${GO_BOOST_DIR}/string/traits)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_STRING_TRAITS_HPP ${GO_BOOST_STRING_TRAITS_DIR}/*.hpp)

########################################################
#  go_boost/type_traits                                #
########################################################

set(GO_BOOST_TYPE_TRAITS_DIRNAME type_traits)
set(GO_BOOST_TYPE_TRAITS_DIR ${GO_BOOST_DIR}/type_traits)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_TYPE_TRAITS_HPP ${GO_BOOST_TYPE_TRAITS_DIR}/*.hpp)

########################################################
#  go_boost/type_traits/detail                         #
########################################################

set(GO_BOOST_TYPE_TRAITS_DETAIL_DIRNAME type_traits/detail)
set(GO_BOOST_TYPE_TRAITS_DETAIL_DIR ${GO_BOOST_DIR}/type_traits/detail)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_TYPE_TRAITS_DETAIL_HPP ${GO_BOOST_TYPE_TRAITS_DETAIL_DIR}/*.hpp)

########################################################
#  go_boost/utility                                    #
########################################################

set(GO_BOOST_UTILITY_DIRNAME utility)
set(GO_BOOST_UTILITY_DIR ${GO_BOOST_DIR}/utility)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_UTILITY_HPP ${GO_BOOST_UTILITY_DIR}/*.hpp)

########################################################
#  go_boost/utility/container                          #
########################################################

set(GO_BOOST_UTILITY_CONTAINER_DIRNAME utility/container)
set(GO_BOOST_UTILITY_CONTAINER_DIR ${GO_BOOST_DIR}/utility/container)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_UTILITY_CONTAINER_HPP ${GO_BOOST_UTILITY_CONTAINER_DIR}/*.hpp)

########################################################
#  go_boost/utility/iterator                           #
########################################################

set(GO_BOOST_UTILITY_ITERATOR_DIRNAME utility/iterator)
set(GO_BOOST_UTILITY_ITERATOR_DIR ${GO_BOOST_DIR}/utility/iterator)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_UTILITY_ITERATOR_HPP ${GO_UTILITY_ITERATOR_DIR}/*.hpp)

########################################################
#  go_boost/utility/range                              #
########################################################

set(GO_BOOST_UTILITY_RANGE_DIRNAME utility/range)
set(GO_BOOST_UTILITY_RANGE_DIR ${GO_BOOST_DIR}/utility/range)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_UTILITY_RANGE_HPP ${GO_BOOST_UTILITY_RANGE_DIR}/*.hpp)

########################################################
#  go_boost/utility/smart_ptr                          #
########################################################

set(GO_BOOST_UTILITY_SMART_PTR_DIRNAME utility/smart_ptr)
set(GO_BOOST_UTILITY_SMART_PTR_DIR ${GO_BOOST_DIR}/utility/smart_ptr)

# *.hpp

file(GLOB GO_LIBS_SRC_GO_BOOST_UTILITY_SMART_PTR_HPP ${GO_BOOST_UTILITY_SMART_PTR_DIR}/*.hpp)

########################################################
#  docs                                                #
########################################################

set(GO_LIBS_DOCS_DIRNAME docs)
set(GO_LIBS_DOCS_DIR ${GO_LIBS_SOURCE_DIR}/docs)

# *.md, *.yml

set(GO_LIBS_DOCS_FILES
    ${GO_LIBS_DOCS_DIR}/_config.yml
    ${GO_LIBS_DOCS_DIR}/index.md
)

set(GO_LIBS_DOCS_LAYOUTS_DIRNAME _layouts)
set(GO_LIBS_DOCS_LAYOUTS_DIR ${GO_LIBS_DOCS_DIR}/_layouts)

set(GO_LIBS_DOCS_SASS_DIRNAME _sass)
set(GO_LIBS_DOCS_SASS_DIR ${GO_LIBS_DOCS_DIR}/_sass)

########################################################
#  libs                                                #
########################################################

set(BOOST_PROJECT_NAME_STR GO_boost_libraries)
set(STD_PROJECT_NAME_STR GO_std_libraries)

ADD_SUBDIRECTORY(docs)
ADD_SUBDIRECTORY(go)
ADD_SUBDIRECTORY(go_boost)
ADD_SUBDIRECTORY(libs)
ADD_SUBDIRECTORY(rnd)

INSTALL(FILES ${GO_LIBS_MD}    DESTINATION  .)

INSTALL(FILES ${GO_LIBS_SRC_GO_HPP}                            DESTINATION  include/${GO_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_ASYNC_HPP}                      DESTINATION  include/${GO_DIRNAME}/${GO_ASYNC_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_CONFIG_HPP}                     DESTINATION  include/${GO_DIRNAME}/${GO_CONFIG_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_CONFIG_COMPILER_HPP}            DESTINATION  include/${GO_DIRNAME}/${GO_CONFIG_COMPILER_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_CONFIG_PLATFORM_HPP}            DESTINATION  include/${GO_DIRNAME}/${GO_CONFIG_PLATFORM_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_DIAGNOSTICS_HPP}                DESTINATION  include/${GO_DIRNAME}/${GO_DIAGNOSTICS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_DIAGNOSTICS_BENCHMARK_HPP}      DESTINATION  include/${GO_DIRNAME}/${GO_DIAGNOSTICS_BENCHMARK_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_DIAGNOSTICS_LOG_HPP}            DESTINATION  include/${GO_DIRNAME}/${GO_DIAGNOSTICS_LOG_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_DIAGNOSTICS_LOG_DETAIL_HPP}     DESTINATION  include/${GO_DIRNAME}/${GO_DIAGNOSTICS_LOG_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_DIAGNOSTICS_LOG_POLICY_HPP}     DESTINATION  include/${GO_DIRNAME}/${GO_DIAGNOSTICS_LOG_POLICY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_EXCEPTION_HPP}                  DESTINATION  include/${GO_DIRNAME}/${GO_EXCEPTION_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_MVVM_HPP}                       DESTINATION  include/${GO_DIRNAME}/${GO_MVVM_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_MVVM_ITERATOR_HPP}              DESTINATION  include/${GO_DIRNAME}/${GO_MVVM_ITERATOR_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_MVVM_UTILITY_HPP}               DESTINATION  include/${GO_DIRNAME}/${GO_MVVM_UTILITY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_HPP}                   DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_DETAIL_HPP}            DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_NAMELESS_HPP}          DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_NAMELESS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_NAMELESS_DETAIL_HPP}   DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_NAMELESS_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_PROPERTY_POLICY_HPP}            DESTINATION  include/${GO_DIRNAME}/${GO_PROPERTY_POLICY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_SIGNALS_HPP}                    DESTINATION  include/${GO_DIRNAME}/${GO_SIGNALS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_STRING_HPP}                     DESTINATION  include/${GO_DIRNAME}/${GO_STRING_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_STRING_CONVERT_HPP}             DESTINATION  include/${GO_DIRNAME}/${GO_STRING_CONVERT_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_STRING_ENCODING_HPP}            DESTINATION  include/${GO_DIRNAME}/${GO_STRING_ENCODING_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_STRING_TRAITS_HPP}              DESTINATION  include/${GO_DIRNAME}/${GO_STRING_TRAITS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_TYPE_TRAITS_HPP}                DESTINATION  include/${GO_DIRNAME}/${GO_TYPE_TRAITS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_TYPE_TRAITS_DETAIL_HPP}         DESTINATION  include/${GO_DIRNAME}/${GO_TYPE_TRAITS_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_UTILITY_HPP}                    DESTINATION  include/${GO_DIRNAME}/${GO_UTILITY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_UTILITY_CONTAINER_HPP}          DESTINATION  include/${GO_DIRNAME}/${GO_UTILITY_CONTAINER_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_UTILITY_ITERATOR_HPP}           DESTINATION  include/${GO_DIRNAME}/${GO_UTILITY_ITERATOR_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_UTILITY_RANGE_HPP}              DESTINATION  include/${GO_DIRNAME}/${GO_UTILITY_RANGE_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_UTILITY_SMART_PTR_HPP}          DESTINATION  include/${GO_DIRNAME}/${GO_UTILITY_SMART_PTR_DIRNAME})

INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_HPP}                            DESTINATION  include/${GO_BOOST_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_ASYNC_HPP}                      DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_ASYNC_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_CONFIG_HPP}                     DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_CONFIG_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_CONFIG_COMPILER_HPP}            DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_CONFIG_COMPILER_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_CONFIG_PLATFORM_HPP}            DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_CONFIG_PLATFORM_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_HPP}                DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_DIAGNOSTICS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_BENCHMARK_HPP}      DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_DIAGNOSTICS_BENCHMARK_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_LOG_HPP}            DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_DIAGNOSTICS_LOG_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_LOG_DETAIL_HPP}     DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_DIAGNOSTICS_LOG_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_DIAGNOSTICS_LOG_POLICY_HPP}     DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_DIAGNOSTICS_LOG_POLICY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_EXCEPTION_HPP}                  DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_EXCEPTION_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_MVVM_HPP}                       DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_MVVM_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_MVVM_ITERATOR_HPP}              DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_MVVM_ITERATOR_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_MVVM_UTILITY_HPP}               DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_MVVM_UTILITY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_HPP}                   DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_DETAIL_HPP}            DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_HPP}          DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_NAMELESS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_NAMELESS_DETAIL_HPP}   DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_NAMELESS_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_PROPERTY_POLICY_HPP}            DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_PROPERTY_POLICY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_SIGNALS_HPP}                    DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_SIGNALS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_STRING_HPP}                     DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_STRING_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_STRING_CONVERT_HPP}             DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_STRING_CONVERT_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_STRING_ENCODING_HPP}            DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_STRING_ENCODING_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_STRING_TRAITS_HPP}              DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_STRING_TRAITS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_TYPE_TRAITS_HPP}                DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_TYPE_TRAITS_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_TYPE_TRAITS_DETAIL_HPP}         DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_TYPE_TRAITS_DETAIL_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_UTILITY_HPP}                    DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_UTILITY_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_UTILITY_CONTAINER_HPP}          DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_UTILITY_CONTAINER_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_UTILITY_ITERATOR_HPP}           DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_UTILITY_ITERATOR_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_UTILITY_RANGE_HPP}              DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_UTILITY_RANGE_DIRNAME})
INSTALL(FILES ${GO_LIBS_SRC_GO_BOOST_UTILITY_SMART_PTR_HPP}          DESTINATION  include/${GO_BOOST_DIRNAME}/${GO_BOOST_UTILITY_SMART_PTR_DIRNAME})

########################################################
#  CMake Configuration                                 #
########################################################

set(PROJECT_GO_LIBS_CMAKE_NAME GO_libraries_CMake_Configuration)

set(GO_LIBS_CMAKE
    ${ROOT_DIR}/CMakeLists.googletest.txt.in
    ${ROOT_DIR}/CMakeLists.txt
)

set(GO_LIBS_DOCS_CMAKE
    ${ROOT_DIR}/docs/CMakeLists.txt
)

set(GO_LIBS_GO_CMAKE
    ${ROOT_DIR}/go/CMakeLists.txt
)

set(GO_LIBS_GO_BOOST_CMAKE
    ${ROOT_DIR}/go_boost/CMakeLists.txt
)

set(GO_LIBS_LIBS_CMAKE
    ${ROOT_DIR}/libs/CMakeLists.txt
)

set(GO_LIBS_LIBS_BOOST_ASYNC_CMAKE
    ${ROOT_DIR}/libs/boost_async/CMakeLists.txt
)

set(GO_LIBS_LIBS_BOOST_CONFIG_CMAKE
    ${ROOT_DIR}/libs/boost_config/CMakeLists.txt
)

set(GO_LIBS_LIBS_BOOST_DIAGNOSTICS_CMAKE
    ${ROOT_DIR}/libs/boost_diagnostics/CMakeLists.txt
)

set(GO_LIBS_LIBS_BOOST_EXCEPTION_CMAKE
    ${ROOT_DIR}/libs/boost_exception/CMakeLists.txt
)

set(GO_LIBS_LIBS_BOOST_MVVM_CMAKE
    ${ROOT_DIR}/libs/boost_mvvm/CMakeLists.txt
)

set(GO_LIBS_LIBS_BOOST_PROPERTY_CMAKE
    ${ROOT_DIR}/libs/boost_property/CMakeLists.txt
)

set(GO_LIBS_LIBS_BOOST_SIGNALS_CMAKE
    ${ROOT_DIR}/libs/boost_signals/CMakeLists.txt
)

set(GO_LIBS_LIBS_BOOST_TYPE_TRAITS_CMAKE
    ${ROOT_DIR}/libs/boost_type_traits/CMakeLists.txt
)

set(GO_LIBS_LIBS_BOOST_UTILITY_CMAKE
    ${ROOT_DIR}/libs/boost_utility/CMakeLists.txt
)

set(GO_LIBS_LIBS_STD_ASYNC_CMAKE
    ${ROOT_DIR}/libs/std_async/CMakeLists.txt
)

set(GO_LIBS_LIBS_STD_CONFIG_CMAKE
    ${ROOT_DIR}/libs/std_config/CMakeLists.txt
)

set(GO_LIBS_LIBS_STD_DIAGNOSTICS_CMAKE
    ${ROOT_DIR}/libs/std_diagnostics/CMakeLists.txt
)

set(GO_LIBS_LIBS_STD_EXCEPTION_CMAKE
    ${ROOT_DIR}/libs/std_exception/CMakeLists.txt
)

set(GO_LIBS_LIBS_STD_MVVM_CMAKE
    ${ROOT_DIR}/libs/std_mvvm/CMakeLists.txt
)

set(GO_LIBS_LIBS_STD_PROPERTY_CMAKE
    ${ROOT_DIR}/libs/std_property/CMakeLists.txt
)

set(GO_LIBS_LIBS_STD_SIGNALS_CMAKE
    ${ROOT_DIR}/libs/std_signals/CMakeLists.txt
)

set(GO_LIBS_LIBS_STD_TYPE_TRAITS_CMAKE
    ${ROOT_DIR}/libs/std_type_traits/CMakeLists.txt
)

set(GO_LIBS_LIBS_STD_UTILITY_CMAKE
    ${ROOT_DIR}/libs/std_utility/CMakeLists.txt
)

set(GO_LIBS_RND_CMAKE
    ${ROOT_DIR}/rnd/CMakeLists.txt
)

set(GO_LIBS_RND_STD_RND_CMAKE
    ${ROOT_DIR}/rnd/std_rnd/CMakeLists.txt
)

add_library(${PROJECT_GO_LIBS_CMAKE_NAME} STATIC
    ${GO_LIBS_CMAKE}
    ${GO_LIBS_DOCS_CMAKE}
    ${GO_LIBS_GO_CMAKE}
    ${GO_LIBS_GO_BOOST_CMAKE}
    ${GO_LIBS_LIBS_CMAKE}
    ${GO_LIBS_LIBS_BOOST_ASYNC_CMAKE}
    ${GO_LIBS_LIBS_BOOST_CONFIG_CMAKE}
    ${GO_LIBS_LIBS_BOOST_DIAGNOSTICS_CMAKE}
    ${GO_LIBS_LIBS_BOOST_EXCEPTION_CMAKE}
    ${GO_LIBS_LIBS_BOOST_MVVM_CMAKE}
    ${GO_LIBS_LIBS_BOOST_PROPERTY_CMAKE}
    ${GO_LIBS_LIBS_BOOST_SIGNALS_CMAKE}
    ${GO_LIBS_LIBS_BOOST_TYPE_TRAITS_CMAKE}
    ${GO_LIBS_LIBS_BOOST_UTILITY_CMAKE}
    ${GO_LIBS_LIBS_STD_ASYNC_CMAKE}
    ${GO_LIBS_LIBS_STD_CONFIG_CMAKE}
    ${GO_LIBS_LIBS_STD_DIAGNOSTICS_CMAKE}
    ${GO_LIBS_LIBS_STD_EXCEPTION_CMAKE}
    ${GO_LIBS_LIBS_STD_MVVM_CMAKE}
    ${GO_LIBS_LIBS_STD_PROPERTY_CMAKE}
    ${GO_LIBS_LIBS_STD_TYPE_TRAITS_CMAKE}
    ${GO_LIBS_LIBS_STD_SIGNALS_CMAKE}
    ${GO_LIBS_LIBS_STD_UTILITY_CMAKE}
)

set_target_properties(${PROJECT_GO_LIBS_CMAKE_NAME} PROPERTIES LINKER_LANGUAGE CXX FOLDER go_libs/CMakeConfiguration)

source_group(CMake FILES ${GO_LIBS_CMAKE})
source_group(CMake\\docs FILES ${GO_LIBS_DOCS_CMAKE})
source_group(CMake\\go FILES ${GO_LIBS_GO_CMAKE})
source_group(CMake\\go_boost FILES ${GO_LIBS_GO_BOOST_CMAKE})
source_group(CMake\\libs FILES ${GO_LIBS_LIBS_CMAKE})
source_group(CMake\\libs\\boost_async FILES ${GO_LIBS_LIBS_BOOST_ASYNC_CMAKE})
source_group(CMake\\libs\\boost_config FILES ${GO_LIBS_LIBS_BOOST_CONFIG_CMAKE})
source_group(CMake\\libs\\boost_diagnostics FILES ${GO_LIBS_LIBS_BOOST_DIAGNOSTICS_CMAKE})
source_group(CMake\\libs\\boost_exception FILES ${GO_LIBS_LIBS_BOOST_EXCEPTION_CMAKE})
source_group(CMake\\libs\\boost_mvvm FILES ${GO_LIBS_LIBS_BOOST_MVVM_CMAKE})
source_group(CMake\\libs\\boost_property FILES ${GO_LIBS_LIBS_BOOST_PROPERTY_CMAKE})
source_group(CMake\\libs\\boost_signals FILES ${GO_LIBS_LIBS_BOOST_SIGNALS_CMAKE})
source_group(CMake\\libs\\boost_type_traits FILES ${GO_LIBS_LIBS_BOOST_TYPE_TRAITS_CMAKE})
source_group(CMake\\libs\\boost_utility FILES ${GO_LIBS_LIBS_BOOST_UTILITY_CMAKE})
source_group(CMake\\libs\\std_async FILES ${GO_LIBS_LIBS_STD_ASYNC_CMAKE})
source_group(CMake\\libs\\std_config FILES ${GO_LIBS_LIBS_STD_CONFIG_CMAKE})
source_group(CMake\\libs\\std_diagnostics FILES ${GO_LIBS_LIBS_STD_DIAGNOSTICS_CMAKE})
source_group(CMake\\libs\\std_exception FILES ${GO_LIBS_LIBS_STD_EXCEPTION_CMAKE})
source_group(CMake\\libs\\std_mvvm FILES ${GO_LIBS_LIBS_STD_MVVM_CMAKE})
source_group(CMake\\libs\\std_property FILES ${GO_LIBS_LIBS_STD_PROPERTY_CMAKE})
source_group(CMake\\libs\\std_signals FILES ${GO_LIBS_LIBS_STD_SIGNALS_CMAKE})
source_group(CMake\\libs\\std_type_traits FILES ${GO_LIBS_LIBS_STD_TYPE_TRAITS_CMAKE})
source_group(CMake\\libs\\std_utility FILES ${GO_LIBS_LIBS_STD_UTILITY_CMAKE})
