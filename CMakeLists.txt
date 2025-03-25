cmake_minimum_required(VERSION 3.30)

project(Pinni
        VERSION 0.1.7
        DESCRIPTION "Pinni library"
        LANGUAGES CXX)

include(CTest)
enable_testing()

# Build options
option(PINNI_STATIC "Build Pinni as static library" OFF)
option(PINNI_BUILD_TESTS "Build the Pinni test suite" OFF)

# Determine library type based on option
if(PINNI_STATIC)
    message("Building static library")
    add_library(Pinni STATIC)
else()
    message("Building shared library")
    add_library(Pinni SHARED)
endif()

# Collect source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

target_sources(Pinni
    PRIVATE
        ${SOURCES}
)

# Add include directories properly
target_include_directories(Pinni PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add dependencies
find_package(spdlog REQUIRED)
target_link_libraries(Pinni PUBLIC
    spdlog::spdlog
)

# Only build tests if enabled
if(PINNI_BUILD_TESTS)
    message("Building tests")
    add_subdirectory(test)
endif()

# ---- Packaging steps begin here ----
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Install the library target and its headers
install(
    TARGETS Pinni
    EXPORT PinniTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)

# Export the targets to a file for use with find_package
install(
    EXPORT PinniTargets
    FILE PinniTargets.cmake
    NAMESPACE Pinni::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Pinni
)

# First, create the config file template if it doesn't exist
file(WRITE cmake/PinniConfig.cmake.in
"@PACKAGE_INIT@

include(CMakeFindDependencyMacro)
find_dependency(spdlog REQUIRED)

include(\"\${CMAKE_CURRENT_LIST_DIR}/PinniTargets.cmake\")
check_required_components(Pinni)
")

# Configure the config file from the template
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/PinniConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/PinniConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Pinni
)

# Generate the version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/PinniConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install the configuration files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/PinniConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/PinniConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Pinni
)
# ---- Packaging steps end here ----
