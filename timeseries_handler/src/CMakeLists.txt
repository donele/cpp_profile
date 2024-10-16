set(LIBNAME timeseries_handler)
set(SOURCES ts.cpp)
add_library(${LIBNAME} ${SOURCES})
install(TARGETS ${LIBNAME} DESTINATION lib64)
