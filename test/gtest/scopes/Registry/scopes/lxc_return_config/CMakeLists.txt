add_library(returnConfigScope MODULE returnConfigScope.cpp)
target_link_libraries(returnConfigScope ${LIBGTEST})
configure_file(returnConfigScope.ini.in returnConfigScope.ini)
