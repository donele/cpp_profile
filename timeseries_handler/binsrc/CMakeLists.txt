add_executable(run_ts run_ts.cpp)
add_executable(run_test run_test.cpp)
target_link_libraries(run_ts scm_timeseries)
target_link_libraries(run_test scm_timeseries)

