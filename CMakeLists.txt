cmake_minimum_required(VERSION 2.8.12)
set(PROJECT_NAME "simpleVector")
# TODO: (sonictk) Make tests
# set(TEST_EXECUTABLE_NAME "tests_${PROJECT_NAME}")

if(APPLE)
    message(STATUS "Setting MacOSX SDK...")
    set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk")
endif(APPLE)

project(${PROJECT_NAME})

# Allow for multithreaded builds on Linux via flag
set(MAKE_MULTITHREADED_BUILD_THREADS 8 CACHE STRING "Number of threads to use when building with GNU Make")
if(MAKE_MULTITHREADED_BUILD_THREADS)
    if(${CMAKE_GENERATOR} MATCHES "Unix Makefiles")
        message(STATUS "Setting number of threads to use for building: ${MAKE_MULTITHREADED_BUILD_THREADS}")
        set(CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} -j${MAKE_MULTITHREADED_BUILD_THREADS}")
    endif()
endif(MAKE_MULTITHREADED_BUILD_THREADS)

# Set compiler flags for each platform
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Setting compiler options for Clang...")
    # Using Clang
    set(CMAKE_CXX_FLAGS "-stdlib=libstdc++ \
                        -std=c++0x \
                        -fno-gnu-keywords \
                        -fpascal-strings \
                        -pthread \
                        -fPIC \
                        -O3 \
                        -dynamic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0 -gdwarf-4 -gmodules")
    set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libstdc++ \
                                -std=c++0x \
                                -fno-gnu-keywords \
                                -fpascal-strings \
                                -O3 \
                                -Wl, \
                                -headerpad_max_install_names \
                                -dynamic")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Setting compiler options for GCC...")
    # using GCC on Linux
    set(CMAKE_C_FLAGS "-DBits64_ \
                      -m64 \
                      -DUNIX \
                      -D_BOOL \
                      -DLINUX \
                      -DFUNCPROTO \
                      -D_GNU_SOURCE \
                      -DLINUX_64 \
                      -fPIC \
                      -fno-strict-aliasing \
                      -DREQUIRE_IOSTREAM \
                      -O3 \
                      -Wall \
                      -Wno-multichar \
                      -Wno-comment \
                      -Wno-sign-compare \
                      -funsigned-char \
                      -pthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} \
                        -Wno-deprecated \
                        -Wno-reorder \
                        -ftemplate-depth-25 \
                        -fno-gnu-keywords")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -ggdb -O0")

elseif(MSVC)
    message(STATUS "Setting compiler options for MSVC...")
    # using Visual Studio C++
    set(CMAKE_CXX_FLAGS "/MP /GR /GS /W3 /Gy /Zc:wchar_t /Zc:forScope /O2 /Ob1 /fp:precise /GF /nologo /openmp /EHsc")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /Zi /EHsc /Od")
endif()

# Set sources for the project
set(PLUGIN_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/vector.cpp")

# Add targets to build
add_library(${PROJECT_NAME} SHARED ${PLUGIN_SOURCE_FILES})
# TODO: (sonictk) make tests
# add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES} ${PLUGIN_SOURCE_FILES})

# TODO: (sonictk) Make install target
# install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION ${CMAKE_INSTALL_PREFIX})
# set(TEST_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/tests)
