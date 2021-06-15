Dear reader,

The source in **googletest-release-1.8.1.zip** is downloaded from
[github.com/google/googletest](https://github.com/google/googletest/archive/refs/tags/release-1.8.1.zip)
and slightly modified to make it work with Visual C++ versions 9.0 - 12.0
(Visual Studio 2008 - 2013). Changes are made in files:

* googletest-release-1.8.1/CMakeLists.txt
* googletest-release-1.8.1/googlemock/CMakeLists.txt
* googletest-release-1.8.1/googlemock/include/gmock/gmock-matchers.h
* googletest-release-1.8.1/googletest/CMakeLists.txt

Compare with .bak file to see my changes.

Kind regards  
Göran Orsander