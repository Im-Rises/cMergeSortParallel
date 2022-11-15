if (WIN32)
    set(SRCS_TEST "mergeSortSequentialTest.c" "mergeSortOpenMPTest.c")
    set(HEADERS "../mergeSortSequential/mergeSortSequential.h" "../mergeSortOpenMp/mergeSortParallelOpenMp.h")
    set(SRCS "../mergeSortSequential/mergeSortSequential.c" "../mergeSortOpenMp/mergeSortParallelOpenMp.c")
elseif (UNIX)
    set(SRCS_TEST mergeSortSequentialTest.c mergeSortOpenMPTest.c mergeSortPThreadTest.c)
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

