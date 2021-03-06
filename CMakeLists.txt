cmake_minimum_required(VERSION 2.8.12)
set(PROJECT_NAME "simpleVector")
set(TEST_EXECUTABLE_NAME "tests_${PROJECT_NAME}")
set(TEST2_EXECUTABLE_NAME "tests2_${PROJECT_NAME}")

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
                        -pthread \
                        -fpic \
                        -fvisibility=hidden \
                        -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0 -gdwarf-4 -gmodules")
    set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libstdc++ \
                                -fpic \
                                -std=c++0x \
                                -O3 \
                                -Wl, \
                                -headerpad_max_install_names ")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Setting compiler options for GCC...")
    # using GCC on Linux
    set(CMAKE_C_FLAGS "-fpic \
                      -O3 \
                      -Wall \
                      -pthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} \
                        -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -ggdb -O0")
    set(CMAKE_EXE_LINKER_FLAGS "-std=c++0x \
                               -fpic \
                                -O3")
elseif(MSVC)
    # TODO: (sonictk) Replace later with environment variable
    #include_directories("$ENV{SDL2_PATH}/include")
    set(SDL2_PATH "c:\\Users\\sonictk\\src\\pkg\\sdl\\src\\win\\SDL2-2.0.5")
    include_directories("${SDL2_PATH}\\include")

    message(STATUS "Setting compiler options for MSVC...")
    # using Visual Studio C++
    set(CMAKE_CXX_FLAGS "/MP /GR /GS /W3 /Gy /Zc:wchar_t /Zc:forScope /O2 /Ob1 /fp:precise /GF /nologo /openmp /EHsc")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /Zi /EHsc /Od")
endif()

# Set sources for the project
set(PLUGIN_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/vector.cpp")
set(TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/vector_test.cpp")
set(TEST2_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/vector_test_load_time_dynamic_linking.cpp")

# Add targets to build
add_library(${PROJECT_NAME} SHARED ${PLUGIN_SOURCE_FILES})
add_library(${PROJECT_NAME}Static STATIC ${PLUGIN_SOURCE_FILES})

add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES})
if(MSVC)
    set_target_properties(${TEST_EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS user32.lib gdi32.lib winmm.lib")
endif()

add_executable(${TEST2_EXECUTABLE_NAME} ${TEST2_SOURCE_FILES})
target_link_libraries(${TEST2_EXECUTABLE_NAME} ${PROJECT_NAME})

if(WIN32)
    target_link_libraries(${TEST2_EXECUTABLE_NAME} "${SDL2_PATH}\\lib\\x64\\SDL2.lib")
    add_custom_command(TARGET ${TEST2_EXECUTABLE_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}\\lib\\x64\\SDL2.dll"
        "$<TARGET_FILE_DIR:${TEST2_EXECUTABLE_NAME}>")
endif()

# TODO: (sonictk) Make install target
# install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION ${CMAKE_INSTALL_PREFIX})
# set(TEST_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/tests)
