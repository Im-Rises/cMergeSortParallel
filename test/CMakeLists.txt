set(SRCS_TEST mergeSortSequentialTest.c mergeSortOpenMPTest.c mergeSortPThreadTest.c)

set(SRCS)
set(HEADERS)

enable_testing()

foreach (test ${SRCS_TEST})
    get_filename_component(testName ${test} NAME_WE)
    add_executable(${testName} ${test} ${HEADERS} ${SRCS})
    add_test(${testName} ${testName})
endforeach ()
