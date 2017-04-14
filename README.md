INTRODUCTION
############

When C++11 was released I wanted to learn the new features introduced. I soon realized that it was
unlikely to happen at work. Migrating the company C++ source code, projects, solutions, etc. was
simply to big a task (and it still is, a least when the managers consider pros and cons). I wanted
a reasonably challenging idea for a hobby project and decided to try implement an MFC-based
application using the MVVM (Model–View–ViewModel) architecture pattern. This was the start of the
GO C++ Libraries.

The GO C++ Libraries have two main implementations. The first uses C++11/14/17 and the std
libraries. The second uses C++98/03 and the Boost Libraries. I find it interesting to do both
implementations. Doing the first std-based implementation gives me the opportunety to learn about
new C++11/14/17 features. The second boost-based implementation broaden my knowledge of the Boost
Libraries.

HOW-TO BUILD
############

Boost Libraries
---------------

If you want to use the boost-based implementation of the GO C++ Libraries you need to build the
Boost Libraries. This is a short how-to.

 1. Download the Boost Libraries source code from
    http://www.boost.org/
 2. Extract the boost source code archive
 3. Open a command prompt or terminal and cd to the boost
    source code root directory
 4. Bootstrap, i.e. build the Boost.Build tools, by calling
     > bootstrap.sh (on Linux)
     > bootstrap.bat (on Windows)
 5. Build boost by calling b2 with appropriate options,
    properties, and target, e.g.
     > b2 --build-dir=build --toolset=gcc debug threading=multi link=static --build-type=complete
       address-model=64 -j 3 stage --layout=versioned
       (on Linux, using gcc, debug build, 64 bits, 3 cores)
     > b2.exe --build-dir=build --toolset=msvc-14.1 release threading=multi link=static
       --build-type=complete address-model=32 -j 6 stage --layout=versioned
       (on Windows, using Visual Studio 2017 C++, release build, 32 bits, 6 cores)

For more information see the Boost.Build Tutorial at
http://www.boost.org/build/tutorial.html

GO C++ Libraries
----------------

The GO C++ Libraries use CMake to manage the build process. CMake can be downloaded from
https://cmake.org/download/

CMake configuration:

 * BOOST_INCLUDEDIR = path to boost, e.g. C:\path\to\boost_1_63_0
 * BOOST_LIBRARYDIR = path to boost link libraries, e.g. C:\path\to\boost_1_63_0\stage\lib
 * BOOST_MAJOR_VERSION = 1
 * BOOST_MINOR_VERSION = 63
 * BUILD_BOOST_MFC_EXAMPLES = TRUE|FALSE
 * BUILD_BOOST_TESTS = TRUE|FALSE
 * BUILD_STD_MFC_EXAMPLES = TRUE|FALSE
 * BUILD_STD_TESTS = TRUE|FALSE
 * CMAKE_CONFIGURATION_TYPES = Debug;Release
 * CMAKE_INSTALL_PREFIX = path to install directory
 * USE_SOLUTION_FOLDERS = TRUE|FALSE
 * BUILD_GMOCK = TRUE|FALSE
 * BUILD_GTEST = TRUE|FALSE
 * BUILD_SHARED_LIBS = TRUE|FALSE
 * gmock_build_tests = TRUE|FALSE
 * gtest_build_samples = TRUE|FALSE
 * gtest_build_tests = TRUE|FALSE
 * gtest_disable_pthreads = TRUE|FALSE
 * gtest_force_shared_crt = TRUE|FALSE
 * gtest_hide_internal_symbols = TRUE|FALSE

Use CMake to configure and generate a build solution for your toolset.

The CMake configurations I use:

---------------------------+-----+-----+-----+------+------+------+------+------+------+------
SETTING                    |clang|gcc  |MSYS2|VS2008|VS2008|VS2010|VS2012|VS2013|VS2015|VS2017
                           |     |     |MinGW|ExprEd|ProEd |ExprEd|ExprEd|ExprEd|CommEd|CommEd
                           |     |     |gcc  |      |      |      |      |      |      |
                           |3.9.1|6.3.1|5.3.0|      |      |      |      |      |      |
---------------------------+-----+-----+-----+------+------+------+------+------+------+------
BOOST_MAJOR_VERSION        |1    |1    |1    |1     |1     |1     |1     |1     |1     |1
BOOST_MINOR_VERSION        |63   |63   |63   |63    |63    |63    |63    |63    |63    |63
BUILD_BOOST_MFC_EXAMPLES   |     |     |     |      |X     |      |      |      |X     |X
BUILD_BOOST_TESTS          |X    |X    |X    |X     |X     |X     |X     |X     |X     |X
BUILD_STD_MFC_EXAMPLES     |     |     |     |      |      |      |      |      |X     |X
BUILD_STD_TESTS            |X    |X    |X    |      |      |X     |X     |X     |X     |X
USE_SOLUTION_FOLDERS       |X    |X    |X    |      |      |      |X     |X     |X     |X
BUILD_GMOCK                |X    |X    |X    |X     |X     |X     |X     |X     |X     |X
BUILD_GTEST                |X    |X    |X    |X     |X     |X     |X     |X     |X     |X
BUILD_SHARED_LIBS          |     |     |     |      |      |      |      |      |      |
gmock_build_tests          |     |     |     |      |      |      |      |      |      |
gtest_build_samples        |     |     |     |      |      |      |      |      |      |
gtest_build_tests          |     |     |     |      |      |      |      |      |      |
gtest_disable_pthreads     |     |     |X    |      |      |      |      |      |      |
gtest_force_shared_crt     |     |     |     |X     |X     |X     |X     |X     |X     |X
gtest_hide_internal_symbols|     |     |     |      |      |      |      |      |      |
---------------------------+-----+-----+-----+------+------+------+------+------+------+------

The settings BOOST_INCLUDEDIR, BOOST_LIBRARYDIR, CMAKE_CONFIGURATION_TYPES, and
CMAKE_INSTALL_PREFIX must be set to match your development environment and toolset.

My development environment and toolset details:

 * Manjaro Linux 17.0 Xfce, 64 bits
    - cmake version 3.7.2
    - clang version 3.9.1 (tags/RELEASE_391/final)
    - gcc (GCC) 6.3.1 20170306
    - Code::Blocks 16.01
    - GNU Make 4.2.1
 * Windows 10 Professional, 64 bit
    - cmake version 3.8.0
    - MSYS2 64bit 20160205
    - gcc.exe (Rev5, Built by MSYS2 project) 5.3.0
    - GNU Make 4.1
    - Visual Studio 2008 Express Edition with SP1
    - Visual Studio 2010 Express
    - Visual Studio Express 2012 for Windows Desktop
    - Visual Studio Express 2013 for Windows Desktop
    - Visual Studio Community 2015
    - Visual Studio 2017, Community Edition
 * Windows 7 Enterprise, 64 bit
    - cmake version 3.8.0
    - Visual Studio 2008 Professional Edition

CODESCENE ANALYSIS
##################

[![](https://codescene.io/projects/1082/status.svg) Get more details at **codescene.io**.](https://codescene.io/projects/1082/jobs/latest-successful/results)
