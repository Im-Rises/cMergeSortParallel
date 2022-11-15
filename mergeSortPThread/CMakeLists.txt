set(THREADS_PREFER_PTHREAD_FLAG ON)

set(SRCS mergeSortParallelPThread.c)
set(HDRS mergeSortParallelPThread.h)

add_executable(${PROJECT_NAME} main.c ${SRCS} ${HDRS})


if (UNIX)
    add_executable(${PROJECT_NAME} "d2p.c")
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
else ()
    message(WARNING "pthread cannot be compiled for other systems than UNIX (skipping build)")
endif ()
