set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(THREADS_PREFER_PTHREAD_FLAG ON)

if (UNIX)
    add_executable(${PROJECT_NAME} "d2p.c")
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
else ()
    message(WARNING "pthread cannot be compiled for other systems than UNIX (skipping build)")
endif ()
