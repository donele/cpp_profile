include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
    )
FetchContent_MakeAvailable(googletest)

target_link_libraries(GTest::GTest INTERFACE gtest_main)

include_directories(include)

add_executable(test_ts test_ts.cpp)
target_link_libraries(test_ts GTest::GTest timeseries_handler)
