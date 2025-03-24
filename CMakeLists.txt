cmake_minimum_required(VERSION 3.30)

project(Pinni)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create a library instead of an executable
add_library(Pinni STATIC)

# You can specify the library type if needed:
# add_library(Pinni STATIC)  # For a static library
# add_library(Pinni SHARED)  # For a shared/dynamic library

target_include_directories(Pinni PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE SOURCES "src/*.cpp")
target_sources(Pinni PRIVATE ${SOURCES})

# Make the headers available to consuming projects
target_include_directories(Pinni PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

add_subdirectory(test)