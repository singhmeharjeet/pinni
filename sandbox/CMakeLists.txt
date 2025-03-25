cmake_minimum_required(VERSION 3.30)
project(sandbox)

add_executable(sandbox)

target_sources(sandbox PUBLIC
	App.cpp
)

find_package(Pinni CONFIG REQUIRED)

target_link_libraries(sandbox PRIVATE Pinni::Pinni)
