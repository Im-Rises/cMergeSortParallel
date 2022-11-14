set(SRCS_TEST mergeSortSequentialTest.c mergeSortOpenMPTest.c mergeSortPThreadTest.c)

set(HEADERS mergeSortSequential.h mergeSortOpenMP.h mergeSortPThread.h)
set(SRCS mergeSortSequential.c mergeSortOpenMP.c mergeSortPThread.c)

enable_testing()

foreach (test ${SRCS_TEST})
    get_filename_component(testName ${test} NAME_WE)
    add_executable(${testName} ${test} ${HEADERS} ${SRCS})
    add_test(${testName} ${testName})
endforeach ()
