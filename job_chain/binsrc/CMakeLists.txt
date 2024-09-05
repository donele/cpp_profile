add_executable(run_chain run_chain.cpp)
add_executable(run_test run_test.cpp)
target_link_libraries(run_chain job_chain)
target_link_libraries(run_test job_chain)

