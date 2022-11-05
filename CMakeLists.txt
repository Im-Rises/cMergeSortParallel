cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project("PThreadVersion")
add_subdirectory(${PROJECT_NAME})

project("OpenMpVersion")
add_subdirectory(${PROJECT_NAME})

project("sequentialVersion")
add_subdirectory(${PROJECT_NAME})
