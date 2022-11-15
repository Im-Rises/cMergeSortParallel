## NEW CMAKE
## (https://cliutils.gitlab.io/modern-cmake/chapters/packages/OpenMP.html)

set(SRCS_COMMON_FUNCTIONS ../commonFunctions/commonFunctions.c)
set(HDRS_COMMON_FUNCTIONS ../commonFunctions/commonFunctions.h)

set(HDRS_MERGE_SORT "../mergeSortSequential/mergeSortSequential.h")
set(SRCS_MERGE_SORT "../mergeSortSequential/mergeSortSequential.c")

set(HDRS mergeSortParallelOpenMp.h)
set(SRCS mergeSortParallelOpenMp.c)

add_executable(${PROJECT_NAME} main.c ${HDRS} ${SRCS} ${HDRS_MERGE_SORT} ${SRCS_MERGE_SORT} ${HDRS_COMMON_FUNCTIONS} ${SRCS_COMMON_FUNCTIONS})

find_package(Threads REQUIRED)
add_library(OpenMP::OpenMP_C IMPORTED INTERFACE)
set_property(TARGET OpenMP::OpenMP_C
        PROPERTY INTERFACE_COMPILE_OPTIONS ${OpenMP_C_FLAGS})
set_property(TARGET OpenMP::OpenMP_C
        PROPERTY INTERFACE_LINK_LIBRARIES ${OpenMP_C_FLAGS} Threads::Threads)


## OLD CMAKE
#add_executable(${PROJECT_NAME} "d2omp.c")
#
#find_package(OpenMP)
#if (OpenMP_C_FOUND)
#    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_C)
#endif ()
