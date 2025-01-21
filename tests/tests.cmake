
include(CTest)
enable_testing()

set(TEST_SCHEDULER tests/test_scheduler.cpp)
add_executable(${PROJECT_NAME}_test ${TEST_SCHEDULER})

target_link_libraries(${PROJECT_NAME}_test _${PROJECT_NAME} pthread)
target_include_directories(${PROJECT_NAME}_test PRIVATE include)

# Register the test with CTest
add_test(NAME TaskSchedulerBasic COMMAND ${PROJECT_NAME}_test)