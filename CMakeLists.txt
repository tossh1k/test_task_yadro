cmake_minimum_required(VERSION 3.2)

project(test_yadro)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)

add_executable(test
	src/time.cpp 
	src/table.cpp 
	src/club.cpp
	src/validating.cpp 
	src/main.cpp
)