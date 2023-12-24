cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows")
#     set(CMAKE_SYSTEM_VERSION 10.0.18362.0 CACHE STRING INTERNAL FORCE)
#     set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION 10.0.18362.0 CACHE STRING INTERNAL FORCE)
# endif()

# Make timestamps of extracted files from FetchContent the time of extraction
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

option(WITH_TESTS "Build unit tests (requires internet connection)" ON)

# Project variables
set(LOCAL_PROJECT_NAME        "vlark")
set(LOCAL_PROJECT_VERSION     "0.3.0")
set(LOCAL_PROJECT_DESCRIPTION "Simple lex,parse for vhdl code")

# Header files (relative to "include" directory)
file(GLOB_RECURSE HEADERS include/*.h)
# set(HEADERS
#     header.h
# )

# Source files (relative to "src" directory)
file(GLOB_RECURSE SOURCES src/*.cpp)
# set(SOURCES
#     main.cpp
# )

# Compiler definitions
set(DEFINES

)

# Compiler options

set(GCC_WARNINGS
        -Wall
        -Wextra # reasonable and standard
        -Wshadow # warn the user if a variable declaration shadows one from a parent context
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
        # catch hard to track down memory errors
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Wunused # warn on anything being unused
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wpedantic # warn if non-standard C++ is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
        -Wuseless-cast # warn if you perform a cast to the same type
    )

# Project setup
project(${LOCAL_PROJECT_NAME}
        VERSION ${LOCAL_PROJECT_VERSION}
        DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
        LANGUAGES CXX)

add_executable(${LOCAL_PROJECT_NAME})

#list(TRANSFORM HEADERS PREPEND "include/")
#list(TRANSFORM SOURCES PREPEND "src/")

target_include_directories(${LOCAL_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(${LOCAL_PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_compile_definitions(${LOCAL_PROJECT_NAME} PRIVATE ${DEFINES})

target_compile_features(${LOCAL_PROJECT_NAME} PRIVATE cxx_std_20)

if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wno-sign-compare
        -Wno-unused-function
        -Wno-unused-parameter
        -Wno-missing-field-initializers
    )

    else()
      target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE ${GCC_WARNINGS})
    endif()
else()
    target_compile_options(
        ${LOCAL_PROJECT_NAME}
        PRIVATE
            /wd4146
            /wd4244
            /wd4251
            /wd4267
            /WX
            /D_CRT_SECURE_NO_WARNINGS
    )
endif()

if(WITH_TESTS)
    enable_testing()
    add_subdirectory(gtest)
    add_subdirectory(test)
    include(GoogleTest)
endif()

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")
