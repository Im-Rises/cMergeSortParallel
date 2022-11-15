set(SRCS mergeSortSequential.c)
set(HDRS mergeSortSequential.h)

set(SRCS_COMMON_FUNCTIONS ../commonFunctions/commonFunctions.c)
set(HDRS_COMMON_FUNCTIONS ../commonFunctions/commonFunctions.h)

add_executable(${PROJECT_NAME} main.c ${SRCS} ${HDRS} ${HDRS_COMMON_FUNCTIONS} ${SRCS_COMMON_FUNCTIONS})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
