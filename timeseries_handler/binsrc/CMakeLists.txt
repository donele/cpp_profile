add_executable(run_ts run_ts.cpp)
add_executable(run_test run_test.cpp)
target_link_libraries(run_ts timeseries_handler)
target_link_libraries(run_test timeseries_handler)

