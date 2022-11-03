# CMakeList.txt : CMake project for ParallelProgramming, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ParallelProgramming "d2s.c" )


find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
# TODO: Add tests and install targets if needed.
