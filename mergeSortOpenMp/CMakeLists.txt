## NEW CMAKE
## (https://cliutils.gitlab.io/modern-cmake/chapters/packages/OpenMP.html)

set(SRCS mergeSortParallelOpenMp.c)
set(HDRS mergeSortParallelOpenMp.h)

add_executable(${PROJECT_NAME} main.c ${SRCS} ${HDRS})

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
