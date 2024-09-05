set(LIBNAME job_chain)
set(SOURCES chain.cpp)
add_library(${LIBNAME} ${SOURCES})
install(TARGETS ${LIBNAME} DESTINATION lib64)
