cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project("mergeSortSequential")
add_subdirectory(${PROJECT_NAME})

project("fileGenerator")
add_subdirectory(${PROJECT_NAME})

project("mergeSortOpenMp")
add_subdirectory(${PROJECT_NAME})

if (UNIX)
    project("mergeSortPThread")
    add_subdirectory(${PROJECT_NAME})
else ()
    message(WARNING "pthread cannot be compiled for other systems than UNIX (skipping build)")
endif ()

enable_testing()
add_subdirectory("test")
