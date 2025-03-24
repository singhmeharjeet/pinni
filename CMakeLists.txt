cmake_minimum_required(VERSION 3.30)

project(Pinni
        VERSION 0.1.0
        DESCRIPTION "Pinni library"
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build options
option(PINNI_SHARED "Build Pinni as shared library" OFF)
option(PINNI_BUILD_TESTS "Build the Pinni test suite" OFF)

# Determine library type based on option
if(PINNI_SHARED)
    message("Building shared library")
    add_library(Pinni SHARED)
else()
    message("Building static library")
    add_library(Pinni STATIC)
endif()

# Collect source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
target_sources(Pinni PRIVATE ${SOURCES})

# Make the headers available to consuming projects
target_include_directories(Pinni PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Only build tests if enabled
if(PINNI_BUILD_TESTS)
    message("Building tests")
    add_subdirectory(test)
endif()
