set(HDRS_COMMON_FUNCTIONS "../commonFunctions/commonFunctions.h")
set(SRCS_COMMON_FUNCTIONS "../commonFunctions/commonFunctions.c")

set(HDRS_MERGE_SORT "../mergeSortSequential/mergeSortSequential.h")
set(SRCS_MERGE_SORT "../mergeSortSequential/mergeSortSequential.c")


# Merge sort sequential test
set(Test_File "mergeSortSequentialTest.c")
get_filename_component(Test_Name ${Test_File} NAME_WE)
add_executable(${Test_Name} ${Test_File} ${HDRS_COMMON_FUNCTIONS} ${SRCS_COMMON_FUNCTIONS} ${HDRS_MERGE_SORT} ${SRCS_MERGE_SORT})
add_test(${Test_Name} ${Test_Name})


# Merge sort OpenMp
set(HDRS_MERGE_SORT_OPENMP "../mergeSortOpenMp/mergeSortParallelOpenMp.h")
set(SRCS_MERGE_SORT_OPENMP "../mergeSortOpenMp/mergeSortParallelOpenMp.c")

set(Test_File "mergeSortOpenMpTest.c")
get_filename_component(Test_Name ${Test_File} NAME_WE)
add_executable(${Test_Name} ${Test_File} ${HDRS_MERGE_SORT_OPENMP} ${SRCS_MERGE_SORT_OPENMP} ${HDRS_COMMON_FUNCTIONS} ${SRCS_COMMON_FUNCTIONS} ${HDRS_MERGE_SORT} ${SRCS_MERGE_SORT})
add_test(${Test_Name} ${Test_Name})

if (UNIX)
    find_package(OpenMP REQUIRED)
    target_link_libraries(${Test_Name} PUBLIC OpenMP::OpenMP_C)
endif()


# Merge sort PThread
if(UNIX)
    set(HDRS_MERGE_SORT_PTHREAD "../mergeSortPThread/mergeSortParallelPThread.h")
    set(SRCS_MERGE_SORT_PTHREAD "../mergeSortPThread/mergeSortParallelPThread.c")

    set(Test_File "mergeSortPThreadTest.c")
    get_filename_component(Test_Name ${Test_File} NAME_WE)
    add_executable(${Test_Name} ${Test_File} ${HDRS_MERGE_SORT_PTHREAD} ${SRCS_MERGE_SORT_PTHREAD} ${HDRS_COMMON_FUNCTIONS} ${SRCS_COMMON_FUNCTIONS} ${HDRS_MERGE_SORT} ${SRCS_MERGE_SORT})
    add_test(${Test_Name} ${Test_Name})
    
    find_package(Threads REQUIRED)
    target_link_libraries(${Test_Name} PRIVATE Threads::Threads)
endif()


# Old CMake
#[[
if (WIN32)
    set(SRCS_TEST "mergeSortSequentialTest.c" "mergeSortOpenMPTest.c")
    set(HEADERS "../mergeSortSequential/mergeSortSequential.h" "../mergeSortOpenMp/mergeSortParallelOpenMp.h")
    set(SRCS "../mergeSortSequential/mergeSortSequential.c" "../mergeSortOpenMp/mergeSortParallelOpenMp.c")
elseif (UNIX)
    set(SRCS_TEST "mergeSortSequentialTest.c" "mergeSortOpenMPTest.c" "mergeSortPThreadTest.c")
    set(HEADERS "../mergeSortSequential/mergeSortSequential.h" "../mergeSortOpenMp/mergeSortParallelOpenMp.h" "../mergeSortPThread/mergeSortPThread.h")
    set(SRCS "../mergeSortSequential/mergeSortSequential.c" "../mergeSortOpenMp/mergeSortParallelOpenMp.c" "../mergeSortPThread/mergeSortPThread.c")
endif ()

set(COMMON_FUNCTIONS_HEADERS ../commonFunctions/commonFunctions.h)
set(COMMON_FUNCTIONS_SRCS ../commonFunctions/commonFunctions.c)

enable_testing()

foreach (test ${SRCS_TEST})
    get_filename_component(testName ${test} NAME_WE)
    add_executable(${testName} ${test} ${HEADERS} ${SRCS} ${COMMON_FUNCTIONS_HEADERS} ${COMMON_FUNCTIONS_SRCS})
    add_test(${testName} ${testName})
endforeach ()
]]
