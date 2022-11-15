#project("MergeSortSequentialTest")
#
#add_executable(${PROJECT_NAME} mergeSortSequentialTest.c ../mergeSortSequential/mergeSortSequential.h ../mergeSortSequential/mergeSortSequential.c)
#add_test(${PROJECT_NAME} ${PROJECT_NAME})

#add_executable(mergeSortOpenMPTest.c ${test} ${HEADERS} ${SRCS})
#add_test(${testName} ${testName})
#
#add_executable(mergeSortPThreadTest.c ${test} ${HEADERS} ${SRCS})
#add_test(${testName} ${testName})

set(SRCS_TEST "mergeSortSequentialTest.c")

#set(SRCS_TEST mergeSortSequentialTest.c mergeSortOpenMPTest.c mergeSortPThreadTest.c)

set(COMMON_FUNCTIONS_HEADERS ../commonFunctions/commonFunctions.h)
set(COMMON_FUNCTIONS_SRCS ../commonFunctions/commonFunctions.c)

set(HEADERS "../mergeSortSequential/mergeSortSequential.h") #"../mergeSortOpenMp/mergeSortOpenMP.h" "../mergeSortPThread/mergeSortPThread.h")
set(SRCS    "../mergeSortSequential/mergeSortSequential.c") #"../mergeSortOpenMp/mergeSortOpenMP.c" "../mergeSortPThread/mergeSortPThread.c")

enable_testing()

foreach (test ${SRCS_TEST})
    get_filename_component(testName ${test} NAME_WE)
    add_executable(${testName} ${test} ${HEADERS} ${SRCS} ${COMMON_FUNCTIONS_HEADERS} ${COMMON_FUNCTIONS_SRCS})
    add_test(${testName} ${testName})
endforeach ()

