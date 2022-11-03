cmake_minimum_required (VERSION 3.9)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THREADS_PREFER_PTHREAD_FLAG ON)

project ("PThreadVersion")
add_subdirectory (${PROJECT_NAME})

project ("OpenMpVersion")
add_subdirectory (${PROJECT_NAME})

project ("sequentialVersion")
add_subdirectory (${PROJECT_NAME})
