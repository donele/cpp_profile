set(LIBNAME nasdaq_vwap)
set(SOURCES nasdaq_vwap.cpp)
add_library(${LIBNAME} ${SOURCES})
install(TARGETS ${LIBNAME} DESTINATION lib64)
