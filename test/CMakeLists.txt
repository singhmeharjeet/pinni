
enable_testing()
include(CTest)

find_package(GTest REQUIRED)

file(GLOB TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*_test.cpp")


# ---------------------------------------------------------
# create_test_sourcelist (Tests "00_driver.cpp" ${TEST_SOURCES})

# add_executable(unit_tests ${Tests})

# target_link_libraries(unit_tests gtest::gtest Pinni)

# foreach (test ${TEST_SOURCES})
#   get_filename_component (TName ${test} NAME_WE)
#   add_test (NAME ${TName} COMMAND unit_tests ${TName})
# endforeach ()
# ---------------------------------------------------------
set(test_name unit_tests)
add_executable(${test_name} ${TEST_SOURCES})
target_compile_options(${test_name} PUBLIC ${GTEST_CFLAGS})
target_link_libraries(${test_name} gtest::gtest Pinni)
target_include_directories( ${test_name}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_test(${test_name} ${test_name})
    
# ---------------------------------------------------------

# Iterate through each test file and create a corresponding executable
# foreach(test_source ${TEST_SOURCES})
#     get_filename_component(test_name ${test_source} NAME_WE)
    
#     # Create an executable for each test file
#     add_executable(${test_name} ${test_source})

#     # Link the test executable to GoogleTest and your project
#     target_link_libraries(${test_name} gtest::gtest Pinni)
    
#     # Register the test with CTest using the executable name
#     add_test(NAME ${test_name} COMMAND ${test_name})
# endforeach()

# ---------------------------------------------------------
# add_executable(unit_tests ${TEST_SOURCES})
# target_link_libraries(unit_tests gtest::gtest Pinni)
# include(GoogleTest)
# gtest_discover_tests(unit_tests)
# ---------------------------------------------------------