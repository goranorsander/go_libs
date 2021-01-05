# INTRODUCTION

When **C++11** was released I wanted to learn the new features introduced. I soon realized that it was
unlikely to happen at work. Migrating the company C++ source code, projects, solutions, etc. was
simply to big a task. I wanted a reasonably challenging idea for a hobby project and decided to try
implement an **MFC**-based application using the **MVVM** (Model–View–ViewModel) architecture pattern.
This was the start of the **GO C++ Libraries**.

The **GO C++ Libraries** have two main implementations. The first uses **C++11/14/17/2a** and the
**C++ Standard Library**. The second uses **C++98/03** and the **Boost Libraries**. I find it
interesting to do both implementations. Doing the first std-based implementation gives me the
opportunety to learn about new **C++11/14/17/2a** features. The second boost-based implementation
broaden my knowledge of the **Boost Libraries**.

Documentation for **GO C++ Libraries** is found at [goranorsander.github.io/go_libs](https://goranorsander.github.io/go_libs/).

# HOW-TO BUILD

## Boost Libraries

If you want to use the boost-based implementation of the **GO C++ Libraries** you need to build the
**Boost Libraries**. This is a short how-to.

1. Download the **Boost Libraries** source code from [www.boost.org](http://www.boost.org/)
1. Extract the boost source code archive
1. Open a command prompt or terminal and cd to the boost source code root directory
1. Bootstrap, i.e. build the Boost.Build tools, by calling
   * bootstrap.sh _(on Linux)_
   * bootstrap.bat _(on Windows)_
1. Build boost by calling **b2** with appropriate options, properties, and target, e.g.
   * __b2 boost.locale.icu=off --build-dir=build --toolset=clang debug threading=multi link=static --build-type=complete address-model=64 --layout=versioned -j 3 stage__
     _(on Linux, using clang, debug build, 64 bits, 3 cores)_
   * __b2.exe --build-dir=build --toolset=msvc-14.1 release threading=multi link=static --build-type=complete address-model=32 --layout=versioned -j 6 stage__
     _(on Windows, using Visual Studio 2017 C++, release build, 32 bits, 6 cores)_
   * __b2.exe boost.locale.iconv=off --build-dir=build --toolset=gcc debug threading=multi link=static --build-type=complete address-model=64 --layout=versioned -j 6 stage__
     _(on Windows, using MinGW/GCC, debug build, 64 bits, 6 cores)_

For more information see the [Boost.Build Tutorial](http://www.boost.org/build/tutorial.html).

I currently use **Boost Libraries** version **1.75.0** when developing the **GO C++ Libraries**.

## GO C++ Libraries

The **GO C++ Libraries** use CMake to manage the build process. CMake can be downloaded from
[cmake.org/download](https://cmake.org/download/).

CMake configuration:

 * **BOOST_INCLUDEDIR** = path to boost *(e.g. C:\path\to\boost_1_75_0)*
 * **BOOST_LIBRARYDIR** = path to boost link libraries *(e.g. C:\path\to\boost_1_75_0\stage\x64\lib)*
 * **BOOST_MAJOR_VERSION** = 1
 * **BOOST_MINOR_VERSION** = 75
 * **BOOST_PATCH_LEVEL** = 0
 * **BUILD_BOOST_EXAMPLES** = TRUE|FALSE
 * **BUILD_BOOST_MFC_EXAMPLES** = TRUE|FALSE
 * **BUILD_BOOST_RND** = TRUE|FALSE
 * **BUILD_BOOST_TESTS** = TRUE|FALSE
 * **BUILD_STD_EXAMPLES** = TRUE|FALSE
 * **BUILD_STD_MFC_EXAMPLES** = TRUE|FALSE
 * **BUILD_STD_RND** = TRUE|FALSE
 * **BUILD_STD_TESTS** = TRUE|FALSE
 * **CXX_COMPILER_WARNING_LEVEL** = W0|W1|W2|W3|W4|W5 *(W0 disables all warnings, W5 enables all warnings)*
 * **ENABLE_SUPPRESS_WARNINGS** = TRUE|FALSE
 * **CMAKE_CONFIGURATION_TYPES** = Debug;Release
 * **CMAKE_INSTALL_PREFIX** = path to install directory
 * **CMAKE_GNUtoMS** = TRUE|FALSE
 * **USE_SOLUTION_FOLDERS** = TRUE|FALSE
 * **BUILD_GMOCK** = TRUE|FALSE
 * **INSTALL_GTEST** = TRUE|FALSE

Use CMake to configure and generate a build solution for your toolset.

The CMake configurations I use:

**SETTING \ TOOLSET**      |clang 9.0.0|gcc 9.2.0|MSYS2 MinGW gcc 10.2.0|Visual Studio 2019 Community|Visual Studio 2017 Community|Visual Studio 2015 Community|Visual Studio 2013 Express|Visual Studio 2012 Express|Visual Studio 2010 Express|Visual Studio 2008 Professional|Visual Studio 2008 Express
---------------------------|-----------|---------|---------------------|----------------------------|----------------------------|----------------------------|--------------------------|--------------------------|--------------------------|-------------------------------|--------------------------
**BOOST_MAJOR_VERSION** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 
**BOOST_MINOR_VERSION** | 75 | 75 | 75 | 75 | 75 | 75 | 75 | 75 | 75 | 75 | 75 
**BOOST_PATCH_LEVEL** | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
**BUILD_BOOST_EXAMPLES** | X | X | X | X | X | X | X | X | X | X | X 
**BUILD_BOOST_MFC_EXAMPLES** | | | | X | X | X | | | | X | 
**BUILD_BOOST_RND** | X | X | X | X | X | X | X | X | X | X | X 
**BUILD_BOOST_TESTS** | X | X | X | X | X | X | X | X | X | X | X 
**BUILD_STD_EXAMPLES** | X | X | X | X | X | X | X | X | X | X | X 
**BUILD_STD_MFC_EXAMPLES** | | | | X | X | X | | | | | 
**BUILD_STD_RND** | X | X | X | X | X | X | X | X | X | | 
**BUILD_STD_TESTS** | X | X | X | X | X | X | X | X | X | | 
**CXX_COMPILER_WARNING_LEVEL** | W4 | W4 | W4 | W4 | W4 | W4 | W4 | W4 | W4 | W4 | W4 
**ENABLE_SUPPRESS_WARNINGS** | X | X | X | X | X | X | X | X | X | X | X 
**CMAKE_GNUtoMS** | N/A | N/A | | N/A | N/A | N/A | N/A | N/A | N/A | N/A | N/A
**USE_SOLUTION_FOLDERS** | X | X | X | X | X | X | X | X | | | 
**BUILD_GMOCK** | X | X | X | X | X | X | X | X | X | X | X 
**INSTALL_GTEST** | X | X | X | X | X | X | X | X | X | X | X 

The settings BOOST_INCLUDEDIR, BOOST_LIBRARYDIR, CMAKE_CONFIGURATION_TYPES, and
CMAKE_INSTALL_PREFIX must be set to match your development environment and toolset.

My development environment and toolset details:

* Manjaro Linux 20.0.3 Lysia, Xfce, 64 bits
  * cmake version 3.17.3
  * clang version 10.0.0
  * gcc (GCC) 10.1.0
  * git 2.27.0
  * GNU Make 4.3
  * Code::Blocks 17.12
  * ruby 2.7.1p83 (2020-03-31 revision a0c7c23c9c) [x86_64-linux]
  * Visual Studio Code 1.19.2 - with same extensions as in Windows environment
* Windows 10 Professional, 64 bit
  * cmake version 3.19.2
  * MSYS2 64bit 20200720
  * gcc (GCC) 10.2.0
  * git 2.30.0.windows.1
  * GNU Make 4.2.1
  * Code::Blocks 17.12
  * ruby 2.4.4p296 (2018-03-28 revision 63013)
  * TortoiseGit 2.11.0.0
  * Visual Studio 2008 Express Edition with SP1
  * Visual Studio 2010 Express
  * Visual Studio Express 2012 for Windows Desktop
  * Visual Studio Express 2013 for Windows Desktop
  * Visual Studio Community 2015
  * Visual Studio 2017, Community Edition, version 15.9.30
  * Visual Studio 2019, Community Edition, version 16.8.3
  * Visual Studio Code 1.52.1 - with extensions:
    * C/C++ 1.1.3 _(C/C++ IntelliSense, debugging, and code browsing)_
    * CMake 0.0.17 _(CMake language support)_
    * CMake Tools 1.5.3 _(Extended CMake support)_
    * Git Lens 11.1.2 _(Supercharge Visual Studio Code's Git capabilities)_
    * Markdown All in One 3.4.0 _(All you need to write Markdown)_

# GOOGLE TEST

I use the Google Test framework for unit testing. See [github.com/google/googletest](https://github.com/google/googletest) for more information.

# CODESCENE ANALYSIS

[![](https://codescene.io/projects/1082/status.svg) Get more details at **codescene.io**.](https://codescene.io/projects/1082/jobs/latest-successful/results)
