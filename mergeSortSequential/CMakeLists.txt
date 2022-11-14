add_executable(${PROJECT_NAME} "d2s.c")

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
