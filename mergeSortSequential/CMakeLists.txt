set(SRCS mergeSortSequential.c)
set(HDRS mergeSortSequential.h)

add_executable(${PROJECT_NAME} main.c ${SRCS} ${HDRS})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
